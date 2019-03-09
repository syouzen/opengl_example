#include <application.h>
#include <shader.h>

class Instancing : public application {
 public:
  virtual void startup() override {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    rendering_program = LoadShaders("VertexShader.vertexshader", "FragmentShader.fragmentshader");

    /* Create VAO and Bind to GL Context */
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    static const GLfloat vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f};

    static const GLfloat color_buffer_data[] = {
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        0.0f,
        1.0f,
    };

    static const GLfloat instance_buffer_data[] = {
        -2.0f, -2.0f, 0.0f, 0.0f,
        2.0f, -2.0f, 0.0f, 0.0f,
        2.0f, 2.0f, 0.0f, 0.0f,
        -2.0f, 2.0f, 0.0f, 0.0f};

    GLuint offset = 0;

    glGenBuffers(1, &square_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, square_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data) + sizeof(color_buffer_data) + sizeof(instance_buffer_data), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertex_buffer_data), vertex_buffer_data);
    offset += sizeof(vertex_buffer_data);

    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color_buffer_data), color_buffer_data);
    offset += sizeof(color_buffer_data);

    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(instance_buffer_data), instance_buffer_data);
    offset += sizeof(instance_buffer_data);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(vertex_buffer_data));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(vertex_buffer_data) + sizeof(color_buffer_data)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
  }

  virtual void render(double current_time) override {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(rendering_program);

    glBindVertexArray(vertex_array_object);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 4);
  }

  virtual void shutdown() override {
    glDeleteBuffers(1, &square_buffer);
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
  }

 private:
  GLuint rendering_program;
  GLuint vertex_array_object;
  GLuint square_buffer;
};

DECLARE_MAIN(Instancing);
