#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"

#define WIDTH 1280
#define HEIGHT 720

typedef struct s_img
{
	void		*ptr;
	int			*data;
	int			width;
	int			height;

	int			size_line;
	int			bpp;
	int			endian;
}				t_img;


int			mouse_hook(int button, int x, int y, void *img)
{
	printf("button : %d, x : %d, y : %d\n", button, x, y);
	return (0);
}

int			main(void)
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			count_h;
	int			count_w;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "mlx_project");
	img.ptr = mlx_new_image(mlx, WIDTH, HEIGHT);
	printf("%d, %d\n", img.width, img.height);
	img.data = (int *)mlx_get_data_addr(img.ptr, &img.bpp, &img.size_line, &img.endian);
	printf("%d, %d\n", img.width, img.height);

	mlx_hook(win, 4, 1L<<2, &mouse_hook, &img);
		// 마우스의 입력을 받기 위해선 x_mask를 1L<<2로 설정한다
		// scroll down button :	4
		// scroll up button : 	5

	count_h = -1;
	while (++count_h < HEIGHT)
	{
		count_w = -1;
		while (++count_w < WIDTH)
		{
			if (count_h < count_w)
				img.data[count_h * (img.size_line / 4) + count_w] = 0x00FFFF;
			else
				img.data[count_h * (img.size_line / 4) + count_w] = 0xFFFF00;
		}
	}
	// mms는 이미지를 처리할 때 이미지의 height가 아닌 size_line을 통해 접근해야한다.
	// size_line/4가 아닌 height로 계산하게 되면 정렬이 이상하게 된다.
	// size_line이 무슨 역할을 하는지??
	mlx_put_image_to_window(mlx, win, img.ptr, 0, 0);
	
	for (int i = 100; i < 200; ++i)
		for (int j = 100; j < 200; ++j)
			mlx_pixel_put(mlx, win, i, j, 0xFF0000);
	mlx_loop(mlx);
}