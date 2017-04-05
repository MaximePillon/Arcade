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
bool arcade::OpenGLGraph::drawSprite(t_pos const &pos, t_image const &image,
				     t_color const &color)
{
  return true;
}

bool arcade::OpenGLGraph::loadFont(std::string const &pathname)
{
  if (FT_Init_FreeType(&_ft))
    std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

  if (FT_New_Face(_ft, "/usr/share/fonts/dejavu/DejaVuSansMono.ttf", 0, &_face))
    std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;

  FT_Set_Pixel_Sizes(_face, 0, 48);

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
      _face->glyph->advance.x
    };
    Characters.insert(std::pair<GLchar, Character>(c, character));
  }
  FT_Done_Face(_face);
  FT_Done_FreeType(_ft);

  /*unsigned char header[54]; // Each BMP file begins by a 54-bytes header
  unsigned int dataPos = 0;     // Position in the file where the actual data begins
  unsigned int width = 0, height = 0;
  unsigned int imageSize = 0;   // = width*height*3
  unsigned char * data = NULL;

  FILE * file = fopen(pathname.c_str(),"r");
  if (!file)
  {
    printf("Image could not be opened\n");
    return false;
  }
  if ( fread(header, 1, 54, file)!=54 )
  {
    printf("Not a correct BMP file\n");
    return false;
  }
  if ( header[0]!='B' || header[1]!='M' )
  {
    printf("Not a correct BMP file\n");
    return false;
  }
  dataPos    = *(int*)(&(header[0x0A]));
  imageSize  = *(int*)(&(header[0x22]));
  width      = *(int*)(&(header[0x12]));
  height     = *(int*)(&(header[0x16]));

  if (!imageSize)
    imageSize=width*height*3;
  if (!dataPos)
    dataPos=54;

  data = new unsigned char [imageSize];
  fread(data,1,imageSize,file);
  fclose(file);

  // Create one OpenGL texture
  glGenTextures(1, &_textureFont);
  // "Bind" the newly created texture : all future texture functions will modify this texture
  glBindTexture(GL_TEXTURE_2D, _textureFont);

// Give the image to OpenGL
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
*/
  return true;
}

bool arcade::OpenGLGraph::drawText(t_pos const &pos, std::string const &text)
{
  int width, height;

  glfwGetFramebufferSize(_window, &width, &height);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height);

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

  GLuint Shader;
// init shader here
  Shader = glCreateShader(GL_VERTEX_SHADER);
  if (!Shader)
  {
    std::cerr << "Shader creation error" << std::endl;
    return false;
  }

  /* Open and read the shader */
  char *src = NULL;   /* code source de notre shader */
  FILE *fp = NULL;    /* fichier */
  long size;          /* taille du fichier */
  long i;             /* compteur */


  /* on ouvre le fichier */
  fp = fopen("./sources/OpenGL/shader/shader1", "r");
  /* on verifie si l'ouverture a echoue */
  if(fp == NULL)
  {
    fprintf(stderr, "impossible d'ouvrir le fichier '%s'\n", "./sources/OpenGL/shader/shader1");
    return NULL;
  }
  /* on recupere la longueur du fichier */
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  /* on se replace au debut du fichier */
  rewind(fp);
  /* on alloue de la memoire pour y placer notre code source */
  src = malloc(size+1); /* +1 pour le caractere de fin de chaine '\0' */
  if(src == NULL)
  {
    fclose(fp);
    fprintf(stderr, "erreur d'allocation de memoire!\n");
    return NULL;
  }
  /* lecture du fichier */
  for(i=0; i<size; i++)
    src[i] = (char)fgetc(fp);

  /* on place le dernier caractere a '\0' */
  src[size] = '\0';
  fclose(fp);


  glShaderSource(Shader, 1, &src, NULL);
  glCompileShader(Shader);
  free(src);



  // Activate corresponding render state
//  void RenderText(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)

  s.Use();
  glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.x, color.y, color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  // Iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = Characters[*c];

    GLfloat xpos = x + ch.Bearing.x * scale;
    GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

    GLfloat w = ch.Size.x * scale;
    GLfloat h = ch.Size.y * scale;
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
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glDeleteShader(Shader);

  /*
  glfwGetFramebufferSize(_window, &width, &height);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.f, 512.f, 0.f, 512.f, -1.f, 1.f);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D , _textureFont);
  glBegin(GL_QUADS);
  glTexCoord2f(0.f, 0.f);
  //glVertex2f(-25, 0);
  glVertex2f(0.f, 0.f);
  glTexCoord2f(1.f, 0.f);
  glVertex2f(512, 0.f);
  //glVertex2f(-25, 512);
  glTexCoord2f(1.f, 1.f);
  glVertex2f(512.f, 512.f);
  glTexCoord2f(0.f, 1.f);
  glVertex2f(0.f, 512.f);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);*/


  return true;
}


bool arcade::OpenGLGraph::drawBlock(t_pos const &pos, t_color const &color)
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

bool arcade::OpenGLGraph::setBackground(t_image const &image)
{

  return true;
}

/*
 * Window usage
 */
bool arcade::OpenGLGraph::init(t_pos const &size,
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
  if (!loadFont("./res/font.bmp"))
    return false;
  return true;
}

bool arcade::OpenGLGraph::close()
{
  glfwTerminate();
  return true;
}

void arcade::OpenGLGraph::refresh()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

bool arcade::OpenGLGraph::isOpen() const
{
  return _isOpen;
}

void arcade::OpenGLGraph::loop(int frequency, void *handler)
{
}

/*
 * GETTER / SETTER
 */
GLFWwindow * arcade::OpenGLGraph::getWindows() { return _window; }