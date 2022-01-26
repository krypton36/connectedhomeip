/*
 *   Copyright (c) 2022 Project CHIP Authors
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

#import <CHIP/CHIP.h>
#import <Foundation/Foundation.h>

const uint16_t kPairingTimeoutInSeconds = 10;
const uint16_t kAddressResolveTimeoutInSeconds = 10;
const uint16_t kCASESetupTimeoutInSeconds = 30;
const uint16_t kTimeoutInSeconds = 3;
const uint64_t kDeviceId = 1;
const uint16_t kDiscriminator = 3840;
const uint32_t kSetupPINCode = 20202021;
const uint16_t kRemotePort = 5542;
const uint16_t kLocalPort = 5541;
NSString * kAddress = @"192.168.1.115";

static CHIPDevice * mConnectedDevice;

@interface CHIPToolPairingDelegate : NSObject <CHIPDevicePairingDelegate>
@end

@implementation CHIPToolPairingDelegate

- (void)onPairingComplete:(NSError *)error
{
    NSLog(@"Pairing Complete");
}

- (void)onCommissioningComplete:(NSError *)error
{
    NSLog(@"onCommissioningComplete");
}

- (void)onAddressUpdated:(NSError *)error
{
    NSLog(@"onAddressUpdated");
}
@end

int main(int argc, const char * argv[]) {
    CHIPDeviceController * controller = [CHIPDeviceController sharedController];
    CHIPToolPairingDelegate * pairing = [[CHIPToolPairingDelegate alloc] init];
    dispatch_queue_t callbackQueue = dispatch_queue_create("com.chip.pairing", DISPATCH_QUEUE_SERIAL);

    [controller setListenPort:kLocalPort];
    [controller setPairingDelegate:pairing queue:callbackQueue];

    BOOL started = [controller startup:nil vendorId:0 nocSigner:nil];
    if (!started){
        NSLog(@"Unable to start controller");
    }
    NSError * error;
//    [controller pairDevice:kDeviceId
//                   address:kAddress
//                      port:kRemotePort
//             discriminator:kDiscriminator
//              setupPINCode:kSetupPINCode
//                     error:&error];
    [controller pairDevice:kDeviceId
             discriminator:kDiscriminator
              setupPINCode:kSetupPINCode
                     error:&error];
    sleep(30);
    BOOL stopped = [controller shutdown];
    if (!stopped){
        NSLog(@"Unable to stop controller");
    }
    return EXIT_SUCCESS;
}
