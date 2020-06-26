//
//  FirebaseService.h
//  FirebaseCocoaTouchFramework
//
//  Created by Andrey on 28.08.2018.
//  Copyright © 2018 Андрей Недов. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class FIRMessaging;
@class FIRMessagingRemoteMessage;

@protocol FirebaseServiceDelegate <NSObject>
@required
- (void)messagingDidRefreshRegistrationToken:(nonnull NSString *)fcmToken;
- (void)messagingDidReceiveMessage:(nonnull NSDictionary *)remoteMessage;
@end

@interface FirebaseService : NSObject 
@property (weak, nonatomic, nullable) id <FirebaseServiceDelegate> delegate;
+ (nullable FirebaseService *)sharedManager;
- (void)configure;
- (void)configureAfterDelay:(int64_t)delay withApplication:(UIApplication *)application delegate:( id <FirebaseServiceDelegate>_Nullable)delegate;
- (nullable NSString *)getFCMToken;
- (void)setAPNSToken:(NSData *_Nonnull)token;
- (void)messagingDelegate:(nullable id <FirebaseServiceDelegate>)delegate;

#pragma mark - Dynamic Links
+ (BOOL)continueUserActivity:(nonnull NSUserActivity *)userActivity;
+ (BOOL)openURL:(NSURL *_Nonnull)url options:(NSDictionary<NSString *, id> *_Nonnull)options;
@end
