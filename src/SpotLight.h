#pragma once
#include "PointLight.h"

struct SpotLight : public PointLight
{
public:
    glm::vec3 direction = glm::vec3(0, -0.75, 0);
    float cutoff = 500.0f;

    glm::vec3 position = glm::vec3(0, 2, 0);
    float intensity = 5;
};
