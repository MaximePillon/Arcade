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
#include "sfml/SfmlGraph.hpp"

namespace arcade
{
  bool SfmlGraph::init(t_pos const &size, std::string const &name)
  {
    this->font.loadFromFile("../../ressources/DejaVuSansMono.ttf");
    this->mainWin = new sf::RenderWindow(sf::VideoMode(size.x, size.y), name);
    this->keyboard[CommandType::GO_UP] = sf::Keyboard::Up;
    this->keyboard[CommandType::GO_DOWN] = sf::Keyboard::Down;
    this->keyboard[CommandType::GO_RIGHT] = sf::Keyboard::Right;
    this->keyboard[CommandType::GO_LEFT] = sf::Keyboard::Left;
    this->keyboard[CommandType::SHOOT] = sf::Keyboard::Space;
    return true;
  }

  bool SfmlGraph::drawBlock(t_pos const &pos, t_color const &color)
  {
    sf::RectangleShape tmp;
    sf::Color col;
    int same = 0;
    auto i = this->block.begin();

    while (i != this->block.end())
    {
      if (i->getPosition().x == pos.x && i->getPosition().y == pos.y)
	same = 1;
      i++;
    }
    if (same != 1)
    {
      col.a = color.argb[0];
      col.r = color.argb[1];
      col.g = color.argb[2];
      col.b = color.argb[3];
      tmp.setPosition(pos.x, pos.y);
      tmp.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
      tmp.setFillColor(col);
      this->block.push_back(tmp);
    }
    i = this->block.begin();
    while (i != this->block.end())
    {
      this->mainWin->draw(*i);
      i++;
    }
    return true;
  }

  bool SfmlGraph::drawText(t_pos const &pos, std::string const &text)
  {
    sf::Text tmp;
    auto i = this->textList.begin();
    int same = 0;

    while (i != this->textList.end())
    {
      if (i->getPosition().x == pos.x && i->getPosition().y == pos.y)
	same = 1;
      i++;
    }
    if (same != 1)
    {
      tmp.setString(text);
      tmp.setFont(this->font);
      tmp.setScale(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
      tmp.setPosition(pos.x, pos.y);
      this->textList.push_back(tmp);
    }
    i = this->textList.begin();
    while (i != textList.end())
    {
      this->mainWin->draw(*i);
      i++;
    }
    return true;
  }

  void SfmlGraph::execEvents()
  {
    while (this->mainWin->pollEvent(this->event))
      for (auto &it : this->keyboard)
	if (it.second == this->event.key.code)
	  this->eventMap[it.first].hdl(this->eventMap[it.first].param);
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
    this->mainWin->clear();
    this->mainWin->display();
  }

  bool SfmlGraph::close()
  {
    this->textList.clear();
    this->block.clear();
    this->mainWin->close();
    delete this->mainWin;
    return true;
  }
}
