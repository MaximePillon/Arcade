/*
** main.cpp for cpp_arcade in /home/soszyn_h/rendu/CPP/cpp_arcade/sources/main.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Mar 07 17:52:18 2017 Hugo SOSZYNSKI
** Last update Tue Mar 07 17:52:18 2017 Hugo SOSZYNSKI
*/

#include <iostream>
#include "launcher/Launcher.hpp"
#include "IGraph.hpp"

typedef arcade::IGraph* (*test)();

int		main(int argc, const char *argv[])
{
  arcade::Launcher 	lol;
  test			ptr;

  if (argc != 2)
    return EXIT_FAILURE;
  if (lol.openLib(argv[1]) == 1)
  {
    std::clog << dlerror() << std::endl;
    return 1;
  }
  *(void **)(&ptr) = lol.loadSym("create_graph");
  if (ptr == NULL)
    return lol.closeLib();
  arcade::IGraph*	yolo = ptr();
  if (yolo == NULL)
    std::clog << "BITE" << std::endl;
  delete yolo;
  lol.closeLib();
  return 0;
}
