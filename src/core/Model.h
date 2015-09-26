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

    private:

        // Model Data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded;

        void LoadModel(std::string path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif
