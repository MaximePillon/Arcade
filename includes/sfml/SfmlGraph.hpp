/*
** SfmlGraph.hpp for cpp_arcade in /home/loens_g/rendu/TEK2/CPP/cpp_arcade/includes/sfml/SfmlGraph.hpp
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Tue Mar 28 07:42:28 2017 Gregoire LOENS
** Last update Tue Mar 28 07:42:28 2017 Gregoire LOENS
*/

#ifndef SFMLGRAPH_HPP
# define SFMLGRAPH_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "IGraph.hpp"

namespace Arcade
{
  class SfmlGraph : IGraph
  {
  public:
    SfmlGraph();
    virtual ~SfmlGraph();

  public:
    bool init(t_pos size);
    bool close();

  public:
    bool drawText(t_pos pos, std::string text);
    bool drawSprite(t_pos pos, t_image image, t_color color);
    bool drawBlock(t_pos pos, t_color color);
    bool setBackground(t_image image);

  protected:
    sf::RenderWindow	*mainWin;
  };
}
#endif //CPP_ARCADE_SFMLGRAPH_HPP
