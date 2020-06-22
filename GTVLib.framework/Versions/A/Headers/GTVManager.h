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

@protocol GTVManagerDelegate <NSObject>

- (void)gtvDidReceivedUserHash:(NSString *)userHash;
- (void)gtvDidClickLoginFacebook;
- (void)gtvDidLogout;
- (void)gtvLoginError:(NSString *)msg;
@end

@interface GTVManager : NSObject
@property (nonatomic, assign) id<GTVManagerDelegate> delegate;
@property (nonatomic, strong) FacebookService *fbService;

@property (nonatomic, copy) NSString *URL_ID;
@property (nonatomic, copy) NSString *URL_PAY;

@property (nonatomic, strong) NSDictionary *installData;

+ (GTVManager *)sharedManager;

#pragma mark - Push Notification
+ (void)registerForRemoteNotifications:(UIApplication *)application;
+ (void)handleRemoteNotification:(NSDictionary *)userInfo application:(UIApplication *)application;
+ (void)postFcmToken:(NSString *)fcmToken;

#pragma mark - Application State
+ (void)handleWillResignActive;
+ (void)handleDidEnterBackground;
+ (void)handleWillEnterForeground;
+ (void)handleDidBecomeActive;
+ (void)handleWillTerminate;
+ (void)handleDidFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
+ (void)handleDidRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;
#pragma mark - Payment
- (void)showPaymentWithOrderID:(NSString *)orderID serverID:(NSString *)serverID serverName:(NSString *)serverName roleID:(NSString *)roleID roleName:(NSString *)roleName userID:(NSString*)userID channel:(NSString*)channel levels:(NSString *)levels;
- (void)startIAPPaymentServerID:(NSString *)serverID roleID:(NSString *)roleID platform:(NSString *)platform levels:(NSString *)levels productID:(NSString*)productID gameOrderID:(NSString*)gameOrderID partner:(NSString*)partner callback:(GTVIAPCallback)callback;
- (BOOL)isIAP:(int)level;
#pragma mark - Account
- (void)showLogin;
- (void)showLinkAccount;
- (void)hideWebview;
- (void)logout;
- (void)loginFacebookWith:(UIViewController *)viewController;
+ (nullable NSString *)getUserHash;
+ (void)useProductServer:(BOOL)useProductServer;
#pragma mark - Tracking
- (void)postTrackingWithAction:(NSString *)action uid:(NSString *)uid revenue:(long)revenue;

@end
NS_ASSUME_NONNULL_END
