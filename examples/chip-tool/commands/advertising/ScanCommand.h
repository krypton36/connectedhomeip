/*
 *   Copyright (c) 2021 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */
#pragma once

#include "../common/Command.h"
#include <lib/core/CHIPEncoding.h>

// Limits on endpoint values.
#define CHIP_ZCL_ENDPOINT_MIN 0x00
#define CHIP_ZCL_ENDPOINT_MAX 0xF0

class ScanCommand : public Command
{
public:
    ScanCommand() : Command("scan-ble")
    {
        AddArgument("timeOutInMs", 0, UINT32_MAX, &mTimeOutInMs);
        AddArgument("interfaceName", &bleInterfaceName);
        AddArgument("--address", &address, optional=true);
    }

    CHIP_ERROR Run() override;

private:
    uint32_t mTimeOutInMs = 0;
    char * bleInterfaceName;
    char * address;
};
