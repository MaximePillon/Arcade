/*
** Ncurses_Events.cpp for MyNcursesPP in /home/soszyn_h/Documents/Projects/MyNcursesPP/sources/Ncurses_Events.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Fri Mar 31 19:30:25 2017 Hugo SOSZYNSKI
** Last update Fri Mar 31 19:30:25 2017 Hugo SOSZYNSKI
*/

#include <Ncurses.hpp>

namespace myncurses
{
/*
 * Constructor and destructor
 */

// <editor-fold>

  Events::Events(Window *window) :
    _window(window)
  {}

  Events::~Events()
  {}

// </editor-fold>

/*
 * Setup Methods
 */

// <editor-fold>

  int Events::termKeypad(bool bf) const
  {
    return keypad(this->_window->getWINDOW(), bf);
  }

  int Events::tremNodelay(bool bf) const
  {
    return nodelay(this->_window->getWINDOW(), bf);
  }

  int Events::termRaw() const
  {
    return raw();
  }

  int Events::termNoraw() const
  {
    return noraw();
  }

  int Events::termCursSet(int visibility) const
  {
    return curs_set(visibility);
  }

// </editor-fold>

  /*
   * Event handling methods
   */

  // <editor-fold>

  int Events::termGetch() const
  {
    return wgetch(this->_window->getWINDOW());
  }

  // </editor-fold>
}