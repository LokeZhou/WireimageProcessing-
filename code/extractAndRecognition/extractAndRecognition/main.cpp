#include<opencv2\opencv.hpp>
#include<iostream>
#include<cstring>
using namespace cv;
using namespace std;

void HoughTransform(Mat src, Mat& dst, int index);
int main()
{

	
	int i = 0;
	for (; i < 29; i++)
	{
		//载入原始图片
		string srcFileImage = format("srcImage/%d.jpg", i);
		Mat srcImage = imread(srcFileImage);
		resize(srcImage, srcImage, Size(), 0.125, 0.125);
		Mat midImage, dstImage;//临时变量和目标图的定义  
		
		//【2】进行边缘检测和转化为灰度图  
		Canny(srcImage, midImage, 100, 250, 3);//进行一此canny边缘检测  
		cvtColor(midImage, dstImage, CV_GRAY2BGR);//转化边缘检测后的图为灰度图  
		//保存边缘检测图
		string templeImage = format("templeImage/templeImage%d.jpg", i);
		imwrite(templeImage, dstImage);
		
	
		HoughTransform(midImage, dstImage,i);

		
	}
	

	cvWaitKey();
	return 0;
}

void HoughTransform(Mat src, Mat & dst, int index)
{
	/*//【3】进行霍夫线变换  
	vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合  
	HoughLines(src, lines, 1, CV_PI / 180, 150, 0, 0);

	//【4】依次在图中绘制出每条线段  
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dst, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
	}*/
	
	//进行霍夫P变换
	vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合  
	HoughLinesP(src, lines, 1, CV_PI / 180, 150, 50, 10);

	//依次在图中绘制出每条线段  
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
	}
	
	//保存图片
	string templeImage = format("dstImage/dstImage%d.jpg", index);
	imwrite(templeImage,dst);
}
