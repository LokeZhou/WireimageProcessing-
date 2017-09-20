#include<opencv2\opencv.hpp>
#include<iostream>
#include<cstring>
using namespace cv;
using namespace std;

void PiecewiseLinearGrayTransformation(Mat &src, Mat& dst, double maxGray, double minGray);
void NoiseSmoothing(Mat &src, Mat &dst);


int main()
{
	int i = 0;
	for(;i<29;i++)
	{ 
	    string srcFileName = format("srcImage/%d.jpg", i);
	    Mat srcImage = imread(srcFileName,CV_8U);
	
	    Mat resizeImage;
	    resize(srcImage, resizeImage, Size(),0.125,0.125);
	
        
	
		Mat PLGImage;
		PLGImage.create(resizeImage.size(), resizeImage.type());
	    Mat NSImage;
		NSImage.create(resizeImage.size(), resizeImage.type());

	  /*灰度线性变换*/
	    PiecewiseLinearGrayTransformation(resizeImage, PLGImage, 255, 0);
	  
     /*均值滤波*/
		NoiseSmoothing(PLGImage, NSImage);

     /*sobel边缘检测*/
		Mat sobelDstImage;
		sobelDstImage.create(resizeImage.size(), resizeImage.type());
	//【4】求Y方向梯度  
		Sobel(NSImage, sobelDstImage, CV_8U, 0, 1, 3, 1, 1, BORDER_DEFAULT);
		convertScaleAbs(sobelDstImage, sobelDstImage);

	/*保存预处理结果*/
	   string dstFileName = format("tempImage/tempImage%d.jpg", i);
	   imwrite(dstFileName, sobelDstImage);
	 
	  
	}

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
				dst.at<uchar>(i, j) = 255;
				  
		}
	}

}



void NoiseSmoothing(Mat & src, Mat &dst)
{
	blur(src, dst, Size(3,3), Point(-1, -1));
	
}

