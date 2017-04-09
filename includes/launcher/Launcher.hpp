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
# include <map>
# include <dlfcn.h>
# include <vector>
# include "IGraph.hpp"

namespace arcade
{

  class Launcher
  {
  public:
    Launcher();

    ~Launcher()
    {};

  protected:
    bool printText(std::string string, unsigned int x, unsigned int y);

    bool printBorderBlock(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY, unsigned int color);

  public:
    int openLib(std::string const &filename);

    void* loadSym(std::string const& symName) const;

    int closeLib();

    int openGameLib(std::string const &filename);

    void* loadGameSym(std::string const& symName) const;

    int closeGameLib();

    int openGraphLib(std::string const &filename);

    void* loadGraphSym(std::string const& symName) const;

    int closeGraphLib();

    int start(std::string const& graph_path);

    void end();

    void loop();

    void get_libs();

    void printChar();

  protected:
    void* handle;
    void* game_handle;
    void* graph_handle;

  public:
    arcade::IGraph* graph;
    std::map<std::string, std::string> libs;
    std::map<std::string, std::string> games;
    std::map<std::string, std::string>::iterator selected_lib;
    std::map<std::string, std::string>::iterator selected_game;
    std::string	playerName;
    std::vector<char> letter;
    std::string	cursX;
    int		posCurs;
    int index;
    bool setName;
    bool quit;
  };
}

#endif // LAUNCHER_HPP
