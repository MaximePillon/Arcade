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
    color(color), pos(), direction()
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

  static void goDown(void *param)
  {
    arcade::Game	*self;
    t_pos		pos;
    t_spos		dir;

    self = static_cast<arcade::Game *>(param);
    dir = self->player->getDirection();
    dir.y = 1;
    dir.x = 0;
    pos = self->player->getPos();
    self->player->changeDirection(dir);

  }

  static void goUp(void *param)
  {
    arcade::Game	*self;
    t_pos		pos;
    t_spos		dir;

    self = static_cast<arcade::Game *>(param);
    dir = self->player->getDirection();
    dir.y = -1;
    dir.x = 0;
    pos = self->player->getPos();
    self->player->changeDirection(dir);
  }

  static void goRight(void *param)
  {
    arcade::Game	*self;
    t_pos		pos;
    t_spos		dir;

    self = static_cast<arcade::Game *>(param);
    dir = self->player->getDirection();
    dir.y = 0;
    dir.x = 1;
    pos = self->player->getPos();
    self->player->changeDirection(dir);
  }

  static void goLeft(void *param)
  {
    arcade::Game	*self;
    t_pos		pos;
    t_spos		dir;

    self = static_cast<arcade::Game *>(param);
    dir = self->player->getDirection();
    dir.y = 0;
    dir.x = -1;
    pos = self->player->getPos();
    self->player->changeDirection(dir);
  }

  static void shoot(void *param)
  {
    arcade::Game	*self;
    t_pos		pos;
    t_spos		dir;
    t_color		color;

    self = static_cast<arcade::Game *>(param);
    if (!self->bullets) {
      dir.y = -1;
      dir.x = 0;
      color.full = 0x00FF00FF;
      pos = self->player->getPos();
      pos.y -= 1;
      self->bullets = new Block(color, pos, dir);
    }
  }

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
			      Centipedes(), blockades(), quit(false),
			      restart(false), menu(false), left_turn(10)
  {
    t_color			color;
    t_pos			pos;
    t_spos			direction;

    //border
    color.full = 0xFFFFFFFF;
    direction.x = 0;
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
    pos.y = WINDOW_HEIGHT - 5;
    for (pos.x = 0; pos.x < WINDOW_WIDTH; ++(pos.x))
      this->border.push_back(Block(color, pos, direction));

    // blockades
    color.full = 0xFFFF00FF;
    srand(getpid());
    for (unsigned int x = 0; x < 15; ++x)
    {
      pos.x = rand() % (WINDOW_WIDTH - 2) + 1;
      pos.y = rand() % (WINDOW_HEIGHT - 8) + 3;
      this->blockades.push_back(Blockade(color, pos, direction));
    }

    // player
    color.full = 0xFF00FFFF;
    pos.x = 10;
    pos.y = WINDOW_HEIGHT - 2;
    this->player = new Block(color, pos, direction);

    // set my bullets
    this->bullets = nullptr;

    // Centipede
    color.full = 0x00FFFFFF;
    direction.x = 1;
    pos.x = 12;
    pos.y = 5;
    this->Centipedes.push_back(Centipede(6, pos, direction));
    for (int i = 0; i < 6; ++i)
    {
      this->Centipedes[0].body.push_back(Block(color, pos, direction));
      pos.x -= 1;
    }
  }

  void Game::saveHighScore()
  {
    std::ofstream oFile;

    if (this->highScore < this->score)
    {
      oFile.open("centipede.score", std::ios::out);
      if (oFile)
      {
	oFile << this->name << "\n" << this->score;
	oFile.close();
      }
      else
	std::cerr << "Unable to open the score file !"  << std::endl;
    }
  }


  void Game::getHighScore()
  {
    std::ifstream file;

    file.open("centipede.score");
    if (file.is_open())
    {
      file >> this->highScoreName >> this->highScore;
      file.close();
    }
    else
    {
      this->highScore = 0;
    }
  }


  void Game::move()
  {
    t_pos	tmp;
    t_spos	Newdir;

    if (bullets)
      bullets->move();
    player->move();
    for (auto it = this->Centipedes.begin(); it != this->Centipedes.end(); ++it)
    {
      for (std::vector<Block>::iterator it2 = it->body.begin(); it2 != it->body.end(); ++it2)
      {
	Newdir.x = it2->getDirection().x;
	tmp = it2->getPos();
	tmp.x += it2->getDirection().x;
	tmp.y += it2->getDirection().y;
	for (std::vector<Blockade>::iterator it3 = this->blockades.begin(); it3 != this->blockades.end(); ++it3)
	  if ((*it3).block.getPos().x == tmp.x && (*it3).block.getPos().y == tmp.y)
	  {
	    Newdir.x = it2->getDirection().x * -1;
	    Newdir.y = 1;
	    it2->changeDirection(Newdir);
	  }
	for (std::vector<Block>::iterator it3 = this->border.begin(); it3 != this->border.end(); ++it3)
	  if ((*it3).getPos().x == tmp.x && (*it3).getPos().y == tmp.y)
	  {
	    Newdir.x = it2->getDirection().x * -1;
	    Newdir.y = 1;
	    it2->changeDirection(Newdir);
	  }
	it2->move();
	Newdir.y = 0;
	it2->changeDirection(Newdir);
      }
    }
  }


  void Game::collide()
  {
    for (auto it = this->border.begin(); it != this->border.end(); ++it)
      if (*it == *(this->player))
	this->loose = true;
    for (std::vector<Centipede>::iterator it = this->Centipedes.begin(); it != this->Centipedes.end(); ++it)
      for (std::vector<Block>::iterator it2 = it->body.begin(); it2 != it->body.end(); ++it2)
      {
	if ((*it2) == *(this->player))
	{
	  this->loose = true;
	  break;
	}
      }
    if (!bullets)
      return ;
    for (auto it = this->border.begin(); it != this->border.end(); ++it)
      if (*it == *(this->bullets) && (it->getPos()).y != (WINDOW_HEIGHT - 5))
      {
	delete(bullets);
	bullets = NULL;
	break ;
      }
    if (!bullets)
      return ;
    for (std::vector<Blockade>::iterator it = this->blockades.begin(); it != this->blockades.end(); ++it)
      if ((*it).block == *(this->bullets))
      {
	delete(bullets);
	bullets = NULL;
	(*it).Lives -= 1;
	if ((*it).Lives == 0)
	  blockades.erase(it);
	this->score += 10;
	break ;
      }
    if (!bullets)
      return ;

    for (std::vector<Centipede>::iterator it = this->Centipedes.begin(); it != this->Centipedes.end(); ++it)
      for (std::vector<Block>::iterator it2 = it->body.begin(); it2 != it->body.end(); ++it2)
      {
	if ((*it2) == *(this->bullets))
	{
	  this->score += 50;
	  if (it2 == it->body.begin() || it2 == --it->body.end())
	  {
	    it->body.erase(it2);
	    ++it2;
	  }
	  else
	  {
	    t_spos Dir;
	    it->body.erase(it2);
	    ++it2;
	    while (it2 != it->body.end())
	    {
	      // block configuration
	      Dir.y = -1;
	      Dir.x = (*it2).getDirection().x * -1;
	      (*it2).changeDirection(Dir);
	      (*it2).move();
	      Dir.y = 0;
	      (*it2).changeDirection(Dir);
	      ++it2;
	    }
	  }
	  return ;
	}
      }
  }

  void Game::print()
  {
    t_pos pos;
    std::ostringstream out;

    for (auto it = this->border.begin(); it != this->border.end(); ++it)
      (*it).print(*(this->graph));
    for (std::vector<Centipede>::iterator it = this->Centipedes.begin(); it != this->Centipedes.end(); ++it)
      for (std::vector<Block>::iterator it2 = it->body.begin(); it2 != it->body.end(); ++it2)
      (*it2).print(*(this->graph));
    for (std::vector<Blockade>::iterator it = this->blockades.begin(); it != this->blockades.end(); ++it)
	(*it).block.print(*(this->graph));
    if (bullets)
      bullets->print(*(this->graph));
    player->print(*(this->graph));

    pos.x = 0;
    pos.y = 0;
    out << "Highscore by " << this->highScoreName << ": " << this->highScore;
    this->graph->drawText(pos, out.str());
    pos.y = 1;
    out.str("");
    out << "Score: " << this->score;
    this->graph->drawText(pos, out.str());
    out.str("");
    pos.x  = WINDOW_WIDTH - 3;
    out << this->name;
    this->graph->drawText(pos, out.str());
  }

  bool Game::play()
  {
    graph->registerEvent(CommandType::CLOSE, arcade::close, this);
    graph->registerEvent(CommandType::GO_DOWN, arcade::goDown, this);
    graph->registerEvent(CommandType::GO_UP, arcade::goUp, this);
    graph->registerEvent(CommandType::GO_RIGHT, arcade::goRight, this);
    graph->registerEvent(CommandType::GO_LEFT, arcade::goLeft, this);
    graph->registerEvent(CommandType::RESTART, arcade::restart, this);
    graph->registerEvent(CommandType::MENU, arcade::goMenu, this);
    graph->registerEvent(CommandType::SHOOT, arcade::shoot, this);
    while (graph->isOpen() && !quit && !restart && !menu && !loose && left_turn)
    {
      usleep(100000);
      this->graph->execEvents();
      this->move();
      this->collide();
      this->graph->clear();
      this->print();
      this->graph->refresh();
      if (this->Centipedes.begin()->body.begin()->getPos().y == (WINDOW_HEIGHT - 1))
      {
	t_color			color;
	t_pos			pos;
	t_spos			direction;

	--left_turn;
	if (score > (10 * this->Centipedes.begin()->body.size()))
	  score -= (10 * this->Centipedes.begin()->body.size());
	else
	  score = 0;
	color.full = 0x00FFFFFF;
	direction.x = 1;
	direction.y = 0;
	pos.x = 12;
	pos.y = 5;
	this->Centipedes.begin()->body.clear();
	this->Centipedes.clear();
	this->Centipedes.push_back(Centipede(6, pos, direction));
	for (int i = 0; i < 6; ++i)
	{
	  this->Centipedes[0].body.push_back(Block(color, pos, direction));
	  pos.x -= 1;
	}
      }
      if (this->Centipedes.begin()->body.empty())
      {
	t_color			color;
	t_pos			pos;
	t_spos			direction;

	--left_turn;
	score += 200;
	color.full = 0x00FFFFFF;
	direction.x = 1;
	direction.y = 0;
	pos.x = 12;
	pos.y = 5;
	this->Centipedes.begin()->body.clear();
	this->Centipedes.clear();
	this->Centipedes.push_back(Centipede(6, pos, direction));
	for (int i = 0; i < 6; ++i)
	{
	  this->Centipedes[0].body.push_back(Block(color, pos, direction));
	  pos.x -= 1;
	}
      }
    }
    return this->quit;
  }

  // <editor-fold>
}

extern "C" {
bool gPlay(arcade::IGraph *graph, std::string const& player)
{
  bool quit = false;
  bool restart = true;
  arcade::t_pos pos;

  pos.x = WINDOW_WIDTH;
  pos.y = WINDOW_HEIGHT;
  graph->init(pos, "Centipede");
  while (restart)
  {
    arcade::Game centipede(graph);
    centipede.name = player;
    centipede.getHighScore();
    quit = centipede.play();
    centipede.saveHighScore();
    restart = centipede.restart;
  }
  graph->close();
  return quit;
}
}