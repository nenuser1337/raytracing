
/* * * * 추가 * * * */
#include "scene.h"
#include "trace.h"
#include "structures.h"
#include "utils.h"
#include "print.h"
#include <mlx.h>

int main(void)
{
    int         i;
    int         j;
    /* * * * 추가 * * * */
    double      u;
    double      v;
    /* * * * 추가 끝 * * * */

    t_color3    pixel_color;
    /* * * * 수정 * * * */
    t_canvas    canv;
    t_camera    cam;
    t_ray       ray;
        t_object    *world;

        t_sphere    sp;

    //Scene setting;
    canv = canvas(400, 300);
    cam = camera(&canv, point3(0, 0, 0));
    /* * * * 추가 * * * */
    // sp = sphere(point3(0, 0, -5), 2);
    world = object(SP, sphere(point3(-2, 0, -5), 2));
    oadd(&world, object(SP, sphere(point3(2, 0, -5), 2))); // world 에 구2 추가
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 990)));
    // oadd(&world, object(SP, sphere(point3(3, 1, -4), 3)));
    // oadd(&world, object(SP, sphere(point3(1, -999, -6), 1)));
    /* * * * 수정 끝 * * * */

    // 랜더링
    // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
    /* * * * 수정 * * * */
    printf("P3\n%d %d\n255\n", canv.width, canv.height);
    j = canv.height - 1;
    /* * * * 수정 끝 * * * */
    while (j >= 0)
    {
        i = 0;
        /* * * * 수정 * * * */
        while (i < canv.width)
        {
            u = (double)i / (canv.width - 1);
            v = (double)j / (canv.height - 1);
            //ray from camera origin to pixel
            ray = ray_primary(&cam, u, v);
             pixel_color = ray_color(&ray, world);
        /* * * * 수정 끝 * * * */
            write_color(pixel_color);
            ++i;
        }
        --j;
    }
}



// #include <mlx.h>
// #include <math.h>

// // Set the pixel color using mlx_pixel_put()
// void set_pixel_color(void *mlx_ptr, void *win_ptr, int x, int y, int color)
// {
//     mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
// }

// int main(void)
// {
//     void *mlx_ptr;
//     void *win_ptr;

//     int i, j;
//     double u, v;
//     t_color3 pixel_color;
//     t_canvas canv;
//     t_camera cam;
//     t_ray ray;

//     // Scene setting
//     canv = canvas(400, 300);
//     cam = camera(&canv, point3(0, 0, 0));

//     // Initialize Minilibx
//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr, canv.width, canv.height, "Ray Tracing");

//     // Rendering loop
//     j = canv.height - 1;
//     while (j >= 0)
//     {
//         i = 0;
//         while (i < canv.width)
//         {
//             u = (double)i / (canv.width - 1);
//             v = (double)j / (canv.height - 1);

//             ray = ray_primary(&cam, u, v);
//             pixel_color = ray_color(&ray, NULL);

//             // Convert the color to the appropriate format (32-bit integer)
//             int color = pixel_color.x * 255;
//             color = (color << 8) + pixel_color.y * 255;
//             color = (color << 8) + pixel_color.z * 255;

//             // Set the pixel color using mlx_pixel_put()
//             set_pixel_color(mlx_ptr, win_ptr, i, j, color);

//             ++i;
//         }
//         --j;
//     }

//     // Start the event loop
//     mlx_loop(mlx_ptr);

//     return 0;
// }
