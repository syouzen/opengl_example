#include <application.h>
#include <shader.h>

#include <vmath.h>

class Framebuffer : public application {
 public:
  virtual void startup() override {
    rendering_program1 = glCreateProgram();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    CompileShader("VertexShader.vertexshader", vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    CompileShader("FragmentShader1.fragmentshader", fs);

    glAttachShader(rendering_program1, vs);
    glAttachShader(rendering_program1, fs);

    glLinkProgram(rendering_program1);

    glDeleteShader(vs);
    glDeleteShader(fs);

    rendering_program2 = glCreateProgram();

    vs = glCreateShader(GL_VERTEX_SHADER);
    CompileShader("VertexShader.vertexshader", vs);

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    CompileShader("FragmentShader2.fragmentshader", fs);

    glAttachShader(rendering_program2, vs);
    glAttachShader(rendering_program2, fs);

    glLinkProgram(rendering_program2);

    glDeleteShader(vs);
    glDeleteShader(fs);

    mv_location1 = glGetUniformLocation(rendering_program1, "mv");
    projection_location1 = glGetUniformLocation(rendering_program1, "projection");
    mv_location2 = glGetUniformLocation(rendering_program2, "mv");
    projection_location2 = glGetUniformLocation(rendering_program2, "projection");

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
        0.25f,
        0.0f,
        1.0f,
        -0.25f,
        -0.25f,
        -0.25f,
        0.0f,
        0.0f,
        0.25f,
        -0.25f,
        -0.25f,
        1.0f,
        0.0f,

        0.25f,
        -0.25f,
        -0.25f,
        1.0f,
        0.0f,
        0.25f,
        -0.25f,
        0.25f,
        1.0f,
        1.0f,
        -0.25f,
        -0.25f,
        0.25f,
        0.0f,
        1.0f,

        0.25f,
        -0.25f,
        -0.25f,
        0.0f,
        0.0f,
        0.25f,
        0.25f,
        -0.25f,
        1.0f,
        0.0f,
        0.25f,
        -0.25f,
        0.25f,
        0.0f,
        1.0f,

        0.25f,
        0.25f,
        -0.25f,
        1.0f,
        0.0f,
        0.25f,
        0.25f,
        0.25f,
        1.0f,
        1.0f,
        0.25f,
        -0.25f,
        0.25f,
        0.0f,
        1.0f,

        0.25f,
        0.25f,
        -0.25f,
        1.0f,
        0.0f,
        -0.25f,
        0.25f,
        -0.25f,
        0.0f,
        0.0f,
        0.25f,
        0.25f,
        0.25f,
        1.0f,
        1.0f,

        -0.25f,
        0.25f,
        -0.25f,
        0.0f,
        0.0f,
        -0.25f,
        0.25f,
        0.25f,
        0.0f,
        1.0f,
        0.25f,
        0.25f,
        0.25f,
        1.0f,
        1.0f,

        -0.25f,
        0.25f,
        -0.25f,
        1.0f,
        0.0f,
        -0.25f,
        -0.25f,
        -0.25f,
        0.0f,
        0.0f,
        -0.25f,
        0.25f,
        0.25f,
        1.0f,
        1.0f,

        -0.25f,
        -0.25f,
        -0.25f,
        0.0f,
        0.0f,
        -0.25f,
        -0.25f,
        0.25f,
        0.0f,
        1.0f,
        -0.25f,
        0.25f,
        0.25f,
        1.0f,
        1.0f,

        -0.25f,
        0.25f,
        -0.25f,
        0.0f,
        1.0f,
        0.25f,
        0.25f,
        -0.25f,
        1.0f,
        1.0f,
        0.25f,
        -0.25f,
        -0.25f,
        1.0f,
        0.0f,

        0.25f,
        -0.25f,
        -0.25f,
        1.0f,
        0.0f,
        -0.25f,
        -0.25f,
        -0.25f,
        0.0f,
        0.0f,
        -0.25f,
        0.25f,
        -0.25f,
        0.0f,
        1.0f,

        -0.25f,
        -0.25f,
        0.25f,
        0.0f,
        0.0f,
        0.25f,
        -0.25f,
        0.25f,
        1.0f,
        0.0f,
        0.25f,
        0.25f,
        0.25f,
        1.0f,
        1.0f,

        0.25f,
        0.25f,
        0.25f,
        1.0f,
        1.0f,
        -0.25f,
        0.25f,
        0.25f,
        0.0f,
        1.0f,
        -0.25f,
        -0.25f,
        0.25f,
        0.0f,
        0.0f,
    };

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glGenFramebuffers(1, &frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

    glGenTextures(1, &color_texture);
    glBindTexture(GL_TEXTURE_2D, color_texture);
    glTexStorage2D(GL_TEXTURE_2D, 9, GL_RGBA8, 512, 512);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexStorage2D(GL_TEXTURE_2D, 9, GL_DEPTH_COMPONENT32F, 512, 512);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color_texture, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture, 0);

    static const GLenum draw_buffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, draw_buffers);
  }

  virtual void render(double current_time) override {
    static const GLfloat green[] = {0.0f, 0.3f, 0.0f, 1.0f};
    static const GLfloat blue[] = {0.0f, 0.0f, 0.3f, 1.0f};
    static const GLfloat one = 1.0f;
    float f = (float)current_time * 0.3f;
    projection = vmath::perspective(50.0f,
                                    4.0f / 3.0f,
                                    0.1f,
                                    1000.0f);
    mv = vmath::translate(0.0f, 0.0f, -4.0f) *
         vmath::translate(sinf(2.1f * f) * 0.5f,
                          cosf(1.7f * f) * 0.5f,
                          sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) *
         vmath::rotate((float)current_time * 45.0f, 0.0f, 1.0f, 0.0f) *
         vmath::rotate((float)current_time * 81.0f, 1.0f, 0.0f, 0.0f);

    glUseProgram(rendering_program1);
    glViewport(0, 0, 512, 512);
    glClearBufferfv(GL_COLOR, 0, green);
    glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    glUniformMatrix4fv(projection_location1, 1, GL_FALSE, projection);
    glUniformMatrix4fv(mv_location1, 1, GL_FALSE, mv);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUseProgram(rendering_program2);
    glViewport(0, 0, 2048, 1536);
    glClearBufferfv(GL_COLOR, 0, blue);
    glClearBufferfv(GL_DEPTH, 0, &one);
    glBindTexture(GL_TEXTURE_2D, color_texture);
    glUniformMatrix4fv(projection_location2, 1, GL_FALSE, projection);
    glUniformMatrix4fv(mv_location2, 1, GL_FALSE, mv);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindTexture(GL_TEXTURE_2D, 0);
  }

  virtual void shutdown() override {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program1);
    glDeleteProgram(rendering_program2);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &index_buffer);
    glDeleteFramebuffers(1, &frame_buffer);
    glDeleteTextures(1, &color_texture);
    glDeleteTextures(1, &depth_texture);
  }

 private:
  GLuint rendering_program1;
  GLuint rendering_program2;
  GLuint vertex_array_object;
  GLuint vertex_buffer;
  GLuint index_buffer;
  GLuint frame_buffer;

  GLuint color_texture;
  GLuint depth_texture;

  GLuint mv_location1;
  GLuint projection_location1;
  GLuint mv_location2;
  GLuint projection_location2;

  vmath::mat4 mv;
  vmath::mat4 projection;
};

DECLARE_MAIN(Framebuffer);
