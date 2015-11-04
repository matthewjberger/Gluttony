#include <stdlib.h>
#include <GL/glew.h> // Glew must be included before the main GL libs
#include <GL/freeglut.h> // Doing otherwise causes compiler errors

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // Makes passing matrices to shaders easier

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>

// Soil
#include <SOIL/SOIL.h>

// Bullet
#include <btBulletDynamicsCommon.h>

// Standard libraries
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>


