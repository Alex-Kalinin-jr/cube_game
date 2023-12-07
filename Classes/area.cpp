#include "area.h"

#include <list>
#include <memory>
#include <vector>

#include "cocos2d.h"

USING_NS_CC;

Area::Area(std::size_t rows, std::size_t cols,
           std::list<Sprite *> &sprites) {
  rect_t buff_area(cols);
  auto itr = sprites.begin();

  for (auto i = 0; i < cols; ++i) {
    for (auto j = 0; j < rows; ++j) {
      Cell buff_cell(*(itr++));
      buff_area.at(i).push_back(buff_cell);
    }
  }
  area_ = std::move(buff_area);
}

//*****************************************************************************
//*****************************************************************************