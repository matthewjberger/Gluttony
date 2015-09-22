#include "Model.h"
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace std;

Model::Model()
{
    textureLoaded = false;
}

Model::~Model(){}

void Model::LoadModel(std::string path)
{
    ifstream file(path.c_str());
    string line = "";
    file.clear();

    vector<unsigned int> vIndices, uvIndices, nIndices;
    vector<glm::vec3> tempV;
    vector<glm::vec2> tempUV;
    //vector<glm::vec3> tempN;

    string textureName = "";

    // Iterate over the file line by line
    while(getline(file, line, '\n'))
    {
        // Get the first token from the line
        string firstToken;
        istringstream ss(line);
        if(!(ss >> firstToken)) { break; }

        // Vertex
        if(firstToken == "v")
        {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            tempV.push_back(vertex);
        }
        // Texture coordinate
        else if(firstToken == "vt")
        {
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            tempUV.push_back(uv);
        }
        // Normal
        /*
        else if(firstToken == "vn")
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tempN.push_back(normal);
        }
        */
        // Face
        else if(firstToken == "f")
        {
            string first, second, third = "";
            unsigned int vIndex[3], uvIndex[3]; //, nIndex[3];

            ss >> first >> second >> third;
            cout << first << " " << second << " " << third << endl;

            vIndex[0]  = atoi(&first[0]);
            vIndex[1]  = atoi(&second[0]);
            vIndex[2]  = atoi(&third[0]);
            vIndices.push_back(vIndex[0]);
            vIndices.push_back(vIndex[1]);
            vIndices.push_back(vIndex[2]);

            uvIndex[0] = atoi(&first[2]);
            uvIndex[1] = atoi(&second[2]);
            uvIndex[2] = atoi(&third[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);

            //nIndex[0]  = atoi(&first[4]);
            //nIndex[1]  = atoi(&second[4]);
            //nIndex[2]  = atoi(&third[4]);
            //nIndices.push_back(nIndex[0]);
            //nIndices.push_back(nIndex[1]);
            //nIndices.push_back(nIndex[2]);

        }
        else if(firstToken == "usemtl")
        {
            ss >> textureName;
        }
    }

    cout << "Loaded Vertices: " << endl;
    for(unsigned int i = 0; i < tempV.size(); i++)
    {
        cout << tempV[i].x << " " << tempV[i].y << " " << tempV[i].z << endl;
    }
    cout << endl;

    cout << "Loaded Tex-Coords: " << endl;
    for(unsigned int i = 0; i < tempUV.size(); i++)
    {
        cout << tempUV[i].x << " " << tempUV[i].y << endl;
    }
    cout << endl;

    //cout << "Loaded Normals: " << endl;
    //for(unsigned int i = 0; i < tempN.size(); i++)
    //{
        //cout << tempN[i].x << " " << tempN[i].y << " " << tempN[i].z << endl;
    //}
    //cout << endl;

    for(unsigned int i = 0; i < vIndices.size(); i++)
    {
        unsigned int vertexIndex = vIndices[i];
        glm::vec3 vertex = tempV[vertexIndex - 1];
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < uvIndices.size(); i++)
    {
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 uvCoords = tempUV[uvIndex - 1];
        texCoords.push_back(uvCoords);
    }

    //for(unsigned int i = 0; i < nIndices.size(); i++)
    //{
        //unsigned int normalIndex = nIndices[i];
        //glm::vec3 normal = tempN[normalIndex - 1];
        //vertices.push_back(normal);
    //}

    cout << "Attempting to load texture: " << textureName << endl;
    if(!ifstream(textureName.c_str()))
    {
        cout << "Texture could not be found!" << endl;
        cout << "Make sure the texture is in the same folder as the executable." << endl;
    }
    else
    {
       texture.Load(textureName.c_str());
       textureLoaded = true;
       cout << "Model texture loaded successfully." << endl;
    }

    cout << "Finished loading model successfully!" << endl;
}

std::vector<glm::vec2> Model::GetTexCoords()
{
    return texCoords;
}

/*
std::vector<glm::vec3> Model::GetNormals()
{
    return normals;
}
*/

std::vector<glm::vec3> Model::GetVertices()
{
    return vertices;
}

void Model::Draw()
{
    if(textureLoaded) texture.Bind(0);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
}

Texture* Model::GetTexture()
{
    return &texture; // null
}
