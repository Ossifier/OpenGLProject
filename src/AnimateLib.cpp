#include "AnimateLib.hpp"
#include <iostream>

#include <cmath>


//////////...
/////...
//... ANIMATION FUNCTIONS - TO FILL OUT LATER...
/////...
//////////...

glm::mat4 mBob(glm::mat4 model, float time, float speed) {
    model = glm::translate(model, glm::vec3(0.0, (sin(time * (speed + 1))/10), 0.0f));
    return model;
}

glm::mat4 mSpin(glm::mat4 model, float time, float speed) {
    model = glm::rotate(model, time * speed, glm::vec3(0.0f, 1.0f, 0.0f));
    return model;
}

glm::mat4 mWobble(glm::mat4 model, float time, float pitch, float speed) {
    float rotation = sin(time * speed);
    model = glm::rotate(model, rotation * pitch, glm::vec3(0.0f, 0.0f, 1.0f));
    return model;
}

// --- NEED TO VALIDATE --- //

// glm::mat4 mBobDecay() {}
// glm::mat4 mSpinDecay() {}
// glm::mat4 mWobbleDecay() {}

// -- TEST DECAY FUNCTIONS //

void mTestDecay(float startSpeed, float decaySpeed) {
    


    std::cout << (startSpeed - decaySpeed) << std::endl;
}
