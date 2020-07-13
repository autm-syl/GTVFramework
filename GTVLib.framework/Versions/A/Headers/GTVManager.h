//
//  GTVManager.h
//  GTVCocoaTouchFramework
//
//  Created by Macbook on 2/26/19.
//  Copyright © 2019 Андрей Недов. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FirebaseService.h"

NS_ASSUME_NONNULL_BEGIN
typedef enum {
    GTVPurchasing = 0,
    GTVPurchased, // Purchased with Apple and verify server error
    GTVRestored,
    GTVFailed,
    GTVRequestError, // Request Product ID error
    GTVVerified // Purchased with Apple and verify server success
}GTVIAPStatus;


typedef void (^GTVIAPCallback)(GTVIAPStatus status, NSString *message);
typedef void (^GTVILogoutCallback)(BOOL isSuccess, NSString * _Nullable message);
typedef void (^GTVILoginCallback)(BOOL isSuccess, NSString * _Nullable message, NSString * _Nullable uuid, NSString * _Nullable username);
typedef void (^FBShareCallback)(NSDictionary<NSString *,id> * _Nullable results, NSError * _Nullable error, BOOL cancel);

typedef void (^RefreshTokenCallback)(BOOL isSuccess, NSString * _Nullable message);

@interface GTVManager : NSObject


/// URL_PAY
@property (nonatomic, copy) NSString *URL_PAY;

/// URL_ID
@property (nonatomic, copy) NSString *URL_ID;

/// URL_API
@property (nonatomic, copy) NSString *URL_API;

#pragma mark - Implement

/// Implement GTV library
/// @param application is an UIApplication variable
/// @param launchOptions didFinishLaunchingWithOptions
/// @param useProductServer  set NO if build dev version. dev version use dev server. Set YES for product build
- (void)ImplementWith:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions useProductServer:(BOOL)useProductServer;
+ (GTVManager *)sharedManager;


#pragma mark - Payment

/// Call payment from GTV gate.
/// @param orderID !
/// @param serverID !
/// @param serverName !
/// @param roleID !
/// @param roleName !
/// @param userID !
/// @param channel !
/// @param levels !
/// @param callback !
- (void)showPaymentWithOrderID:(NSString *)orderID serverID:(NSString *)serverID serverName:(NSString *)serverName roleID:(NSString *)roleID roleName:(NSString *)roleName userID:(NSString*)userID channel:(NSString*)channel levels:(NSString *)levels callback:(GTVIAPCallback)callback;


/// Call in app purchase with a exist products
/// @param serverID !
/// @param roleID !
/// @param platform !
/// @param levels !
/// @param productID !
/// @param gameOrderID !
/// @param partner !
/// @param callback !
- (void)startIAPPaymentServerID:(NSString *)serverID roleID:(NSString *)roleID platform:(NSString *)platform levels:(NSString *)levels productID:(NSString*)productID gameOrderID:(NSString*)gameOrderID partner:(NSString*)partner callback:(GTVIAPCallback)callback;
- (BOOL)isIAP:(int)level;


/// help tracking by facebook and firebase
/// @param application app
/// @param url url
/// @param options optioon
- (BOOL)gtvApplication:(UIApplication *)application openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;

- (void)handleNotificationsWithDeviceToken:(NSData *)deviceToken;

/// Share Facebook
/// @param link url
/// @param fromViewController !
/// @param callback FBShareCallback
- (void)shareLinkContent:(NSString*)link fromViewController:(UIViewController*)fromViewController callback:(FBShareCallback)callback;

#pragma mark - Account

/// Call login by GTV
/// @param callback call back help you know it done, maybe success or error
- (void)showLogin:(GTVILoginCallback)callback;

/// Call logout by GTV
/// @param callback call back help you know it done. often successful
- (void)logout: (GTVILogoutCallback)callback;

/// UserHash
- (nullable NSString *)getUserHash __attribute__((deprecated("function has been deprecated from version 2.0.2, please use UUID and token instead")));

/// uuid gen by GTV. You must to login first, if not this uuid maybe nil.
- (nullable NSString *)getUUID;

/// User name, who loggin GTV.  if nobody login, this username maybe nil.
- (nullable NSString *)getUserName;

#pragma mark - Tracking

/// GTV tracking function
/// @param eventName name event tracking, ex. : @"click news"
/// @param value value tracking, ex. : @{"watch_time": 100 }
- (void)trackingWithEvent:(NSString *)eventName value:(NSDictionary  * _Nullable )value;

#pragma mark - Support method

/// This token for user-related APIs. You must to login first, if not this token maybe nil. in the case this token is nil, you need to call refresh it by use below method.
- (nullable NSString *)getAccountToken;

/// This token for payment-related APIs. You must to login first, if not this token maybe nil. in the case this token is nil, you need to call refresh it by use below method. like as account token
- (nullable NSString *)getPaymentToken;


/// Refresh to get new token for account-related
///  This framework do not automatic check token was invalid or not. This way to save resources
///  so you need to refresh manually
/// @param callback call back help you know it done, maybe success or error.
- (void)refreshTokenAccountNow:(RefreshTokenCallback)callback;

/// Refresh to get new token payment-related
///  This framework do not automatic check token was invalid or not. This way to save resources
///  so you need to refresh manually
/// @param callback call back help you know it done, maybe success or error.
- (void)refreshTokenPaymentNow:(RefreshTokenCallback)callback;


/// My web form is show when login or do something related to the payment. It is automic, show or hidden.
/// but for some reason it was not closed, this method to help close it manully.
- (void)hideWebview;


/// Post custom tracking
/// @param action action name
/// @param uid uid is a value for define user unique. can use uuid value.
/// @param revenue value to track.
- (void)postTrackingWithAction:(NSString *)action uid:(NSString *)uid revenue:(long)revenue;

@end
NS_ASSUME_NONNULL_END
