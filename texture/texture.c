#include "vectors.h"

#define _2PI 6.283185307179586476925286766559
#define PI 3.1415926535897932384626433832795
#define BUMP_DENSITY 64.
#define BUMP_SIZE .15

float sdSphere(Vec3 p, float r){
    return length_vec3(p) - r;
}

int texture(t_vars *vars)
{
    
 static clock_t start_time = 0;
    double scaling_factor =2; // speed up the animation
  
    if (start_time == 0) start_time = clock();

    double t = ((double)(clock() - start_time) / CLOCKS_PER_SEC) * scaling_factor;
    
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Vec2 fragCoord = vec2_create((float)i, (float)j);
            Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);

            // Normalized pixel coordinates (from 0 to 1)
            //Vec2 uv = vec2_divide_vec(fragCoord, iResolution);
            Vec2 uv;
            uv.x = (2.0 * fragCoord.x - iResolution.x) / iResolution.y;
            uv.y = (2.0 * fragCoord.y - iResolution.y) / iResolution.y;
            // uv = vec2_subtract_scalar(uv, 0.5f);
            // uv.x *= iResolution.x / iResolution.y;
            Vec3 origin = vec3_create(0, 0, 0);
            Vec3 dir = normalize_vec3(vec3_create(uv.x, uv.y, -1));
                        
            Vec3 col = vec3_create(1,1,1);
            Vec3 albedo = vec3_create(0.7, 0.6, 0.18);
            Vec3 lightPos = vec3_create(0, 0, 1);
            Vec3 center = vec3_create(0, 0, -3);
            float radius = 2.;
            float dist = 0.2;
                    for(int i2 = 0; i2 < 100; i2++){
                        Vec3 p = vec3_add( origin ,  vec3_multiply_float(dir, dist));
                        
                        Vec3 x = vec3_subtract(p , center);
                        float t = sdSphere(x, radius);
                        if(t < 0.0001){
                            Vec3 n = normalize_vec3(x);
                            float theta = atan2(x.b, x.r);
                            float phi = acos(x.g/radius);
                            
                            Vec3 t = vec3_create(-sin(theta) * sin(phi), 0, cos(theta) * sin(phi));
                            Vec3 b = vec3_create(cos(theta) * cos(phi), -sin(phi), sin(theta) * cos(phi));
                            
                            mat3 tbn = mat3_transpose(mat3_create(t, b, n));

                            Vec3 L = normalize_vec3(vec3_subtract(lightPos ,p));
                            Vec3 V = normalize_vec3(vec3_subtract(origin , p));
                            L =  mat3_mul_vec3(tbn ,L);
                            V =  mat3_mul_vec3(tbn ,V);
                            Vec3 H = normalize_vec3(vec3_add (V , L));
                            
                            Vec2 uv = vec2_create((theta/_2PI + 0.5), phi/PI);

                            Vec2 i = vec2_floor_multiply(uv , 16.);
                            float cc = step(mod(i.x + i.y, 2.), 0.);
                            albedo = mix_vec3(vec3_create(0.6,0.6,0.6), vec3_create(1,1,1), cc);
                            
                            Vec2 c =vec2_multiply(uv ,BUMP_DENSITY );
                            Vec2 p = vec2_subtract(fract_vec2(c) , vec2_create(.5,.5)) ;
                            
                            float d, f;
                            d = dot_vec2(p, p);
                            
                            f = inversesqrt(d + 1.);
                            
                            
                            if(d >= BUMP_SIZE) {
                                p = vec2_create(0,0);
                                f = 1.;
                            }
                            Vec3 normDelta = vec3_multiply_float( vec3_create(p.x,p.y, 1) , f);
                            
                            col = vec3_multiply_float(albedo , max(dot_vec3(normDelta, L), 0.));
                            float variable = powf(max(0.0f, dot_vec3(normDelta, H)), 250.0f);
                            col = vec3_add(col, vec3_multiply_float(albedo , variable));

                           
                            break;
                        }
                        dist += t;
                        
                    }
                            
           
            col.r = fmax(0.0, fmin(col.r, 1.0));
            col.g = fmax(0.0, fmin(col.g, 1.0));
            col.b = fmax(0.0, fmin(col.b, 1.0));
                Vec4 fragColor = vec4_create(col.r, col.g, col.b, 0.0f);
            int color = vec4_to_color(fragColor);
            // Set pixel color
            my_mlx_pixel_put(&vars->img, i, j, color);
        }
    }

    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return 0;

}