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
#include <lib/support/CHIPMem.h>
#include <platform/CHIPDeviceLayer.h>
#include <platform/Linux/bluez/AdapterIterator.h>
#include <platform/Linux/bluez/MainLoop.h>
#include <platform/internal/BLEManager.h>

#include "ScanCommand.h"
#include "ScannerDelegate.h"

CHIP_ERROR ScanCommand::Run()
{
    ChipLogProgress(chipTool, "Scanning BLE Advertising data.");
    std::unique_ptr<ScannerDelegateImpl> delegate = std::make_unique<ScannerDelegateImpl>();

    AdapterIterator * adapterIterator = new AdapterIterator();
    chip::DeviceLayer::SystemLayer().Init();

    while (adapterIterator->Next())
    {
        if (strcmp(adapterIterator->GetName(), bleInterfaceName) == 0)
        {
            ChipLogProgress(chipTool, "Adapter Name: %s", adapterIterator->GetName());
            ChipLogProgress(chipTool, "Adapter Address: %s", adapterIterator->GetAddress());
            std::unique_ptr<ChipDeviceScanner> scanner =
                ChipDeviceScanner::Create(static_cast<BluezAdapter1 *>(adapterIterator->GetAdapter()), delegate.get());
            if (!scanner)
            {
                ChipLogError(chipTool, "Failed to create a BLE device scanner");
                return CHIP_ERROR_CONNECTION_ABORTED;
            }

            ReturnErrorOnFailure(scanner->StartScan(chip::System::Clock::Milliseconds32(mTimeOutInMs + 1)));
            sleep(mTimeOutInMs / 1000); // Wait while command is running.
            ReturnErrorOnFailure(scanner->StopScan());

            return CHIP_NO_ERROR;
        }
    }
    return CHIP_ERROR_CONNECTION_ABORTED;
}
