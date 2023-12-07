/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "HelloWorldScene.h"

// #define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;

static cocos2d::Size design_size = cocos2d::Size(480, 320);
static cocos2d::Size small_size = cocos2d::Size(480, 320);
static cocos2d::Size medium_size = cocos2d::Size(1024, 768);
static cocos2d::Size large_size = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {
#if USE_AUDIO_ENGINE
  AudioEngine::end();
#endif
}

void AppDelegate::initGLContextAttrs() {}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  auto director = Director::getInstance();
  auto glview = director->getOpenGLView();
  if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) ||                               \
    (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) ||                                 \
    (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    glview = GLViewImpl::createWithRect(
        "MyGame", cocos2d::Rect(0, 0, design_size.width, design_size.height));
#else
    glview = GLViewImpl::create("Cubes");
#endif
    director->setOpenGLView(glview);
  }

  director->setAnimationInterval(1.0f / 60);

  // Set the design resolution
  glview->setDesignResolutionSize(design_size.width, design_size.height,
                                  ResolutionPolicy::NO_BORDER);
  auto frameSize = glview->getFrameSize();

  if (frameSize.height > medium_size.height) {
    director->setContentScaleFactor(MIN(large_size.height / design_size.height,
                                        large_size.width / design_size.width));
  } else if (frameSize.height > small_size.height) {
    director->setContentScaleFactor(MIN(medium_size.height / design_size.height,
                                        medium_size.width / design_size.width));
  } else {
    director->setContentScaleFactor(MIN(small_size.height / design_size.height,
                                        small_size.width / design_size.width));
  }

  auto scene = HelloWorld::CreateScene();
  director->runWithScene(scene);

  return true;
}

void AppDelegate::applicationDidEnterBackground() {
  Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
  AudioEngine::pauseAll();
#endif
}

void AppDelegate::applicationWillEnterForeground() {
  Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
  AudioEngine::resumeAll();
#endif
}
