#include<opencv2\opencv.hpp>
#include<iostream>
#include<cstring>
using namespace cv;
using namespace std;

void PiecewiseLinearGrayTransformation(Mat &src, Mat& dst, double maxGray, double minGray);
void NoiseSmoothing(Mat &src, Mat &dst);

int g_nMeanBlurValue = 3;
Mat *NSsrcImage, *NSdstImage;
int main()
{
	Mat srcImage = imread("1.jpg", CV_8UC1);
	Mat resizeImage;
	resize(srcImage, resizeImage, Size(),0.125,0.125);

	/*
	namedWindow("resizeImage", CV_WINDOW_AUTOSIZE); //创建原图像窗口  
	imshow("resizeImage", resizeImage); //显示原图像  
	*/
	
	Mat PLGImage(resizeImage.rows,resizeImage.cols, CV_8UC1);
	Mat NSImage(resizeImage.rows, resizeImage.cols, CV_8UC1);

	/*灰度线性变换*/
	PiecewiseLinearGrayTransformation(resizeImage, PLGImage, 255, 0);
	
	/*平滑去噪*/
	NoiseSmoothing(PLGImage, NSImage);

	cvWaitKey();
	
	return 0;
}

void PiecewiseLinearGrayTransformation(Mat &src, Mat& dst, double maxGray, double minGray)
{
	double maxVal = 0;
	double minVal = 0;

	minMaxLoc(src, &minVal, &maxVal);

	double k = (maxGray - minGray) / (maxVal - minVal) ;

	
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			int temp = (int)src.at<uchar>(i, j);
          
			if ((temp > minVal ||(temp == minVal)) && temp < maxVal)
				dst.at<uchar>(i,j) = k*((double)temp - minVal) + minGray;

			if(temp < minVal || ((temp > maxVal) && (temp == maxVal)))
				dst.at<uchar>(i, j) = temp;
				  
		}
	}

	namedWindow("drcImage", CV_WINDOW_AUTOSIZE); //创建灰度变换图像窗口  
	imshow("drcImage", dst); //显示灰度变换图像 

}

static void on_MeanBlur(int, void *);           //均值滤波回调函数 


void NoiseSmoothing(Mat & src, Mat &dst)
{
	
	//创建窗口  
	namedWindow("【<2>均值滤波】", CV_WINDOW_AUTOSIZE);
	//创建轨迹条  
	createTrackbar("内核值：", "【<2>均值滤波】", &g_nMeanBlurValue, 40, on_MeanBlur);
	NSsrcImage = &src;
	NSdstImage = &dst;
	on_MeanBlur(g_nMeanBlurValue, 0);
}
void on_MeanBlur(int , void *)
{
	Mat src = *NSsrcImage;
	Mat dst = *NSdstImage;
	//均值滤波操作  
	blur(src, dst, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	//显示窗口  
	imshow("【<2>均值滤波】", dst);
	String tempImageName = "tempImage/NSImage.jpg";
	imwrite(tempImageName, dst);
}
