#include "vectors.h"

void setupScene()
{
    camera.position = vec3_create(0., 0., 3.5);
    camera.direction = vec3_create(0., 0., -1.);
    camera.zoom = 1.0;
    
    sphere.position = vec3_create(0., 0., 0.);
    sphere.radius = 0.3;
    sphere.color = vec3_create(0.6, 0.9, 0.3);
    
    light.direction = normalize_vec3(vec3_create(0., 1., -0.78));
    material.ambience = 0.2;
    material.diffuse = 0.7;
    material.specular = 1.4;
    material.shininess = 12.0; 
}

bool solveQuadratic(float a, float b, float c,  float *t0,  float *t1)
{
    float disc = b * b - 4. * a * c;
    
    if (disc < 0.)
    {
        return false;
    } 
    
    if (disc == 0.)
    {
        *t0 = *t1 = -b / (2. * a);
        return true;
    }
    
    *t0 = (-b + sqrt(disc)) / (2. * a);
    *t1 = (-b - sqrt(disc)) / (2. * a);
    return true;    
}

bool intersect(Vec3 direction, Vec3 *surfaceNormal)
{
    Vec3 L = vec3_subtract (camera.position ,sphere.position);
    
    float a = dot_vec3(direction, direction);
    float b = 2. * dot_vec3(direction, L);
    float c = dot_vec3(L, L) - pow(sphere.radius, 2.);
    
    float           t0 = 0;
    float t1 = 0;
    
    if (solveQuadratic(a, b, c, &t0, &t1))
    {
        float t = t0;
        if (t1 < t0)
        {
            t = t1;
        }
        
        Vec3 Phit = vec3_add(camera.position,vec3_multiply_float(direction, t) )  ;
        *surfaceNormal = normalize_vec3( vec3_subtract(Phit , sphere.position));
        
        return true;
    }  
     
    return false;
}

Vec3 rayTrace(Vec3 direction)
{
    Vec3 surfaceNormal;
    
    if (intersect(direction, &surfaceNormal))
    {
        float coeff = -1 * dot_vec3(light.direction, surfaceNormal);                          
        // Clamp coeff to the range [0, 1]
        coeff = coeff < 0 ? 0 : coeff;  
        Vec3 ambient = vec3_multiply_float(sphere.color, material.ambience);
        Vec3 diffuse = vec3_multiply_float(sphere.color, coeff * material.diffuse);

        Vec3 reflectedLightDirection = reflect(light.direction, surfaceNormal);
        float shininess = pow(max(-dot_vec3(direction, reflectedLightDirection), 0.0), material.shininess);
        shininess = shininess < 0 ? 0 : shininess; 
        Vec3 specular = vec3_multiply_float(sphere.color, shininess * material.specular);
        return  vec3_add(vec3_add(ambient, diffuse), specular);
    }
    
    return vec3_create(0., 0., 0.);
}
