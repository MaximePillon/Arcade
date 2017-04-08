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

namespace arcade
{
//  void close(void* param);

  /// \class Block
  class Block
  {
  public:
    Block(t_color const& color, t_pos const& pos, t_spos const& direction);
    virtual ~Block() {};

  public:
    /// \brief Move the block
    void move();

    /// \brief Get the position of the block
    t_pos const& getPos(void) const;

    /// \brief Change the direction of the block
    /// \param direction The new direction to apply to the block
    void changeDirection(t_spos const& direction);

    /// \brief Get th direction of the Block
    /// \return The direction of the Block
    t_spos const& getDirection() const;

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
    t_spos	direction; //!< Direction of the block
  };

  /// \class Snake
  class Snake
  {
  public:
    /// \brief Print the snake
    void print();

    /// \brief Move all the blocks the snake
    void move();

    /// \brief Collision detections and reactions
    void collide();

    /// \brief The main game function
    bool play();

  public:
    Snake(IGraph* graph);
    virtual ~Snake() {};

  protected:
    std::vector<Block>		powerup; //!< Powerups
    std::vector<Block>		border; //!< Border
    unsigned int		score; //!< The score
    IGraph			*graph; //!< The graph interface to draw with
    bool			loose;

  public:
    std::vector<Block>		body; //!< Block of the body
    std::vector<Block>		turns; //!< The turning points
    bool			quit; //!< if the quit bind has been press
    bool			restart; //!< if the restart bind has been press
    bool			menu;
  };
}

#endif //CPP_ARCADE_SNAKE_HPP
