#ifndef ANIMATELIB_HPP
#define ANIMATELIB_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>


//////////...
/////...
//... CONTINUOUS ANIMATION FUNCTIONS
/////...
//////////...


glm::mat4 mBob(glm::mat4 model, float time, float speed);
glm::mat4 mSpin(glm::mat4 model, float time, float speed);
glm::mat4 mWobble(glm::mat4 model, float time, float pitch, float speed);

//////////...
/////...
//... DECAYING ANIMATION FUNCTIONS
/////...
//////////...

// glm::mat4 mBobDecay();
// glm::mat4 mSpinDecay();
// glm::mat4 mWobbleDecay();

// --- TEST DECAY FUNCTIONS -- //

void mTestDecay(float startSpeed, float decaySpeed);

#endif
