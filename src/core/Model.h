#ifndef __MODEL_H
#define __MODEL_H

#include "../core/GlobalIncludes.h"

class Model
{
    public:
        Model();
        ~Model();

        void LoadModel(std::string path);

        std::vector<glm::vec3> GetVertices();
        std::vector<glm::vec2> GetTexCoords();
        //std::vector<glm::vec3> GetNormals();

    private:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> texCoords;
        //std::vector<glm::vec3> normals;
};

#endif
