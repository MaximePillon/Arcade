/*
** Launcher.cpp for cpp_arcade in /home/loens_g/rendu/TEK2/CPP/cpp_arcade/sources/launcher/Launcher.cpp
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Fri Apr 07 12:52:48 2017 Gregoire LOENS
** Last update Fri Apr 07 12:52:48 2017 Gregoire LOENS
*/

#include "launcher/Launcher.hpp"

namespace arcade
{
  int Launcher::openLib(const std::string &filename)
  {
    this->handle = dlopen(filename.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (handle == NULL)
      return 1;
    return 0;
  }

  void* Launcher::loadSym(std::string const& symName) const
  {
    return dlsym(this->handle, symName.c_str());
  }

  int Launcher::closeLib()
  {
    return dlclose(this->handle);
  }
}
