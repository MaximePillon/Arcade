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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  // When a user presses the escape key, we set the WindowShouldClose property to true,
  // closing the application
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int			main(int ac, char **av)
{
  arcade::OpenGLGraph	openGl;
  arcade::t_pos		toto;
  arcade::t_pos		square;
  arcade::t_color	color;

  color.argb[0] = 255;
  color.argb[1] = 0;
  color.argb[2] = 255;
  color.argb[3] = 0;
  toto.x = 1024;
  toto.y = 512;
  // add basics color to the background (black + blue)
  openGl.init(toto, "test");
  glfwSetKeyCallback(openGl.getWindows(), key_callback);
  while(!glfwWindowShouldClose(openGl.getWindows()))
  {
    // Check and call events
    glfwPollEvents();

    // Rendering commands here
    openGl.refresh();
    square.x = 50;
    square.y = 50;
    openGl.drawBlock(square, color);
    openGl.drawText(square, "abcd");

    // Swap the buffers
    glfwSwapBuffers(openGl.getWindows());

  }
  openGl.close();
  return (0);
}