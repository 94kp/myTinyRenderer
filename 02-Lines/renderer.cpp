#include "tgaimage.h"

// function declarations
void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);

const TGAColor white = TGAColor({ 255, 255, 255, 255 });
const TGAColor red = TGAColor({ 0, 0, 255, 255 });

int main(int argc, char* argv[])
{
	TGAImage image(100, 100, TGAImage::RGB);
	//image.set(52, 41, white);
	line(20, 30, 80, 90, image, red);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	for (float t = 0.0; t < 1.0; t += 0.1)
	{
		int x = x0 + (x1 - x0) * t;
		int y = y0 + (y1 - y0) * t;
		image.set(x, y, color);
	}
}

