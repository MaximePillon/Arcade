/*
** SfmlGraph.hpp.cpp for cpp_arcade in /home/loens_g/rendu/TEK2/CPP/cpp_arcade/sources/sfml/SfmlGraph.hpp.cpp
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Tue Mar 28 08:06:59 2017 Gregoire LOENS
** Last update Tue Mar 28 08:07:03 2017 Gregoire LOENS
*/

#include <IGraph.hpp>
#include <iostream>
#include <sfml/SfmlGraph.hpp>
#include <zconf.h>
#include "sfml/SfmlGraph.hpp"

namespace arcade
{

  void SfmlGraph::initMap()
  {
    this->keyboard[CommandType::GO_UP] = sf::Keyboard::Up;
    this->keyboard[CommandType::GO_DOWN] = sf::Keyboard::Down;
    this->keyboard[CommandType::GO_RIGHT] = sf::Keyboard::Right;
    this->keyboard[CommandType::GO_LEFT] = sf::Keyboard::Left;
    this->keyboard[CommandType::CLOSE] = sf::Keyboard::Escape;
    this->keyboard[CommandType::PREVIOUS_GL] = sf::Keyboard::Num2;
    this->keyboard[CommandType::NEXT_GL] = sf::Keyboard::Num3;
    this->keyboard[CommandType::PREVIOUS_GAME] = sf::Keyboard::Num4;
    this->keyboard[CommandType::NEXT_GAME] = sf::Keyboard::Num5;
    this->keyboard[CommandType::RESTART] = sf::Keyboard::Num8;
    this->keyboard[CommandType::MENU] = sf::Keyboard::Num9;
    this->keyboard[CommandType::PLAY] = sf::Keyboard::Return;
    this->keyboard[CommandType::SHOOT] = sf::Keyboard::Space;
  }

  bool SfmlGraph::init(t_pos const &size, std::string const &name)
  {
    this->font.loadFromFile("res/DejaVuSansMono.ttf");
    this->mainWin = new sf::RenderWindow(sf::VideoMode(size.x * BLOCK_SIZE, size.y * BLOCK_SIZE), name);
    this->initMap();
    return true;
  }

  bool SfmlGraph::drawBlock(t_pos const &pos, t_color const &color)
  {
    sf::RectangleShape tmp;
    sf::Color col;

    col.a = color.argb[0];
    col.r = color.argb[1];
    col.g = color.argb[2];
    col.b = color.argb[3];
    tmp.setPosition(pos.x * BLOCK_SIZE, pos.y * BLOCK_SIZE);
    tmp.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    tmp.setFillColor(col);
    this->mainWin->draw(tmp);
    return true;
  }

  bool SfmlGraph::drawText(t_pos const &pos, std::string const &text)
  {
    sf::Text	tmp;

    tmp.setFont(this->font);
    tmp.setPosition(pos.x * BLOCK_SIZE, pos.y * BLOCK_SIZE);
    tmp.setString(text);
    tmp.setScale(0.7, 0.7);
    this->mainWin->draw(tmp);
    return true;
  }

  void SfmlGraph::gstKey()
  {
    if (this->event.key.code == sf::Keyboard::Escape)
      this->mainWin->close();
    for (auto it : this->keyboard)
      if (it.second == this->event.key.code)
      {
	if (this->eventMap[it.first].hdl)
	  this->eventMap[it.first].hdl(this->eventMap[it.first].param);
      }
  }

  void SfmlGraph::execEvents()
  {
    while (this->mainWin->pollEvent(this->event))
    {
      switch (this->event.type)
      {
	case sf::Event::Closed:
	  this->close();
	  break;

	case sf::Event::KeyPressed:
	  this->gstKey();
	  break;

	default:
	  break;
      }
    }
  }

  void SfmlGraph::registerEvent(CommandType type,
				event_handler hdl,
				void *param)
  {
    handler_t	tmp;

    tmp.hdl = hdl;
    tmp.param = param;
    this->eventMap[type] = tmp;
  }

  bool SfmlGraph::isOpen() const
  {
    return this->mainWin->isOpen();
  }

  void SfmlGraph::refresh()
  {
    this->mainWin->display();
    this->mainWin->clear();
  }

  bool SfmlGraph::setBackground(t_color const& color)
  {
    sf::Color		tmp;

    tmp.a  = color.argb[0];
    tmp.r  = color.argb[1];
    tmp.g  = color.argb[2];
    tmp.b  = color.argb[3];
    this->background.setPosition(0, 0);
    this->background.setScale(WINDOW_WIDTH * BLOCK_SIZE,
			      WINDOW_HEIGHT * BLOCK_SIZE);
    this->background.setFillColor(tmp);
    this->mainWin->draw(background);
    return true;
  }

  bool SfmlGraph::close()
  {
    this->mainWin->close();
    return true;
  }
}

extern "C"
{
arcade::IGraph* create_graph()
{
  arcade::IGraph	*newGraph;

  newGraph = new arcade::SfmlGraph();
  return newGraph;
}
}