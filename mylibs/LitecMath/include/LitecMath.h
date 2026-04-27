#ifndef LITEC_MATH_H
#define LITEC_MATH_H

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

Vec3 vec3_create(float x, float y, float z);

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_scale(Vec3 v, float scale);
Vec3 vec3_div(Vec3 v, float scale);
Vec3 vec3_negate(Vec3 v);

float vec3_length(Vec3 v);
float vec3_length_squared(Vec3 v);

Vec3 vec3_normalize(Vec3 v);

float vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);

#endif