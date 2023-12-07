#ifndef AREA_H
#define AREA_H

#include <list>
#include <memory>
#include <vector>

#include "cocos2d.h"

USING_NS_CC;

class Cell {
public:
  explicit Cell(Sprite *sprite)
      : sprite_{sprite}, left_(nullptr), right_(nullptr), top_(nullptr),
        bottom_(nullptr) {}
  ~Cell() = default;
  Cell(const Cell &) = default;
  Cell(Cell &&) = delete;
  Cell &operator=(const Cell &) = delete;
  Cell &operator=(Cell &&) = delete;

  bool operator==(const Cell &other) const {

    return &sprite_ == &(other.sprite_);
  }
  bool operator!=(const Cell &other) const { return !(*this == other); }

  Sprite *sprite_;
  Cell *left_;
  Cell *right_;
  Cell *top_;
  Cell *bottom_;
};

//*****************************************************************************
//*****************************************************************************
class Area {
  using rect_t = std::vector<std::list<Cell>>;

public:
  Area(std::size_t rows, std::size_t cols,
       std::list<Sprite *> &sprites);
  rect_t area_;
};

#endif // AREA_H