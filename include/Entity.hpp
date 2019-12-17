#pragma once
#include "Mesh.hpp"
#include "Mat4.hpp"
#include "tools.hpp"
#include "Vec3.hpp"

class Entity
{
private:
    Mesh *_mesh;
    Mat4 _transform;
    DRAW_MODE _draw_mode;

    Vec3 _position;
    Vec3 _rotation;
    Vec3 _scale;

    void scale();
    void translate();
    void rotate();

public:

    Entity();
    Entity(Mesh *mesh);
    Entity(Mesh *mesh, Mat4 transfo);

    virtual void update(double DeltaTime);
    virtual void draw();

    void setScale(Vec3 &scale);
    void setPosition(Vec3 &position);
    void setRotation(Vec3 &rotation);

    void resetTransformation();

    void setDrawMode(const DRAW_MODE draw_mode);
    DRAW_MODE getDrawMode() const;
};

inline Entity::Entity() : _draw_mode{TRIANGLE}, _transform{Mat4::identity()} {}
inline Entity::Entity(Mesh *mesh) : _draw_mode{TRIANGLE}, _mesh{mesh}, _transform{Mat4::identity()} {}
inline Entity::Entity(Mesh *mesh, Mat4 transform) : _draw_mode{TRIANGLE}, _mesh{mesh}, _transform{transform} {}

inline void Entity::setScale(Vec3 &scale)
{
    _scale = scale;
}

inline void Entity::setPosition(Vec3 &position)
{
    _position = position;
}

inline void Entity::setRotation(Vec3 &rotation)
{
    _position = rotation; 
}

/**
 * @brief Update the matrix with a rotation
 * 
 */
inline void Entity::scale()
{
    _transform = _transform * Mat4::CreateScaleMatrix(_scale);
}

/**
 * @brief Update the matrix with a translation
 * 
 */
inline void Entity::translate()
{
    _transform = _transform * Mat4::CreateTranslationMatrix(_position);
}

/**
 * @brief update the entity matrix with a rotation
 * 
 */
inline void Entity::rotate()
{
    if (_rotation.z != 0.f)
        _transform = _transform * Mat4::CreateZRotationMatrix(_rotation.z);

    if (_rotation.x != 0.f)
        _transform = _transform * Mat4::CreateXRotationMatrix(_rotation.x);

    if (_rotation.y != 0.f)
        _transform = _transform * Mat4::CreateYRotationMatrix(_rotation.y);
}

inline void Entity::resetTransformation()
{
    // _transform = Mat4::identity();
    memset(&_transform, 0, 16 * sizeof(float));
    _transform.a[0] = 1.f;
    _transform.a[5] = 1.f;
    _transform.a[10] = 1.f;
    _transform.a[15] = 1.f;
}

inline void Entity::setDrawMode(DRAW_MODE draw_mode)
{
    _draw_mode = draw_mode;
}

inline DRAW_MODE Entity::getDrawMode() const
{
    return _draw_mode;
}
