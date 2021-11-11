
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

using namespace chip::DeviceLayer::Internal;

/////////// CHIP Device scanner implementation //////////

namespace {

class ScannerDelegateImpl : public ChipDeviceScannerDelegate
{
public:
    ScannerDelegateImpl() {}

    void OnDeviceScanned(BluezDevice1 * device, const chip::Ble::ChipBLEDeviceIdentificationInfo & info) override
    {
        ChipLogProgress(chipTool, "Device Scanned");
        ChipLogProgress(chipTool, "Device Address: %s", bluez_device1_get_address(device));
        ChipLogProgress(chipTool, "Descriminator: %d", info.GetDeviceDiscriminator());
        ChipLogProgress(chipTool, "Product ID: %d", info.GetProductId());
        ChipLogProgress(chipTool, "Vendor ID: %d", info.GetVendorId());
    }

    void OnScanComplete() override { ChipLogProgress(chipTool, "Scan is complete"); }
};

} // namespace
