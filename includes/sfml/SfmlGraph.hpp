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
# include <map>
# include <SFML/Graphics/Sprite.hpp>
# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Graphics/Text.hpp>
# include <SFML/Graphics/Font.hpp>
# include <SFML/Graphics/RectangleShape.hpp>
# include <SFML/Window/Event.hpp>
# include "IGraph.hpp"
# include "arcade_protocol.hpp"

namespace arcade
{

  /// \class SfmlGraph
  class SfmlGraph : IGraph
  {
  public:
    SfmlGraph() {};
    virtual ~SfmlGraph() {};

  public:
    bool init(t_pos const& size, std::string const& name);
    void initMap();
    bool close();

  public:
    bool drawText(t_pos const& pos,
		  std::string const& text);
    bool drawBlock(t_pos const& pos,
		   t_color const& color);
    bool setBackground(t_color const& color);

  public:
    void execEvents();
    void registerEvent(CommandType type,
		       event_handler hdl,
		       void* param);

  public:
    bool isOpen() const;
    void refresh();

  protected:
    std::map<CommandType, sf::Keyboard::Key>	keyboard; //!< Map of keyboard macros
    std::map<CommandType, handler_t>		eventMap; //!< Map of handler
    std::list<sf::Text> 			textList; //!< List of text object
    std::list<sf::RectangleShape>		block; //!< List of block
    sf::Font					font; //!< Font of the project
    sf::Event					event; //!< Keyboard Event
    sf::RectangleShape				background; //!< Background

    sf::RenderWindow*				mainWin; //!< The main window
  };
}
#endif // !SFMLGRAPH_HPP
