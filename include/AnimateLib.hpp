#ifndef ANIMATELIB_HPP
#define ANIMATELIB_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>


//////////...
/////...
//... ANIMATION FUNCTIONS - TO FILL OUT LATER...
/////...
//////////...


glm::mat4 mBobStatic(glm::mat4 model, float time, float speed);
glm::mat4 mSpinStatic(glm::mat4 model, float time, float speed);
glm::mat4 mWobbleStatic(glm::mat4 model, float time, float pitch, float speed);

// glm::mat4 mBobDecay();
// glm::mat4 mSpinDecay();
// glm::mat4 mWobbleDecay();

#endif
