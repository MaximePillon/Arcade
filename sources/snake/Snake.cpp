/*
** Snake.cpp for cpp_arcade in /home/soszyn_h/rendu/CPP/cpp_arcade/sources/snake/Snake.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Thu Apr 06 07:08:36 2017 Hugo SOSZYNSKI
** Last update Thu Apr 06 07:08:36 2017 Hugo SOSZYNSKI
*/

#include <IGraph.hpp>
#include "game/Snake.hpp"

namespace arcade
{
  /*
   * Block
   */

  // <editor-fold>

  Block::Block(t_color const &color, t_pos const &pos, t_pos const& direction):
    color(color)
  {
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    this->direction.x = direction.x;
    this->direction.y = direction.y;
  }

  void Block::move()
  {
    this->pos.x += this->direction.x;
    this->pos.y += this->direction.y;
  }

  void Block::changeDirection(t_pos const& direction)
  {
    this->direction.x = direction.x;
    this->direction.y = direction.y;
  }

  void Block::print(IGraph &graph)
  {
    graph.drawBlock(this->pos, this->color);
  }

  bool Block::operator==(Block const &other)
  {
    if (this->pos.x == other.pos.x && this->pos.y == other.pos.y)
      return true;
    return false;
  }

  // </editor-fold>
}