#include "Mesh.h"
#include "Texture.h"
#include <sstream>
using namespace std;

Mesh::Mesh(vector<Vertex> _vertices, vector<GLuint> _indices, vector<Texture> _textures)
{
    vertices = _vertices;
    indices  = _indices;
    textures = _textures;

    SetupMesh();
}

void Mesh::Draw(ShaderProgram shaderProgram)
{
    GLuint diffuse  = 1;
    GLuint specular = 1;

    for(GLuint i = 0; i < textures.size(); i++)
    {
        stringstream ss;
        string number;
        string name = textures[i].GetType();
        if(name == "texture_diffuse")
            ss << diffuse++;
        else if(name == "texture_specular")
            ss << specular++;
        number = ss.str();

        string materialID =  "material." + name + number;
        shaderProgram.SetUniform(materialID, float(i));
        textures[i].Bind(i);
    }
    glActiveTexture(GL_TEXTURE0);

    // Render the mesh
    meshVAO.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices.front());
    meshVAO.Unbind();
}

void Mesh::SetupMesh()
{
    meshVAO.Create();
    meshVBO.Create();
    meshIBO.Create();

    meshVAO.Bind();

        meshVBO.Bind();
        meshVBO.AddData(&vertices.front(), sizeof(Vertex) * vertices.size());
        meshVBO.UploadData();

        meshIBO.Bind(GL_ELEMENT_ARRAY_BUFFER);
        meshIBO.AddData(&indices.front(), sizeof(GLuint) * indices.size());
        meshIBO.UploadData();

        // Vertex Positions
        meshVAO.EnableAttribute(0);
        meshVAO.ConfigureAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

        // Vertex Normals
        meshVAO.EnableAttribute(1);
        meshVAO.ConfigureAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

        // Vertex Texture Coordinates
        meshVAO.EnableAttribute(2);
        meshVAO.ConfigureAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

    meshVAO.Unbind();
}

