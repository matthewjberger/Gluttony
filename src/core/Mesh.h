#ifndef __MESH_H
#define __MESH_H

#include "GlobalIncludes.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"

struct Vertex
{
    glm::vec3 Position;
    //glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
    public:
        // Mesh Data
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        // Functions
        Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Texture> _textures);
        void Draw(ShaderProgram shaderProgram);

    private:
        VAO meshVAO;
        VBO meshVBO;
        VBO meshIBO;

        void SetupMesh();
};

#endif
