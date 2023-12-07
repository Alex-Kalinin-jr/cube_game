#include "areaalgorithms.h"

#include <algorithm>
#include <list>
#include <queue>
#include <vector>

void AreaAlgorithms::Unlink(Area *area) {
  if (area) {
    for (auto &col : area->area_) {
      for (auto &cell : col) {
        cell.left_ = nullptr;
        cell.right_ = nullptr;
        cell.top_ = nullptr;
        cell.bottom_ = nullptr;
      }
    }
  }
}

void AreaAlgorithms::Link(Area *area) {
  Unlink(area);
  if (area) {
    if (area->area_.size() > 1) {
      for (auto left_col = area->area_.begin(),
                right_col = area->area_.begin() + 1;
          right_col != area->area_.end(); ++left_col, ++right_col) {
        for (auto itr_left = left_col->begin(), itr_right = right_col->begin();
            itr_right != right_col->end() && itr_left != left_col->end();
            ++itr_left, ++itr_right) {
          itr_left->right_ = &(*itr_right);
          itr_right->left_ = &(*itr_left);
        }
      }
    }

    for (auto col = area->area_.begin(); col != area->area_.end(); ++col) {
      for (auto itr = col->begin(), top_itr = ++(col->begin());
           top_itr != col->end(); ++itr, ++top_itr) {
        itr->top_ = &(*(top_itr));
        (top_itr)->bottom_ = &(*itr);
      }
    }
  }
}

std::vector<Cell *> AreaAlgorithms::FindAdjacentCells(Cell *cell) {
  std::vector<Cell *> adjacentCells;
  std::queue<Cell *> queue;

  queue.push(cell);

  while (!queue.empty()) {
    Cell *currentCell = queue.front();
    queue.pop();
    adjacentCells.push_back(currentCell);

    if (currentCell->left_ &&
        currentCell->left_->sprite_->getColor() ==
            currentCell->sprite_->getColor() &&
        std::find(adjacentCells.begin(), adjacentCells.end(),
                  currentCell->left_) == adjacentCells.end()) {
      queue.push(currentCell->left_);
    }
    if (currentCell->right_ &&
        currentCell->right_->sprite_->getColor() ==
            currentCell->sprite_->getColor() &&
        std::find(adjacentCells.begin(), adjacentCells.end(),
                  currentCell->right_) == adjacentCells.end()) {
      queue.push(currentCell->right_);
    }
    if (currentCell->top_ &&
        currentCell->top_->sprite_->getColor() ==
            currentCell->sprite_->getColor() &&
        std::find(adjacentCells.begin(), adjacentCells.end(),
                  currentCell->top_) == adjacentCells.end()) {
      queue.push(currentCell->top_);
    }
    if (currentCell->bottom_ &&
        currentCell->bottom_->sprite_->getColor() ==
            currentCell->sprite_->getColor() &&
        std::find(adjacentCells.begin(), adjacentCells.end(),
                  currentCell->bottom_) == adjacentCells.end()) {
      queue.push(currentCell->bottom_);
    }
  }
  return adjacentCells;
}

void AreaAlgorithms::DeleteCellsFromArea(
    Area &area, const std::vector<Cell *> &cellsToDelete) {

  for (const auto &cell : cellsToDelete) {
    for (auto &column : area.area_) {
      auto it = std::find(column.begin(), column.end(), *cell);
      if (it != column.end()) {
        column.erase(it);
        break;
      }
    }
  }

  for (auto col = area.area_.begin(); col != area.area_.end(); ++col) {
    if (col->empty()) {
      auto buff = col - 1;
      area.area_.erase(col);
      col = buff;
    }
  }
}