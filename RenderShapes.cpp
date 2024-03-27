#include "RenderShapes.h"

namespace WIP_Polygon {
	std::vector<float> RenderShapes::cube{
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
    std::vector<float> RenderShapes::plane{
                             //scale down the texture 2x
        0.5f,  0.5f,  0.0f,  2.0f, 2.0f,
       -0.5f,  0.5f,  0.0f,  0.0f, 2.0f,
        0.5f, -0.5f,  0.0f,  2.0f, 0.0f,

        0.5f, -0.5f,  0.0f,  2.0f, 0.0f,
       -0.5f,  0.5f,  0.0f,  0.0f, 2.0f,
       -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
    };
    std::vector<float> RenderShapes::circle{ RenderShapes::CreateCircle(90) };
    std::vector<float> RenderShapes::CreateCircle(int _num_verts) {
        _num_verts = glm::max(3, _num_verts);
        float step = 360.0f / static_cast<float>(_num_verts);
        std::vector<float>verts{};
        for (float i = 0.0f; i < 360.0f; i += step) {
            verts.push_back(glm::cos(glm::radians(i)));
            verts.push_back(glm::sin(glm::radians(i)));
        }
        verts.erase(verts.begin() + verts.size() - 1);
        verts.erase(verts.begin() + verts.size() - 1);
        return verts;
    }

}