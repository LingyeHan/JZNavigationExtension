//
//  _JZ-objc-internal.h
//  JZNavigationExtensionDemo
//
//  Created by Jazys on 3/11/16.
//  Copyright © 2016 Jazys. All rights reserved.
//

#ifndef _JZ_objc_internal_h
#define _JZ_objc_internal_h

#import <objc/runtime.h>

#define objc_getProperty(objc,key) [objc valueForKey:key]

@interface UINavigationController (_JZExtension)
#pragma clang diagnostic push
#pragma clang diagnostic ignored"-Wnullability-completeness"
@property (nonatomic, copy) void (^jz_interactivePopGestureRecognizerCompletion)(UINavigationController *, UIViewController *, BOOL);
@property (nonatomic, copy) void (^_jz_navigationTransitionFinished)(BOOL);
- (void)setJz_interactivePopedViewController:(UIViewController *)jz_interactivePopedViewController;
#pragma clang diagnostic pop
- (BOOL)jz_isTransitioning;
- (BOOL)jz_isInteractiveTransition;
@end

@protocol JZExtensionBarProtocol <NSObject>
@property (nonatomic, assign) CGSize jz_size;
- (UIView * _Nullable)jz_backgroundView;
- (CGSize)jz_sizeThatFits:(CGSize)size;
@end

#define JZExtensionBarImplementation \
- (CGSize)jz_sizeThatFits:(CGSize)size { \
CGSize newSize = [self jz_sizeThatFits:size]; \
return CGSizeMake(self.jz_size.width == 0.f ? newSize.width : self.jz_size.width, self.jz_size.height == 0.f ? newSize.height : self.jz_size.height); \
} \
- (void)setJz_size:(CGSize)size { \
objc_setAssociatedObject(self, @selector(jz_size), [NSValue valueWithCGSize:size], OBJC_ASSOCIATION_RETAIN_NONATOMIC); \
[self sizeToFit]; \
} \
- (CGSize)jz_size { \
return [objc_getAssociatedObject(self, _cmd) CGSizeValue]; \
} \
- (UIView *)jz_backgroundView { \
return objc_getProperty(self, @"_backgroundView"); \
}

#endif /* _JZ_objc_internal_h */
