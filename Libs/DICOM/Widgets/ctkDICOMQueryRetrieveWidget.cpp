/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

//Qt includes
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QProgressDialog>
#include <QSettings>
#include <QTreeView>
#include <QTabBar>

/// CTK includes
#include <ctkCheckableHeaderView.h>
#include <ctkCheckableModelHelper.h>
#include <ctkLogger.h>

// ctkDICOMCore includes
#include "ctkDICOMDatabase.h"
#include "ctkDICOMModel.h"
#include "ctkDICOMQuery.h"
#include "ctkDICOMRetrieve.h"

// ctkDICOMWidgets includes
#include "ctkDICOMQueryRetrieveWidget.h"
#include "ctkDICOMQueryResultsTabWidget.h"
#include "ui_ctkDICOMQueryRetrieveWidget.h"

static ctkLogger logger("org.commontk.DICOM.Widgets.ctkDICOMQueryRetrieveWidget");

//----------------------------------------------------------------------------
class ctkDICOMQueryRetrieveWidgetPrivate: public Ui_ctkDICOMQueryRetrieveWidget
{
  Q_DECLARE_PUBLIC( ctkDICOMQueryRetrieveWidget );

protected:
  ctkDICOMQueryRetrieveWidget* const q_ptr;
  
public:
  ctkDICOMQueryRetrieveWidgetPrivate(ctkDICOMQueryRetrieveWidget& obj);
  ~ctkDICOMQueryRetrieveWidgetPrivate();
  void init();

  QMap<QString, ctkDICOMQuery*>     QueriesByServer;
  QMap<QString, ctkDICOMQuery*>     QueriesByStudyUID;
  QMap<QString, ctkDICOMRetrieve*>  RetrievalsByStudyUID;
  ctkDICOMDatabase                  QueryResultDatabase;
  QSharedPointer<ctkDICOMDatabase>  RetrieveDatabase;
  ctkDICOMModel                     Model;
  
  QProgressDialog*                  ProgressDialog;
  QString                           CurrentServer;
};

//----------------------------------------------------------------------------
// ctkDICOMQueryRetrieveWidgetPrivate methods

//----------------------------------------------------------------------------
ctkDICOMQueryRetrieveWidgetPrivate::ctkDICOMQueryRetrieveWidgetPrivate(
  ctkDICOMQueryRetrieveWidget& obj)
  : q_ptr(&obj)
{
  this->ProgressDialog = 0;
}

//----------------------------------------------------------------------------
ctkDICOMQueryRetrieveWidgetPrivate::~ctkDICOMQueryRetrieveWidgetPrivate()
{
  foreach(ctkDICOMQuery* query, this->QueriesByServer.values())
    {
    delete query;
    }
  foreach(ctkDICOMRetrieve* retrieval, this->RetrievalsByStudyUID.values())
    {
    delete retrieval;
    }
}

//----------------------------------------------------------------------------
void ctkDICOMQueryRetrieveWidgetPrivate::init()
{
  Q_Q(ctkDICOMQueryRetrieveWidget);
  this->setupUi(q);

  QObject::connect(this->QueryButton, SIGNAL(clicked()), q, SLOT(query()));
  QObject::connect(this->RetrieveButton, SIGNAL(clicked()), q, SLOT(retrieve()));
  QObject::connect(this->CancelButton, SIGNAL(clicked()), q, SLOT(cancel()));

  this->results->setModel(&this->Model);
  // TODO: use the checkable headerview when it becomes possible
  // to select individual studies.  For now, assume that the 
  // user will use the query terms to narrow down the transfer
  /*
  this->Model.setHeaderData(0, Qt::Horizontal, Qt::Unchecked, Qt::CheckStateRole);
  QHeaderView* previousHeaderView = this->results->header();
  ctkCheckableHeaderView* headerView =
    new ctkCheckableHeaderView(Qt::Horizontal, this->results);
  headerView->setClickable(previousHeaderView->isClickable());
  headerView->setMovable(previousHeaderView->isMovable());
  headerView->setHighlightSections(previousHeaderView->highlightSections());
  headerView->checkableModelHelper()->setPropagateDepth(-1);
  this->results->setHeader(headerView);
  // headerView is hidden because it was created with a visisble parent widget 
  headerView->setHidden(false);
  */
}

//----------------------------------------------------------------------------
// ctkDICOMQueryRetrieveWidget methods

//----------------------------------------------------------------------------
ctkDICOMQueryRetrieveWidget::ctkDICOMQueryRetrieveWidget(QWidget* parentWidget)
  : Superclass(parentWidget) 
  , d_ptr(new ctkDICOMQueryRetrieveWidgetPrivate(*this))
{
  Q_D(ctkDICOMQueryRetrieveWidget);
  d->init();
}

//----------------------------------------------------------------------------
ctkDICOMQueryRetrieveWidget::~ctkDICOMQueryRetrieveWidget()
{
}

