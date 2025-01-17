/*
 * Copyright (c) 2011, The Iconfactory. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of The Iconfactory nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE ICONFACTORY BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "UIView.h"

typedef enum {
    UIScrollViewIndicatorStyleDefault,
    UIScrollViewIndicatorStyleBlack,
    UIScrollViewIndicatorStyleWhite
} UIScrollViewIndicatorStyle;

UIKIT_EXPORT const float UIScrollViewDecelerationRateNormal;
UIKIT_EXPORT const float UIScrollViewDecelerationRateFast;

@class UIScroller, UIImageView, UIScrollView, UIPanGestureRecognizer, UIScrollWheelGestureRecognizer;

@protocol UIScrollViewDelegate <NSObject>
@optional
- (void)scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView;
- (void)scrollViewDidScroll:(UIScrollView *)scrollView;
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView;
- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;
- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView;
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView;
- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView;
- (void)scrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(UIView *)view;
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(float)scale;
- (void)scrollViewDidZoom:(UIScrollView *)scrollView;
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset;
- (void)scrollViewDidScrollToTop:(UIScrollView *)scrollView;
- (BOOL)scrollViewShouldScrollToTop:(UIScrollView *)scrollView;
@end

UIKIT_EXPORT_CLASS
@interface UIScrollView : UIView {
    id _delegate;
    id       _pressTimer;
    idretain _savedTouch, _savedEvent;
    idretain _zoomView;
    CGPoint  _lastTouchPos;
    double   _lastTouchTime;

    BOOL     _showsVerticalScrollIndicator;
    idretain _verticalScroller;
    bool     _shouldShowScroller;
    bool     _scrollerVisible;

    CGPoint  _panStart;

    CGPoint  _contentOffset;
    CGSize   _contentSize;
    UIEdgeInsets _contentInset;
    UIEdgeInsets _scrollIndicatorInsets;
    BOOL     _isDragging;
    BOOL     _pagingEnabled;
    BOOL     _bounces;
    BOOL     _alwaysBounceVertical;
    BOOL     _alwaysBounceHorizontal;
    BOOL     _canCancelContentTouches;
    BOOL     _delaysContentTouches;
    BOOL     _scrollEnabled;
    BOOL     _forwardingTouch;
    BOOL     _forwardsToSuperview;
    BOOL     _scrollAnimation;
    bool     _cancellableAnim;

    BOOL     _sendingScrollEvent;

    float    _zoomScale, _maximumZoomScale, _minimumZoomScale;
    float    _savedZoomDistance, _savedZoomScale;
    CGRect   _originalZoomRect;

    bool _xStuck, _yStuck;
    
    idretain _panGesture, _pinchGesture;

    float   _enterPos, _enterDir;

    BOOL    _isZooming, _isZoomingToRect;
    bool    _lockVertical, _lockHorizontal;

    enum AnimationReason 
    { 
        ANIMATION_DECELERATING, 
        ANIMATION_DECELERATING_TARGET,
        ANIMATION_BOUNCING,
        ANIMATION_PAGING, 
        ANIMATION_USER
    };
    
    enum AnimationReason _animationReason;

    idretain _displayLink;

    double   _scrollStartTime;
    int      _scrollFrame;
    CGPoint  _scrollVelocity, _scrollPosition;
    CGPoint  _scrollDirection;

    CGPoint  _scrollAnimStart, _scrollAnimDest;
    double   _scrollAnimStartTime, _scrollAnimDecaySpeed;
}

- (void)scrollRectToVisible:(CGRect)rect animated:(BOOL)animated;

- (void)setZoomScale:(float)scale animated:(BOOL)animated;
- (void)zoomToRect:(CGRect)rect animated:(BOOL)animated;

- (void)setContentOffset:(CGPoint)theOffset animated:(BOOL)animated;
- (void)flashScrollIndicators;      // does nothing

- (BOOL)touchesShouldCancelInContentView:(UIView *)view;

@property (nonatomic) CGSize contentSize;
@property (nonatomic) CGPoint contentOffset;
@property (nonatomic) UIEdgeInsets contentInset;
@property (nonatomic) UIEdgeInsets scrollIndicatorInsets;
@property (nonatomic) UIScrollViewIndicatorStyle indicatorStyle;
@property (nonatomic) BOOL showsHorizontalScrollIndicator;
@property (nonatomic) BOOL showsVerticalScrollIndicator;
@property (nonatomic) BOOL bounces;
@property (nonatomic) BOOL alwaysBounceVertical;
@property (nonatomic) BOOL alwaysBounceHorizontal;
@property (nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;
@property (nonatomic, assign) id<UIScrollViewDelegate> delegate;
@property (nonatomic) BOOL scrollsToTop;            // no effect
@property (nonatomic) BOOL delaysContentTouches;    // no effect
@property (nonatomic) BOOL canCancelContentTouches; // no effect
@property (nonatomic, readonly, getter=isDragging) BOOL dragging;
@property (nonatomic, readonly, getter=isTracking) BOOL tracking;           // always returns NO
@property (nonatomic, readonly, getter=isDecelerating) BOOL decelerating;   // always returns NO
@property (nonatomic, assign) BOOL pagingEnabled;
@property (nonatomic) float decelerationRate;

@property (nonatomic) float maximumZoomScale;
@property (nonatomic) float minimumZoomScale;
@property (nonatomic) float zoomScale;
@property (nonatomic, readonly, getter=isZooming) BOOL zooming;
@property (nonatomic, readonly, getter=isZoomBouncing) BOOL zoomBouncing;   // always NO
@property (nonatomic) BOOL bouncesZoom;                                     // no effect

@property (nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer;
@property (nonatomic, readonly) UIScrollWheelGestureRecognizer *scrollWheelGestureRecognizer;   // non-standard
@property (nonatomic, getter=isDirectionalLockEnabled) BOOL directionalLockEnabled;

@end
