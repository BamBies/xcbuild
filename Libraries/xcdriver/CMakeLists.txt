#
# Copyright (c) 2015-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.
#

add_library(xcdriver SHARED
            Sources/Action.cpp
            Sources/Driver.cpp
            Sources/Options.cpp
            Sources/BuildAction.cpp
            Sources/FindAction.cpp
            Sources/HelpAction.cpp
            Sources/LicenseAction.cpp
            Sources/ListAction.cpp
            Sources/ShowBuildSettingsAction.cpp
            Sources/ShowSDKsAction.cpp
            Sources/Usage.cpp
            Sources/UsageAction.cpp
            Sources/VersionAction.cpp
            )

# Copy project LICENSE into build directory as a header.
if ("${PROJECT_SOURCE_DIR}/LICENSE" IS_NEWER_THAN "${CMAKE_CURRENT_BINARY_DIR}/LICENSE.h")
    file(READ "${PROJECT_SOURCE_DIR}/LICENSE" LICENSE_CONTENTS HEX)
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " LICENSE_CONTENTS "${LICENSE_CONTENTS}")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/LICENSE.h" "static char const LICENSE[] = { ${LICENSE_CONTENTS} };\n")
endif ()
target_include_directories(xcdriver PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(xcdriver PUBLIC xcexecution xcformatter pbxbuild xcworkspace xcsdk pbxsetting process util plist builtin)
target_include_directories(xcdriver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Headers")
install(TARGETS xcdriver DESTINATION usr/lib)

add_executable(xcbuild Tools/xcbuild.cpp)
target_link_libraries(xcbuild xcdriver)
install(TARGETS xcbuild DESTINATION usr/bin)

add_custom_command(TARGET xcbuild
                   COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE_NAME:xcbuild> $<TARGET_FILE_DIR:xcbuild>/xcodebuild
                   DEPENDS $<TARGET_FILE:xcbuild>)
install(FILES $<TARGET_FILE_DIR:xcbuild>/xcodebuild DESTINATION usr/bin)

if (BUILD_TESTING)
  ADD_UNIT_GTEST(xcdriver Options Tests/test_Options.cpp)
  ADD_UNIT_GTEST(xcdriver Action Tests/test_Action.cpp)
endif ()

