#include "stdio.h"
#include "math.h"
#include "scene.h"
#include "trace.h"

//ray 생성자(정규화 된 ray)
t_ray       ray(t_point3 orig, t_vec3 dir)
{
    t_ray ray;

    ray.orig = orig;
    ray.dir = vunit(dir);
    return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3    ray_at(t_ray *ray, double t)
{
    t_point3 at;

    at = vplus(ray->orig, vmult(ray->dir, t));
    return (at);
}
//primary_ray 생성자
t_ray       ray_primary(t_camera *cam, double u, double v)
{
    t_ray   ray;

    ray.orig = cam->orig;
    // left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
    ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
    return (ray);
}

t_color3    ray_color(t_ray *ray, t_object *world)
    {
        double  t;
    /* * * * 추가 * * * */
    t_vec3  n;
    /* * * * 추가 끝 * * * */
    t_hit_record    rec;

    rec.tmin = 0;
    rec.tmax = INFINITY;

     if (hit(world, ray, &rec))
        return (vmult(vplus(rec.normal, color3(1, 1, 1)), 0.5));
    
     else
        {
            //ray의 방향벡터의 y 값을 기준으로 그라데이션을 주기 위한 계수.
            t = 0.5 * (ray->dir.y + 1.0);
            // (1-t) * 흰색 + t * 하늘색
            return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0),     t)));
        }
    return (vplus(vmult(color3(1, 1, 1), 1.0 - 0.2), vmult(color3(0.5, 0.7, 1.0),     0.5)));
    }

// t_color3    ray_color(t_ray *r, t_object *world)
// {

//         // Variables for the circle
//     t_point3 circle_center = point3(0, 0, -10); // Position of the circle center
//     double circle_radius = 3.0; // Radius of the circle

//      t_vec3 oc = vminus(r->orig, circle_center);
//     double a = vdot(r->dir, r->dir);
//     double b = 2.0 * vdot(oc, r->dir);
//     double c = vdot(oc, oc) - circle_radius * circle_radius;
//     double discriminant = b * b - 4 * a * c;

//     if (discriminant > 0)
//     {
//         // Ray intersects with the circle, return white color
//         return color3(1.0, 1.0, 1.0);
//     }

//     // Ray does not intersect with the circle, return background color
//     double t = 0.5 * (r->dir.y + 1.0);
//     return vplus(vmult(color3(1.0, 1.0, 1.0), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t));

// }