#ifndef AREAALGORITHMS_H
#define AREAALGORITHMS_H

#include <memory>

#include "area.h"
#include "cocos2d.h"

USING_NS_CC;

class AreaAlgorithms {
public:
  static void Link(Area *);
  static void Unlink(Area *);
  static std::vector<Cell *> FindAdjacentCells(Cell *cell);
  static void DeleteCellsFromArea(Area &area,
                                  const std::vector<Cell *> &cellsToDelete);
};

#endif // AREAALGORITHMS_H