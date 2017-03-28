/*
** IGraph.hpp for cpp_arcade in /home/sylvain/Travail/Epitech/cpp_arcade/IGraph.hpp
**
** Made by Sylvain CORSINI
** Login   <sylvain.corsini@epitech.eu>
**
** Started on  Fri Mar 24 13:27:57 2017 Sylvain CORSINI
** Last update Fri Mar 24 13:27:57 2017 Sylvain CORSINI
*/

#ifndef CPP_ARCADE_IGRAPH_HPP
#define CPP_ARCADE_IGRAPH_HPP

#include <string>

/// \namespace Arcade
namespace Arcade
{
  /// \struct t_pos
  typedef struct
  {
    unsigned int x;
    unsigned int y;
  } t_pos;

  /// \union t_color
  typedef union
  {
    int full;			//!< Full color
    unsigned char argb[4];	//!< ARGB color
  } t_color;

  /// \struct t_image
  typedef struct
  {
    std::string path;		//!< The path to the image file
    t_color default_color;	//!< The color to use for ascii lib
    char default_char;		//!< The character to display for ascii lib
  } t_image;

  /// \class IGraph
  class IGraph
  {
  public:
    /// \brief Destroy window, lib and potential allocated memory.
    ///	       It also close window if it is opened.
    virtual ~IGraph(void)
    {};

    /// \brief Initialize window and lib (if not already initialized).
    ///
    /// \param size Size of the window
    /// \return True on success or false otherwise
    virtual bool init(t_pos size) = 0;

    /// \brief Close and destroy window.
    ///
    /// \return True on success or false otherwise
    virtual bool close(void) = 0;

    /// \brief Draw a text on the window.
    ///
    /// \param pos Position (top left)
    /// \param text Text to draw
    /// \return True on success or false otherwise
    virtual bool drawText(t_pos pos, std::string text) = 0;

    /// \brief Draw a sprite on the window.
    ///
    /// \param pos Position (top left)
    /// \param image Sprite to draw
    /// \param color Background color
    /// \return True on success or false otherwise
    virtual bool drawSprite(t_pos pos, t_image image, t_color color) = 0;

    /// \brief Draw a block on the window.
    ///
    /// \param pos Position (top left)
    /// \param color Background color
    /// \return True on success or false otherwise
    virtual bool drawBlock(t_pos pos, t_color color) = 0;

    /// \brief Draw the following sprite on all block of the window.
    ///
    /// \param image Background sprite (default_char must be ignored for text library)
    /// \return True on success or false otherwise
    virtual bool setBackground(t_image image) = 0;
  };
}

#endif //CPP_ARCADE_IGRAPH_HPP
