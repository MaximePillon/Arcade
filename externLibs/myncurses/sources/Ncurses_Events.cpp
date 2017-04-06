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

Events::Events(Window* window):
  _window(window), _handlers(), _params(), _inputs()
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

// </editor-fold>

  /*
   * Event handling methods
   */

  // <editor-fold>

  void Events::registerEvent(int key, handler func, void* param)
  {
    this->_handlers[key] = func;
    this->_params[key] = param;
  }

  void Events::inputs()
  {
    int in;

    while ((in = getch()) != ERR)
    {
      if (this->_handlers.find(in) != this->_handlers.end())
	this->_inputs.push(in);
    }
  }

  void Events::events()
  {
    int in;

    while (this->_inputs.size() > 0)
    {
      in = this->_inputs.front();
      this->_inputs.pop();
      this->_handlers[in](this->_params[in]);
    }
  }

  // </editor-fold>
}