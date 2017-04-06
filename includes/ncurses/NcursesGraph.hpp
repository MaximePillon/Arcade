/*
** NcursesGraph.hpp for cpp_arcade in /home/soszyn_h/rendu/CPP/cpp_arcade/includes/ncurses/NcursesGraph.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Wed Apr 05 09:04:09 2017 Hugo SOSZYNSKI
** Last update Wed Apr 05 09:04:09 2017 Hugo SOSZYNSKI
*/

#ifndef NCURSESGRAPH_HPP
# define NCURSESGRAPH_HPP

# include <map>
# include "IGraph.hpp"
# include "libs/Ncurses.hpp"

namespace arcade
{
  class NcursesGraph: public IGraph
  {
  public:
    NcursesGraph();
    virtual ~NcursesGraph();

  public:
    virtual bool init(t_pos const& size, std::string const& window_name);
    virtual bool close(void);

  public:
    virtual void refresh(void);
    virtual bool isOpen(void) const;
    virtual void registerEvent(CommandType command,
			       event_handler hdl,
			       void* param);
    virtual void execEvents();

  public:
    virtual bool drawText(t_pos const& pos, std::string const& text);
    virtual bool drawBlock(t_pos const& pos, t_color const& color);
    virtual bool setBackground(t_color const& color);

  protected:

  protected:
    myncurses::Window*	_window;
    myncurses::Events*	_events;
    std::map<CommandType, int> _keyboard;
    bool		_isOpen;
  };
}

#endif // !NCURSESGRAPH_HPP
