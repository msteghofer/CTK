PROJECT(CTKDICOMWidgets)

#
# See CTK/CMake/ctkMacroBuildLib.cmake for details
#

SET(KIT_export_directive "CTK_DICOM_WIDGETS_EXPORT")


# Source files
SET(KIT_SRCS
  ctkDICOMAppWidget.cpp
  ctkDICOMAppWidget.h
  ctkDICOMDatasetView.cpp
  ctkDICOMDatasetView.h
  ctkDICOMDirectoryListWidget.cpp
  ctkDICOMDirectoryListWidget.h
  ctkDICOMImage.cpp
  ctkDICOMImage.h
  ctkDICOMImportWidget.cpp
  ctkDICOMImportWidget.h
  ctkDICOMListenerWidget.cpp
  ctkDICOMListenerWidget.h
  ctkDICOMQueryResultsTabWidget.cpp
  ctkDICOMQueryResultsTabWidget.h
  ctkDICOMQueryRetrieveWidget.cpp
  ctkDICOMQueryRetrieveWidget.h
  ctkDICOMQueryWidget.cpp
  ctkDICOMQueryWidget.h
  ctkDICOMServerNodeWidget.cpp
  ctkDICOMServerNodeWidget.h
  ctkDICOMThumbnailGenerator.cpp
  ctkDICOMThumbnailGenerator.h
  ctkDICOMThumbnailListWidget.cpp
  ctkDICOMThumbnailListWidget.h
  )

# Headers that should run through moc
SET(KIT_MOC_SRCS
  ctkDICOMAppWidget.h
  ctkDICOMDatasetView.h
  ctkDICOMDirectoryListWidget.h
  ctkDICOMImage.h
  ctkDICOMImportWidget.h
  ctkDICOMQueryRetrieveWidget.h
  ctkDICOMQueryWidget.h
  ctkDICOMServerNodeWidget.h
  ctkDICOMThumbnailGenerator.h
  ctkDICOMThumbnailListWidget.h
  )

# UI files - includes new widgets
SET(KIT_UI_FORMS
  Resources/UI/ctkDICOMAppWidget.ui
  Resources/UI/ctkDICOMDirectoryListWidget.ui
  Resources/UI/ctkDICOMImportWidget.ui
  Resources/UI/ctkDICOMListenerWidget.ui
  Resources/UI/ctkDICOMQueryRetrieveWidget.ui
  Resources/UI/ctkDICOMQueryWidget.ui
  Resources/UI/ctkDICOMServerNodeWidget.ui
)

# Resources
SET(KIT_resources
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
