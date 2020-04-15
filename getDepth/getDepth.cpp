#include "getDepth.h"
#include "opencv2/opencv.hpp"
#include <cmath>
#include <algorithm>
using namespace std;
using namespace cv;

int getDepth(int Rows, int Cols, int &x, int &y,  const char* inputDepth_mat, double&laser_depth, bool flag) {
	FILE * pFile;
	float * depth;
	//long * center;
	size_t result;
	errno_t err;
	vector<double>depth_data;
	laser_depth = 0.0;
	double Min;
	double Max;

	x = Rows / 2;
	y = Cols / 2;

	err = fopen_s(&pFile, inputDepth_mat, "rb");
	if (pFile == NULL) { fputs("Depth File error", stderr); exit(-1); }
	depth = new float[Rows * Cols];
	if (depth == NULL) { fputs("Memory error", stderr); exit(-2); }
	result = fread(depth, 4, Rows * Cols, pFile);
	if (result != Rows * Cols) { fputs("Depth Reading error", stderr); exit(-3); }
	fclose(pFile);
	Mat Depth_mat = Mat(1, Rows * Cols, CV_32F, depth);
	Depth_mat = Depth_mat.reshape(0, Rows);

	for (int i = 0; i < Depth_mat.rows; i++)
		for (int j = 0; j < Depth_mat.cols; j++)
		{
			if (Depth_mat.at<float>(i, j) != -999)
				depth_data.push_back(Depth_mat.at<float>(i, j));
		}

	sort(depth_data.begin(), depth_data.end());

	double mean = (depth_data[7] + depth_data[depth_data.size() - 7])/2;


	vector<double> min_data;
	vector<double>max_data;
	for (int i = 0; i < depth_data.size(); i++)
	{
		if (depth_data[0] == depth_data[depth_data.size() - 1])
		{
			max_data.push_back((depth_data[i]));
			min_data.push_back(depth_data[i]);
		}		
		else if (depth_data[i] > mean)
		{
			max_data.push_back(depth_data[i]);
		}
		else
			min_data.push_back(depth_data[i]);
	}


	int max_num = max_data.size() / 3;
	int min_num = min_data.size() / 3;
	

	if (flag == 0)//视差较小
	{
		for (int i = min_num; i < 2 * min_num; i++)

		{
			laser_depth += min_data[i];
		}

		laser_depth /= min_num;
		//laser_depth += 0.1;

	}

	else if (flag == 1)//视差较大
	{
		for (int i = max_data.size() - 2 * max_num; i < max_data.size() - max_num; i++)

		{
			laser_depth += max_data[i];
			//laser_depth += 0.1;

		}
		laser_depth /= max_num;

	}
	else
		return 2;

	return 0;

}


//int main()
//{
//	double laser_depth_bottom;
//	double laser_depth_top;
//
//	double laser_depth_bottom_dust;
//
//	double laser_depth_top_dust;
//	int num;
//	float determine;
//	int x;
//	int y;
//	const char * path = "I:\\hyc0415\\depth\\depthBottom01.txt";
//	const char * path1 = "I:\\hyc0415\\depth\\depthTop01.txt";
//	//int rangeCut[2][2] = { { 50 , 50 },{ 5382, 7700 } };
//	//float interval = (rangeCut[1][1] - rangeCut[0][1]) / float(800 - 1);
//	//int Row = (rangeCut[1][0] - rangeCut[0][0]) / interval;
//	const char * path3 = "I:\\hyc0415\\depth\\depth01.txt";
//	getDepth(545, 800, x, y,  path, laser_depth_bottom, 1);
//	//laser_depth_bottom += 0.2;
//	getDepth(545, 800, x, y,  path1, laser_depth_top, 0);
//
//
//	//getDepth(545, 800, x, y, num, path3, laser_depth_top_dust, 1, determine);
//
//	//getDepth(545, 800, x, y, num, path3, laser_depth_bottom_dust, 0, determine);
//	//cout << x << endl;
//	//cout << y << endl;
//	cout << laser_depth_bottom << endl;
//
//	cout << laser_depth_top << endl;
//
//	//cout << laser_depth_top_dust << endl;
//
//	//cout << laser_depth_bottom_dust << endl;
//	//cout << determine << endl;
//	system("pause");
//	return 0;
//}
