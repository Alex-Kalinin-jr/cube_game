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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "area.h"
#include "cocos/ui/UIWidget.h"
#include "cocos2d.h"
#include "score.h"

#define kMIN_FOR_DESTROY 3
#define kINTERVAL 10

enum Difficulties { D_EASY, D_MEDIUM, D_HARD, D_END };

enum Colour { C_RED, C_GREEN, C_BLUE, C_YELLOW, C_PURPLE, C_END };

class HelloWorld : public cocos2d::Scene {
public:
  static cocos2d::Scene *CreateScene();

  virtual bool init();
  bool FillWithArea(Difficulties);

private:
  std::shared_ptr<Area> area_;
  std::size_t size_;
  Score *score_;
  std::list<cocos2d::Sprite *> sprites_;
  cocos2d::EventListenerTouchOneByOne *listener_;

  void CreateCells(std::size_t size, Difficulties);

  bool FillFirstTime();
  void HideCells(std::vector<Cell *> &);
  void DeleteAllCells();
  void MoveCells();
  void CreateListener();
  void ResetButtonCallback(Ref *sender, ui::Widget::TouchEventType,
                           Difficulties);

  CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

//