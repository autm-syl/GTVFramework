//
//  GTVFRAMEWORKViewController.m
//  GTVFramework
//
//  Created by lecuong.bka@gmail.com on 06/22/2020.
//  Copyright (c) 2020 lecuong.bka@gmail.com. All rights reserved.
//

#import "GTVFRAMEWORKViewController.h"
#import "GameViewController.h"

#import <GTVLib/GTVLib.h>


@interface GTVFRAMEWORKViewController ()

@end

@implementation GTVFRAMEWORKViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)showLogin {
    [[GTVManager sharedManager] showLogin:^(BOOL isSuccess, NSString * _Nullable message, NSString * _Nullable uuid, NSString * _Nullable username) {
        //
        if (isSuccess && uuid != nil) {
            NSLog(@"gtv login success: %@", uuid);
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
   
}

- (IBAction)logout {
    [[GTVManager sharedManager] logout:^(BOOL isSuccess, NSString * _Nullable message) {
        //
        if (isSuccess) {
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:@"Logout success!" preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
            [self presentViewController:alert animated:YES completion:nil];
        }
    }];
}
- (IBAction)getUserInformation:(id)sender {
    NSString *userinfor = [NSString stringWithFormat:@"uuid:%@\n----username:%@\nPayment:%@\nAcount:%@",[[GTVManager sharedManager] getUUID], [[GTVManager sharedManager] getUserName], [[GTVManager sharedManager] getPaymentToken], [[GTVManager sharedManager] getAccountToken]];
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:[NSString stringWithFormat:@"Information\n%@", userinfor] preferredStyle:UIAlertControllerStyleAlert];
    [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
    [self presentViewController:alert animated:YES completion:nil];
}

- (IBAction)showPayment {
    if ([[GTVManager sharedManager] getUserHash]) {
        [[GTVManager sharedManager] showPaymentWithOrderID:@"orderID" serverID:@"1" serverName:@"serverName" roleID:@"49" roleName:@"roleName" userID:@"userID" channel:@"channel" levels:@"1" callback:^(GTVIAPStatus status, NSString * _Nonnull message) {
            //
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
}
- (IBAction)refreshToken:(id)sender {
    [[GTVManager sharedManager] refreshTokenPaymentNow:^(BOOL isSuccess, NSString * _Nullable message) {
        //
        if (isSuccess) {
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:message preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
            [self presentViewController:alert animated:YES completion:nil];
        }
    }];
    
    
    
    [[GTVManager sharedManager] refreshTokenAccountNow:^(BOOL isSuccess, NSString * _Nullable message) {
        //
        if (isSuccess) {
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:message preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
            [self presentViewController:alert animated:YES completion:nil];
        }
    }];
}

- (IBAction)shareFB:(id)sender {
    [[GTVManager sharedManager] shareLinkContent:@"https://gtv.com.vn/" fromViewController:self callback:^(NSDictionary<NSString *,id> * _Nullable results, NSError * _Nullable error, BOOL cancel) {
        //
        NSLog(@"\nResults: %@ \n Error: %@ \n Cancel: %d", results, error, cancel);
    }];
}

@end
