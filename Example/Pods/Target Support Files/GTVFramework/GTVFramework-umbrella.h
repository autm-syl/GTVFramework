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

#import "FirebaseService.h"
#import "GTVLib-umbrella.h"
#import "GTVLib.h"
#import "GTVManager.h"

FOUNDATION_EXPORT double GTVFrameworkVersionNumber;
FOUNDATION_EXPORT const unsigned char GTVFrameworkVersionString[];

