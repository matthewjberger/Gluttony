#include <GL/glew.h> // Glew must be included before the main GL libs
#include <GL/glut.h> // Doing otherwise causes compiler errors

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // Makes passing matrices to shaders easier

#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

#include <chrono>
