//
// Created by 李唐 on 2024/8/24.
//

#ifndef RT_WEEKEND_RAY_H
#define RT_WEEKEND_RAY_H

#include "vec3.h"

class ray {
public:
    ray(){}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction){}

    const point3& origin() const{ return orig;}
    const vec3& direction() const {return dir;}// return an immutable reference to their members

    point3 at(double t) const{
        return orig + t*dir;
    }


private:
    point3 orig;
    vec3 dir;
};


#endif //RT_WEEKEND_RAY_H
