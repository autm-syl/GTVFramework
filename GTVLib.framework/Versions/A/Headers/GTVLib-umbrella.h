//
//  GTVLib-umbrella.h
//  GTVLib
//
//  Created by Sylvanas on 6/29/20.
//  Copyright © 2020 Sylvanas. All rights reserved.
//

#ifndef GTVLib_umbrella_h
#define GTVLib_umbrella_h


#endif /* GTVLib_umbrella_h */


#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "GTVLib.h"

FOUNDATION_EXPORT double GTVLibVersionNumber;
FOUNDATION_EXPORT const unsigned char GTVLibVersionString[];

