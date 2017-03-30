/*
** SfmlGraph.hpp.cpp for cpp_arcade in /home/loens_g/rendu/TEK2/CPP/cpp_arcade/sources/sfml/SfmlGraph.hpp.cpp
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Tue Mar 28 08:06:59 2017 Gregoire LOENS
** Last update Tue Mar 28 08:07:03 2017 Gregoire LOENS
*/

#include "IGraph.hpp"
#include "sfml/SfmlGraph.hpp"

Arcade::SfmlGraph::SfmlGraph()
{}

Arcade::SfmlGraph::~SfmlGraph()
{}

bool Arcade::SfmlGraph::init(t_pos const& size, std::string const& name)
{
  this->font.loadFromFile("../../ressources/DejaVuSansMono.ttf");
  this->mainWin = new sf::RenderWindow(sf::VideoMode(size.x, size.y), name);
  return true;
}

bool Arcade::SfmlGraph::drawBlock(t_pos const &pos, t_color const &color)
{
  (void)(pos);
  (void)(color);
  return true;
}

bool Arcade::SfmlGraph::drawSprite(t_pos const &pos, t_image const &image,
				   t_color const &color)
{
  (void)(pos);
  (void)(image);
  (void)(color);
  return true;
}

bool Arcade::SfmlGraph::drawText(t_pos const& pos, std::string const& text)
{
  sf::Text tmp;

  tmp.setFont(this->font);
  tmp.setPosition(pos.x, pos.y);
  tmp.setScale(sf::Vector2f(10, 10));
  tmp.setString(text);
  this->textList.push_back(tmp);
  return true;
}

bool Arcade::SfmlGraph::isOpen() const
{
 return this->mainWin->isOpen();
}

bool Arcade::SfmlGraph::setBackground(t_image const& image)
{
  sf::Texture texture;

  texture.loadFromFile(image.path);
  back.setTexture(texture);
  back.setPosition(0, 0);
  return true;
}

void Arcade::SfmlGraph::refresh()
{
  this->mainWin->clear();
  this->textList.clear();
}

bool Arcade::SfmlGraph::close()
{
  this->textList.clear();
  this->spriteMap.clear();
  this->mainWin->close();
  delete this->mainWin;
  return true;
}

