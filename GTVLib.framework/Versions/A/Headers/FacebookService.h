//
//  FacebookService.h
//  GTVCocoaTouchFramework
//
//  Created by Macbook on 3/15/19.
//  Copyright © 2019 Андрей Недов. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class FBSDKCoreKit;
@class FBSDKLoginKit;

NS_ASSUME_NONNULL_BEGIN
typedef void (^FBShareCallback)(NSDictionary<NSString *,id> * _Nullable results, NSError * _Nullable error, BOOL cancel);

@interface FacebookService : NSObject
+ (FacebookService *)shareService;

- (void)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;

/// Share Facebook
/// @param link url
/// @param fromViewController !
/// @param callback FBShareCallback
- (void)shareLinkContent:(NSString*)link fromViewController:(UIViewController*)fromViewController callback:(FBShareCallback)callback;
@end

NS_ASSUME_NONNULL_END
