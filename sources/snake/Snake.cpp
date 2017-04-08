/*
** Snake.cpp for cpp_arcade in /home/soszyn_h/rendu/CPP/cpp_arcade/sources/snake/Snake.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Thu Apr 06 07:08:36 2017 Hugo SOSZYNSKI
** Last update Thu Apr 06 07:08:36 2017 Hugo SOSZYNSKI
*/

#include <unistd.h>
#include <iostream>
#include <IGraph.hpp>
#include "arcade_protocol.hpp"
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

  /*
   * Snake
   */

  // <editor-fold>

  Snake::Snake(IGraph* graph):
    powerup(), body(), turns(), border(), score(0), graph(graph), quit(false)
  {
    t_color color;
    t_pos   pos;
    t_pos   direction;

    // Body
    color.argb[0] = 255;
    color.argb[1] = 255;
    color.argb[2] = 255;
    color.argb[3] = 0;
    direction.x = 0;
    direction.y = 1;
    pos.x = 16;
    pos.y = 12;
    for (int i = 0; i < 4; ++i)
    {
      this->body.push_back(Block(color, pos, direction));
      pos.y += 1;
    }

    // Borders
    color.argb[0] = 255;
    color.argb[1] = 255;
    color.argb[2] = 255;
    color.argb[3] = 255;
    direction.y = 0;
    pos.y = 2;
    for (pos.x = 0; pos.x < WINDOW_WIDTH; ++(pos.x))
      this->border.push_back(Block(color, pos, direction));
    pos.x = 0;
    for (pos.y = 2; pos.y < WINDOW_HEIGHT; ++(pos.y))
      this->border.push_back(Block(color, pos, direction));
    pos.x = WINDOW_WIDTH - 1;
    for (pos.y = 2; pos.y < WINDOW_HEIGHT; ++(pos.y))
      this->border.push_back(Block(color, pos, direction));
    pos.y = WINDOW_HEIGHT - 1;
    for (pos.x = 0; pos.x < WINDOW_WIDTH; ++(pos.x))
      this->border.push_back(Block(color, pos, direction));
  }

  void Snake::print()
  {
    for (auto it = this->border.begin(); it != this->border.end(); ++it)
      (*it).print(*(this->graph));
    for (auto it = this->body.begin(); it != this->body.end(); ++it)
      (*it).print(*(this->graph));
    for (auto it = this->powerup.begin(); it != this->powerup.end(); ++it)
      (*it).print(*(this->graph));
  }

  // </editor-fold>

/*
 * Event method
 */
static void close(void* param)
{
  arcade::Snake* self;

  self = static_cast<arcade::Snake*>(param);
  self->quit = true;
}

bool arcade::Snake::play()
{
  graph->registerEvent(CommandType::CLOSE, arcade::close, this);
  while (graph->isOpen() && !quit)
  {
    this->graph->execEvents();
    this->graph->clear();
    this->print();
    this->graph->refresh();
  }
  return this->quit;
}
}

extern "C" {
bool Play(arcade::IGraph *graph)
{
  arcade::Snake snake(graph);

  return snake.play();
}
}