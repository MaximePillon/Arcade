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
#include <unistd.h>
#include <IGraph.hpp>
#include "launcher/Launcher.hpp"
#include "IGraph.hpp"

typedef arcade::IGraph* (*test)();

int		main(int argc, const char *argv[])
{
  arcade::Launcher 	launcher;

  if (argc != 2)
    return EXIT_FAILURE;
  if (launcher.start(argv[1]) != 0)
    return 1;
  launcher.get_libs();
  launcher.loop();
  launcher.end();
  return 0;
}
