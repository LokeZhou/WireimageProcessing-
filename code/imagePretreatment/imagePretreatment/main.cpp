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
	namedWindow("resizeImage", CV_WINDOW_AUTOSIZE); //����ԭͼ�񴰿�  
	imshow("resizeImage", resizeImage); //��ʾԭͼ��  
	*/
	
	Mat PLGImage(resizeImage.rows,resizeImage.cols, CV_8UC1);
	Mat NSImage(resizeImage.rows, resizeImage.cols, CV_8UC1);

	/*�Ҷ����Ա任*/
	PiecewiseLinearGrayTransformation(resizeImage, PLGImage, 255, 0);
	
	/*ƽ��ȥ��*/
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

	namedWindow("drcImage", CV_WINDOW_AUTOSIZE); //�����Ҷȱ任ͼ�񴰿�  
	imshow("drcImage", dst); //��ʾ�Ҷȱ任ͼ�� 

}

static void on_MeanBlur(int, void *);           //��ֵ�˲��ص����� 


void NoiseSmoothing(Mat & src, Mat &dst)
{
	
	//��������  
	namedWindow("��<2>��ֵ�˲���", CV_WINDOW_AUTOSIZE);
	//�����켣��  
	createTrackbar("�ں�ֵ��", "��<2>��ֵ�˲���", &g_nMeanBlurValue, 40, on_MeanBlur);
	NSsrcImage = &src;
	NSdstImage = &dst;
	on_MeanBlur(g_nMeanBlurValue, 0);
}
void on_MeanBlur(int , void *)
{
	Mat src = *NSsrcImage;
	Mat dst = *NSdstImage;
	//��ֵ�˲�����  
	blur(src, dst, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	//��ʾ����  
	imshow("��<2>��ֵ�˲���", dst);
	String tempImageName = "tempImage/NSImage.jpg";
	imwrite(tempImageName, dst);
}
