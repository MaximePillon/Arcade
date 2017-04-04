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

  return true;
}

bool Arcade::OpenGLGraph::drawSprite(t_pos const &pos, t_image const &image,
				     t_color const &color)
{
  return true;
}

bool Arcade::OpenGLGraph::drawBlock(t_pos const &pos, t_color const &color)
{
  int width, height;
  t_pos		tmpPosMax;
  t_pos		tmpPos;

  glfwGetFramebufferSize(_window, &width, &height);
  glClear( GL_COLOR_BUFFER_BIT);
  glColor3f(static_cast<float>(color.argb[1]), static_cast<float>(color.argb[2]), static_cast<float>(color.argb[3]));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.f, static_cast<float>(width), static_cast<float>(height), 0.f, 0.f, 1.f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRecti(pos.x * BLOCK_SIZE, pos.y * BLOCK_SIZE, pos.x * BLOCK_SIZE + BLOCK_SIZE, pos.y * BLOCK_SIZE + BLOCK_SIZE);
  return true;
}

bool Arcade::OpenGLGraph::setBackground(t_image const &image)
{

  return true;
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
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  _window = glfwCreateWindow( size.x, size.y, window_name.c_str(), NULL, NULL);
  if (!_window)
  {
    std::cerr << "Failed to open GLFW window\n";
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(_window);

  // initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
  _isOpen = true;
  return true;
}

bool Arcade::OpenGLGraph::close()
{
  glfwTerminate();
  return true;
}

void Arcade::OpenGLGraph::refresh()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

bool Arcade::OpenGLGraph::isOpen() const
{
  return _isOpen;
}

void Arcade::OpenGLGraph::loop(int frequency, void *handler)
{
}

/*
 * GETTER / SETTER
 */
GLFWwindow * Arcade::OpenGLGraph::getWindows() { return _window; }