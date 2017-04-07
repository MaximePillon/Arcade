/*
** Launcher.hpp for cpp_arcade in /home/loens_g/rendu/TEK2/CPP/cpp_arcade/includes/launcher/Launcher.hpp
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Fri Apr 07 12:52:54 2017 Gregoire LOENS
** Last update Fri Apr 07 12:52:54 2017 Gregoire LOENS
*/

#ifndef LAUNCHER_HPP
# define LAUNCHER_HPP

# include <string>
# include <dlfcn.h>

namespace arcade
{
  class Launcher
  {
  public:
    Launcher()
    {};

    ~Launcher()
    {};

  public:
    int openLib(std::string const &filename);

    void* loadSym(std::string const& symName) const;

    int closeLib();

  protected:
    void* handle;
  };
}

#endif // LAUNCHER_HPP
