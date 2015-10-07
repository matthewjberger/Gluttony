#ifndef __MODEL_H
#define __MODEL_H

#include "../core/GlobalIncludes.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Mesh.h"

class Model
{
    public:
        Model(std::string path);
        ~Model();

        void Draw(ShaderProgram shaderProgram);

        std::vector<Mesh> meshes;
        std::vector<Texture> textures_loaded;

    private:

        // Model Data
        std::string directory;

        void LoadModel(std::string path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif
