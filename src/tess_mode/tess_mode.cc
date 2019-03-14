#include <application.h>
#include <shader.h>

class TessMode : public application {
 public:
  virtual void startup() override {
    rendering_program = glCreateProgram();

    const char* vs_code = ReadShaderCode("VertexShader.vertexshader");
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_code, NULL);
    glCompileShader(vs);

    const char* tcs_code = ReadShaderCode("TessControlShader.tesscontrolshader");
    GLuint tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tcs, 1, &tcs_code, NULL);
    glCompileShader(tcs);

    const char* tes_code = ReadShaderCode("TessEvaluationShader.tessevaluationshader");
    GLuint tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tes, 1, &tes_code, NULL);
    glCompileShader(tes);

    const char* fs_code = ReadShaderCode("FragmentShader.fragmentshader");
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_code, NULL);
    glCompileShader(fs);

    glAttachShader(rendering_program, vs);
    glAttachShader(rendering_program, tcs);
    glAttachShader(rendering_program, tes);
    glAttachShader(rendering_program, fs);

    glLinkProgram(rendering_program);

    glDeleteShader(vs);
    glDeleteShader(tcs);
    glDeleteShader(tes);
    glDeleteShader(fs);

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  virtual void render(double current_time) override {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(rendering_program);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_PATCHES, 0, 4);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  virtual void shutdown() override {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
  }

 private:
  GLuint rendering_program;
  GLuint vertex_array_object;
};

DECLARE_MAIN(TessMode);
