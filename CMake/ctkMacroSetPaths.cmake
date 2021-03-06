###########################################################################
#
#  Library:   CTK
#
#  Copyright (c) Kitware Inc.
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
###########################################################################

#!
#! Depending on the platform, either PATH, LD_LIBRARY_PATH or DYLD_LIBRARY_PATH
#! will be updated using the paths specified using PATH_LIST
#!
#! \ingroup CMakeUtilities
MACRO(ctkMacroSetPaths PATH_LIST)
  FOREACH(p ${PATH_LIST})
    IF(WIN32)
      SET(ENV{PATH} "${p};$ENV{PATH}")
    ELSEIF(APPLE)
      SET(ENV{DYLD_LIBRARY_PATH} "${p}:$ENV{DYLD_LIBRARY_PATH}")
    ELSE()
      SET(ENV{LD_LIBRARY_PATH} "${p}:$ENV{LD_LIBRARY_PATH}")
    ENDIF()
  ENDFOREACH()
ENDMACRO()
