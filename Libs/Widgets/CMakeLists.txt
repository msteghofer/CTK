PROJECT(CTKWidgets)

#
# See CTK/CMake/ctkMacroBuildLib.cmake for details
#

SET(KIT_export_directive "CTK_WIDGETS_EXPORT")


# Source files
SET(KIT_SRCS
  ctkActionsWidget.cpp
  ctkActionsWidget.h
  ctkAddRemoveComboBox.cpp
  ctkAddRemoveComboBox.h
  ctkAxesWidget.cpp
  ctkAxesWidget.h
  ctkBasePopupWidget.cpp
  ctkBasePopupWidget.h
  ctkBasePopupWidget_p.h
  ctkButtonGroup.cpp
  ctkButtonGroup.h
  ctkCheckableComboBox.cpp
  ctkCheckableComboBox.h
  ctkCheckableHeaderView.cpp
  ctkCheckableHeaderView.h
  ctkCheckBox.cpp
  ctkCheckBox.h
  ctkCheckBoxPixmaps.cpp
  ctkCheckBoxPixmaps.h
  ctkCheckablePushButton.cpp
  ctkCheckablePushButton.h
  ctkComboBox.cpp
  ctkComboBox.h
  ctkCompleter.cpp
  ctkCompleter.h
  ctkCollapsibleButton.cpp
  ctkCollapsibleButton.h
  ctkCollapsibleGroupBox.cpp
  ctkCollapsibleGroupBox.h
  ctkColorDialog.cpp
  ctkColorDialog.h
  ctkColorPickerButton.cpp
  ctkColorPickerButton.h
  ctkConsole.cpp
  ctkConsole.h
  ctkConsole_p.h
  ctkConfirmExitDialog.cpp
  ctkConfirmExitDialog.h
  ctkCoordinatesWidget.cpp
  ctkCoordinatesWidget.h
  ctkCrosshairLabel.cpp
  ctkCrosshairLabel.h
  ctkDateRangeWidget.cpp
  ctkDateRangeWidget.h
  ctkDirectoryButton.cpp
  ctkDirectoryButton.h
  ctkDoubleRangeSlider.cpp
  ctkDoubleRangeSlider.h
  ctkDoubleSlider.cpp
  ctkDoubleSlider.h
  ctkDynamicSpacer.cpp
  ctkDynamicSpacer.h
  ctkErrorLogStatusMessageHandler.cpp
  ctkErrorLogStatusMessageHandler.h
  ctkErrorLogWidget.cpp
  ctkErrorLogWidget.h
  ctkExpandButton.cpp
  ctkExpandButton.h
  ctkFileDialog.cpp
  ctkFileDialog.h
  ctkFittedTextBrowser.cpp
  ctkFittedTextBrowser.h
  ctkFlowLayout.cpp
  ctkFlowLayout.h
  ctkFontButton.cpp
  ctkFontButton.h
  ctkIconEnginePlugin.cpp
  ctkIconEnginePlugin.h
  ctkLayoutManager.cpp
  ctkLayoutManager.h
  ctkMaterialPropertyPreviewLabel.cpp
  ctkMaterialPropertyPreviewLabel.h
  ctkMaterialPropertyWidget.cpp
  ctkMaterialPropertyWidget.h
  ctkMatrixWidget.cpp
  ctkMatrixWidget.h
  ctkMenuButton.cpp
  ctkMenuButton.h
  ctkMenuComboBox.cpp
  ctkMenuComboBox.h
  ctkMenuComboBox_p.h
  ctkModalityWidget.cpp
  ctkModalityWidget.h
  ctkPathLineEdit.cpp
  ctkPathLineEdit.h
  ctkPixmapIconEngine.cpp
  ctkPixmapIconEngine.h
  ctkPopupWidget.cpp
  ctkPopupWidget.h
  ctkPopupWidget_p.h
  ctkQImageView.cpp
  ctkQImageView.h
  ctkRangeSlider.cpp
  ctkRangeSlider.h
  ctkRangeWidget.cpp
  ctkRangeWidget.h
  ctkScreenshotDialog.cpp
  ctkScreenshotDialog.h
  ctkScreenshotDialog_p.h
  ctkSearchBox.cpp
  ctkSearchBox.h
  ctkSettings.cpp
  ctkSettings.h
  ctkSettingsDialog.cpp
  ctkSettingsDialog.h
  ctkSettingsPanel.cpp
  ctkSettingsPanel.h
  ctkSignalMapper.cpp
  ctkSignalMapper.h
  ctkSimpleLayoutManager.cpp
  ctkSimpleLayoutManager.h
  ctkSliderWidget.cpp
  ctkSliderWidget.h
  ctkTestApplication.cpp
  ctkTestApplication.h
  ctkThumbnailLabel.cpp
  ctkThumbnailLabel.h
  ctkThumbnailListWidget.cpp
  ctkThumbnailListWidget.h
  ctkThumbnailListWidget_p.h
  ctkToolTipTrapper.cpp
  ctkToolTipTrapper.h
  ctkTransferFunctionBarsItem.cpp
  ctkTransferFunctionBarsItem.h
  ctkTransferFunctionControlPointsItem.cpp
  ctkTransferFunctionControlPointsItem.h
  ctkTransferFunctionGradientItem.cpp
  ctkTransferFunctionGradientItem.h
  ctkTransferFunctionItem.cpp
  ctkTransferFunctionItem.h
  ctkTransferFunctionScene.cpp
  ctkTransferFunctionScene.h
  ctkTransferFunctionView.cpp
  ctkTransferFunctionView.h
  ctkTreeComboBox.cpp
  ctkTreeComboBox.h
  ctkWidgetsUtils.cpp
  ctkWidgetsUtils.h
  ctkWorkflowAbstractPagedWidget.cpp
  ctkWorkflowAbstractPagedWidget.h
  ctkWorkflowButtonBoxWidget.cpp
  ctkWorkflowButtonBoxWidget.h
  ctkWorkflowGroupBox.cpp
  ctkWorkflowGroupBox.h
  ctkWorkflowStackedWidget.cpp
  ctkWorkflowStackedWidget.h
  ctkWorkflowTabWidget.cpp
  ctkWorkflowTabWidget.h
  ctkWorkflowWidget.cpp
  ctkWorkflowWidget.h
  ctkWorkflowWidgetStep.cpp
  ctkWorkflowWidgetStep_p.h
  ctkWorkflowWidgetStep.h
  )

