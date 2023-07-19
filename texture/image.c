    #include "mlx.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>




    typedef struct s_data
    {
        void			*img;
        char			*addr;
        int				bits_per_pixel;
        int				line_length;
        int				endian;
    }					t_data;




    int	rgb(int r, int g, int b)
    {
        return (r << 16 | g << 8 | b);
    }


    unsigned int get_color_from_pos(t_data *img,int x, int y)
    {
        unsigned int hex_color;

        int pos = (y * img->line_length + x * (img->bits_per_pixel / 8));

        unsigned char r = img->addr[pos + 2];  // Red
        unsigned char g = img->addr[pos + 1];  // Green
        unsigned char b = img->addr[pos];      // Blue

        hex_color = rgb(r,g,b);
        return hex_color;
    }


    void read_xpm_file(void *mlx,void *win )
    {
        char *path;
        t_data *object_sprite;
        int a = 0;
        int color;
        object_sprite = malloc(sizeof(t_data));

            path = "/Users/yait-oul/Desktop/minirt/raytracing/texture/cabin.xpm";
            
            object_sprite = mlx_xpm_file_to_image(mlx, path, &a, &a); 
        object_sprite->addr = mlx_get_data_addr(object_sprite, &object_sprite->bits_per_pixel, &object_sprite->line_length, &object_sprite->endian);
            for(int y = 0; y < 722; y++)
            {
                for(int x = 0; x < 1042; x++)
                {
                
                    color = get_color_from_pos(object_sprite, (float)x , (float)y);
                    mlx_pixel_put(mlx, win, x, y, color);
            }
            }
    
    }


    int main()
    {
        void *mlx;
        void *win;
    
        int x, y;

        mlx = mlx_init();
        win = mlx_new_window(mlx, 1042, 722, "Texture Test");

        
        read_xpm_file(mlx, win);
    

        mlx_loop(mlx);


        return 0;
    }
