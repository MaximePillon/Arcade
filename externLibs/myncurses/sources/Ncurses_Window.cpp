/*
** Ncurses_Window.cpp for MyNcursesPP in /home/soszyn_h/Documents/Projects/MyNcursesPP/sources/Ncurses_Window.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Fri Mar 31 19:29:39 2017 Hugo SOSZYNSKI
** Last update Fri Mar 31 19:29:39 2017 Hugo SOSZYNSKI
*/

#include <Ncurses.hpp>

namespace myncurses
{
/*
 * Coplien Form
 */

  // <editor-fold>

  Window::Window():
    _nLines(0), _nCols(0), _beginY(0), _beginX(0), _window(NULL)
  {
    if (this->isNcursesInitialised())
      throw NcursesError("Ncurses already initialised");
    if (initscr() == NULL)
      throw NcursesError("Cannot initialise ncurses");
    this->_window = stdscr;
    getmaxyx(stdscr, this->_nLines, this->_nCols);
  }

  Window::Window(int nLines, int nCols, int beginY, int beginX):
    _nLines(nLines), _nCols(nCols),
    _beginY(beginY), _beginX(beginX), _window(NULL)
  {
    this->_window = newwin(this->_nLines, this->_nCols,
			   this->_beginY, this->_beginX);
    if (this->_window == NULL)
      throw NcursesError("Cannot create new window");
  }

  Window::Window(Window const &other):
    _nLines(other._nLines), _nCols(other._nCols),
    _beginY(other._beginY), _beginX(other._beginX)
  {
    if (this->isStdscr())
      throw NcursesError("Cannot duplicate main window");
    this->_window = dupwin(other._window);
    if (this->_window == NULL)
      throw NcursesError("Cannot duplicate window");
  }

  Window::~Window()
  {
    if (this->isStdscr()) // If you want to destroy the main window, you quit the ncurses
      endwin();
    else
      delwin(this->_window);
  }

  Window& Window::operator=(Window const &other)
  {
    if (this->isStdscr())
      throw NcursesError("Cannot duplicate main window");
    this->_nLines = other._nLines;
    this->_nCols = other._nCols;
    this->_beginY = other._beginY;
    this->_beginX = other._beginX;
    this->_window = dupwin(other._window);
    if (this->_window == NULL)
      throw NcursesError("Cannot duplicate window");
    return *this;
  }

  // </editor-fold>

/*
 * Getters
 */

  // <editor-fold>

  int Window::getNbLines() const { return this->_nLines; }
  int Window::getNbCols() const { return this->_nCols; }
  int Window::getBeginY() const { return this->_beginY; }
  int Window::getBeginX() const { return this->_beginX; }
  WINDOW* Window::getWINDOW() { return this->_window; }

  // </editor-fold>

  /*
   * Setup Methods
   */

  // <editor-fold>

  bool Window::hasColor() const { return has_colors(); }

  int Window::startColor() const { return start_color(); }

  int Window::termEcho(){ return echo(); }

  int Window::termNoecho() { return noecho(); }

  int Window::initPair(short pair, short f, short b) { return init_pair(pair, f, b); }

  // </editor-fold>

  /*
   * Attributes Methods
   */

  // <editor-fold>

  int Window::initPair(short pair, short f, short b) const
  {
    return init_pair(pair, f, b);
  }

  int Window::attributeOn(int attr) const
  {
    return wattron(this->_window, attr);
  }

  int Window::attributeOff(int attr) const
  {
    return wattroff(this->_window, attr);
  }

  // </editor-fold>

  /*
   * Display Methods
   */

  // <editor-fold>

  int Window::clear() const { return wclear(this->_window); }

  int Window::refresh() const { return wrefresh(this->_window); }

  int Window::mvprintw(int y, int x, std::string const &fmt, ...) const
  {
    va_list	args;
    int		ret;

    if (wmove(this->_window, y, x) == ERR)
      return (ERR);
    va_start(args, fmt);
    ret = vwprintw(this->_window, fmt.c_str(), args);
    va_end(args);
    return ret;
  }

  // </editor-fold>

  /*
   * Internal Check Functions
   */

  // <editor-fold>

  bool Window::isStdscr() const
  {
    if (this->_window == stdscr)
      return true;
    return false;
  }

  bool Window::isNcursesInitialised() const
  {
    if (stdscr) // If ncurses not initialised, stdscr is NULL.
      return false;
    return true;
  }

  // </editor-fold>

}