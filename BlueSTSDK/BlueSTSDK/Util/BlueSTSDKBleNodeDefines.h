/*******************************************************************************
 * COPYRIGHT(c) 2015 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef BlueSTSDK_BlueSTSDKBleNodeDefines_h
#define BlueSTSDK_BlueSTSDKBleNodeDefines_h

#import <CoreBluetooth/CoreBluetooth.h>

/**
 *  type used for store the feature mask, each 1 bit means that the node export
 * a specific feature
 */
typedef uint32_t featureMask_t;

/**
 *  Utils function for manage the the feature characteristic
 * @author STMicroelectronics - Central Labs.
 */
@interface BlueSTSDKFeatureCharacteristics : NSObject
/**
 *  extract the feature mask from an uuid value, tell to the user witch feature
 *  are exported by this characteristics
 *
 *  @param uuid characteristics uuid
 *
 *  @return characteristics feature mask
 */
+(featureMask_t)extractFeatureMask:(nonnull CBUUID *)uuid;

/**
 *  tell if a characteristics has a valid uuid for be manage by this sdk
 *
 *  @param c characteristic to test
 *
 *  @return true if the characteristics can be manage by this sdk
 */
+(bool) isFeatureCharacteristics:(nonnull CBCharacteristic*) c;

/**
 *  tell if a characteristics has a valid uudi for be manage by this sdk as a
 *  general pourpose characteristics
 *
 *  @param c characteristic to test
 *
 *  @return true if the characteristics can be manage by this sdk as general purpose characteristics
 */
+(bool) isFeatureGeneralPurposeCharacteristics:(nonnull CBCharacteristic*) c;

+(nullable NSArray<Class>*)getExtendedFeatureInCharacteristics:(nonnull CBCharacteristic*) c;

@end

/**
 *  utility function about the debug service
 */
@interface BlueSTSDKServiceDebug: NSObject
/**
 *  uuid of the debug service
 *
 *  @return uuid of the debug service
 */
+(CBUUID*_Nonnull) serviceUuid;

/**
 *  uuid of the characteristics where the node will notify error message
 *
 *  @return uuid where the node will notify error message
 */
+(CBUUID*_Nonnull) stdErrUuid;

/**
 *  uuid of the characteristics where the node will notify the output message
 * and the user can send message to the node
 *
 *  @return terminal uuid
 */
+(CBUUID*_Nonnull) termUuid;

/**
 *  tell if the characteristics is a valid characteristics for the debug service
 *
 *  @param c characteristic to test
 *
 *  @return true if c has stdErrUuid or temrUuid uuid
 */
+(bool) isDebugCharacteristics:(CBCharacteristic*_Nonnull) c;

@end

/**
 *  utility function for the configuration service
 */
@interface BlueSTSDKServiceConfig: NSObject

/**
 *  uuid of the config service
 *
 *  @return uuid of the service config
 */
+(CBUUID*_Nonnull) serviceUuid;

/**
 *  uuid of the config control characteristic, with this characteristic the user
 *  can modify the register values
 *
 *  @return uuid of the command characteristic
 */
+(CBUUID*_Nonnull) configControlUuid;

/**
 *  uuid of the command characteristic, the user can send command and receive the
 * response from this characteristic
 *
 *  @return uuid of the command characteristic
 */
+(CBUUID*_Nonnull) featureCommandUuid;

/**
 *  tell if the characteristics is a valid characteristics for the config service
 *
 *  @param c characteristic to test
 *
 *  @return true if it is valid
 */
+(bool) isConfigCharacteristics:(CBCharacteristic*_Nonnull) c;

/**
 *  tell if the characteristics is the config control characteristics
 *
 *  @param c characteristic to test
 *
 *  @return true if it is valid
 */
+(bool) isConfigControlCharacteristic:(CBCharacteristic*_Nonnull) c;

/**
 *  tell if the characteristics is the feature command characteristics
 *
 *  @param c characteristic to test
 *
 *  @return true if it is valid
 */
+(bool) isConfigFeatureCommandCharacteristic:(CBCharacteristic*_Nonnull) c;
@end

/**
 *  utility class for manage the sdk service
 */
@interface BlueSTSDKServices : NSObject

/**
 *  class with the utility function for the debug service
 *
 *  @return class with the utility function for the debug service
 */
+(BlueSTSDKServiceDebug*_Nonnull) debugService;

/**
 *  class with the utility function for the configuration service
 *
 *  @return class with the utility function for the configuration service
 */
+(BlueSTSDKServiceConfig*_Nonnull) configService;

@end

/**
 *  For each board type contains a map for of pair ( {@link featureMask_t},
 *  {@link BlueSTSDKFeature } class )
 */
@interface BlueSTSDKBoardFeatureMap : NSObject

/**
 *  return a map of type <boardId, map<{@link featureMask_t}, {@link BlueSTSDKFeature }> >
 *  from this data you can understand what class will be manage a specific characteristics
 *
 *  @return map needed for build a feature class that manage a specific characteristics
 */
+(NSDictionary<NSNumber*,NSDictionary<NSNumber*,Class>*>*_Nonnull)boardFeatureMap;

/**
 * if the board doesn't have a specific device id the map returned by this feature will be used
 *
 * @return the default map used to convert the bit in the advertise mask into feature.
 */
+(NSDictionary<NSNumber*,Class>*_Nonnull)defaultMaskToFeatureMap;
@end


#endif