//----------------------------------------------------------------------------
void ctkDICOMQueryRetrieveWidget::setRetrieveDatabase(QSharedPointer<ctkDICOMDatabase> dicomDatabase)
{
  Q_D(ctkDICOMQueryRetrieveWidget);

  d->RetrieveDatabase = dicomDatabase;
}

//----------------------------------------------------------------------------
QSharedPointer<ctkDICOMDatabase> ctkDICOMQueryRetrieveWidget::retrieveDatabase()const
{
  Q_D(const ctkDICOMQueryRetrieveWidget);
  return d->RetrieveDatabase;
}

//----------------------------------------------------------------------------
void ctkDICOMQueryRetrieveWidget::query()
{
  Q_D(ctkDICOMQueryRetrieveWidget);

  d->RetrieveButton->setEnabled(false);
  
  // create a database in memory to hold query results
  try { d->QueryResultDatabase.openDatabase( ":memory:", "QUERY-DB" ); }
  catch (std::exception e)
  {
    logger.error ( "Database error: " + d->QueryResultDatabase.lastError() );
    d->QueryResultDatabase.closeDatabase();
    return;
  }

  d->QueriesByStudyUID.clear();

  // for each of the selected server nodes, send the query
  QProgressDialog progress("Query DICOM servers", "Cancel", 0, 100, this,
                           Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
  // We don't want the progress dialog to resize itself, so we bypass the label
  // by creating our own
  QLabel* progressLabel = new QLabel(tr("Initialization..."));
  progress.setLabel(progressLabel);
  d->ProgressDialog = &progress;
  progress.setWindowModality(Qt::WindowModal);
  progress.setMinimumDuration(0);
  progress.setValue(0);
  foreach (d->CurrentServer, d->ServerNodeWidget->selectedServerNodes())
    {
    if (progress.wasCanceled())
      {
      break;
      }
    QMap<QString, QVariant> parameters =
      d->ServerNodeWidget->serverNodeParameters(d->CurrentServer);
    // if we are here it's because the server node was checked
    Q_ASSERT(parameters["CheckState"] == static_cast<int>(Qt::Checked) );
    // create a query for the current server
    ctkDICOMQuery* query = new ctkDICOMQuery;
    query->setCallingAETitle(d->ServerNodeWidget->callingAETitle());
    query->setCalledAETitle(parameters["AETitle"].toString());
    query->setHost(parameters["Address"].toString());
    query->setPort(parameters["Port"].toInt());

    // populate the query with the current search options
    query->setFilters( d->QueryWidget->parameters() );

    try
      {
      connect(query, SIGNAL(progress(QString)),
              //&progress, SLOT(setLabelText(QString)));
              progressLabel, SLOT(setText(QString)));
      // for some reasons, setLabelText() doesn't refresh the dialog.
      connect(query, SIGNAL(progress(int)),
              this, SLOT(onQueryProgressChanged(int)));
      // run the query against the selected server and put results in database
      query->query ( d->QueryResultDatabase );
      disconnect(query, SIGNAL(progress(QString)),
                 //&progress, SLOT(setLabelText(QString)));
                 progressLabel, SLOT(setText(QString)));
      disconnect(query, SIGNAL(progress(int)),
                 this, SLOT(onQueryProgressChanged(int)));
      }
    catch (std::exception e)
      {
      logger.error ( "Query error: " + parameters["Name"].toString() );
      progress.setLabelText("Query error: " + parameters["Name"].toString());
      delete query;
      }

    d->QueriesByServer[d->CurrentServer] = query;
    
    foreach( QString studyUID, query->studyInstanceUIDQueried() )
      {
      d->QueriesByStudyUID[studyUID] = query;
      }
    }
  
  // checkable headers - allow user to select the patient/studies to retrieve
  d->Model.setDatabase(d->QueryResultDatabase.database());

  d->RetrieveButton->setEnabled(d->Model.rowCount());
  progress.setValue(progress.maximum());
  d->ProgressDialog = 0;
}

//----------------------------------------------------------------------------
void ctkDICOMQueryRetrieveWidget::retrieve()
{
  Q_D(ctkDICOMQueryRetrieveWidget);

  if (!d->RetrieveButton->isEnabledTo(this))
    {
    return;
    }

  // for each of the selected server nodes, send the query
  QProgressDialog progress("Retrieve from DICOM servers", "Cancel", 0, 100, this,
                           Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
  // We don't want the progress dialog to resize itself, so we bypass the label
  // by creating our own
  QLabel* progressLabel = new QLabel(tr("Initialization..."));
  progress.setLabel(progressLabel);
  d->ProgressDialog = &progress;
  progress.setWindowModality(Qt::WindowModal);
  progress.setMinimumDuration(0);
  progress.setValue(0);

  QMap<QString,QVariant> serverParameters = d->ServerNodeWidget->parameters();
  ctkDICOMRetrieve *retrieve = new ctkDICOMRetrieve;
  // only start new association if connection parameters change
  retrieve->setKeepAssociationOpen(true);
  // pull from GUI
  retrieve->setMoveDestinationAETitle( serverParameters["StorageAETitle"].toString() );
  int step = 0;
  progress.setMaximum(d->QueriesByStudyUID.keys().size());
  progress.open();
  progress.setValue(1);
  foreach( QString studyUID, d->QueriesByStudyUID.keys() )
    {
    if (progress.wasCanceled())
      {
      break;
      }

    progressLabel->setText(QString(tr("Retrieving:\n%1")).arg(studyUID));
    this->updateRetrieveProgress( step );
    ++step;

    // Get information which server we want to get the study from and prepare request accordingly
    ctkDICOMQuery *query = d->QueriesByStudyUID[studyUID];
    retrieve->setRetrieveDatabase( d->RetrieveDatabase );
    retrieve->setCallingAETitle( query->callingAETitle() );
    retrieve->setCalledAETitle( query->calledAETitle() );
    retrieve->setCalledPort( query->port() );
    retrieve->setHost( query->host() );
    // TODO: check the model item to see if it is checked
    // for now, assume all studies queried and shown to the user will be retrieved
    logger.debug("About to retrieve " + studyUID + " from " + d->QueriesByStudyUID[studyUID]->host());
    logger.info ( "Starting to retrieve" );

    try
      {
      // perform the retrieve
      retrieve->retrieveStudy ( studyUID );
      }
    catch (std::exception e)
      {
      logger.error ( "Retrieve failed" );
      if ( QMessageBox::question ( this, 
            tr("Query Retrieve"), tr("Retrieve failed.  Keep trying?"),
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
        continue;
        }
      else
        {
        break;
        }
      }
    // Store retrieve structure for later use.
    // Comment MO: I do not think that makes much sense; you store per study one fat
    // structure including an SCU. Also, I switched the code to re-use the retrieve
    // SCU in order to not start/stop the association for every study. In general,
    // it would make most sense in my opinion to have one SCU for each server you
    // like to retrieve from. There is no good reason to have one for each study.
    // d->RetrievalsByStudyUID[studyUID] = retrieve;
    logger.info ( "Retrieve success" );
    }
  progressLabel->setText(tr("Retrieving Finished"));
  this->updateRetrieveProgress(progress.maximum());

  delete retrieve;
  d->ProgressDialog = 0;
  QMessageBox::information ( this, tr("Query Retrieve"), tr("Retrieve Process Finished.") );
  emit studiesRetrieved(d->RetrievalsByStudyUID.keys());
}

//----------------------------------------------------------------------------
void ctkDICOMQueryRetrieveWidget::cancel()
{
  emit studiesRetrieved(QStringList());
  emit canceled();
}

//----------------------------------------------------------------------------
void ctkDICOMQueryRetrieveWidget::onQueryProgressChanged(int value)
{
  Q_D(ctkDICOMQueryRetrieveWidget);
  if (d->ProgressDialog == 0)
    {
    return;
    }
  QStringList servers = d->ServerNodeWidget->selectedServerNodes();
  int serverIndex = servers.indexOf(d->CurrentServer);
  if (serverIndex < 0)
    {
    return;
    }
  if (d->ProgressDialog->width() != 500)
    {
    QPoint pp = this->mapToGlobal(QPoint(0,0));
    pp = QPoint(pp.x() + (this->width() - d->ProgressDialog->width()) / 2,
                pp.y() + (this->height() - d->ProgressDialog->height())/ 2);
    d->ProgressDialog->move(pp - QPoint((500 - d->ProgressDialog->width())/2, 0));
    d->ProgressDialog->resize(500, d->ProgressDialog->height());
    }
  float serverProgress = 100. / servers.size();
  d->ProgressDialog->setValue( (serverIndex + (value / 101.)) * serverProgress);
}

//----------------------------------------------------------------------------
void ctkDICOMQueryRetrieveWidget::updateRetrieveProgress(int value)
{
  Q_D(ctkDICOMQueryRetrieveWidget);
  if (d->ProgressDialog == 0)
    {
    return;
    }
  if (d->ProgressDialog->width() != 500)
    {
    QPoint pp = this->mapToGlobal(QPoint(0,0));
    pp = QPoint(pp.x() + (this->width() - d->ProgressDialog->width()) / 2,
                pp.y() + (this->height() - d->ProgressDialog->height())/ 2);
    d->ProgressDialog->move(pp - QPoint((500 - d->ProgressDialog->width())/2, 0));
    d->ProgressDialog->resize(500, d->ProgressDialog->height());
    }
  d->ProgressDialog->setValue( value );
  logger.error(QString("setting value to %1").arg(value) );
}
