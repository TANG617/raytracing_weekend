#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "fstream"
#include "camera.h"
#include "material.h"

int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

//    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
//    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 720;
    cam.max_depth = 50;
    cam.samples_per_pixel = 500;

    cam.render(world);
}


//color ray_color(const ray& r, const hittable& world) {
//        hit_record rec;
//    if (world.hit(r, interval(0, infinity), rec)) {
//            return 0.5 * (rec.normal + color(1,1,1));
//        }
//
//    vec3 unit_direction = unit_vector(r.direction());
//    auto a = 0.5*(unit_direction.y() + 1.0);
//    return (1.0-a)*color (1.0,1.0,1.0)+a*color (0.5,0.7,1.0);
//}
//
//
//
//
//int main() {
//
//    // Image
//    auto aspect_ratio = 16.0/9.0;
//    int image_width = 2160;
//    int image_height = int(image_width / aspect_ratio);
//
//    int    samples_per_pixel = 10;
//        // image_height = (image_height < 1) ? 1 : image_height;
//
//    // Viewport
//    auto viewport_height = 2.0;
//    auto viewport_width = viewport_height * (double (image_width)/image_height);
//
//    //Camera
//    auto focal_length = 1.0;
//    auto camera_center = point3 (0,0,0);
//
//    //Pixel grid
//    auto viewport_u = vec3(viewport_width,0,0); // u<-->width
//    auto viewport_v = vec3(0,-viewport_height,0);//v<-->height
//    auto pixel_delta_u = viewport_u / image_width;
//    auto pixel_delta_v = viewport_v /image_height;
//
//    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
//    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
//
//    auto pixel_samples_scale = 1.0 / samples_per_pixel;
//
//
//    //File
//
//    std::ofstream ofs; // save the framebuffer to file
//    ofs.open("./image.ppm");
//
//    // World
//
//    hittable_list world;
//
//    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
//    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
//
//    // Render
//
//    ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";
//
//    for (int j = 0; j < image_height; j++) {
//        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
//        for (int i = 0; i < image_width; i++) { //Render pixel one by one
//            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
//            auto ray_direction = pixel_center - camera_center;
//            ray r(camera_center, ray_direction);
//
////            color pixel_color = ray_color(r);
//            color pixel_color = ray_color(r, world);
//            write_color(ofs, pixel_color);
//        }
//    }
//    std::clog << "\rDone.                 \n";
//}