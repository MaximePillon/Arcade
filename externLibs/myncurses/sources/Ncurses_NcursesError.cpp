/*
** Ncurses_NcursesError.cpp for MyNcursesPP in /home/soszyn_h/Documents/Projects/MyNcursesPP/sources/Ncurses_NcursesError.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Fri Mar 31 19:30:02 2017 Hugo SOSZYNSKI
** Last update Fri Mar 31 19:30:02 2017 Hugo SOSZYNSKI
*/

#include "Ncurses.hpp"

namespace myncurses
{

NcursesError::NcursesError(std::string msg):
  _message(msg)
{}

const char* NcursesError::what() const throw()
{
  return this->_message.c_str();
}

}