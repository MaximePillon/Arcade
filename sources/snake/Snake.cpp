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
#include <algorithm>
#include <IGraph.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "game/Snake.hpp"

namespace arcade
{

  /*
   * Event method
   */

  // <editor-fold>

  static void close(void *param)
  {
    arcade::Snake *self;

    self = static_cast<arcade::Snake *>(param);
    self->quit = true;
  }

  static void goDown(void *param)
  {
    arcade::Snake	*self;
    t_pos		head;
    t_spos		dir;
    t_color		color;

    self = static_cast<arcade::Snake *>(param);
    dir = self->body[0].getDirection();
    if (dir.y)
      return ;
    color.full = 0x00000000;
    dir.y = 1;
    dir.x = 0;
    head = self->body[0].getPos();
    self->body[0].changeDirection(dir);
    self->turns.push_back(Block(color, head, dir));
  }

  static void goUp(void *param)
  {

    arcade::Snake	*self;
    t_pos		head;
    t_spos		dir;
    t_color		color;

    self = static_cast<arcade::Snake *>(param);
    dir = self->body[0].getDirection();
    if (dir.y)
      return ;
    color.full = 0x00000000;
    dir.y = -1;
    dir.x = 0;
    head = self->body[0].getPos();
    self->body[0].changeDirection(dir);
    self->turns.push_back(Block(color, head, dir));
  }

  static void goRight(void *param)
  {
    arcade::Snake	*self;
    t_pos		head;
    t_spos		dir;
    t_color		color;

    self = static_cast<arcade::Snake *>(param);
    dir = self->body[0].getDirection();
    if (dir.x)
      return ;
    color.full = 0x00000000;
    dir.y = 0;
    dir.x = 1;
    head = self->body[0].getPos();
    self->body[0].changeDirection(dir);
    self->turns.push_back(Block(color, head, dir));
  }

  static void goLeft(void *param)
  {

    arcade::Snake	*self;
    t_pos		head;
    t_spos		dir;
    t_color		color;

    self = static_cast<arcade::Snake *>(param);
    dir = self->body[0].getDirection();
    if (dir.x)
      return ;
    color.full = 0x00000000;
    dir.y = 0;
    dir.x = -1;
    head = self->body[0].getPos();
    self->body[0].changeDirection(dir);
    self->turns.push_back(Block(color, head, dir));
  }

  static void restart(void *param)
  {
    arcade::Snake *self;

    self = static_cast<arcade::Snake *>(param);
    self->restart = true;
  }

  static void goMenu(void *param)
  {
    arcade::Snake *self;

    self = static_cast<arcade::Snake *>(param);
    self->menu = true;
  }

  // </editor-fold>

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
   * Snake
   */

  // <editor-fold>

  Snake::Snake(IGraph *graph) :
    powerup(), border(), score(0), graph(graph), loose(false), body(),
    turns(), quit(false), restart(false), menu(false)
  {
    t_color color;
    t_pos pos;
    t_spos direction;

    // Body
    color.full = 0x00FFFFFF;
    direction.x = 0;
    direction.y = 1;
    pos.x = 16;
    pos.y = 12;
    for (int i = 0; i < 4; ++i)
    {
      this->body.push_back(Block(color, pos, direction));
      pos.y -= 1;
    }

    // Borders
    color.full = 0xFFFFFFFF;
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
    color.full = 0x0000FFFF;
    srand(getpid());
    pos.x = rand() % (WINDOW_WIDTH - 2) + 1;
    pos.y = rand() % (WINDOW_HEIGHT - 4) + 3;
    direction.x = 0;
    direction.y = 0;
    this->powerup.push_back(Block(color, pos, direction));
  }

  void Snake::print()
  {
    t_pos pos;
    std::ostringstream out;

    for (auto it = this->border.begin(); it != this->border.end(); ++it)
      (*it).print(*(this->graph));
    for (auto it = this->body.begin(); it != this->body.end(); ++it)
      (*it).print(*(this->graph));
    for (auto it = this->powerup.begin(); it != this->powerup.end(); ++it)
      (*it).print(*(this->graph));
    pos.x = 0;
    pos.y = 0;
    out << "Highscore: " << this->highScore;
    this->graph->drawText(pos, out.str());
    pos.y = 1;
    out.str("");
    out << "Score: " << this->score;
    this->graph->drawText(pos, out.str());
  }

  bool Snake::play()
  {
    graph->registerEvent(CommandType::CLOSE, arcade::close, this);
    graph->registerEvent(CommandType::GO_DOWN, arcade::goDown, this);
    graph->registerEvent(CommandType::GO_UP, arcade::goUp, this);
    graph->registerEvent(CommandType::GO_RIGHT, arcade::goRight, this);
    graph->registerEvent(CommandType::GO_LEFT, arcade::goLeft, this);
    graph->registerEvent(CommandType::RESTART, arcade::restart, this);
    graph->registerEvent(CommandType::MENU, arcade::goMenu, this);
    while (graph->isOpen() && !quit && !restart && !menu && !loose)
    {
      usleep(100000);
      this->graph->execEvents();
      this->move();
      this->collide();
      this->graph->clear();
      this->print();
      this->graph->refresh();
    }
    return this->quit;
  }

  void Snake::move()
  {
    for (auto it = this->body.begin(); it != this->body.end(); ++it)
    {
      it->move();
      auto turn = std::find(this->turns.begin(), this->turns.end(), *it);
      if (turn != this->turns.end())
      {
	it->changeDirection(turn->getDirection());
	std::vector<Block>::iterator tmp = it;
	if (++tmp == this->body.end())
	  this->turns.erase(turn);
      }
    }
  }

  void Snake::collide()
  {
    t_color color;
    t_pos pos;
    t_spos direction;

    for (auto it = this->border.begin(); it != this->border.end(); ++it)
      if (*it == this->body[0])
	this->loose = true;
    for (auto it = ++this->body.begin(); it != this->body.end(); ++it)
      if (*it == this->body[0])
	this->loose = true;
    for (auto it = this->powerup.begin(); it != this->powerup.end(); ++it)
      if (*it == this->body[0])
      {
	this->score += 10;
	this->powerup.erase(it);
	color.full = 0x0000FFFF;
	pos.x = rand() % (WINDOW_WIDTH - 2) + 1;
	pos.y = rand() % (WINDOW_HEIGHT - 4) + 3;
	direction.x = 0;
	direction.y = 0;
	this->powerup.push_back(Block(color, pos, direction));
	color.full = 0x00FFFFFF;
	pos = this->body[this->body.size() - 1].getPos();
	direction = this->body[this->body.size() - 1].getDirection();
	pos.x -= direction.x;
	pos.y -= direction.y;
	this->body.push_back(Block(color, pos, direction));
      }
  }

  void Snake::saveHighScore()
  {
    std::ofstream oFile;

    if (this->highScore < this->score)
    {
      oFile.open("score", std::ios::out);
      if (oFile)
      {
	oFile << this->score;
	oFile.close();
      }
      else
	std::cerr << "Unable to open the score file !"  << std::endl;
    }
  }


  void Snake::getHighScore()
  {
    std::ifstream file("score", std::ios::in);


    if (file)
    {
      file >>this->highScore;
      file.close();
    }
    else
      this->highScore = 0;
  }

  // </editor-fold>

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
    arcade::Snake snake(graph);
    snake.getHighScore();
    quit = snake.play();
    snake.saveHighScore();
    restart = snake.restart;
  }
  graph->close();
  return quit;
}
}