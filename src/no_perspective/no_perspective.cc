#include <application.h>
#include <shader.h>

#include <vmath.h>

class NoPerspective : public application {
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

    mvp_location = glGetUniformLocation(rendering_program, "mvp");

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    static const unsigned char texture_data[] = {
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
        0xFF,
        0x00,
    };

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8, 8, 8);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 8, 8, GL_RED, GL_UNSIGNED_BYTE, texture_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  virtual void render(double current_time) override {
    static const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    static const GLfloat one = 1.0f;

    float f = (float)current_time * 14.3f;

    glViewport(0, 0, 2048, 1536);
    glClearBufferfv(GL_COLOR, 0, black);
    glClearBufferfv(GL_DEPTH, 0, &one);

    projection = vmath::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    mv = vmath::translate(0.0f, 0.0f, -1.5f) *
         vmath::rotate(f, 0.0f, 1.0f, 0.0f);

    glUseProgram(rendering_program);

    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, projection * mv);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }

  virtual void shutdown() override {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
  }

 private:
  GLuint rendering_program;
  GLuint vertex_array_object;
  GLuint texture_id;

  GLuint mvp_location;

  vmath::mat4 projection;
  vmath::mat4 mv;
};

DECLARE_MAIN(NoPerspective);
