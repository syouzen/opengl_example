#include <application.h>
#include <shader.h>
#include <vmath.h>

class AntiAliasing : public application {
 public:
  virtual void startup() override {
    rendering_program = glCreateProgram();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    CompileShader("VertexShader.vertexshader", vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    CompileShader("FragmentShader.fragmentshader", fs);

    glAttachShader(rendering_program, vs);
    glAttachShader(rendering_program, fs);

    glLinkProgram(rendering_program);

    mv_location = glGetUniformLocation(rendering_program, "mv");
    projection_location = glGetUniformLocation(rendering_program, "projection");

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    static const GLushort index_data[] = {
        0, 1, 2,
        2, 1, 3,
        2, 3, 4,
        4, 3, 5,
        4, 5, 6,
        6, 5, 7,
        6, 7, 0,
        0, 7, 1,
        6, 0, 2,
        2, 4, 6,
        7, 5, 3,
        7, 3, 1};

    static const GLfloat vertex_data[] = {
        -0.25f,
        -0.25f,
        -0.25f,
        -0.25f,
        0.25f,
        -0.25f,
        0.25f,
        -0.25f,
        -0.25f,
        0.25f,
        0.25f,
        -0.25f,
        0.25f,
        -0.25f,
        0.25f,
        0.25f,
        0.25f,
        0.25f,
        -0.25f,
        -0.25f,
        0.25f,
        -0.25f,
        0.25f,
        0.25f,
    };

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

    glEnable(GL_CULL_FACE);
  }

  virtual void render(double current_time) override {
    static const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    static const GLfloat one = 1.0f;

    glViewport(0, 0, 1024 * 2, 768 * 2);
    glClearBufferfv(GL_COLOR, 0, black);

    glUseProgram(rendering_program);

    projection = vmath::perspective(50.0f,
                                    4.0f / 3.0f,
                                    0.1f,
                                    1000.0f);

    glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);

    float f = (float)current_time * 0.3f;
    current_time = 3.15f;
    mv = vmath::translate(0.0f, 0.0f, -4.0f) *
         vmath::rotate((float)current_time * 45.0f, 0.0f, 1.0f, 0.0f) *
         vmath::rotate((float)current_time * 81.0f, 1.0f, 0.0f, 0.0f);

    glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
  }

  virtual void shutdown() override {
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &index_buffer);
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
  }

 private:
  GLuint rendering_program;
  GLuint vertex_array_object;
  GLuint vertex_buffer;
  GLuint index_buffer;

  GLuint mv_location;
  GLuint projection_location;
  vmath::mat4 mv;
  vmath::mat4 projection;
};

DECLARE_MAIN(AntiAliasing);
