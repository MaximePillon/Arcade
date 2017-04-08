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
#include <openGL/OpenGLGraph.hpp>
#include <IGraph.hpp>
#include "openGL/OpenGLGraph.hpp"



/*
 * Constructor and destructor
 */

arcade::OpenGLGraph::OpenGLGraph()
{
  _isOpen = false;
}

arcade::OpenGLGraph::~OpenGLGraph()
{

}

/*
 * Edit window function
 */
bool arcade::OpenGLGraph::loadFont()
{

  /*
   *
   * Font for text
   *
   */
  if (FT_Init_FreeType(&_ft))
    std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

  if (FT_New_Face(_ft, "res/DejaVuSansMono.ttf", 0, &_face))
    std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;

  FT_Set_Pixel_Sizes(_face, 0, 25);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction


  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph
    if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
    {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      _face->glyph->bitmap.width,
      _face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      _face->glyph->bitmap.buffer
    );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Now store character for later use
    Character character = {
      texture,
      glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
      glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
      static_cast<GLuint>(_face->glyph->advance.x)
    };
    Characters.insert(std::pair<GLchar, Character>(c, character));
  }
  /*
   *
   * Font for block
   *
   */
  FT_Set_Pixel_Sizes(_face, 0, 50);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction


  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph
    if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
    {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      _face->glyph->bitmap.width,
      _face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      _face->glyph->bitmap.buffer
    );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Now store character for later use
    Character character = {
      texture,
      glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
      glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
      static_cast<GLuint>(_face->glyph->advance.x)
    };
    Block.insert(std::pair<GLchar, Character>(c, character));
  }


  FT_Done_Face(_face);
  FT_Done_FreeType(_ft);
  return true;
}


bool arcade::OpenGLGraph::drawText(t_pos const &pos, std::string const &text)
{
  int width, height;

  glfwGetFramebufferSize(_window, &width, &height);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Shader shader("./sources/OpenGL/shader/shader1.vec", "./sources/OpenGL/shader/shader2.fra");
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));
  shader.Use();
  glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  t_pos newpos;
  newpos.x = pos.x * BLOCK_SIZE;
  newpos.y = height - ((pos.y  + 1) * BLOCK_SIZE);

  glm::vec3 color(1.f, 1.f, 1.f);
  shader.Use();
  glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  // Iterate through all characters
  // for (auto it = text.begin() : text)
  for (auto c = text.begin(); c != text.end(); c++)
  {
    Character ch = Characters[*c];
    GLfloat xpos = (float)newpos.x + ch.Bearing.x * 1;
    GLfloat ypos = (float)newpos.y - (ch.Size.y - ch.Bearing.y) * 1;

    GLfloat w = ch.Size.x * 1;
    GLfloat h = ch.Size.y * 1;
    // Update VBO for each character
    GLfloat vertices[6][4] = {
      { xpos,     ypos + h,   0.0, 0.0 },
      { xpos,     ypos,       0.0, 1.0 },
      { xpos + w, ypos,       1.0, 1.0 },

      { xpos,     ypos + h,   0.0, 0.0 },
      { xpos + w, ypos,       1.0, 1.0 },
      { xpos + w, ypos + h,   1.0, 0.0 }
    };
    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    newpos.x += (ch.Advance >> 6) * 1; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  return true;
}


bool arcade::OpenGLGraph::drawBlock(t_pos const &pos, t_color const &color_char)
{
  int width, height;

  glfwGetFramebufferSize(_window, &width, &height);
  std::string text("o");
  glDisable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Shader shader("./sources/OpenGL/shader/shader1.vec", "./sources/OpenGL/shader/shader2.fra");
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));
  shader.Use();
  glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  t_pos newpos;
  newpos.x = pos.x * BLOCK_SIZE;
  newpos.y = height - ((pos.y  + 1) * BLOCK_SIZE);

  glm::vec3 color(static_cast<float>(color_char.argb[1] / 255), static_cast<float>(color_char.argb[2] / 255), static_cast<float>(color_char.argb[3] / 255));
  shader.Use();
  glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  // Iterate through all characters
  // for (auto it = text.begin() : text)
  for (auto c = text.begin(); c != text.end(); c++)
  {
    Character ch = Block[*c];
    GLfloat xpos = (float)newpos.x + ch.Bearing.x * 1;
    GLfloat ypos = (float)newpos.y - (ch.Size.y - ch.Bearing.y) * 1;

    GLfloat w = ch.Size.x * 1;
    GLfloat h = ch.Size.y * 1;
    // Update VBO for each character
    GLfloat vertices[6][4] = {
      { xpos,     ypos + h,   0.0, 0.0 },
      { xpos,     ypos,       0.0, 1.0 },
      { xpos + w, ypos,       1.0, 1.0 },

      { xpos,     ypos + h,   0.0, 0.0 },
      { xpos + w, ypos,       1.0, 1.0 },
      { xpos + w, ypos + h,   1.0, 0.0 }
    };
    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    newpos.x += (ch.Advance >> 6) * 1; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  return true;
}

