#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void medianFilter(Mat& input, Mat& output, int kernelSize)
{
	vector<int> newPixelValue;
	int halfSize = kernelSize / 2;
	for (int i{ halfSize }; i < input.rows - halfSize; i++)
		for (int j{ halfSize }; j < input.cols - halfSize; j++)
		{
			newPixelValue.clear();
			for (int x = { -halfSize }; x <= halfSize; x++)
				for (int y = { -halfSize }; y <= halfSize; y++)
				{
					newPixelValue.push_back(input.at<uchar>(i + x, j + y));
				}
			sort(begin(newPixelValue), end(newPixelValue));
			output.at<uchar>(i, j) = newPixelValue[newPixelValue.size()/2];
		}
}
int main(int argc, char *argv[])
{
	double start{ (double)getTickCount() };
	Mat input_img;
	input_img = imread(argv[1], IMREAD_GRAYSCALE);
	if (input_img.empty())
	{
		cerr << "Couldn't open image . Exit program...................." << endl;
		return 1;
	}
	Mat output_img(input_img.clone());
	//-------------------------------------------------------------------------------------------
	int kernelSize{};
	cout << " Nhap vao kich thuoc m cua ma tran Kernel: ";
	cin >> kernelSize;
	medianFilter(input_img, output_img, kernelSize);
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	namedWindow("Median Filter", WINDOW_AUTOSIZE);
	imshow("Median Filter", output_img);
	double end{ (double)(getTickCount() - start) / getTickFrequency() };
	cout << " Timing : " << end << endl;
	waitKey();
	return 0;
}
