/*
** IGame.hpp for cpp_arcade in /home/loens_g/rendu/TEK2/CPP/cpp_arcade/includes/game/IGame.hpp
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Wed Apr 05 11:59:13 2017 Gregoire LOENS
** Last update Wed Apr 05 11:59:13 2017 Gregoire LOENS
*/

#ifndef IGAME_HPP
# define IGAME_HPP

# include "arcade_protocol.hpp"
# include "IGraph.hpp"

class IGame
{
public:
  virtual void moveUp(void *param) = 0;
  virtual void moveRight(void *param) = 0;
  virtual void moveLeft(void *param) = 0;
  virtual void moveDown(void *param) = 0;
  virtual void moveForward(void *param) = 0;
  virtual void shoot(void *param) = 0;

public:
  virtual void getMap(void *param) = 0;
  virtual void whereAmI(void *param) = 0;

public:
  virtual void play() = 0;
  virtual void play(IGraph const& graph) = 0;

public:
  virtual ~IGame() {}
};

#endif // IGAME_HPP
