#include <application.h>
#include <objloader.h>
#include <shader.h>
#include <texture.h>

class ModelLoader : public application {
 public:
  virtual void startup() override {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    rendering_program = LoadShaders("VertexShader.vertexshader", "FragmentShader.fragmentshader");

    bool res = loadOBJ("cube.obj", vertices, uvs, normals);
    texture = loadDDS("uvmap.DDS");

    texture_id = glGetUniformLocation(rendering_program, "textureSampler");

    /* Create VAO and Bind to GL Context */
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    /* Create Buffer Name */
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uv_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    matrix_id = glGetUniformLocation(rendering_program, "MVP");

    projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    view = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  }

  virtual void render(double current_time) override {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(rendering_program);

    float f = (float)current_time * (float)M_PI * 0.1f;

    model = glm::rotate(glm::mat4(1.0f), f, glm::vec3(1.0));
    mvp = projection * view * model;

    glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(texture_id, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
  }

  virtual void shutdown() override {
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &uv_buffer);
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
  }

 private:
  GLuint rendering_program;
  GLuint vertex_array_object;
  GLuint vertex_buffer;
  GLuint uv_buffer;

  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;

  GLuint texture;
  GLuint texture_id;

  GLuint matrix_id;
  glm::mat4 projection;
  glm::mat4 view;
  glm::mat4 model;
  glm::mat4 mvp;
};

DECLARE_MAIN(ModelLoader);
