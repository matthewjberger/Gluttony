#include "Model.h"
using namespace std;

Model::Model(string path)
{
    LoadModel(path.c_str());
}

Model::~Model()
{
}

void Model::Draw(ShaderProgram shaderProgram)
{
    for(GLuint i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shaderProgram);
    }
}

void Model::LoadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR: Assimp - " << importer.GetErrorString() << endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // Process all meshes in the node
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh,scene));
    }

    // Process all child nodes
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        // Positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        // Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        // Texture Coordinates
        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }
    // Process indices
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        // Get all the indices from the face and store them
        for(GLuint j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    // Process Material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // Diffuse
        vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // Specular
        vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    cout << "---- New Mesh Loaded ----" << endl;
    cout << "Total Vertices in mesh: " << vertices.size() << endl;
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        cout << "Position:" << endl;
        cout << vertices[i].Position.x  << " " << vertices[i].Position.y  << " "  << vertices[i].Position.z << endl;

        cout << "Normal:" << endl;
        cout << vertices[i].Normal.x    << " " << vertices[i].Normal.y    << " "  << vertices[i].Normal.z << endl;

        cout << "TexCoords:" << endl;
        cout << vertices[i].TexCoords.x << " " << vertices[i].TexCoords.y << endl << endl;
    }

    cout << "Total Indices for mesh: " << indices.size() << endl;
    for(unsigned int i = 0; i < indices.size(); i++)
    {
        cout << indices[i] << endl;
    }

    cout << "Total Textures loaded for mesh: " << textures.size() << endl;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        cout << textures[i].GetPath().C_Str() << endl;
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    vector<Texture> textures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        // Check if already loaded
        GLboolean skip = false;
        for(GLuint j = 0; j < textures_loaded.size(); j++)
        {
            if(textures_loaded[j].GetPath() == str)
            {
                textures.push_back(textures_loaded[j]);
            }
            if(!skip)
            {
                Texture texture;
                texture.Load(str.C_Str(), directory, true);
                texture.SetType(typeName);
                texture.SetPath(str);
                textures.push_back(texture);
            }
        }
    }
    return textures;
}

