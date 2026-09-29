#include "core/recoil_math.h"

#include <cmath>

namespace recoil
{
    void ApplyVertical(Vector &direction, float degrees)
    {
        const float horizontalLenght = 
            std::sqrt(
                direction.x * direction.x + 
                direction.y * direction.y
            );

        if (horizontalLenght <= 0.0001f)
            return;

        const float radians = degrees * (3.14159265358979323846f / 180.0f);

        const float sinAngle = std::sin(radians);
        const float cosAngle = std::cos(radians);

        const float newZ = 
            direction.z * cosAngle -
            horizontalLenght * sinAngle;

        const float newHorizontalLenght = 
            horizontalLenght * cosAngle +
            direction.z * sinAngle;

        const float horizontalScale =
            newHorizontalLenght / horizontalLenght;

        direction.x *= horizontalScale;
        direction.y *= horizontalScale;
        direction.z = newZ;
    }
}
