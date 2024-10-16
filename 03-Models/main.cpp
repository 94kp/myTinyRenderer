#include <vector>
#include <cmath>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

// function declarations
void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);

const TGAColor white = TGAColor({ 255, 255, 255, 255 });
const TGAColor red = TGAColor({ 0, 0, 255, 255 });
Model* model = NULL;

const int width = 800;
const int height = 800;

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		model = new Model(argv[1]);
	}
	else
	{
		model = new Model("obj/monkeyhead.obj");
	}

	TGAImage image(width, height, TGAImage::RGB);
	//image.set(52, 41, white);
	//line(20, 30, 80, 90, image, red);
	//line(13, 20, 80, 40, image, white);
	//line(20, 13, 40, 80, image, red);
	//line(80, 40, 13, 20, image, red);

	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);

		for (int i = 0; i < model->nfaces(); i++)
		{
			std::vector<int> face = model->face(i);
			for (int j = 0; j < 3; j++) 
			{
				Vec3f v0 = model->vert(face[j]);
				Vec3f v1 = model->vert(face[(j + 1) % 3]);
				int x0 = (v0.x + 1.0) * width / 2.0;
				int y0 = (v0.y + 1.0) * height / 2.0;
				int x1 = (v1.x + 1.0) * width / 2.0;
				int y1 = (v1.y + 1.0) * height / 2.0;
				line(x0, y0, x1, y1, image, white);
			}
		}

	}

	//image.flip_vertically();
	//printf("write file now\n");
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	/*
	for (float t = 0.0; t < 1.0; t += 0.1)
	{
		int x = x0 + (x1 - x0) * t;
		int y = y0 + (y1 - y0) * t;
		image.set(x, y, color);
	}
	*/

	// Bresenham
	/*for (int x = x0; x <= x1; x++)
	{
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1.0 - t) + y1 * t;
		image.set(x, y, color);
	}*/

	// DDA
	int dx = x1 - x0;
	int dy = y1 - y0;

	//float m = dy / dx;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	float inc_x = dx / (float)steps;
	float inc_y = dy / (float)steps;

	float x = x0;
	float y = y0;

	for (int i = 0; i < steps; i++)
	{
		image.set(round(x), round(y), color);
		x += inc_x;
		y += inc_y;
	}

}

/*
void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}
*/

