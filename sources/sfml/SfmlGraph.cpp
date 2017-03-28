/*
** SfmlGraph.hpp.cpp for cpp_arcade in /home/loens_g/rendu/TEK2/CPP/cpp_arcade/sources/sfml/SfmlGraph.hpp.cpp
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Tue Mar 28 08:06:59 2017 Gregoire LOENS
** Last update Tue Mar 28 08:07:03 2017 Gregoire LOENS
*/

#include "sfml/SfmlGraph.hpp"

Arcade::SfmlGraph::SfmlGraph()
{}

Arcade::SfmlGraph::~SfmlGraph()
{}

bool Arcade::SfmlGraph::init(t_pos size)
{
  this->mainWin = new sf::RenderWindow(sf::VideoMode(size.x, size.y), "sfml");
  return true;
}

bool Arcade::SfmlGraph::close()
{
  this->mainWin->close();
  delete this->mainWin;
  return true;
}