/*
 * Window usage
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  // When a user presses the escape key, we set the WindowShouldClose property to true,
  // closing the application
  (void)scancode;
  (void)mode;
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}


void arcade::OpenGLGraph::initMap()
{
  this->keyboard[CommandType::GO_UP] = GLFW_KEY_UP;
  this->keyboard[CommandType::GO_DOWN] = GLFW_KEY_DOWN;
  this->keyboard[CommandType::GO_RIGHT] = GLFW_KEY_RIGHT;
  this->keyboard[CommandType::GO_LEFT] = GLFW_KEY_LEFT;
  this->keyboard[CommandType::SHOOT] = GLFW_KEY_SPACE;
  this->keyboard[CommandType::CLOSE] = GLFW_KEY_ESCAPE;
  this->keyboard[CommandType::PREVIOUS_GL] = GLFW_KEY_2;
  this->keyboard[CommandType::NEXT_GL] = GLFW_KEY_3;
  this->keyboard[CommandType::PREVIOUS_GAME] = GLFW_KEY_4;
  this->keyboard[CommandType::NEXT_GAME] = GLFW_KEY_5;
  this->keyboard[CommandType::RESTART] = GLFW_KEY_8;
  this->keyboard[CommandType::MENU] = GLFW_KEY_9;
  this->keyboard[CommandType::PLAY] = GLFW_KEY_ENTER;

}

bool arcade::OpenGLGraph::init(t_pos const &size,
			       std::string const &window_name)
{
  // initialise GLFW
  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW\n";
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  _window = glfwCreateWindow( size.x * BLOCK_SIZE, size.y * BLOCK_SIZE, window_name.c_str(), NULL, NULL);
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

  // Load font for text and blick rendering
  if (!loadFont())
    return false;

  // initialise the corresponding of maccro key
  initMap();

  // set the close calback
  glfwSetKeyCallback(_window, key_callback);
  return true;
}

bool arcade::OpenGLGraph::setBackground(t_color const &color)
{
  glClearColor(static_cast<float>(color.argb[1] / 255), static_cast<float>(color.argb[2] / 255), static_cast<float>(color.argb[3] / 255), static_cast<float>(color.argb[0] / 255));
  return true;
}

bool arcade::OpenGLGraph::close()
{
  glfwTerminate();
  return true;
}

void arcade::OpenGLGraph::refresh()
{
  glfwSwapBuffers(_window);
  glClear(GL_COLOR_BUFFER_BIT);
}

void arcade::OpenGLGraph::clear() const {}

bool arcade::OpenGLGraph::isOpen() const
{
  if (glfwWindowShouldClose(_window))
    return false;
  return _isOpen;
}

void arcade::OpenGLGraph::loop(int frequency, void *handler)
{
  (void)frequency;
  (void)handler;
}

void arcade::OpenGLGraph::execEvents()
{
  glfwPollEvents();
  for (auto &it : this->keyboard)
    if (glfwGetKey(_window, it.second) == GLFW_PRESS)
      this->eventMap[it.first].hdl(this->eventMap[it.first].param);
}

void arcade::OpenGLGraph::registerEvent(CommandType command, event_handler hdl,
					void *param)
{
  handler_t		tmp;

  tmp.hdl = hdl;
  tmp.param = param;
  this->eventMap[command] = tmp;
}

/*
 * GETTER / SETTER
 */
GLFWwindow * arcade::OpenGLGraph::getWindows() { return _window; }

extern "C" { arcade::IGraph* create_graph() { return new arcade::OpenGLGraph(); } }
