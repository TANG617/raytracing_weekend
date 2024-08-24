#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "fstream"


//Calculate the ray from the “eye” through the pixel,
//Determine which objects the ray intersects, and
//Compute a color for the closest intersection point.


//double hit_sphere(const point3& center, double radius, const ray& r){ //calculate t instead of whether hit
//    vec3 oc = center - r.origin();
//    auto a = dot(r.direction(), r.direction());
//    auto b = -2.0 * dot(r.direction(), oc);
//    auto c = dot(oc, oc) - radius*radius;
//    auto discriminant = b*b - 4*a*c;// NO simplification
//
//    if (discriminant < 0) return -1.0;
//    else return (-b - std::sqrt(discriminant) ) / (2.0*a);
//}

//color ray_color(const ray& r) {
//    if(hit_sphere(point3(0,0,-1),0.5,r)) return color (1,0,0);

//    auto t = hit_sphere(point3(0,0,-1),0.5,r);
//    if(t > 0.0) {
//        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1)); // N is normalized vector pointing from center of sphere to the hit point
//        return color(0.6 + 0.4 * dot(N,-r.direction()),0,0);
//    }

color ray_color(const ray& r, const hittable& world) {
        hit_record rec;
        if (world.hit(r, 0, infinity, rec)) {
            return 0.5 * (rec.normal + color(1,1,1));
        }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color (1.0,1.0,1.0)+a*color (0.5,0.7,1.0);
}


int main() {

    // Image
    auto aspect_ratio = 16.0/9.0;
    int image_width = 2160;
    int image_height = int(image_width / aspect_ratio);
        // image_height = (image_height < 1) ? 1 : image_height;

    // Viewport
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double (image_width)/image_height);

    //Camera
    auto focal_length = 1.0;
    auto camera_center = point3 (0,0,0);

    //Pixel grid
    auto viewport_u = vec3(viewport_width,0,0); // u<-->width
    auto viewport_v = vec3(0,-viewport_height,0);//v<-->height
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v /image_height;

    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    //File

    std::ofstream ofs; // save the framebuffer to file
    ofs.open("./image.ppm");

    // World

    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Render

    ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) { //Render pixel one by one
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

//            color pixel_color = ray_color(r);
            color pixel_color = ray_color(r, world);
            write_color(ofs, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}