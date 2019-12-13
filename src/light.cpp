#include "light.hpp"
#include "Vec3.hpp"
#include "Color.hpp"
#include "tools.hpp"

Light::Light(Vec3 light, Vec3 camera, float ambientIntensity, float diffuseIntensity, float specularIntensity, float shininess)
    : m_ambientIntensity{ambientIntensity},
      m_diffuseIntensity{diffuseIntensity},
      m_specularIntensity{specularIntensity},
      m_shininess{shininess},
      camera_pos{camera},
      light_pos{light} {}