# Headers that should run through moc
SET(KIT_MOC_SRCS
  ctkActionsWidget.h
  ctkAxesWidget.h
  ctkAddRemoveComboBox.h
  ctkBasePopupWidget.h
  ctkBasePopupWidget_p.h
  ctkButtonGroup.h
  ctkCheckableComboBox.h
  ctkCheckableHeaderView.h
  ctkCheckablePushButton.h
  ctkCheckBox.h
  ctkCheckBoxPixmaps.h
  ctkComboBox.h
  ctkCompleter.h
  ctkCollapsibleButton.h
  ctkCollapsibleGroupBox.h
  ctkColorDialog.h
  ctkColorPickerButton.h
  ctkConfirmExitDialog.h
  ctkConsole.h
  ctkConsole_p.h
  ctkCoordinatesWidget.h
  ctkCrosshairLabel.h
  ctkDateRangeWidget.h
  ctkDirectoryButton.h
  ctkDoubleRangeSlider.h
  ctkDoubleSlider.h
  ctkDynamicSpacer.h
  ctkErrorLogWidget.h
  ctkErrorLogStatusMessageHandler.h
  ctkExpandButton.h
  ctkFileDialog.h
  ctkFittedTextBrowser.h
  ctkFlowLayout.h
  ctkFontButton.h
  ctkIconEnginePlugin.h
  ctkLayoutManager.h
  ctkMaterialPropertyPreviewLabel.h
  ctkMaterialPropertyWidget.h
  ctkMatrixWidget.h
  ctkMenuButton.h
  ctkMenuComboBox.h
  ctkMenuComboBox_p.h
  ctkModalityWidget.h
  ctkPathLineEdit.h
  ctkPopupWidget.h
  ctkPopupWidget_p.h
  ctkQImageView.h
  ctkRangeSlider.h
  ctkRangeWidget.h
  ctkScreenshotDialog.h
  ctkScreenshotDialog_p.h
  ctkSearchBox.h
  ctkSettings.h
  ctkSettingsDialog.h
  ctkSettingsPanel.h
  ctkSignalMapper.h
  ctkSimpleLayoutManager.h
  ctkSliderWidget.h
  ctkTestApplication.h
  ctkThumbnailLabel.h
  ctkThumbnailListWidget.h
  ctkToolTipTrapper.h
  ctkTransferFunctionBarsItem.h
  ctkTransferFunctionControlPointsItem.h
  ctkTransferFunctionGradientItem.h
  ctkTransferFunctionItem.h
  ctkTransferFunctionScene.h
  ctkTransferFunctionView.h
  ctkTreeComboBox.h
  ctkWorkflowAbstractPagedWidget.h
  ctkWorkflowButtonBoxWidget.h
  ctkWorkflowGroupBox.h
  ctkWorkflowStackedWidget.h
  ctkWorkflowTabWidget.h
  ctkWorkflowWidget.h
  ctkWorkflowWidgetStep.h
  ctkWorkflowWidgetStep_p.h
  )

