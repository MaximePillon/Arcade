/*
** Centipede.cpp for cpp_arcade in /home/god/TEK2/C++/cpp_arcade/sources/Centipede/Centipede.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Sun Apr 09 11:15:21 2017 Maxime PILLON
** Last update Sun Apr 09 11:15:21 2017 Maxime PILLON
*/

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <IGraph.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "game/Centipede.hpp"

namespace arcade
{
  /*
  * Block
  */

  // <editor-fold>

  Block::Block(t_color const &color, t_pos const &pos, t_spos const &direction) :
    color(color)
  {
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    this->direction.x = direction.x;
    this->direction.y = direction.y;
  }

  t_pos const& Block::getPos() const
  {
    return this->pos;
  }

  void Block::move()
  {
    this->pos.x += this->direction.x;
    this->pos.y += this->direction.y;
  }

  void Block::changeDirection(t_spos const &direction)
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

  t_spos const& Block::getDirection() const
  {
    return this->direction;
  }

  // </editor-fold>

  /*
  * Event method
  */

  // <editor-fold>

  static void close(void *param)
  {
    arcade::Game *self;

    self = static_cast<arcade::Game *>(param);
    self->quit = true;
  }

  static void goDown(void *param) {}

  static void goUp(void *param) {}

  static void goRight(void *param) {}

  static void goLeft(void *param) {}

  static void restart(void *param)
  {
    arcade::Game *self;

    self = static_cast<arcade::Game *>(param);
    self->restart = true;
  }

  static void goMenu(void *param)
  {
    arcade::Game *self;

    self = static_cast<arcade::Game *>(param);
    self->menu = true;
  }

  // </editor-fold>

  /*
   * Game
   */
  Blockade::Blockade(t_color const &color, t_pos const &pos,
		     t_spos const &direction, size_t Lives)
    : block(color, pos, direction), Lives(Lives) {}

  // <editor-fold>


  // </editor-fold>

  /*
   * Centipede
   */
  Centipede::Centipede(size_t size, t_pos startPos, t_spos dir)
    : size(size), headPos(startPos), dir(dir), body(), turns() {}

  // <editor-fold>


  // </editor-fold>

  /*
   * Game
   */

  Game::Game(IGraph *graph) : border(), score(0), graph(graph), loose(false),
			      Centipedes(), blockades(), bullets(),
			      quit(false), restart(false), menu(false)
  {

  }

  void Game::print() {}

  void Game::move() {}

  void Game::collide() {}

  void Game::saveHighScore() {}

  void Game::getHighScore() {}

  bool Game::play() {}

  // <editor-fold>
}

extern "C" {
bool Play(arcade::IGraph *graph)
{
  bool quit = false;
  bool restart = true;
  arcade::t_pos pos;

  pos.x = WINDOW_WIDTH;
  pos.y = WINDOW_HEIGHT;
  graph->init(pos, "Snake");
  while (restart)
  {
    arcade::Game snake(graph);
    snake.getHighScore();
    quit = snake.play();
    snake.saveHighScore();
    restart = snake.restart;
  }
  graph->close();
  return quit;
}
}