#include "LitecMath.h"
#include <math.h>

Vec3 vec3_create(float x, float y, float z)
{
    Vec3 v = { x, y, z };
    return v;
}

Vec3 vec3_add(Vec3 a, Vec3 b)
{
    return vec3_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 vec3_sub(Vec3 a, Vec3 b)
{
    return vec3_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 vec3_scale(Vec3 v, float scale)
{
    return vec3_create(v.x * scale, v.y * scale, v.z * scale);
}

Vec3 vec3_div(Vec3 v, float scale)
{
    return vec3_create(v.x / scale, v.y / scale, v.z / scale);
}

Vec3 vec3_negate(Vec3 v)
{
    return vec3_create(-v.x, -v.y, -v.z);
}

float vec3_length_squared(Vec3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float vec3_length(Vec3 v)
{
    return sqrtf(vec3_length_squared(v));
}

Vec3 vec3_normalize(Vec3 v)
{
    float len = vec3_length(v);

    if (len == 0.0f) {
        return vec3_create(0.0f, 0.0f, 0.0f);
    }

    return vec3_div(v, len);
}

float vec3_dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec3_cross(Vec3 a, Vec3 b)
{
    return vec3_create(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}