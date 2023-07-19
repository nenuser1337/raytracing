// #include "vectors.h"


// void setupScene()
// {
//     camera.position = vec3_create(0., 0.2, 1.5);
//     camera.direction = vec3_create(0., -1., 0.);
//     camera.zoom = 1.0;

//     plane.normal = vec3_create(0., 1., 0.); // Plane is horizontal, facing up
//     plane.distance = -0.4; // Positioned at the origin
// }

// bool intersectPlane(Vec3 origin, Vec3 direction, Vec3 *hitPoint,  float *t)
// {
//     float denom = dot_vec3(direction, plane.normal);

//     if(fabsf(denom) > 0.001)
//     {
//         *t = dot_vec3(vec3_subtract(vec3_multiply_float(plane.normal , plane.distance)  , origin), plane.normal) / denom ;
    

//         if(*t >= 0.)
//         {
//             *hitPoint = vec3_add(origin,vec3_multiply_float(direction, *t))  ;
//             return true;
//         }
//     }

//     return false;
// }

// Vec3 rayTrace2(Vec3 origin, Vec3 direction, Texture* texture)
// {
//     Vec3 hitPoint;
//     float t;

//     if (intersectPlane(origin, direction, &hitPoint, &t))
//     {
//         // Normalize hitPoint.x and hitPoint.z to be between 0 and 1 for texture lookup
//         float u = hitPoint.x - floorf(hitPoint.x);
//         float v = hitPoint.z - floorf(hitPoint.z);

//         // Lookup color in texture
//         RGBColor color = texture_lookup(texture, u, v);

//         // Convert RGBColor to Vec3
//         Vec3 col;
//         col.r = color.r / 255.0;
//         col.g = color.g / 255.0;
//         col.b = color.b / 255.0;

//         return col;
//     }

//     return vec3_create(0., 0., 0.);
// }


// RGBColor texture_lookup(Texture* texture, float u, float v) {
//     // wrap around when the coordinates go beyond [0, 1]
//     if(u < 0.0f) u = 1.0f + fmodf(u, 1.0f);
//     else if(u > 1.0f) u = fmodf(u, 1.0f);
    
//     if(v < 0.0f) v = 1.0f + fmodf(v, 1.0f);
//     else if(v > 1.0f) v = fmodf(v, 1.0f);
    
//     // convert the normalized coordinates to pixel coordinates
//     int x = u * (texture->width - 1);
//     int y = v * (texture->height - 1);
    
//     // calculate the index into the texture data
//     int index = y * texture->width + x;
    
//     // return the color from the texture
//     return texture->data[index];
// }



