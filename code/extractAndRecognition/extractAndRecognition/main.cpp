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
		//����ԭʼͼƬ
		string srcFileImage = format("tempImage/tempImage%d.jpg", i);
		Mat srcImage = imread(srcFileImage);
	
	//	cout << srcImage.type() << endl;
		
	    //����任
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
	/*//��3�����л����߱任  
	vector<Vec2f> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������  
	HoughLines(src, lines, 1, CV_PI / 180, 150, 0, 0);

	//��4��������ͼ�л��Ƴ�ÿ���߶�  
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
	
	//���л���P�任
	vector<Vec4i> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������  
	HoughLinesP(src, lines, 1, CV_PI / 180, 80, 50, 10);

	//������ͼ�л��Ƴ�ÿ���߶�  
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
	}
	
	//����ͼƬ
	string templeImage = format("srcImage/templeImage%d.jpg", index);
	imwrite(templeImage,dst);
}
