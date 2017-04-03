/*
** openGL.hpp for cpp_arcade in /home/god/TEK2/C++/cpp_arcade/includes/openGL/openGLGraph.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Mon Apr 03 07:39:02 2017 Maxime PILLON
** Last update Mon Apr 03 07:39:02 2017 Maxime PILLON
*/

#ifndef CPP_ARCADE_OPENGL_HPP
# define CPP_ARCADE_OPENGL_HPP

#include <stdio.h>
#include <stdlib.h>
#include <list>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "IGraph.hpp"

namespace Arcade
{
  class OpenGLGraph : public IGraph
  {
  protected:
    GLFWwindow* _window;
    bool _isOpen;

  public:
    OpenGLGraph();
    virtual ~OpenGLGraph();

  public:
    bool drawText(t_pos const& pos,
		  std::string const& text);
    bool drawSprite(t_pos const& pos,
		    t_image const& image, t_color const& color);
    bool drawBlock(t_pos const& pos,
		   t_color const& color);
    bool setBackground(t_image const& image);

  public:
    bool init(t_pos const& size, std::string const& window_name);
    bool close(void);
    void refresh(void);
    bool isOpen(void);

    // GETTER  | SETTER
    GLFWwindow *getWindows();
  };
}

#endif //CPP_ARCADE_OPENGL_HPP
