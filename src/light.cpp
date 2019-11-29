#include "light.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "Vertex.hpp"
#include "Color.hpp"

Color light::diffuse_light(Vertex& v)
{
    Vec3 lightRay { v_light.x - v.position.x , v_light.y - v.position.y, v_light.z - v.position.z};
    lightRay.Normalize();
    return v.color * diffuseLight * dot_product(lightRay, v.normal);
}

Color light::ambient_light(Vertex& v)
{
    return v.color * ambientLight;
}

void light::apply_light(Vertex& v)
{
    Color m_ambientLight = ambient_light(v);
    Color m_diffuseLight = diffuse_light(v);

    v.color = m_diffuseLight;
    
    // if(m_ambientLight.r + m_diffuseLight.r < 255)
    //     v.color.r = m_ambientLight.r + m_diffuseLight.r;
    // else
    //     v.color.r = 255;

    // if(m_ambientLight.g + m_diffuseLight.g < 255)
    //     v.color.g = m_ambientLight.g + m_diffuseLight.g;
    // else
    //     v.color.g = 255;

    // if(m_ambientLight.b + m_diffuseLight.b < 255)
    //     v.color.b = m_ambientLight.b + m_diffuseLight.b;
    // else
    //     v.color.b = 255;
    
}