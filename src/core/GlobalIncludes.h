#include <stdlib.h>
#include <GL/glew.h> // Glew must be included before the main GL libs
#include <GL/freeglut.h> // Doing otherwise causes compiler errors

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // Makes passing matrices to shaders easier

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

#include <chrono>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <SOIL/SOIL.h>