# UI files
SET(KIT_UI_FORMS
  Resources/UI/ctkAddRemoveComboBox.ui
  Resources/UI/ctkRangeWidget.ui
  Resources/UI/ctkDateRangeWidget.ui
  Resources/UI/ctkErrorLogWidget.ui
  Resources/UI/ctkMaterialPropertyWidget.ui
  Resources/UI/ctkModalityWidget.ui
  Resources/UI/ctkScreenshotDialog.ui
  Resources/UI/ctkSettingsDialog.ui
  Resources/UI/ctkSliderWidget.ui
  Resources/UI/ctkThumbnailLabel.ui
  Resources/UI/ctkThumbnailListWidget.ui
  Resources/UI/ctkWorkflowGroupBox.ui
  )

# Resources
SET(KIT_resources
  Resources/ctkWidgets.qrc
  )

# Target libraries - See CMake/ctkFunctionGetTargetLibraries.cmake
# The following macro will read the target libraries from the file 'target_libraries.cmake'
ctkFunctionGetTargetLibraries(KIT_target_libraries)

ctkMacroBuildLib(
  NAME ${PROJECT_NAME}
  EXPORT_DIRECTIVE ${KIT_export_directive}
  SRCS ${KIT_SRCS}
  MOC_SRCS ${KIT_MOC_SRCS}
  UI_FORMS ${KIT_UI_FORMS}
  TARGET_LIBRARIES ${KIT_target_libraries}
  RESOURCES ${KIT_resources}
  LIBRARY_TYPE ${CTK_LIBRARY_MODE}
  )

IF(CTK_WRAP_PYTHONQT_FULL OR CTK_WRAP_PYTHONQT_LIGHT)
  ctkMacroBuildLibWrapper(
    TARGET ${PROJECT_NAME}
    SRCS ${KIT_SRCS}
    WRAPPER_LIBRARY_TYPE ${CTK_LIBRARY_MODE}
    )
ENDIF()

# Plugins
IF(BUILD_QTDESIGNER_PLUGINS)
  ADD_SUBDIRECTORY(Plugins)
ENDIF()

# Testing
IF(BUILD_TESTING)
  ADD_SUBDIRECTORY(Testing)
ENDIF(BUILD_TESTING)
