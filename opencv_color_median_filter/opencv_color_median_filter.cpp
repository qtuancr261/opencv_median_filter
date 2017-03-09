#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	Mat input_img, output_img;
	input_img = imread(argv[1], IMREAD_COLOR);
	if (input_img.empty())
	{
		cerr << "Couldn't open image . Exit program...................." << endl;
		return 1;
	}
	output_img = input_img.clone();
	//--------------------------------------------------------------------------------------------
	vector<vector<Vec3b>> pixel(input_img.rows, vector<Vec3b>(input_img.cols));
	vector<unsigned int>BPixel;
	vector<unsigned int>GPixel;
	vector<unsigned int>RPixel;
	for (int i{}; i < input_img.rows; i++)
		for (int j{}; j < input_img.cols; j++)
		{
			pixel[i][j] = input_img.at<Vec3b>(i, j);
		}
	for (int i{}; i < input_img.rows; i++)
		for (int j{}; j < input_img.cols; j++)
		{
			if ((i == 0 || j == 0) || (i == input_img.rows - 1 || j == input_img.cols - 1)) continue;
			BPixel.clear();
			GPixel.clear();
			RPixel.clear();
			for (int x = i - 1; x <= i + 1; x++)
				for (int y = j - 1; y <= j + 1; y++)
				{
					BPixel.push_back(pixel[x][y][0]);
					GPixel.push_back(pixel[x][y][1]);
					RPixel.push_back(pixel[x][y][2]);
				}
			std::sort(std::begin(BPixel), std::end(BPixel));
			std::sort(std::begin(GPixel), std::end(GPixel));
			std::sort(std::begin(RPixel), std::end(RPixel));
			pixel[i][j][0] = BPixel[BPixel.size() / 2];
			pixel[i][j][1] = GPixel[GPixel.size() / 2];
			pixel[i][j][2] = RPixel[RPixel.size() / 2];
		}
	for (int i{}; i < output_img.rows; i++)
		for (int j{}; j < output_img.cols; j++)
		{
			output_img.at<Vec3b>(i, j) = pixel[i][j];
		}
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	namedWindow("Median Filter 3x3", WINDOW_AUTOSIZE);
	imshow("Median Filter 3x3", output_img);

	waitKey();
	return 0;
}
