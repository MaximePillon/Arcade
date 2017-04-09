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
    Block(t_pos const& pos, t_spos const& direction);
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

    /// \brief Compare the positions of the Blocks
    /// \param other The Block to compare with
    /// \return true if positions are equal, false otherwise
    bool operator==(Block const& other);

  protected:
    t_pos	pos; //!< Position of the block
    t_spos	direction; //!< Direction of the block
  };

  /// \class Snake
  class Snake
  {
  public:

    /// \brief Move all the blocks the snake
    void move();

    /// \brief Collision detections and reactions
    void collide();

    /// \brief The main game function
    bool play();

    CommandType readIn() const;

    void whereAmI();

    void getMap(CommandType cmd);

    void goUp();

    void goDown();

    void goLeft();

    void goRight();

    void goForward();

    void illegal();

    void playRound();

  public:
    Snake();
    virtual ~Snake() {};

  protected:
    std::vector<Block>		powerup; //!< Powerups
    std::vector<Block>		body; //!< Block of the body
    std::vector<Block>		turns; //!< The turning points

  public:
    bool			quit; //!< if the quit bind has been press
  };
}

#endif //CPP_ARCADE_SNAKE_HPP
