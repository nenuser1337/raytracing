#include "vectors.h"



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int sphere_shader(t_vars *vars)
{
     static clock_t start_time = 0;
    double scaling_factor =2; // speed up the animation
  
    if (start_time == 0) start_time = clock();

    double t = ((double)(clock() - start_time) / CLOCKS_PER_SEC) * scaling_factor;
    setupScene();
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Vec2 fragCoord = vec2_create((float)i, (float)j);
            Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);

            // Normalized pixel coordinates (from 0 to 1)
            Vec2 uv = vec2_divide_vec(fragCoord, iResolution);
            uv = vec2_subtract_scalar(uv, 0.5f);
            uv.x *= iResolution.x / iResolution.y;

             
            Vec3 direction = normalize_vec3(vec3_subtract(vec3_create(uv.x,uv.y, camera.zoom) , camera.position));
                light.direction.r = -((float)vars->mouse_x / WIDTH - 0.5f);
                light.direction.g = -((float)vars->mouse_y / HEIGHT - 0.5f);
                light.direction = normalize_vec3(light.direction);
            Vec3 col = rayTrace(direction);
            // max(0.0, min(c, 1.0));
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
int mouse_move(int x, int y, t_vars *vars)
{
    vars->mouse_x = x;
    vars->mouse_y = y;
    return (0);
}
int main(void)
{
    t_vars  vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRt");
    vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
                                 &vars.img.endian);
  
    vars.mouse_x = WIDTH / 2;
    vars.mouse_y = HEIGHT / 2;

    mlx_loop_hook(vars.mlx,sphere_shader , &vars);
      mlx_hook(vars.win, 6, 1L<<6, mouse_move, &vars);

    // mlx_hook(vars.win, 2, 1L << 0, closing, &vars);
	// //mlx_hook(vars.win, 17, 0, closingesc, &vars);
     mlx_loop(vars.mlx);
}