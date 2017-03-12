#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
void medianFilter(Mat& input, Mat& output, int kernelSize)
{
	vector<int> newBValue;
	vector<int> newGValue;
	vector<int> newRValue;
	int halfSize{ kernelSize / 2 };
	int pos = {kernelSize*kernelSize / 2};
	for (int i{ halfSize }; i < input.rows - halfSize; i++)
		for (int j{ halfSize }; j < input.cols - halfSize; j++)
		{
			newRValue.clear(); newGValue.clear(); newBValue.clear();
			for (int x = { -halfSize }; x <= halfSize; x++)
				for (int y = { -halfSize }; y <= halfSize; y++)
				{
					newBValue.push_back(input.at<Vec3b>(i + x, j + y)[0]);
					newGValue.push_back(input.at<Vec3b>(i + x, j + y)[1]);
					newRValue.push_back(input.at<Vec3b>(i + x, j + y)[2]);
				}
			sort(begin(newRValue), end(newRValue));
			sort(begin(newGValue), end(newGValue));
			sort(begin(newBValue), end(newBValue));
			output.at<Vec3b>(i, j) = Vec3b(newBValue[pos], newGValue[pos], newRValue[pos]);
		}
}
int main(int argc, char *argv[])
{
	double start{ (double)getTickCount() };
	Mat input_img;
	input_img = imread(argv[1], IMREAD_COLOR);
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
