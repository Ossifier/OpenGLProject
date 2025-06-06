#include "DrawLib.hpp"

void PreDraw() {
    // glDisable(GL_DEPTH_TEST);
    // glDisable(GL_CULL_FACE);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
};
