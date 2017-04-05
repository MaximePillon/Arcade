/*
** IGraph.hpp for cpp_arcade in /home/soszyn_h/rendu/CPP/cpp_arcade/includes/IGraph.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Mar 28 20:28:46 2017 Hugo SOSZYNSKI
** Last update Tue Mar 28 20:28:46 2017 Hugo SOSZYNSKI
*/

#ifndef IGRAPH_HPP
# define IGRAPH_HPP

# include <string>
# include "arcade_protocol.hpp"

#ifndef BLOCK_SIZE
# define BLOCK_SIZE 25
#endif // !BLOCK_SIZE

typedef void (*event_handler)(void*);

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
    /// \param window_name The name of the window to be created
    /// \return True on success or false otherwise
    virtual bool init(t_pos const& size, std::string const& window_name) = 0;

    /// \brief Close and destroy window.
    ///
    /// \return True on success or false otherwise
    virtual bool close(void) = 0;

    /// \brief Draw a text on the window.
    ///
    /// \param pos Position (top left)
    /// \param text Text to draw
    /// \return True on success or false otherwise
    virtual bool drawText(t_pos const& pos, std::string const& text) = 0;

    /// \brief Draw a block on the window.
    ///
    /// \param pos Position (top left)
    /// \param color Background color
    /// \return True on success or false otherwise
    virtual bool drawBlock(t_pos const& pos, t_color const& color) = 0;

    /// \brief Refresh the window content
    virtual void refresh(void) = 0;

    /// \brief Check if the window is open
    ///
    /// \return True if the window is open, false otherwise
    virtual bool isOpen(void) const = 0;

    /// \brief Method used to bind event to a function.
    ///
    /// \param command The command you want to bind the handler to.
    /// \param hdl The handler you want to bind to the key (handler's prototype: "void handler(void *);").
    /// \param param The parameter to pass to the handler.
    virtual void registerEvent(arcade::CommandType command,
			       event_handler hdl,
			       void* param) = 0;

    /// \brief Get the inputs and execute the corresponding handler
    virtual void execEvents() = 0;
  };
}

#endif // !IGRAPH_HPP
