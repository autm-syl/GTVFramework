//
//  GTVManager.h
//  GTVCocoaTouchFramework
//
//  Created by Macbook on 2/26/19.
//  Copyright © 2019 Андрей Недов. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FacebookService.h"
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
typedef void (^GTVILoginCallback)(BOOL isSuccess, NSString * _Nullable message, NSString * _Nullable userHash);

@interface GTVManager : NSObject

#pragma mark - Property
@property (nonatomic, strong) FacebookService *fbService;
@property (nonatomic, copy) NSString *URL_ID;
@property (nonatomic, copy) NSString *URL_PAY;
@property (nonatomic, strong) NSDictionary *installData;


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


#pragma mark - Account

/// GTV Login form
- (void)showLogin:(GTVILoginCallback)callback;

/// GTV Logout
- (void)logout: (GTVILogoutCallback)callback;


/// UserHash
- (nullable NSString *)getUserHash;

#pragma mark - Tracking

/// GTV tracking function
/// @param eventName name event tracking, ex. : @"click news"
/// @param value value tracking, ex. : @{"watch_time": 100 }
- (void)trackingWithEvent:(NSString *)eventName value:(NSDictionary  * _Nullable )value;

#pragma mark - Support method
- (void)hideWebview;
- (void)postFcmToken:(NSString *)fcmToken;
- (void)postTrackingWithAction:(NSString *)action uid:(NSString *)uid revenue:(long)revenue;

@end
NS_ASSUME_NONNULL_END
