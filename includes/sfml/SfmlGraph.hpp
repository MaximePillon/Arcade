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

# include <list>
# include <SFML/Graphics/Sprite.hpp>
# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Graphics/Text.hpp>
# include <SFML/Graphics/Font.hpp>
# include "IGraph.hpp"

namespace Arcade
{
  class SfmlGraph : IGraph
  {
  public:
    SfmlGraph();
    virtual ~SfmlGraph();

  public:
    bool init(t_pos const& size, std::string const& name);
    bool close();

  public:
    bool drawText(t_pos const& pos,
		  std::string const& text);
    bool drawSprite(t_pos const& pos,
		    t_image const& image, t_color const& color);
    bool drawBlock(t_pos const& pos,
		   t_color const& color);
    bool setBackground(t_image const& image);

  public:
    bool isOpen() const;
    void refresh();

  protected:
    std::map<std::string, sf::Sprite>	spriteMap;
    std::list<sf::Text> 		textList;
    sf::Sprite				back;
    sf::Font				font;
    sf::RenderWindow			*mainWin;
  };
}
#endif // !SFMLGRAPH_HPP
