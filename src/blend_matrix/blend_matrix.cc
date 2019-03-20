#include <application.h>
#include <shader.h>

#include <vmath.h>

class BlendMatrix : public application {
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
        -0.25f, -0.25f, -0.25f,
        -0.25f, 0.25f, -0.25f,
        0.25f, -0.25f, -0.25f,
        0.25f, 0.25f, -0.25f,
        0.25f, -0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        -0.25f, -0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f};

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
    static const GLfloat orange[] = {0.6f, 0.4f, 0.1f, 1.0f};
    static const GLfloat one = 1.0f;
    static const GLenum blend_funcs[] = {
        GL_ZERO,
        GL_ONE,
        GL_SRC_COLOR,
        GL_ONE_MINUS_SRC_COLOR,
        GL_DST_COLOR,
        GL_ONE_MINUS_DST_COLOR,
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_ALPHA,
        GL_ONE_MINUS_DST_ALPHA,
        GL_CONSTANT_COLOR,
        GL_ONE_MINUS_CONSTANT_COLOR,
        GL_CONSTANT_ALPHA,
        GL_ONE_MINUS_CONSTANT_ALPHA,
        GL_SRC_ALPHA_SATURATE,
        GL_SRC1_COLOR,
        GL_ONE_MINUS_SRC1_COLOR,
        GL_SRC1_ALPHA,
        GL_ONE_MINUS_SRC1_ALPHA};

    static const int num_blend_funcs = sizeof(blend_funcs) / sizeof(blend_funcs[0]);
    static const float x_scale = 20.0f / float(num_blend_funcs);
    static const float y_scale = 16.0f / float(num_blend_funcs);
    const float f = (float)current_time;

    glViewport(0, 0, 2048, 1536);
    glClearBufferfv(GL_COLOR, 0, orange);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glUseProgram(rendering_program);

    projection = vmath::perspective(50.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection);

    glEnable(GL_BLEND);
    glBlendColor(0.2f, 0.5f, 0.7f, 0.5f);

    for (int j = 0; j < num_blend_funcs; j++) {
      for (int i = 0; i < num_blend_funcs; i++) {
        mv = vmath::translate(9.5f - x_scale * float(i),
                              7.5f - y_scale * float(j),
                              -18.0f) *
             vmath::rotate(f * -45.0f, 0.0f, 1.0f, 0.0f) *
             vmath::rotate(f * -21.0f, 1.0f, 0.0f, 0.0f);

        glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv);
        glBlendFunc(blend_funcs[i], blend_funcs[j]);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
      }
    }
  }

  virtual void shutdown() override {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &index_buffer);
  }

 private:
  GLuint rendering_program;
  GLuint vertex_array_object;
  GLuint vertex_buffer;
  GLuint index_buffer;

  GLuint projection_location;
  GLuint mv_location;

  vmath::mat4 projection;
  vmath::mat4 mv;
};

DECLARE_MAIN(BlendMatrix);
