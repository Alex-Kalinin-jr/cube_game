#ifndef __GAMEARG_H__
#define __GAMEARG_H__

#include "cocos2d.h"
#include "score.h"

class Score : public cocos2d::Layer {
public:
  Score();
  ~Score();

  virtual bool init();
  void Update(std::size_t dt);
  void Reset();

  CREATE_FUNC(Score);

private:
  std::size_t total_score_;
};

#endif // __GAMEARG_H__