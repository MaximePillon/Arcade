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
  arcade::IGraph*	yolo = ptr();
  if (yolo == NULL)
    std::clog << "BITE" << std::endl;
  pos.x = WINDOW_WIDTH;
  pos.y = WINDOW_HEIGHT;
  yolo->init(pos, "BITE");
  pos.x = 10;
  pos.y = 10;
  arcade::t_color color;
  color.full = 0x00FFFFFF;
  yolo->setBackground(color);
  yolo->drawText(pos, "BITE");
  pos.x = 15;
  color.full = 0xFF00FFFF;
  yolo->drawBlock(pos, color);
  yolo->refresh();
  sleep(5);
  yolo->close();
  delete yolo;
  lol.closeLib();
  return 0;
}
