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

#include <cstdio>
#include <cstdlib>
#include <list>
#include <map>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "IGraph.hpp"
#include "shader.hpp"
namespace arcade
{
  struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
  };

  class OpenGLGraph : public IGraph
  {
  protected:
    Shader* _shader;
    GLFWwindow* _window;
    bool _isOpen;
    GLuint _textureFont;
    FT_Library _ft;
    FT_Face _face;
    std::map<GLchar, Character> Characters;
    std::map<GLchar, Character> Block;
    std::map<CommandType, int>	keyboard; //!< Map of keyboard macros
    std::map<CommandType, handler_t>		eventMap; //!< Map of handler

  public:
    OpenGLGraph();
    virtual ~OpenGLGraph();

  public:
    bool drawText(t_pos const& pos,
		  std::string const& text);
    bool drawBlock(t_pos const& pos,
		   t_color const& color);

  public:
    void initMap();
    bool init(t_pos const& size, std::string const& window_name);
    bool loadFont();
    bool close(void);
    void refresh(void);
    void clear(void) const;
    bool isOpen(void) const;
    void loop(int frequency, void *handler);
    virtual void registerEvent(CommandType command,
			       event_handler hdl,
			       void* param);
    void execEvents();
    bool setBackground(t_color const& color);

    // GETTER  | SETTER
    GLFWwindow *getWindows();
  };
}

#endif //CPP_ARCADE_OPENGL_HPP
