/*
** Map.hpp for cpp_arcade in /home/soszyn_h/rendu/CPP/cpp_arcade/includes/game/Map.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Wed Apr 05 15:11:58 2017 Hugo SOSZYNSKI
** Last update Wed Apr 05 15:11:58 2017 Hugo SOSZYNSKI
*/

#ifndef MAP_HPP_
# define MAP_HPP_

# include <vector>
#include <IGraph.hpp>
# include "arcade_protocol.hpp"

namespace arcade
{
  class Map
  {
  public:
    Map(uint16_t width, uint16_t height);
    ~Map();

  public:
    uint16_t getWidth() const;
    uint16_t getHeight() const;
    GetMap const* getMap() const;
    TileType getTile(t_pos const& pos) const;

  public:
    void setTile(t_pos const& pos, TileType type);

  protected:
    arcade::GetMap	*_map;

  };
}

#endif // !MAP_HPP_
