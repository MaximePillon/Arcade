/*
** Launcher.cpp for cpp_arcade in /home/loens_g/rendu/TEK2/CPP/cpp_arcade/sources/launcher/Launcher.cpp
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Fri Apr 07 12:52:48 2017 Gregoire LOENS
** Last update Fri Apr 07 12:52:48 2017 Gregoire LOENS
*/

#include <iostream>
#include <unistd.h>
#include <IGraph.hpp>
#include "launcher/Launcher.hpp"

typedef arcade::IGraph* (*graph_func)();
typedef bool (*game_func)(arcade::IGraph*);

namespace arcade
{
  Launcher::Launcher():
    handle(NULL), game_handle(NULL), graph_handle(NULL), graph(NULL),
    libs(), games(), selected_lib(), selected_game(), quit(false)
  {
    this->libs["Ncurses"] = "lib/lib_arcade_ncurses.so";
    this->libs["OpenGL"] = "lib/lib_arcade_opengl.so";
    this->libs["SFML"] = "lib/lib_arcade_sfml.so";
    this->libs["LibLapin"] = "lib/lib_arcade_liblapin.so";
    this->libs["SDL"] = "lib/lib_arcade_sdl.so";

    this->games["Snake"] = "lib/lib_arcade_snake.so";
  }

  /*
   * Libs utils
   */
  // <editor-fold>

