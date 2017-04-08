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

  /*
 * Events Methods
 */

  // <editor-fold>

  void launch_game(void *param)
  {
    IGraph* graph;
    graph_func gr_creat;
    game_func ga_creat;
    t_pos pos;
    Launcher* self;

    self = static_cast<Launcher*>(param);
    pos.x = WINDOW_WIDTH;
    pos.y = WINDOW_HEIGHT;
    self->graph->close();
    if (self->openGraphLib((*(self->selected_lib)).second.c_str()) == 1)
    {
      std::clog << dlerror() << std::endl;
      self->graph->init(pos, "Arcade");
      return ;
    }
    *(void**)(&gr_creat) = self->loadGraphSym("create_graph");
    if (gr_creat == NULL)
    {
      std::clog << dlerror() << std::endl;
      self->closeGraphLib();
      self->graph->init(pos, "Arcade");
      return ;
    }
    if (self->openGameLib((*(self->selected_game)).second.c_str()) == 1)
    {
      std::clog << dlerror() << std::endl;
      self->graph->init(pos, "Arcade");
      return ;
    }
    *(void**)(&ga_creat) = self->loadGameSym("launch_game");
    if (ga_creat == NULL)
    {
      std::clog << dlerror() << std::endl;
      self->closeGraphLib();
      self->closeGameLib();
      self->graph->init(pos, "Arcade");
      return ;
    }
    graph = gr_creat();
    if (graph == NULL)
    {
      std::clog << dlerror() << std::endl;
      self->closeGraphLib();
      self->closeGameLib();
      self->graph->init(pos, "Arcade");
      return ;
    }
    graph->init(pos, (*(self->selected_game)).second);
    self->quit = ga_creat(graph);
    graph->close();
    delete graph;
    self->closeGameLib();
    self->closeGraphLib();
    self->graph->init(pos, "Arcade");
  }

  void close(void* param)
  {
    Launcher* self;

    self = static_cast<Launcher*>(param);
    self->quit = true;
  }

  void previousGl(void* param)
  {
    Launcher* self;

    //std::clog << "previous gl" << std::endl;
    self = static_cast<Launcher*>(param);
    if (self->selected_lib != self->libs.begin())
      self->selected_lib--;
  }

  void nextGl(void* param)
  {
    Launcher* self;

    //std::clog << "next gl" << std::endl;
    self = static_cast<Launcher*>(param);
    if (self->selected_lib != --self->libs.end())
      self->selected_lib++;
  }

  void previousGame(void* param)
  {
    Launcher* self;

    self = static_cast<Launcher*>(param);
    if (self->selected_game != self->games.begin())
      self->selected_game--;
  }

  void nextGame(void* param)
  {
    Launcher* self;

    self = static_cast<Launcher*>(param);
    if (self->selected_game != self->games.end()--)
      self->selected_game++;
  }

  // </editor-fold>

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

  bool Launcher::printText(std::string string, unsigned int x,
			   unsigned int y)
  {
    t_pos	pos;

    pos.x = x;
    pos.y = y;
    return this->graph->drawText(pos, string);
  }

  bool Launcher::printBorderBlock(unsigned int startX, unsigned int startY,
				    unsigned int endX, unsigned int endY,
				    unsigned int color)
  {
    t_pos	end;
    t_pos	wherePrint;
    t_color	blockColor;

    end.x = endX;
    end.y = endY;
    blockColor.full = color;
    for (unsigned int x = startX; x <= end.x; x += (end.x - startX))
    {
      for (unsigned y = startY; y <= end.y; ++y)
      {
	wherePrint.x = x;
	wherePrint.y = y;
	  if (!this->graph->drawBlock(wherePrint, blockColor))
	  return false;
      }
    }
    for (unsigned int y = startY; y <= end.y; y += (end.y - startY))
    {
      for (unsigned x = startX; x <= end.x; ++x)
      {
	wherePrint.x = x;
	wherePrint.y = y;
	if (!this->graph->drawBlock(wherePrint, blockColor))
	  return false;
      }
    }
    return true;
  }

  void Launcher::loop()
  {
    this->graph->registerEvent(CommandType::PLAY, launch_game, this);
    this->graph->registerEvent(CommandType::CLOSE, close, this);
    this->graph->registerEvent(CommandType::PREVIOUS_GL, previousGl, this);
    this->graph->registerEvent(CommandType::NEXT_GL, nextGl, this);
    this->graph->registerEvent(CommandType::PREVIOUS_GAME, previousGame, this);
    this->graph->registerEvent(CommandType::NEXT_GAME,nextGame, this);
    while (this->graph->isOpen() && !this->quit)
    {
      unsigned int x = 3;
      unsigned int y = 5;
      this->graph->execEvents();

      this->graph->clear();
      // titles
      printText("Arcade launcher", 12, 0);
      printText("games", 6, 2);
      printText("librairies", 21, 2);

      // games block
      printBorderBlock(1, 4, 14, 21, 0xFFFFFFFF);
	for (auto it = games.begin(); it != games.end(); ++it)
      {
	printText((*it).first.c_str(), x, y);
	if (it == selected_game)
	{
	  printText(">", x - 1, y);
	}
	++y;
      }

      //libs block
      x = 18;
      y = 5;
      printBorderBlock(16, 4, 30, 21, 0xFFFFFFFF);
      for (auto it = libs.begin(); it != libs.end(); ++it)
      {
	printText((*it).first.c_str(), x, y);
	if (it == selected_lib)
	{
	  printText(">", x - 1, y);
	}
	++y;
      }
      usleep(10000);
      this->graph->refresh();
    }
  }
}
