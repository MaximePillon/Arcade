/*
** Centipede.hpp for cpp_arcade in /home/god/TEK2/C++/cpp_arcade/includes/game/Centipede.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Sun Apr 09 11:14:36 2017 Maxime PILLON
** Last update Sun Apr 09 11:14:36 2017 Maxime PILLON
*/

#ifndef CPP_ARCADE_CENTIPEDE_HPP
#define CPP_ARCADE_CENTIPEDE_HPP

# include		<vector>
# include		"IGraph.hpp"

namespace arcade
{
  /// \enum Who
  enum Who {
    PLAYER,
    CENTIPEDE
  };

  /// \class Block
  class Block
  {
  public:
    /// \brief Block object constructor.
    /// \param color The color of the Block.
    /// \param pos The position of the Block.
    /// \param direction The movement direction of the Block.
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

  /// \class Centipede
  class Centipede {

  public:
    /// \brief The constructor of a Centipede object.
    /// \param size The starting size of the Centipede.
    /// \param startPos The starting position of the Centipede.
    /// \param dir The starting movement direction of the Centipede.
    Centipede(size_t size, t_pos startPos, t_spos dir);
    virtual ~Centipede() {};

  protected:
    size_t			size; //!< The size of the Centipede.
    t_pos			headPos; //!< The position of the head.
    t_spos			dir; //!< the direction of the Centipede.

  public:
    std::vector<Block>		body; //!< The Blocks of the body
    std::vector<Block>		turns; //!< the turning points of the Centipede.
  };

  /// \class Blockade
  class Blockade {
  public:
    /// \brief Constructor of the Blockade object.
    /// \param color
    /// \param pos
    /// \param direction
    /// \param Lives
    Blockade(t_color const& color, t_pos const& pos, t_spos const& direction, size_t Lives = 5);
    virtual ~Blockade() {};

  public:
    Block block;
    size_t Lives;
  };

  class Game {
  public:

    void print();

    void move();

    void collide();

    bool play();

    void saveHighScore();

    void getHighScore();

  public:
    Game(IGraph* graph);
    virtual ~Game() {};

  protected:
    std::vector<Block>			border;
    unsigned int			score;
    IGraph				*graph;
    bool				loose;

  public:
    std::vector<Centipede>		Centipedes;
    std::vector<Blockade>		blockades;
    bool				quit;
    bool				restart;
    bool				menu;
    size_t				left_turn;
    unsigned int			highScore;
    Block				*player;
    Block				*bullets;
  };

}

#endif //CPP_ARCADE_CENTIPEDE_HPP
