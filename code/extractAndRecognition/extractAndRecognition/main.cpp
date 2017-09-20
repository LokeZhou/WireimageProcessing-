#include<opencv2\opencv.hpp>
#include<iostream>
#include<cstring>
using namespace cv;
using namespace std;

void HoughTransform(Mat src, Mat& dst, int index);
int main()
{
	int i = 0;
	for (; i < 1; i++)
	{
		//载入原始图片
		string srcFileImage = format("tempImage/tempImage%d.jpg", i);
		Mat srcImage = imread(srcFileImage);
	
	//	cout << srcImage.type() << endl;
		
	    //霍夫变换
		Mat houghDstImage;
		houghDstImage = srcImage.clone();
/*
		Mat midImage;
		midImage.create(srcImage.size(), srcImage.type());
		threshold(srcImage, midImage, 96, 255, THRESH_BINARY);
		*/
		HoughTransform(srcImage, houghDstImage,i);

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
	HoughLinesP(src, lines, 1, CV_PI / 180, 80, 50, 10);

	//依次在图中绘制出每条线段  
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
	}
	
	//保存图片
	string templeImage = format("srcImage/templeImage%d.jpg", index);
	imwrite(templeImage,dst);
}
