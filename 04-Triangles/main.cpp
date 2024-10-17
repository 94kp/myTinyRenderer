#include <vector>
#include <cmath>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

// function declarations
void line(Vec2i xy0, Vec2i xy1, TGAImage& image, TGAColor color);
void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color);

const TGAColor white = TGAColor({ 255, 255, 255, 255 });
const TGAColor red = TGAColor({ 0, 0, 255, 255 });
const TGAColor green = TGAColor({ 0, 255, 0, 255 });

int width = 600;
int height = 800;

int main(int argc, char* argv[])
{
	TGAImage image(height, width, TGAImage::RGB);
	//image.set(52, 41, white);
	//line(20, 30, 80, 90, image, red);
	//line(13, 20, 80, 40, image, white);
	//line(20, 13, 40, 80, image, red);
	//line(80, 40, 13, 20, image, red);

	Vec2i t0[3] = { Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80) };
	Vec2i t1[3] = { Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180) };
	Vec2i t2[3] = { Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180) };

	triangle(t0[0], t0[1], t0[2], image, red);
	triangle(t1[0], t1[1], t1[2], image, white);
	triangle(t2[0], t2[1], t2[2], image, green);

	//image.flip_vertically();
	image.write_tga_file("output.tga");
	printf("output file generated\n");
	return 0;
}

void line(Vec2i xy0, Vec2i xy1, TGAImage& image, TGAColor color)
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
	int dx = xy1.x - xy0.x;
	int dy = xy1.y - xy0.y;

	//float m = dy / dx;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	float inc_x = dx / (float)steps;
	float inc_y = dy / (float)steps;

	float x = xy0.x;
	float y = xy0.y;

	for (int i = 0; i < steps; i++)
	{
		image.set(round(x), round(y), color);
		x += inc_x;
		y += inc_y;
	}

}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color)
{
	if (t0.y > t1.y) std::swap(t0, t1);
	if (t0.y > t2.y) std::swap(t0, t2);
	if (t1.y > t2.y) std::swap(t1, t2);

	int total_height = t2.y - t0.y;
	for (int y = t0.y; y <= t1.y; y++)
	{
		int segment_height = t1.y - t0.y + 1;
		float alpha = (float)(y - t0.y) / total_height;
		float beta = (float)(y - t0.y) / segment_height;

		Vec2i A = t0 + (t2 - t0) * alpha;
		Vec2i B = t0 + (t1 - t0) * beta;
		for (int j = A.x; j <= B.x; j++)
		{
			image.set(j, y, color);
		}

		//image.set(A.x, y, red);
		//image.set(B.x, y, green);
	}
	for (int y = t1.y; y <= t2.y; y++)
	{
		int segment_height = t2.y - t1.y + 1;
		float alpha = (float)(y - t0.y) / total_height;
		float beta = (float)(y - t1.y) / segment_height;
		Vec2i A = t0 + (t2 - t0) * alpha;
		Vec2i B = t1 + (t2 - t1) * beta;
		if (A.x > B.x)
			std::swap(A, B);
		for (int j = A.x; j <= B.x; j++)
		{
			image.set(j, y, color);
		}
	}

	//line(t0, t1, image, green);
	//line(t1, t2, image, green);
	//line(t2, t0, image, red);
}

