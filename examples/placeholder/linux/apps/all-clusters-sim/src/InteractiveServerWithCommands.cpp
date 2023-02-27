/*
 *
 *    Copyright (c) 2023 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "InteractiveServer.h"
#include <zap-generated/SetAttributeCommands.h>

#include <json/json.h>
#include <lib/support/Base64.h>
#include <platform/CHIPDeviceLayer.h>
#include <platform/logging/LogV.h>
#include "commands/common/Commands.h"

using namespace chip::DeviceLayer;

namespace {

Commands gCommands;

} // namespace

void InteractiveServer::Run(const chip::Optional<uint16_t> port)
{
    registerSetAttributeCommands(gCommands);
    InteractiveServer::Run(port);
}

bool InteractiveServer::OnWebSocketMessageReceived(char * msg)
{
    if (strcmp(msg, kWaitForCommissioningCommand) != 0)
    {
       gCommands.RunInteractive(msg);
    }
    return InteractiveServer::OnWebSocketMessageReceived(msg)
}