  int Launcher::openLib(const std::string &filename)
  {
    this->handle = dlopen(filename.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (handle == NULL)
      return 1;
    return 0;
  }

  void *Launcher::loadSym(std::string const &symName) const
  {
    return dlsym(this->handle, symName.c_str());
  }

  int Launcher::closeLib()
  {
    return dlclose(this->handle);
  }

  int Launcher::openGameLib(const std::string &filename)
  {
    this->game_handle = dlopen(filename.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (game_handle == NULL)
      return 1;
    return 0;
  }

  void *Launcher::loadGameSym(std::string const &symName) const
  {
    return dlsym(this->game_handle, symName.c_str());
  }

  int Launcher::closeGameLib()
  {
    return dlclose(this->game_handle);
  }

  int Launcher::openGraphLib(const std::string &filename)
  {
    this->graph_handle = dlopen(filename.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (graph_handle == NULL)
      return 1;
    return 0;
  }

  void *Launcher::loadGraphSym(std::string const &symName) const
  {
    return dlsym(this->graph_handle, symName.c_str());
  }

  int Launcher::closeGraphLib()
  {
    return dlclose(this->graph_handle);
  }

  // </editor-fold>

  int Launcher::start(std::string const &graph_path)
  {
    graph_func ptr;
    arcade::t_pos		pos;

    if (this->openLib(graph_path.c_str()) == 1)
    {
      std::clog << dlerror() << std::endl;
      return EXIT_FAILURE;
    }
    *(void **) (&ptr) = this->loadSym("create_graph");
    if (ptr == NULL)
    {
      std::clog << dlerror() << std::endl;
      return this->closeLib();
    }
    this->graph = ptr();
    if (this->graph == NULL)
      return EXIT_FAILURE;
    pos.x = WINDOW_WIDTH;
    pos.y = WINDOW_HEIGHT;
    this->graph->init(pos, "Arcade");
    return EXIT_SUCCESS;
  }

  void Launcher::end()
  {
    this->graph->close();
    delete this->graph;
    this->closeLib();
  }

  void Launcher::get_libs()
  {
    for (auto it = this->libs.begin(); it != this->libs.end(); ++it)
    {
      if (access((*it).second.c_str(), R_OK) == -1)
	this->libs.erase(it);
    }
    for (auto it = this->games.begin(); it != this->games.end(); ++it)
    {
      if (access((*it).second.c_str(), R_OK) == -1)
	this->games.erase(it);
    }
    this->selected_lib = this->libs.begin();
    this->selected_game = this->games.begin();
  }

  /*
   * Events Methods
   */

  // <editor-fold>

  void Launcher::launch_game(void *param)
  {
    IGraph* graph;
    graph_func gr_creat;
    game_func ga_creat;
    t_pos pos;

    pos.x = WINDOW_WIDTH;
    pos.y = WINDOW_HEIGHT;
    this->graph->close();
    static_cast<void>(param);
    if (this->openGraphLib((*(this->selected_lib)).second.c_str()) == 1)
    {
      std::clog << dlerror() << std::endl;
      this->graph->init(pos, "Arcade");
      return ;
    }
    *(void**)(&gr_creat) = this->loadGraphSym("create_graph");
    if (gr_creat == NULL)
    {
      std::clog << dlerror() << std::endl;
      this->closeGraphLib();
      this->graph->init(pos, "Arcade");
      return ;
    }
    if (this->openGameLib((*(this->selected_game)).second.c_str()) == 1)
    {
      std::clog << dlerror() << std::endl;
      this->graph->init(pos, "Arcade");
      return ;
    }
    *(void**)(&ga_creat) = this->loadGameSym("launch_game");
    if (ga_creat == NULL)
    {
      std::clog << dlerror() << std::endl;
      this->closeGraphLib();
      this->closeGameLib();
      this->graph->init(pos, "Arcade");
      return ;
    }
    graph = gr_creat();
    if (graph == NULL)
    {
      std::clog << dlerror() << std::endl;
      this->closeGraphLib();
      this->closeGameLib();
      this->graph->init(pos, "Arcade");
      return ;
    }
    graph->init(pos, (*(this->selected_game)).second);
    this->quit = ga_creat(graph);
    graph->close();
    delete graph;
    this->closeGameLib();
    this->closeGraphLib();
    this->graph->init(pos, "Arcade");
  }

  void Launcher::close(void* param)
  {
    static_cast<void>(param);
    this->quit = true;
  }

  void Launcher::previousGl(void* param)
  {
    static_cast<void>(param);
    if (this->selected_lib != this->libs.begin())
      this->selected_lib--;
  }

  void Launcher::nextGl(void* param)
  {
    static_cast<void>(param);
    if (this->selected_lib != this->libs.end()--)
      this->selected_lib++;
  }

  void Launcher::previousGame(void* param)
  {
    static_cast<void>(param);
    if (this->selected_game != this->games.begin())
      this->selected_game--;
  }

  void Launcher::nextGame(void* param)
  {
    static_cast<void>(param);
    if (this->selected_game != this->games.end()--)
      this->selected_game++;
  }

  bool Launcher::printText(std::string string, unsigned int x,
			   unsigned int y)
  {
    t_pos	pos;

    pos.x = x;
    pos.y = y;
    return this->graph->drawText(pos, string);
  }

  bool Launcher::printExtentedBlock(unsigned int startX, unsigned int startY,
				    unsigned int endX, unsigned int endY,
				    unsigned int color)
  {
    t_pos	end;
    t_pos	wherePrint;
    t_color	blockColor;

    end.x = endX;
    end.y = endY;
    blockColor.full = color;
    for (unsigned int x = startX; x < end.x; ++x)
    {
      for (unsigned y = startY; y < end.y; ++y)
      {
	wherePrint.x = x;
	wherePrint.y = y;
	if (this->graph->drawBlock(wherePrint, blockColor) == false)
	  return false;
      }
    }
    return true;
  }

  // </editor-fold>

  void Launcher::loop()
  {
    unsigned int x = 3;
    unsigned int y = 5;
    this->graph->registerEvent(CommandType::PLAY, this->launch_game, NULL);
    this->graph->registerEvent(CommandType::CLOSE, this->close, NULL);
    this->graph->registerEvent(CommandType::PREVIOUS_GL, this->previousGl, NULL);
    this->graph->registerEvent(CommandType::NEXT_GL, this->nextGl, NULL);
    this->graph->registerEvent(CommandType::PREVIOUS_GAME, this->previousGame, NULL);
    this->graph->registerEvent(CommandType::NEXT_GAME, this->nextGame, NULL);
    while (this->graph->isOpen() && !this->quit)
    {
      this->graph->execEvents();
      // titles
      printText("Arcade launcher", 12, 0);
      printText("games", 4, 2);
      printText("librairies", 20, 2);

      // games block
      printExtentedBlock(1, 3, 11, 20, 0x00FF00FF);
      printExtentedBlock(2, 4, 10, 19, 0x00000000);
	for (auto it = games.begin(); it != games.end(); ++it)
      {
	printText((*it).first.c_str(), x, y);
	++y;
      }

      //libs block
      x = 15;
      y = 5;
      printExtentedBlock(13, 3, 24, 20, 0x00FF00FF);
      printExtentedBlock(14, 4, 23, 19, 0x00000000);
      for (auto it = libs.begin(); it != libs.end(); ++it)
      {
	printText((*it).first.c_str(), x, y);
	++y;
      }
      this->graph->refresh();
    }
  }
}
