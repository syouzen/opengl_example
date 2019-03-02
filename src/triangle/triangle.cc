#include <application.h>
#include <shader.h>

class Triangle : public application {
 public:
  virtual void startup() override {
    rendering_program = LoadShaders("VertexShader.vertexshader", "FragmentShader.fragmentshader");

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    static const GLfloat vertex_buffer_data[] = {
        -1.0f,
        -1.0f,
        0.0f,
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
    };

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
  }

  virtual void render(double current_time) override {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(rendering_program);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
  }

  virtual void shutdown() override {
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
  }

 private:
  GLuint rendering_program;
  GLuint vertex_array_object;
  GLuint vertex_buffer;
};

DECLARE_MAIN(Triangle);
