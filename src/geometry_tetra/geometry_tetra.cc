#include <application.h>
#include <shader.h>

#include <vmath.h>

class GeometryTetra : public application {
 public:
  virtual void startup() override {
    rendering_program = glCreateProgram();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    CompileShader("VertexShader.vertexshader", vs);

    GLuint gs = glCreateShader(GL_GEOMETRY_SHADER);
    CompileShader("GeometryShader.geometryshader", gs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    CompileShader("FragmentShader.fragmentshader", fs);

    glAttachShader(rendering_program, vs);
    glAttachShader(rendering_program, gs);
    glAttachShader(rendering_program, fs);

    glLinkProgram(rendering_program);

    mv_location = glGetUniformLocation(rendering_program, "mvMatrix");
    mvp_location = glGetUniformLocation(rendering_program, "mvpMatrix");
    stretch_location = glGetUniformLocation(rendering_program, "stretch");

    static const GLfloat tetra_vertex_data[] = {
        0.000f, 0.000f, 1.000f,
        0.943f, 0.000f, -0.333f,
        -0.471f, 0.816f, -0.333f,
        -0.471f, -0.816f, -0.333f};

    static const GLushort tetra_index_data[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 1,
        3, 2, 1};

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tetra_vertex_data) + sizeof(tetra_index_data), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(tetra_index_data), tetra_index_data);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tetra_index_data), sizeof(tetra_vertex_data), tetra_vertex_data);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(tetra_index_data));
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
  }

  virtual void render(double current_time) override {
    static const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    static const GLfloat one = 1.0f;
    float f = (float)current_time;

    glViewport(0, 0, 1024, 768);
    glClearBufferfv(GL_COLOR, 0, black);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glUseProgram(rendering_program);

    projection = vmath::perspective(50.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    mv = vmath::translate(0.0f, 0.0f, -8.0f) *
         vmath::rotate((float)current_time * 71.0f, 0.0f, 1.0f, 0.0f) *
         vmath::rotate((float)current_time * 10.0f, 1.0f, 0.0f, 0.0f);

    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, projection * mv);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv);

    glUniform1f(stretch_location, sinf(f * 4.0f) * 0.75f + 1.0f);

    glBindVertexArray(vertex_array_object);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, NULL);
  }

  virtual void shutdown() override {
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(rendering_program);
    glDeleteBuffers(1, &buffer);
  }

 private:
  GLuint rendering_program;
  GLuint vertex_array_object;
  GLuint buffer;

  GLuint mv_location;
  GLuint mvp_location;
  GLuint stretch_location;

  vmath::mat4 projection;
  vmath::mat4 mv;
};

DECLARE_MAIN(GeometryTetra);
