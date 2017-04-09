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
#include <fstream>
#include <sstream>
#include <iostream>
#include "protocol/PSnake.hpp"

namespace arcade
{

  /*
   * Block
   */

  // <editor-fold>

  Block::Block(t_pos const &pos, t_spos const &direction)
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

  Snake::Snake() :
    powerup(), body(), turns(), quit(false)
  {
    t_pos pos;
    t_spos direction;

    // Body
    direction.x = 0;
    direction.y = 1;
    pos.x = 15;
    pos.y = 10;
    for (int i = 0; i < 4; ++i)
    {
      this->body.push_back(Block(pos, direction));
      pos.y -= 1;
    }

    srand(getpid());
    pos.x = rand() % 30;
    pos.y = rand() % 20;
    direction.x = 0;
    direction.y = 0;
    this->powerup.push_back(Block(pos, direction));
  }

  CommandType Snake::readIn() const
  {
    CommandType command;

    std::cin.read(static_cast<char*>(&command), sizeof(CommandType));
    return command;
  }

  void Snake::whereAmI()
  {
    struct WhereAmI *ret = NULL;
    unsigned long size = 0;
    int cpt = 0;

    size = this->body.size();
    ret = static_cast<struct WhereAmI*>(new char[sizeof(struct WhereAmI) +
						 size * sizeof(Position)]);
    ret->type = CommandType::WHERE_AM_I;
    ret->lenght = static_cast<uint16_t>(size);
    for (auto it = this->body.begin(); it != this->body.end(); ++it)
    {
      ret->position[cpt].x = static_cast<uint16_t>((*it).getPos().x);
      ret->position[cpt].y = static_cast<uint16_t>((*it).getPos().y);
      ++cpt;
    }
    std::cout.write(static_cast<char*>(ret), sizeof(struct WhereAmI) +
					     size * sizeof(Position));
    delete[] static_cast<char*>(ret);
  }

  void Snake::getMap(CommandType cmd)
  {
    struct GetMap *map;
    size_t size = 30 * 20;

    map = static_cast<struct GetMap*>(new char[sizeof(struct GetMap) +
					       size * sizeof(TileType)]);
    map->type = cmd;
    map->width = 30;
    map->height = 20;
    for (int i = 0; i < size; ++i)
      map->tile[i] = TileType::EMPTY;
    for (auto it = this->powerup.begin(); it != this->powerup.end(); ++it)
      map->tile[it->getPos().y * 30 + it->getPos().x] = TileType::POWERUP;
    std::cout.write(static_cast<char*>(map), sizeof(struct GetMap) +
					     size * sizeof(TileType));
    delete[] static_cast<char*>(map);
  }

  void Snake::goUp()
  {
    t_pos		head;
    t_spos		dir;

    dir = this->body[0].getDirection();
    if (dir.y)
      return ;
    dir.y = -1;
    dir.x = 0;
    head = this->body[0].getPos();
    this->body[0].changeDirection(dir);
    this->turns.push_back(Block(head, dir));
    this->playRound(CommandType::GO_UP);
  }

  void Snake::goDown()
  {
    t_pos		head;
    t_spos		dir;

    dir = this->body[0].getDirection();
    if (dir.y)
      return ;
    dir.y = 1;
    dir.x = 0;
    head = this->body[0].getPos();
    this->body[0].changeDirection(dir);
    this->turns.push_back(Block(head, dir));
    this->playRound(CommandType::GO_DOWN);
  }

  void Snake::goLeft()
  {
    t_pos		head;
    t_spos		dir;

    dir = this->body[0].getDirection();
    if (dir.y)
      return ;
    dir.y = 0;
    dir.x = -1;
    head = this->body[0].getPos();
    this->body[0].changeDirection(dir);
    this->turns.push_back(Block(head, dir));
    this->playRound(CommandType::GO_LEFT);
  }

  void Snake::goRight()
  {
    t_pos		head;
    t_spos		dir;

    dir = this->body[0].getDirection();
    if (dir.y)
      return ;
    dir.y = 0;
    dir.x = 1;
    head = this->body[0].getPos();
    this->body[0].changeDirection(dir);
    this->turns.push_back(Block(head, dir));
    this->playRound(CommandType::GO_RIGHT);
  }

  void Snake::goForward()
  {
    this->playRound(CommandType::GO_FORWARD);
  }

  void Snake::playRound(CommandType cmd)
  {
    this->move();
    this->collide();
    if (!this->quit)
      this->getMap(cmd);
  }

  void Snake::illegal()
  {
    this->getMap(CommandType::ILLEGAL);
  }

  bool Snake::play()
  {
    while (!quit)
    {
      switch (this->readIn()) {
	case CommandType::WHERE_AM_I:
	  this->whereAmI();
	  break;

	case CommandType::GET_MAP:
	  this->getMap(CommandType::GET_MAP);
	  break;

	case CommandType::GO_UP:
	  this->goUp();
	  break;

	case CommandType::GO_DOWN:
	  this->goDown();
	  break;

	case CommandType::GO_LEFT:
	  this->goLeft();
	  break;

	case CommandType::GO_RIGHT:
	  this->goRight();
	  break;

	case CommandType::GO_FORWARD:
	  this->goForward();
	  break;

	case CommandType::PLAY:
	  this->playRound(CommandType::PLAY);
	  break;

	default:
	  this->illegal();
	  break;
      }
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
    t_pos pos;
    t_spos direction;

    if (this->body[0].getPos().x >= 30 || this->body[0].getPos().y >= 20)
	this->quit = true;
    for (auto it = ++this->body.begin(); it != this->body.end(); ++it)
      if (*it == this->body[0])
	this->quit = true;
    for (auto it = this->powerup.begin(); it != this->powerup.end(); ++it)
      if (*it == this->body[0])
      {
	this->powerup.erase(it);
	pos.x = rand() % 30;
	pos.y = rand() % 20;
	direction.x = 0;
	direction.y = 0;
	this->powerup.push_back(Block(pos, direction));
	pos = this->body[this->body.size() - 1].getPos();
	direction = this->body[this->body.size() - 1].getDirection();
	pos.x -= direction.x;
	pos.y -= direction.y;
	this->body.push_back(Block(pos, direction));
      }
  }

  // </editor-fold>

}

extern "C" {
void Play(void)
{
  arcade::Snake snake;
  snake.play();
}
}