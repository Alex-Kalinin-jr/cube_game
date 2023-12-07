#include "score.h"

USING_NS_CC;

Score::Score() : total_score_{0} {}

Score::~Score() {}

bool Score::init() {
  if (!Layer::init()) {
    return false;
  }
  auto visible_size = Director::getInstance()->getVisibleSize();
  auto label_score =
      Label::createWithSystemFont(std::to_string(total_score_), "Arial", 30);

  label_score->setPosition(
      Vec2(visible_size.width / 2,
           visible_size.height - label_score->getContentSize().height * 2));
  label_score->setTextColor(Color4B::RED);
  label_score->enableItalics();
  label_score->setTag(10);
  this->addChild(label_score);

  scheduleUpdate();

  return true;
}

void Score::Update(std::size_t dt) {
  total_score_ += dt;
  cocos2d::Label *label_score = (cocos2d::Label *)this->getChildByTag(10);
  label_score->setString(std::to_string(total_score_));
  scheduleUpdate();
}

void Score::Reset() {
  total_score_ = 0;
  cocos2d::Label *label_score = (cocos2d::Label *)this->getChildByTag(10);
  label_score->setString(std::to_string(total_score_));
  scheduleUpdate();
}
