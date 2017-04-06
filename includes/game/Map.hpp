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
  /// \class Map
  class Map
  {
  public:
    Map(uint16_t width, uint16_t height);
    ~Map();

  public:
    uint16_t getWidth() const; //!< Return the map width
    uint16_t getHeight() const; //!< Return the map height
    GetMap const* getMap() const; //!< Return the map
    TileType getTile(t_pos const& pos) const; //!< Return tile

  public:
    void setTile(t_pos const& pos, TileType type); //! set tile

  protected:
    arcade::GetMap	map; //!< Protocol map structure

  };
}

#endif // !MAP_HPP_
