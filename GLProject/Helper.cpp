#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
class Helper {
    static void printMat4(const glm::mat4& m)
    {
        const float* p = (const float*)glm::value_ptr(m);
        std::cout << "\n[mat4]\n";
        for (int i = 0; i < 4; i++)
        {
            std::cout << p[i] << " " << p[i + 4] << " " << p[i + 8] << " " << p[i + 12] << "\n";
        }
        std::cout << "-----------\n";
    }
};