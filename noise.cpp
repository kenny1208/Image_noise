#include <iostream>
#include <vector>
#include <random>
#include <time.h> 


using namespace std;

int main() {
	FILE* fp_r;
	FILE* fp_w;

	bool err_r = fopen_s(&fp_r, "AiPicG.bmp", "rb");
	bool err_w = fopen_s(&fp_w, "AIgened_x.bmp", "wb");
	if (err_r != 0 || err_w != 0)
		return 0;

	unsigned char c;
	for (int i = 0; i < 1078; i++) {
		c = getc(fp_r);
		putc(c, fp_w);
	}

	int w = 1024;
	int h = 1024;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> noise_prob(1, 20); 
	uniform_int_distribution<> black_or_white(0, 1); 
	//normal_distribution<> dis(0.0f, 32.0f);
	//uniform_int_distribution<> dis(-64, 64);

	vector<vector<unsigned char>> imgArr;
	imgArr.resize(h, vector<unsigned char>(w));

	for (int i = 0; i < w * h; i++) 
	{
		int x = i % w;
		int y = i / w;
		int pixel = getc(fp_r);

		if (noise_prob(gen) == 1) 
		{
			pixel = (black_or_white(gen) == 0) ? 0 : 255;
		}

		imgArr[x][h - y - 1] = static_cast<unsigned char>(pixel);
	}

	for (int i = h - 1; i >= 0; i--)
	{
		for (int j = 0; j < w; j++)
		{
			putc(imgArr[j][i], fp_w);
		}

	}
	fclose(fp_r);
	fclose(fp_w);
	return 0;
}


