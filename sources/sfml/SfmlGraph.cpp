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
#include "sfml/SfmlGraph.hpp"

bool Arcade::SfmlGraph::init(t_pos const& size, std::string const& name)
{
  this->font.loadFromFile("../../ressources/DejaVuSansMono.ttf");
  this->mainWin = new sf::RenderWindow(sf::VideoMode(size.x, size.y), name);
  return true;
}

bool Arcade::SfmlGraph::drawBlock(t_pos const &pos, t_color const &color)
{
  sf::RectangleShape	tmp;
  sf::Color		col;
  int			same = 0;
  auto			i = block.begin();

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
}

bool Arcade::SfmlGraph::drawText(t_pos const& pos, std::string const& text)
{
  sf::Text	tmp;
  auto		i = this->textList.begin();
  int 		same = 0;

  while (i != this->textList.end())
  {
    if (i->getPosition().x == pos.x && i->getPosition().y == pos.y)
      same = 1;
    i++;
  }
  if (same != 1)
  {
    tmp.setFont(this->font);
    tmp.setScale(sf::Vector2f(10, 10));
    tmp.setPosition(pos.x, pos.y);
    this->textList.push_back(tmp);
  }
  i = this->textList.begin();
  while (i != textList.end())
  {
    this->mainWin->draw(*i);
    i++;
  }
}

bool Arcade::SfmlGraph::isOpen() const
{
 return this->mainWin->isOpen();
}

void Arcade::SfmlGraph::refresh()
{
  this->mainWin->clear();
  this->mainWin->display();
}

bool Arcade::SfmlGraph::close()
{
  this->textList.clear();
  this->spriteMap.clear();
  this->block.clear();
  this->mainWin->close();
  delete this->mainWin;
  return true;
}

