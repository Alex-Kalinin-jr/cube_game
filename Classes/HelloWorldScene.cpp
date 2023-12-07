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

#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"

#include <functional>
#include <random>
#include <list>
#include <map>
#include <vector>

#include "areaalgorithms.h"
#include "score.h"

USING_NS_CC;
using namespace ui;

std::map<Difficulties, std::size_t> _m_sizes = {{Difficulties::D_EASY, 6},
                                                {Difficulties::D_MEDIUM, 13},
                                                {Difficulties::D_HARD, 20}};

std::map<Colour, Color3B> color_map = {{Colour::C_RED, Color3B(255, 0, 0)},
                                       {Colour::C_GREEN, Color3B(0, 255, 0)},
                                       {Colour::C_BLUE, Color3B(0, 0, 255)},
                                       {Colour::C_YELLOW, Color3B(255, 200, 100)},
                                       {Colour::C_PURPLE, Color3B(255, 100, 200)},};

Scene *HelloWorld::CreateScene() {
  auto scene = HelloWorld::create();
  scene->area_ = nullptr;
  scene->size_ = 0;
  scene->score_ = nullptr;
  scene->listener_ = nullptr;
  return scene;
}

//*****************************************************************************
//*****************************************************************************
bool HelloWorld::init() {
  if (!Scene::init()) {
    return false;
  }
  auto visible_size = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  score_ = Score::create();
  this->addChild(score_, 3);
  score_->setPosition(Vec2(0, 50));

  auto reset_easy = Button::create("easy.png");
  reset_easy->setTitleText("Easy");
  reset_easy->setPosition(Vec2(50, 50));
  this->addChild(reset_easy, 4);
  reset_easy->addTouchEventListener(CC_CALLBACK_2(
      HelloWorld::ResetButtonCallback, this, Difficulties::D_EASY));

  auto reset_medium = Button::create("medium.png");
  reset_medium->setPosition(Vec2(50, 110));
  reset_medium->setTitleText("Medium");
  this->addChild(reset_medium, 4);
  reset_medium->addTouchEventListener(CC_CALLBACK_2(
      HelloWorld::ResetButtonCallback, this, Difficulties::D_MEDIUM));

  auto reset_hard = Button::create("hard.png");
  reset_hard->setTitleText("Hard");
  reset_hard->setPosition(Vec2(50, 170));
  this->addChild(reset_hard, 4);
  reset_hard->addTouchEventListener(CC_CALLBACK_2(
      HelloWorld::ResetButtonCallback, this, Difficulties::D_HARD));

  return true;
}

//***************************************************************************
//***************************************************************************
bool HelloWorld::FillWithArea(Difficulties level) {
  auto rows = _m_sizes[level];
  auto cols = _m_sizes[level];
  auto buff_size = Director::getInstance()->getVisibleSize();
  size_ = std::min(buff_size.width / cols, (buff_size.height - 50) / rows);

  DeleteAllCells();
  CreateCells(rows * cols, level);
  CreateListener();
  for (auto sprite : sprites_) {
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_->clone(),
                                                             sprite);
  }

  area_ = std::make_shared<Area>(rows, cols, sprites_);
  AreaAlgorithms::Link(area_.get());
  FillFirstTime();
  return true;
}

//*****************************************************************************
//*****************************************************************************
bool HelloWorld::FillFirstTime() {
  auto x_pos = (Director::getInstance()->getVisibleSize().width -
                (size_ * area_->area_.size())) /
               2;
  auto y_pos = 0;
  for (auto &area_col : area_->area_) {
    for (auto &cell : area_col) {
      cell.sprite_->setPosition(Vec2(x_pos, y_pos));
      y_pos += size_;
    }
    x_pos += size_;
    y_pos = 0;
  }
  return true;
}

//*****************************************************************************
//*****************************************************************************
void HelloWorld::MoveCells() {
  auto x_pos = (Director::getInstance()->getVisibleSize().width -
                (size_ * area_->area_.size())) /
               2.0f;
  auto y_pos = 0.0f;
  for (auto &col : area_->area_) {
    for (auto itr = col.begin(); itr != col.end(); ++itr) {
      auto moveTo = MoveTo::create(0.5, Vec2(x_pos, y_pos));
      itr->sprite_->runAction(moveTo);
      y_pos += size_;
    }
    x_pos += size_;
    y_pos = 0;
  }
}

//*****************************************************************************
//*****************************************************************************
void HelloWorld::HideCells(std::vector<Cell *> &vctr_to_del) {
  for (auto &cell : vctr_to_del) {
    if (cell->sprite_) {
      cell->sprite_->setVisible(false);
      cell->sprite_ = nullptr;
    }
  }

  AreaAlgorithms::DeleteCellsFromArea(*area_, vctr_to_del);
  AreaAlgorithms::Link(area_.get());
}

//*****************************************************************************
//*****************************************************************************
void HelloWorld::DeleteAllCells() {
  for (auto &sprite : sprites_) {
    _eventDispatcher->removeEventListenersForTarget(sprite);
    if (sprite->getParent() != nullptr) {
      sprite->removeFromParent();
    }
  }
  sprites_.clear();
}
//*****************************************************************************
//*****************************************************************************
void HelloWorld::CreateCells(std::size_t size, Difficulties level) {
  std::random_device rd;
  std::default_random_engine engine(rd());
  int top_rand = 0;
  switch (level) {
    case Difficulties::D_EASY:
      top_rand = 2;
      break;
    case Difficulties::D_MEDIUM:
      top_rand = 3;
      break;
    case Difficulties::D_HARD:
      top_rand = 4;
      break;
    default:
      top_rand = 2;
      break;
  }
  auto gen =
      std::bind(std::uniform_int_distribution<>(0, top_rand), engine);
  for (auto i = 0; i < size; ++i) {
    auto sprite = 
        Sprite::create("white.png", Rect(0, 0, size_, size_));
    sprite->setColor(color_map[static_cast<Colour>(gen())]);
    sprite->setAnchorPoint(Vec2(0, 0));
    this->addChild(sprite, 2);
    sprites_.emplace_back(sprite);
  }
}

//*****************************************************************************
// //*****************************************************************************
void HelloWorld::CreateListener() {
  listener_ = EventListenerTouchOneByOne::create();
  listener_->setSwallowTouches(true);
  listener_->onTouchBegan = [this](Touch *touch, Event *event) {
    auto target = static_cast<Sprite *>(event->getCurrentTarget());
    if (target) {
      for (auto &col : area_->area_) {
        for (auto cell = col.begin(); cell != col.end(); ++cell) {
          if (cell->sprite_ && cell->sprite_->getBoundingBox().containsPoint(
                                   touch->getLocation())) {
            std::vector<Cell *> vctr_to_del =
                AreaAlgorithms::FindAdjacentCells(&(*cell));
            if (vctr_to_del.size() >= kMIN_FOR_DESTROY) {
              HideCells(vctr_to_del);
              MoveCells();
              score_->Update(vctr_to_del.size());
            }
            return true;
          }
        }
      }
    }
    return true;
  };
}

void HelloWorld::ResetButtonCallback(Ref *sender, Widget::TouchEventType type,
                                     Difficulties difficulty) {
  if (type == Widget::TouchEventType::ENDED) {
    FillWithArea(difficulty);
    score_->Reset();
  }
}