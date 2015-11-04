#ifndef __CAMERA_H
#define __CAMERA_H

#include "GlobalIncludes.h"

class Camera
{
    public:

        Camera(glm::vec3 pos = glm::vec3(0.0f), float speed = 0.7);
        ~Camera();

        void SetPosition(glm::vec3 position, float horizontalAngle = M_PI, float verticalAngle =  0.0f);
        void Update();

        void LookAt(glm::vec3 position, glm::vec3 focusPoint, glm::vec3 up);

        // Membor Accessors
        float GetPitchSensitivity();
        void  SetPitchSensitivity(float newSens);
        float GetYawSensitivity();
        void  SetYawSensitivity(float newSens);

        glm::mat4 GetMVP(glm::mat4 modelMatrix);

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        void EnableInput(bool enabled = true);

    private:

        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 right;
        glm::vec3 up;

        float horizontalAngle;
        float verticalAngle;

        float initialFOV;
        float curFOV;

        float speed;
        float pitchSensitivity;
        float yawSensitivity;

        int mouseX;
        int mouseY;

        bool forward;

        bool inputEnabled;

};

#endif
