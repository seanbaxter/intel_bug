#define GL_GLEXT_PROTOTYPES
#include <gl3w/GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

std::vector<char> read_file(const char* filename) {
  FILE* f = fopen(filename, "r");

  // Should really use stat here.
  fseek(f, 0, SEEK_END);
  size_t length = ftell(f);
  fseek(f, 0, SEEK_SET);

  std::vector<char> v;
  v.resize(length);

  // Read the data.
  fread(v.data(), sizeof(char), length, f);

  // Close the file.
  fclose(f);

  // Return the file.
  return v;
}

void create_shader(GLuint shader, const char* filename, const char* name) {
  printf("Loading shader %s from %s\n", name, filename);
  auto data = read_file(filename);
  glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, data.data(),
    data.size());
  glSpecializeShader(shader, name, 0, nullptr, nullptr);
}

void debug_callback(GLenum source, GLenum type, GLuint id, 
  GLenum severity, GLsizei length, const GLchar* message, 
  const void* user_param) {

  printf("OpenGL: %s\n", message);
}

int main() {

  glfwInit();
  gl3wInit();
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); 
  glfwWindowHint(GLFW_STENCIL_BITS, 8);
  glfwWindowHint(GLFW_SAMPLES, 4); // HQ 4x multisample.
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

  GLFWwindow* window = glfwCreateWindow(800, 800, "Circle does Shadertoy", 
    NULL, NULL);
  if(!window) {
    printf("Cannot create GLFW window\n");
    exit(1);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(debug_callback, nullptr);

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
#ifdef GOOD
  create_shader(vs, "linked_good.spv", "vert1");
#elif defined(BAD)
  create_shader(vs, "linked_bad.spv", "vert2");
#else
  #error "Tell me GOOD or BAD"
#endif
  
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  create_shader(fs, "linked_good.spv", "frag");

  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);

  char log[10000];
  GLsizei len = 10000;
  glGetProgramInfoLog(program, 10000, &len, log);
  printf("program log: %s\n", log);


  return 0;

}