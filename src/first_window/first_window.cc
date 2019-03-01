#include <application.h>

class FirstWindow : public application {
 public:
  virtual void render() override {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
  }
};

DECLARE_MAIN(FirstWindow);
