# GTVFramework

[![Version](https://img.shields.io/cocoapods/v/GTVFramework.svg?style=flat)](https://cocoapods.org/pods/GTVFramework)
[![License](https://img.shields.io/cocoapods/l/GTVFramework.svg?style=flat)](https://cocoapods.org/pods/GTVFramework)
[![Platform](https://img.shields.io/cocoapods/p/GTVFramework.svg?style=flat)](https://cocoapods.org/pods/GTVFramework)
[![CocoaPods compatible](https://img.shields.io/badge/CocoaPods-compatible-green.svg?style=flat)](https://cocoapods.org)

## Example

To run the example project, clone the repo, and run `pod install` from the Example directory first.

## Requirements

- ios version > 10.0

## Installation

GTVFramework is available through [CocoaPods](https://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby
pod 'GTVFramework'
```
## Objective-C
### Init
In AppDelegate.m
```objective-c
#import <GTVLib/GTVLib.h>
```
```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [[GTVManager sharedManager] ImplementWith:application didFinishLaunchingWithOptions:launchOptions useProductServer:NO];// YES to switch to production, NO to switch to development 
    return YES;
}
```

```objective-c
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    // Handle notify.
    [[GTVManager sharedManager] handleNotificationsWithDeviceToken:deviceToken];
}
```

#### If you use SceneDelegate in your project, let set this handle at call back openURLContexts.
```objective-c
- (void)scene:(UIScene *)scene openURLContexts:(NSSet<UIOpenURLContext *> *)URLContexts API_AVAILABLE(ios(13.0)){
    NSURL *url = [[URLContexts allObjects] firstObject].URL;
    bool shouldOpen = [[GTVManager sharedManager] gtvApplication:[UIApplication sharedApplication] openURL:url options:nil];
}
```

### API
Login and logout:
```objective-c
[[GTVManager sharedManager] showLogin:^(BOOL isSuccess, NSString * _Nullable message, NSString * _Nullable userHash) {
    //
    if (isSuccess && userHash != nil) {
        NSLog(@"gtvDidReceivedUserHash: %@", userHash);
        dispatch_async(dispatch_get_main_queue(), ^{
            GameViewController *gameVC = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:@"GameViewController"];
            [self.navigationController pushViewController:gameVC animated:YES];
        });
    } else {
        dispatch_async(dispatch_get_main_queue(), ^{
        // offending code goes in here
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:[NSString stringWithFormat:@"Login error : %@", message] preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
            [self presentViewController:alert animated:YES completion:nil];
        });
    }
}];


[[GTVManager sharedManager] logout:^(BOOL isSuccess, NSString * _Nullable message) {
    //
    if (isSuccess) {
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:@"Logout success!" preferredStyle:UIAlertControllerStyleAlert];
        [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
        [self presentViewController:alert animated:YES completion:nil];
    }
}];
```

Payment:
```objective-c
if ([[GTVManager sharedManager] getUserHash]) {
     [[GTVManager sharedManager] showPaymentWithOrderID:@"orderID" serverID:@"1" serverName:@"serverName" roleID:@"49" roleName:@"roleName" userID:@"userID" channel:@"channel" levels:@"1" callback:^(GTVIAPStatus status, NSString * _Nonnull message) {
         switch (status) {
             case GTVRequestError:
                 //
                 break;
             default:
                 break;
         }
         NSLog(@"Payment: %u, mess: %@", status, message);
     }];
 } else {
     UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:@"Login required" preferredStyle:UIAlertControllerStyleAlert];
     [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
     [self presentViewController:alert animated:YES completion:nil];
 }
```

share FB:
```objective-c
[[GTVManager sharedManager] shareLinkContent:@"https://gtv.com.vn/" fromViewController:self callback:^(NSDictionary<NSString *,id> * _Nullable results, NSError * _Nullable error, BOOL cancel) {
   NSLog(@"\nResults: %@ \n Error: %@ \n Cancel: %d", results, error, cancel);
}];
```
    

## Swift

Even though `GTVFramework` is written in Objective-C, it can be used in Swift with no hassle. If you use [CocoaPods](http://cocoapods.org) add the following line to your [Podfile](http://guides.cocoapods.org/using/using-cocoapods.html):
```ruby
pod 'GTVFramework'
```

You need create a bridging-header file, [Here is tutorial](https://medium.com/@javedmultani16/adding-a-swift-bridging-header-5562f8855311)
Then import GTVLib into this header file.

```objective-c
#import <GTVLib/GTVLib.h>
```
Now you can you GTVLib without import anymore!

### init
```swift
func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
    GTVManager.shared().implement(with: application, didFinishLaunchingWithOptions: launchOptions!, useProductServer: false)
    return true
}

func application(_ app: UIApplication, open url: URL, options: [UIApplication.OpenURLOptionsKey : Any] = [:]) -> Bool {
    let shouldOpen = GTVManager.shared().gtvApplication(app, open: url, options: options)
    return shouldOpen;
}
```

#### If you use SceneDelegate in your project, let set this handle at call back openURLContexts.
```swift
func scene(_ scene: UIScene, openURLContexts URLContexts: Set<UIOpenURLContext>) {
    guard let url = URLContexts.first?.url else {
        return
    }
    
    GTVManager.shared().gtvApplication(UIApplication.shared, open: url, options: [:])
}
```
### API

Login and logout
```swift
GTVManager.shared().showLogin { (isSuccess, message, userHash) in
    //
}
```

```swift
GTVManager.shared().logout { (isSuccess, message) in
    //
}
```

Payment
```swift
GTVManager.shared().showPayment(withOrderID: "orderID", serverID: "serverID", serverName: "serverName", roleID: "roleID", roleName: "roleName", userID: "userID", channel: "channel", levels: "levels") { (status, message) in
    //
}
```

Share
```swift
GTVManager.shared().shareLinkContent("https://gtv.com.vn/", from: self) { (result, error, cancel) in
   //
}
```


## Author

cuonglv@gametv.com.vn

## License

GTVFramework is available under the MIT license. See the [LICENSE](https://github.com/autm-syl/GTVFramework/blob/master/LICENSE) file for more info.


## PS
Please create new issue if you got any trouble when you integrate this library. 
Thank!
