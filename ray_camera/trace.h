#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"

t_ray       ray(t_point3 orig, t_vec3 dir);
    t_point3    ray_at(t_ray *ray, double t);
t_ray       ray_primary(t_camera *cam, double u, double v);
t_color3    ray_color(t_ray *ray, t_object *world); 
//double        hit_sphere(t_sphere *sp, t_ray *ray); 아래로 변경
void        set_face_normal(t_ray *r, t_hit_record *rec);

 // trace/hit/
    t_bool      hit(t_object *obj, t_ray *ray, t_hit_record *rec);
    t_bool      hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
    t_bool      hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec);
    /* * * * 추가 끝 * * * */
 

#endif