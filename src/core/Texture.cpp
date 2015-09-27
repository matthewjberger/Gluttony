#include "GlobalIncludes.h"
#include "Texture.h"
using namespace std;

Texture::Texture()
{
    // Initialize variables
    mWidth    = 0;
    mHeight   = 0;
    mBPP      = 0;

    mTextureID = 0;
    mSampler   = 0;

    mMipMapsGenerated = false;

    mMinification  = 0;
    mMagnification = 0;
}

Texture::~Texture()
{
    // Free the texture
    Free();
}

void Texture::Free()
{
    // Delete the sampler
    glDeleteSamplers(1, &mSampler);

    // Delete the texture
    glDeleteTextures(1, &mTextureID);
}

void Texture::Load(string path, bool genMipMaps)
{
    // The texture id
    mTextureID = 0;

    // Load the image
    unsigned char* textureImage = SOIL_load_image(path.c_str(), &mWidth, &mHeight, 0, SOIL_LOAD_RGB);

    // Check for errors
    if (textureImage == NULL)
    {
        printf("Couldn't load image %s./n", path.c_str());
    }

    // Generate the texture and bind it
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    // Set pixel mode
    int pixelMode = GL_RGB;

    // Send data to gpu
    glTexImage2D(GL_TEXTURE_2D, 0, pixelMode, mWidth, mHeight, 0, pixelMode, GL_UNSIGNED_BYTE, textureImage);

    // Generate mipmaps if requested
    if (genMipMaps)
    {
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set mipmap generation flag
        mMipMapsGenerated = true;
    }

    // Generate samplers
    glGenSamplers(1, &mSampler);

    // Set filtering
    SetFiltering(GL_LINEAR, GL_LINEAR);

    // Set path
    mPath = path;

    // Get rid of the temporary surface
    SOIL_free_image_data(textureImage);
}

void Texture::SetFiltering(int magnification, int minification)
{
    // Set magnification filter
    glSamplerParameteri(mSampler, GL_TEXTURE_MAG_FILTER, magnification);

    // Set minification filter
    glSamplerParameteri(mSampler, GL_TEXTURE_MIN_FILTER, minification);

    // Set magnification member variable
    mMagnification = magnification;

    // Set miniification member variable
    mMinification = minification;
}

void Texture::Bind(int textureUnit)
{
    // Bind as current texture for rendering
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glBindSampler(textureUnit, mSampler);
}
