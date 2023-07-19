#include "vectors.h"


// Vec3 hitPoint; 

void setupScene()
{
    camera.position = vec3_create(0., 0.2, 1.5);
    camera.direction = vec3_create(0., -1., 0.);
    camera.zoom = 1.0;

    plane.normal = vec3_create(0., 1., 0.); // Plane is horizontal, facing up
    plane.distance = -0.4; // Positioned at the origin
}
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

Texture* load_texture(char *path, void *mlx)
{
    Texture *texture = malloc(sizeof(Texture));
    int w, h; // Add width and height variables

    texture->img = mlx_xpm_file_to_image(mlx, path, &w, &h);
    if (!texture->img)
    {
        free(texture);
        return NULL;
    }

    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
    texture->width = w; // Use actual width
    texture->height = h; // Use actual height
    return texture;
}

int	rgb(int r, int g, int b)
    {
        return (r << 16 | g << 8 | b);
    }

int get_color_from_pos(Texture *img, int x, int y)
{
    int pos = (y * img->line_length + x * (img->bits_per_pixel / 8));
  unsigned char b = img->addr[pos]; // Blue
unsigned char g = img->addr[pos + 1]; // Green
unsigned char r = img->addr[pos + 2]; // Red


    return (r << 16 | g << 8 | b);
}

bool intersectPlane(Vec3 origin, Vec3 direction, Vec3* hitPoint, float *t)
{
    float denom = dot_vec3(direction, plane.normal);

    if(fabsf(denom) > 0.001)
    {
        *t = dot_vec3(vec3_subtract(vec3_multiply_float(plane.normal , plane.distance)  , origin), plane.normal) / denom ;

        if(*t >= 0.)
        {
            *hitPoint = vec3_add(origin,vec3_multiply_float(direction, *t))  ;
            return true;
        }
    }

    return false;
}


Vec3 rayTrace2(Vec3 origin, Vec3 direction, Texture* texture)
{
    Vec3 hitPoint;
    float t;

    if (intersectPlane(origin, direction, &hitPoint, &t))
    {
        Vec2 uv = vec2_create(hitPoint.r, hitPoint.b);
        return (texture2(texture, uv));
    }

    return vec3_create(0., 0., 0.);
}

Vec3 texture2(Texture* texture, Vec2 uv)
{
    // Wrap uv coordinates, as GLSL texture sampler does.
    uv.x = uv.x - floor(uv.x);
    uv.y = uv.y - floor(uv.y);

    // Map uv to pixel coordinates
    int x = (int)(uv.x * texture->width);
    int y = (int)(uv.y * texture->height);

    // Get the color from the texture
    int color = get_color_from_pos(texture, x, y);

    // Convert color to Vec3 and normalize to [0, 1]
    return vec3_create(((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, (color & 0xFF) / 255.0f);
}

int plane_texture(t_vars *vars)
{
    setupScene();
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            Vec2 fragCoord = vec2_create((float)i, (float)j);
            Vec2 iResolution = vec2_create((float)WIDTH, (float)HEIGHT);

            Vec2 uv = vec2_divide_vec(fragCoord, iResolution);
            uv = vec2_subtract_scalar(uv, 0.5f);
            uv.x *= iResolution.x / iResolution.y;

            Vec3 direction = normalize_vec3(vec3_subtract(vec3_create(uv.x,uv.y, camera.zoom) , camera.position));
                
            Vec3 color = rayTrace2(camera.position, direction, vars->texture);
            color.r = fmax(0.0, fmin(color.r, 1.0));
            color.g = fmax(0.0, fmin(color.g, 1.0));
            color.b = fmax(0.0, fmin(color.b, 1.0));

            // Pack RGB values into the final color representation
            // Pack RGB values into the final color representation
            int final_color = ((int)(color.r * 255) << 16) + ((int)(color.g * 255) << 8) + (int)((color.b ) * 255);

           
            // Put the pixel to the window
            mlx_pixel_put(vars->mlx, vars->win, i, HEIGHT - j - 1, final_color);

        }
    }

    // mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return 0;
}

int main(void)
{
    t_vars  vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRt");
    vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

    vars.texture = load_texture("/Users/yait-oul/Desktop/minirt/raytracing/texture/wallpaperflare.com_wallpaper.xpm", vars.mlx);
    if (!vars.texture)
    {
        // Error loading texture
        return 1;
    }

    mlx_loop_hook(vars.mlx, plane_texture, &vars);

    mlx_loop(vars.mlx);

    // Remember to free the memory allocated for the texture
    mlx_destroy_image(vars.mlx, vars.texture->img);
    free(vars.texture);

    return 0;
}
