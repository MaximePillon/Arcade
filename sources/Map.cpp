/*
** Map.cpp for cpp_arcade in /home/soszyn_h/rendu/CPP/cpp_arcade/sources/Map.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Thu Apr 06 07:12:22 2017 Hugo SOSZYNSKI
** Last update Thu Apr 06 07:12:22 2017 Hugo SOSZYNSKI
*/

#include <IGraph.hpp>
#include "game/Map.hpp"

namespace arcade
{
  Map::Map(uint16_t width, uint16_t height)
  {
    this->map.tile = new TileType[width * height];
    this->map.height = height;
    this->map.width = width;
  }

  Map::~Map()
  {
    delete[] this->map.tile;
  }

  uint16_t Map::getWidth() const
  {
    return this->map.width;
  }

  uint16_t Map::getHeight() const
  {
    return this->map.height;
  }

  GetMap const* Map::getMap() const
  {
    return &(this->map);
  }

  TileType Map::getTile(t_pos const &pos) const
  {
    return this->map.tile[pos.y * this->map.width + pos.x];
  }

  void Map::setTile(t_pos const &pos, TileType type)
  {
    this->map.tile[pos.y * this->map.width + pos.x] = type;
  }
}