#include <application.h>

class ColorfulWindow : public application {
 public:
  virtual void render(double current_time) override {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor((float)sin(current_time) * 0.5f + 0.5f,
                 (float)cos(current_time) * 0.5f + 0.5f, 0.0f, 0.0f);
  }
};

DECLARE_MAIN(ColorfulWindow);
