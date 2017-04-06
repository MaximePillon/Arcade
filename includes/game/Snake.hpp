/*
** Snake.hpp for cpp_arcade in /home/loens_g/rendu/TEK2/CPP/cpp_arcade/sources/snake/Snake.hpp
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Wed Apr 05 21:51:14 2017 Gregoire LOENS
** Last update Wed Apr 05 21:51:14 2017 Gregoire LOENS
*/

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <vector>
# include "IGraph.hpp"
# include "Map.hpp"

namespace arcade
{
  /// \class Block
  class Block
  {
  public:
    Block() {};
    virtual ~Block() {};

  public:
    void move(); //!< Move the block
    void changeDirection(); //!< Change the direction of the block
    void print(); //!< Print the block

  protected:
    t_color	color; //!< Color of the block
    t_pos	pos; //!< Position of the block
    t_pos	direction; //!< Direction of the block
  };

  /// \class Snake
  class Snake
  {
  public:
    void turn(CommandType type); //!< turn the snake
    void print(); //!< Print the snake
    void move(); //!< Move the snake
    void collide(); //!< Gst of collide

  public:
    Snake();
    virtual ~Snake() {};

  protected:
    std::vector<Block>		mystere;
    std::vector<Block>		body; //!< block of the body
    std::vector<Block>		turns;
    std::vector<Block>		border; //!< border
    int				lol;
    Map				map; //!< Map class
  };
}

#endif //CPP_ARCADE_SNAKE_HPP
