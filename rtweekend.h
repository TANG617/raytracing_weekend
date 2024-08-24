//
// Created by 李唐 on 2024/8/24.
//

#ifndef RT_WEEKEND_RTWEEKEND_H
#define RT_WEEKEND_RTWEEKEND_H


#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"


#endif //RT_WEEKEND_RTWEEKEND_H
