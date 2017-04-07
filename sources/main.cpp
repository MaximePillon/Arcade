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
  arcade::Launcher 	lol;
  test			ptr;
  arcade::t_pos		pos;
  arcade::t_color	color;
  arcade::IGraph*	graph;
  
  if (argc != 2)
    return EXIT_FAILURE;
  if (lol.openLib(argv[1]) == 1)
  {
    std::clog << dlerror() << std::endl;
    return 1;
  }
  *(void **)(&ptr) = lol.loadSym("create_graph");
  if (ptr == NULL)
  {
    std::clog << dlerror() << std::endl;
    return lol.closeLib();
  }
   graph = ptr();
  if (graph == NULL)
  {
    std::cerr << "can't load the graphic library\n";
    return -1;
  }
  pos.x = WINDOW_WIDTH;
  pos.y = WINDOW_HEIGHT;
  graph->init(pos, "Arcade launcher");

  pos.x = 15;
  pos.y = 0;
  graph->drawText(pos, "CPP_ARCADE");
  color.full = 0x00FF00FF;
  for (unsigned int j = 0; j < 3; ++j) {
    pos.x = 5;
    pos.y = 5 * (j + 1);
    graph->drawText(pos, "graph");
  }
  graph->refresh();
  sleep(5);
  graph->close();
  delete graph;
  lol.closeLib();
  return 0;
}
