/*
** main_test.cpp for cpp_arcade in /home/god/TEK2/C++/cpp_arcade/sources/OpenGL/main_test.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Apr 03 07:59:55 2017 Maxime PILLON
** Last update Mon Apr 03 07:59:55 2017 Maxime PILLON
*/

#include "openGL/OpenGLGraph.hpp"

int			main(int ac, char **av)
{
  Arcade::OpenGLGraph	openGl;
  Arcade::t_pos		toto;
Arcade::t_pos		square;

  toto.x = 1024;
  toto.y = 972;

  // add basics color to the background (black + blue)
  openGl.init(toto, "test");
  do
  {
    openGl.refresh();
    openGl.drawBlock
    glfwSwapBuffers(openGl.getWindows());
    glfwPollEvents();

  }
  while( glfwGetKey(openGl.getWindows(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	 glfwWindowShouldClose(openGl.getWindows()) == 0 );
  openGl.close();
  return (0);
}
