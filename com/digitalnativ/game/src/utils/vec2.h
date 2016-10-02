#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <iostream>
#include <QDebug>
class Vec2
{
public:
    float x;
    float y;
    Vec2();
    Vec2(float x, float y);
    void operator=(const Vec2 &other);

    inline static void add(Vec2* v1, Vec2 v2) {
        v1->x += v2.x;
        v1->y += v2.y;
    }
    inline static void subtract(Vec2* v1, Vec2 v2) {
        v1->x -= v2.x;
        v1->y -= v2.y;
    }


    inline static Vec2 subtract(Vec2 v1, Vec2 v2) {
        Vec2 result = v1;
        result.x -= v2.x;
        result.y -= v2.y;
        return result;
    }
    inline static Vec2 add(Vec2 v1, Vec2 v2) {
        Vec2 result = v1;
        result.x += v2.x;
        result.y += v2.y;
        return result;
    }

    inline static void multiply(Vec2* v1, float m) {
        v1->x *= m;
        v1->y *= m;
    }

    inline static Vec2 multiply(Vec2 &v1, float m) {
        Vec2 result = v1;
        result.x *= m;
        result.y *= m;
        return result;
    }

    inline static float dot(Vec2 v1, Vec2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    inline static float magnitude(Vec2 &v1) {
       return std::sqrt(Vec2::dot(v1, v1));
    }

    /**
     * @brief Returns the normalized vector
     * @param v1
     * @return 0 vector if magnitude of v1 is 0
     */
    inline static Vec2 norm(Vec2 v1) {
        float mag = Vec2::magnitude(v1);
        if (mag == 0) {
            return Vec2(0, 0);
        }
        Vec2 result(v1.x / mag, v1.y / mag);
        return result;
    }


    inline static Vec2 project(Vec2 &v1, Vec2 &v2) {
        float dot = Vec2::dot(v1, v2);
        Vec2 result = Vec2::norm(v2);
        Vec2::multiply(&result, dot);

        return result;
    }

    //Rotates clockwise
    inline static Vec2 perpendicular(Vec2 &v1) {
        return Vec2(v1.y, -v1.x);
    }

    inline static void print(Vec2 v1) {
        std::cout << "<" << v1.x << ", " << v1.y << ">\n" << std::flush;
    }
};

#endif // VEC2_H
