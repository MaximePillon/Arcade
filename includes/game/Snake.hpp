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
    Block(t_color const& color, t_pos const& pos, t_pos const& direction);
    virtual ~Block() {};

  public:
    /// \brief Move the block
    void move();

    /// \brief Change the direction of the block
    /// \param direction The new direction to apply to the block
    void changeDirection(t_pos const& direction);

    /// \brief Print the block on screen
    /// \param graph The graphical interface on which to print the block
    void print(IGraph &graph);

    /// \brief Compare the positions of the Blocks
    /// \param other The Block to compare with
    /// \return true if positions are equal, false otherwise
    bool operator==(Block const& other);

  protected:
    t_color	color; //!< Color of the block
    t_pos	pos; //!< Position of the block
    t_pos	direction; //!< Direction of the block
  };

  /// \class Snake
  class Snake
  {
  public:
    /// \brief Change the direction of the head and add a turn position
    /// \param type The direction in which you turn
    void turn(CommandType type);

    /// \brief Print the snake
    void print();

    /// \brief Move all the blocks the snake
    void move();

    /// \brief Collision detections and reactions
    void collide();

  public:
    Snake();
    virtual ~Snake() {};

  protected:
    std::vector<Block>		powerup; //!< Powerups
    std::vector<Block>		body; //!< Block of the body
    std::vector<Block>		turns; //!< The truning points
    std::vector<Block>		border; //!< Border
    unsigned int		score; //!< The score
    Map				map; //!< Map class
  };
}

#endif //CPP_ARCADE_SNAKE_HPP
