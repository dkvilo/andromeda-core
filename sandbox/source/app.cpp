#include "app.hpp"
#include <cstdlib>
#include <stdio.h>

int main(int argc, char const *argv[])
{

  Sandbox app;
  app.Init();

  glfwSetKeyCallback(app.get_widnow(), app.key_callback);

  double prevTime = glfwGetTime();
  while (!glfwWindowShouldClose(app.get_widnow()))
  {

    double t = glfwGetTime();
    double dt = t - prevTime;
    prevTime = t;

    glViewport(0, 0, 500, 500);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0.4, 0, 0.05);

    L::Vec2 v2(10.f, 5.f);
    L::Vec2 v3(2.f, 1.f);
    L::Vec2 v4(2.f, 2.f);

    app.mouse_pos = v2 + &v3;
    app.mouse_pos = app.mouse_pos * &v4;

    printf("Delta Time: %f | X(%f) Y(%f)\n", dt, app.mouse_pos.x, app.mouse_pos.y);

    glfwSwapBuffers(app.get_widnow());
    glfwPollEvents();
  }

  glfwDestroyWindow(app.get_widnow());
  glfwTerminate();

  return 0;
}
