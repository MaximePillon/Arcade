/*
** OpenGLGraph.cpp for cpp_arcade in /home/god/TEK2/C++/cpp_arcade/sources/OpenGL/OpenGLGraph.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Apr 03 07:57:41 2017 Maxime PILLON
** Last update Mon Apr 03 07:57:41 2017 Maxime PILLON
*/

#include <iostream>
#include "openGL/OpenGLGraph.hpp"

/*
 * Constructor and destructor
 */

Arcade::OpenGLGraph::OpenGLGraph()
{
  _isOpen = false;
}

Arcade::OpenGLGraph::~OpenGLGraph()
{

}

/*
 * Edit window function
 */
bool Arcade::OpenGLGraph::drawText(t_pos const &pos, std::string const &text)
{

}

bool Arcade::OpenGLGraph::drawSprite(t_pos const &pos, t_image const &image,
				     t_color const &color)
{

}

bool Arcade::OpenGLGraph::drawBlock(t_pos const &pos, t_color const &color)
{
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool Arcade::OpenGLGraph::setBackground(t_image const &image)
{

}

/*
 * Window usage
 */
bool Arcade::OpenGLGraph::init(t_pos const &size,
			       std::string const &window_name)
{
  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW\n";
    getchar();
    return false;
  }
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  _window = glfwCreateWindow( size.x, size.y, window_name.c_str(), NULL, NULL);
  if (_window == NULL)
  {
    std::cerr << "Failed to open GLFW window\n";
    getchar();
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(_window);
  if (glewInit() != GLEW_OK)
  {
    std::cerr << "Failed to initialize GLEW\n";
    getchar();
    glfwTerminate();
    return false;
  }
  glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  _isOpen = true;
}

bool Arcade::OpenGLGraph::close()
{
  glfwTerminate();
}

void Arcade::OpenGLGraph::refresh()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

bool Arcade::OpenGLGraph::isOpen()
{
  return _isOpen;
}

/*
 * GETTER / SETTER
 */
GLFWwindow * Arcade::OpenGLGraph::getWindows() { return _window; }