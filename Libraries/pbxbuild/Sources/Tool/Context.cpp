/**
 Copyright (c) 2015-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree. An additional grant
 of patent rights can be found in the PATENTS file in the same directory.
 */

#include <pbxbuild/Tool/Context.h>

namespace Tool = pbxbuild::Tool;

Tool::Context::
Context(
    xcsdk::SDK::Target::shared_ptr const &sdk,
    std::vector<xcsdk::SDK::Toolchain::shared_ptr> const &toolchains,
    std::vector<std::string> const &executablePaths,
    std::string const &workingDirectory,
    Tool::SearchPaths const &searchPaths) :
    _sdk             (sdk),
    _toolchains      (toolchains),
    _executablePaths (executablePaths),
    _workingDirectory(workingDirectory),
    _searchPaths     (searchPaths)
{
}

Tool::Context::
~Context()
{
}
