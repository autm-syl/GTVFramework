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

- (IBAction)getUserHash:(id)sender {
    NSString *userHash = [[GTVManager sharedManager] getUserHash];
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:[NSString stringWithFormat:@"user_hash = %@", userHash] preferredStyle:UIAlertControllerStyleAlert];
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

- (IBAction)paymentWithProductID:(id)sender {
    if ([[GTVManager sharedManager] getUserHash]) {
        NSArray *arrs = [NSArray arrayWithObjects:@"com.gtv.thiensu.99", @"com.gtv.thiensu.499",  @"com.gtv.thiensu.999",  @"com.gtv.thiensu.1499",  @"com.gtv.thiensu.2499",  @"com.gtv.thiensu.4999",  @"com.gtv.thiensu.9999", nil];
        uint32_t rnd = arc4random_uniform((uint32_t)[arrs count]);
        NSString *productID = [arrs objectAtIndex:rnd];
        [[GTVManager sharedManager] startIAPPaymentServerID:@"100" roleID:@"431067320809" platform:@"9005" levels:@"370" productID:productID gameOrderID:@"201910161073899979" partner:@"2" callback:^(GTVIAPStatus status, NSString * _Nonnull message) {
            NSLog(@"\nStatus: %d \n Message: %@", status, message);
            if (status != GTVPurchasing) {
                // Do anything
            }
        }];
    } else {
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil message:@"Login required" preferredStyle:UIAlertControllerStyleAlert];
        [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
        [self presentViewController:alert animated:YES completion:nil];
    }
}
- (IBAction)shareFB:(id)sender {
    [[GTVManager sharedManager] shareLinkContent:@"https://gtv.com.vn/" fromViewController:self callback:^(NSDictionary<NSString *,id> * _Nullable results, NSError * _Nullable error, BOOL cancel) {
        //
        NSLog(@"\nResults: %@ \n Error: %@ \n Cancel: %d", results, error, cancel);
    }];
}

@end
