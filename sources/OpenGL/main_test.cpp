/*
** main_test.cpp for cpp_arcade in /home/god/TEK2/C++/cpp_arcade/sources/OpenGL/main_test.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Apr 03 07:59:55 2017 Maxime PILLON
** Last update Mon Apr 03 07:59:55 2017 Maxime PILLON
*/

#include <IGraph.hpp>
#include "openGL/OpenGLGraph.hpp"



int			main(int ac, char **av)
{
  arcade::OpenGLGraph	openGl;
  arcade::t_pos		toto;
  arcade::t_pos		square;
  arcade::t_color	color;

  color.argb[0] = 0;
  color.argb[1] = 255;
  color.argb[2] = 255;
  color.argb[3] = 255;
  toto.x = 1024;
  toto.y = 512;
  // add basics color to the background (black + blue)
  openGl.init(toto, "test");

  while(openGl.isOpen())
  {
    openGl.execEvents();
    // Rendering commands here
    openGl.refresh();
    color.argb[1] = 255;
    color.argb[2] = 255;
    color.argb[3] = 255;
    openGl.setBackground(color);
    color.argb[3] = 0;
    color.argb[2] = 0;
    color.argb[1] = 0;
    square.x = 0;
    square.y = 0;
    openGl.drawBlock(square, color);
    square.x += 1;
    openGl.drawBlock(square, color);
    square.x -= 1;
    color.argb[1] = 0;
    square.y = 1;
    openGl.drawText(square, "score:");

    // Swap the buffers
  }
  openGl.close();
  return (0);
}
