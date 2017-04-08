/*
** NcursesGraph.cpp for cpp_arcade in /home/soszyn_h/rendu/CPP/cpp_arcade/sources/ncurses/NcursesGraph.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Wed Apr 05 09:04:04 2017 Hugo SOSZYNSKI
** Last update Wed Apr 05 09:04:04 2017 Hugo SOSZYNSKI
*/

#include <unistd.h>
#include <IGraph.hpp>
#include "IGraph.hpp"
#include "ncurses/NcursesGraph.hpp"

namespace arcade
{
  /*
   * Ctor & Dtor
   */

  // <editor-fold>

  NcursesGraph::NcursesGraph():
    _window(NULL), _events(NULL), _isOpen(false)
  {
    this->_keyboard[CommandType::GO_UP] = KEY_UP;
    this->_keyboard[CommandType::GO_DOWN] = KEY_DOWN;
    this->_keyboard[CommandType::GO_RIGHT] = KEY_RIGHT;
    this->_keyboard[CommandType::GO_LEFT] = KEY_LEFT;
    this->_keyboard[CommandType::SHOOT] = ' ';
    this->_keyboard[CommandType::CLOSE] = 27;
    this->_keyboard[CommandType::PREVIOUS_GL] = '2';
    this->_keyboard[CommandType::NEXT_GL] = '3';
    this->_keyboard[CommandType::PREVIOUS_GAME] = '4';
    this->_keyboard[CommandType::NEXT_GAME] = '5';
    this->_keyboard[CommandType::RESTART] = '8';
    this->_keyboard[CommandType::MENU] = '9';
    this->_keyboard[CommandType::PLAY] = '\n';
  }

  NcursesGraph::~NcursesGraph()
  {}

  // </editor-fold>

  /*
   * Init & Close
   */

  // <editor-fold>

  bool NcursesGraph::init(t_pos const &size, std::string const &window_name)
  {
    (void)size;
    (void)window_name;
    this->_window = new myncurses::Window();
    this->_events = new myncurses::Events(this->_window);
    this->_isOpen = true;
    this->_window->startColor();
    this->_window->termNoecho();
    this->_events->termRaw();
    this->_events->termCursSet(0);
    this->_events->termKeypad(TRUE);
    this->_events->tremNodelay(TRUE);
    this->_window->initPair(1, COLOR_BLACK, COLOR_RED);
    this->_window->initPair(2, COLOR_BLACK, COLOR_WHITE);
    this->_window->initPair(3, COLOR_BLACK, COLOR_BLACK);
    this->_window->initPair(4, COLOR_BLACK, COLOR_GREEN);
    this->_window->initPair(5, COLOR_BLACK, COLOR_BLUE);
    this->_window->initPair(6, COLOR_BLACK, COLOR_YELLOW);
    this->_window->initPair(7, COLOR_BLACK, COLOR_MAGENTA);
    this->_window->initPair(8, COLOR_BLACK, COLOR_CYAN);
    return true;
  }

  bool NcursesGraph::close()
  {
    this->_isOpen = false;
    delete this->_events;
    delete this->_window;
    return true;
  }

  // </editor-fold>

  /*
   * Refresh and Events
   */

  // <editor-fold>

  void NcursesGraph::clear() const
  {
    this->_window->clear();
  }

  void NcursesGraph::refresh()
  {
    this->_window->refresh();
  }

  bool NcursesGraph::isOpen() const
  {
    return this->_isOpen;
  }

  void NcursesGraph::registerEvent(CommandType command, event_handler hdl,
				   void *param)
  {
    handler_t handler;

    handler.hdl = hdl;
    handler.param = param;
    if (this->_keyboard.find(command) != this->_keyboard.end())
      this->_handlers[this->_keyboard[command]] = handler;
  }

  void NcursesGraph::execEvents()
  {
    int input;

    while ((input = this->_events->termGetch()) != ERR)
    {
      if (this->_handlers.find(input) != this->_handlers.end())
	this->_handlers[input].hdl(this->_handlers[input].param);
    }
  }

  // </editor-fold>


  /*
   * Print Methods
   */

  // <editor-fold>

  bool NcursesGraph::drawText(t_pos const &pos, std::string const &text)
  {
    this->_window->mvprintw(pos.y, pos.x, text.c_str());
    return true;
  }

  bool NcursesGraph::drawBlock(t_pos const &pos, t_color const &color)
  {
    short print_color = COLOR_BLACK;
    int red;
    int green;
    int blue;

    red = color.argb[1] * 200 / 51;
    green = color.argb[2] * 200 / 51;
    blue = color.argb[3] * 200 / 51;
    if (red >= 500 && green <= 100 && blue <= 100)
      print_color = 1;
    else if (red >= 500 && green >= 500 && blue >= 500)
      print_color = 2;
    else if (red < 500 && green < 500 && blue < 500)
      print_color = 3;
    else if (red <= 100 && green >= 500 && blue <= 100)
      print_color = 4;
    else if (red <= 100 && green <= 100 && blue >= 500)
      print_color = 5;
    else if (red >= 500 && green >= 500 && blue <= 100)
      print_color = 6;
    else if (red >= 500 && green <= 100 && blue >= 500)
      print_color = 7;
    else if (red <= 100 && green >= 500 && blue >= 500)
      print_color = 8;

    this->_window->attributeOn(COLOR_PAIR(print_color));
    this->_window->attributeOn(WA_TOP);
    this->_window->mvprintw(pos.y, pos.x, " ");
    this->_window->attributeOff(WA_TOP);
    this->_window->attributeOff(COLOR_PAIR(print_color));

    return true;
  }

  bool NcursesGraph::setBackground(t_color const &color)
  {
    t_pos pos;

    for (pos.x = 0; pos.x < WINDOW_WIDTH; pos.x++)
      for (pos.y = 0; pos.y < WINDOW_HEIGHT; pos.y++)
	this->drawBlock(pos, color);
    return true;
  }

  // </editor-fold>
}

extern "C"
{
arcade::IGraph* create_graph()
{
  return new arcade::NcursesGraph();
}
}