/*
 *  ctkEventDispatcher.h
 *  ctkEventBus
 *
 *  Created by Paolo Quadrani on 27/03/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef CTKEVENTDISPATCHER_H
#define CTKEVENTDISPATCHER_H

#include "mafEventDefinitions.h"

namespace ctkEventBus {

/**
 Class name: ctkEventDispatcher
 This allows dispatching events coming from local application to attached observers.
 */
class CTKEVENTBUSSHARED_EXPORT ctkEventDispatcher : public QObject {
    Q_OBJECT

public:
    /// object constructor.
    ctkEventDispatcher();

    /// object destructor.
    virtual ~ctkEventDispatcher();

    /// Add the observer to the events.
    /** Return true if observer has beed added correctly, false otherwise.
    This method check before adding a new observer that it has not already been inserted into the events' Hash with the same id and callback signature.*/
    bool addObserver(const ctkEvent &props);

    /// remove the callback from the observer's hash.
    bool removeObserver(const ctkEvent &props);

    /// remove the callback from the observer's hash.
    bool removeObserver(const QObject *obj, const QString topic, bool qt_disconnect = true);

    /// Remove the signal from the signal's hash.
    bool removeSignal(const QObject *obj, const QString topic = "", bool qt_disconnect = true);

    /// register custom signals use by objects to raise them events.
    /** Return true if signal has beed added correctly, false otherwise.
    This method check before adding a new signal that it has not already been inserted into the events' Hash with the same id and signal signature.
    WARNING: due to Qt limitation you cannot use the same signal in different Topics.*/
    bool registerSignal(const ctkEvent &props);

    /// Remove the signal from the signal's hash.
    bool removeSignal(const ctkEvent &props);

    /// method used to check if the given signal has been already registered for the given id.
    bool isLocalSignalPresent(const QString topic) const;

    /// Emit event corresponding to the given id (present into the event_dictionary) locally to the application.
    virtual void notifyEvent(const ctkEvent &event_dictionary, ctkEventArgumentsList *argList = NULL, mafGenericReturnArgument *returnArg = NULL) const;

    /// clean the signal and callback hashes.
    /** This method is used when the destructor is called. The destructor of the dispatcher is called by the ctkEventBusManager destructor.*/
    void resetHashes();
signals:
    /// Default notification signals for default events.
    void notifyDefaultEvent();

    /// Signal used to notify to observers that the remote communication has been terminated with success.
    void remoteCommunicationDone();

    /// Signal used to notify to observers that the remote communication failed.
    void remoteCommunicationFailed();

protected:
    /// Register MAF global events
    virtual void initializeGlobalEvents();

    /// Interanl method used to remove the given event property.
    bool removeEventItem(const ctkEvent &props);

    /// Return the signal item property associated to the given ID.
    ctkEventItemListType signalItemProperty(const QString topic) const;

private:
    /// method used to check if the given object has been already registered for the given id and signature.
    bool isSignaturePresent(const ctkEvent &props) const;

    /// disconnection signal/observer.
    /** This function disconnects the signal and all the observers. */
    bool disconnectSignal(const ctkEvent &props);

    /// This function disconnects observer from signal.
    bool disconnectCallback(const ctkEvent &props);

    /// Remove the given object from the has passed as argument
    bool removeFromHash(ctkEventsHashType *hash, const QObject *obj, const QString topic, bool qt_disconnect = true);

    ctkEventsHashType m_CallbacksHash; ///< Callbacks' hash for receiving events like updates or refreshes.
    ctkEventsHashType m_SignalsHash; ///< Signals' hash for sending events.
};

/////////////////////////////////////////////////////////////
// Inline methods
/////////////////////////////////////////////////////////////

inline ctkEventItemListType ctkEventDispatcher::signalItemProperty(const QString topic) const {
    return m_SignalsHash.values(topic);
}

} // namespace ctkEventBus

#endif // CTKEVENTDISPATCHER_H