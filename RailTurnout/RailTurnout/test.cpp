/*********************����ֱ��ͼ*********************/
/*********************����ֱ��ͼ*********************/
/*********************����ֱ��ͼ*********************/
//#include<opencv2/opencv.hpp>    
//#include<iostream>    
//#include<vector>     
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Mat srcImage = imread("1.bmp");
//	imshow("ScrImage", srcImage);
//	int channels = 0;
//	MatND dstHist;
//	int histSize[] = { 256 };       //���д��int histSize = 256;���ü���ֱ��ͼ�ĺ�����ʱ���ñ�����д��&histSize    
//	float midRanges[] = { 0, 256 };
//	const float *ranges[] = { midRanges };
//	calcHist(&srcImage, 1, &channels, Mat(), dstHist, 1, histSize, ranges, true, false);
//
//	//����ֱ��ͼ,�����ȴ���һ���ڵ׵�ͼ��Ϊ�˿�����ʾ��ɫ�����Ըû���ͼ����һ��8λ��3ͨ��ͼ��    
//	Mat drawImage = Mat::zeros(Size(256, 256), CV_8UC3);
//	//�κ�һ��ͼ���ĳ�����ص��ܸ����п��ܻ�ܶ࣬���������������ͼ��ĳߴ磬  
//	//������Ҫ�ȶԸ������з�Χ�����ƣ���minMaxLoc�������õ�����ֱ��ͼ������ص�������    
//	double g_dHistMaxValue;
//	minMaxLoc(dstHist, 0, &g_dHistMaxValue, 0, 0);
//	//�����صĸ������ϵ�ͼ������Χ��    
//	for (int i = 0; i < 256; i++)
//	{
//		int value = cvRound(dstHist.at<float>(i) * 256 * 0.9 / g_dHistMaxValue);
//		line(drawImage, Point(i, drawImage.rows - 1), Point(i, drawImage.rows - 1 - value), Scalar(0, 0, 255));
//	}
//
//	imshow("hist", drawImage);
//	waitKey(0);
//	return 0;
//}
//

/*********************2.ͨ������*********************/
/*********************2.ͨ������*********************/
/*********************2.ͨ������*********************/
//#include <opencv2\opencv.hpp>
//#include <iostream>
//using namespace std;
//using namespace cv;
//int main()
//{
//	Mat SrcMat = imread("1.bmp");
//	cout << "ͨ������" << SrcMat.channels() << endl;
//	//namedWindow("ԭͼ��", WINDOW_NORMAL);
//	imshow("ԭͼ��", SrcMat);
//
//	std::vector<cv::Mat>SrcMatpart(SrcMat.channels());      //������ͨ������Ŀ��ȵ�ͼ������
//	cv::split(SrcMat, SrcMatpart);                          //�ֽ���ͨ������Ŀ��ȵ�ͼ������
//	//cv::Mat MergeMat;
//	//cv::merge(SrcMatpart, MergeMat);                                //�ϳ���ͨ������Ŀ��ȵ�ͼ������
//
//	Mat a= SrcMatpart[0];
//	imshow("�ϳɺ�", SrcMatpart[0]);
//	cout << "�ϳɺ�ͨ������" << SrcMatpart[0].channels() << endl;
//	waitKey(20171209);
//	//destroyWindow("ԭͼ��");
//}

/*********************3.OTSU�Զ���ֵ�ָ�*********************/
/*********************3.OTSU�Զ���ֵ�ָ�*********************/
/*********************3.OTSU�Զ���ֵ�ָ�*********************/
//#include <iostream>  
//#include <opencv2/opencv.hpp>  
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	//Mat img = imread(argv[1], -1);
//	//if (img.empty())
//	//{
//	//	cout << "Error: Could not load image" << endl;
//	//	return 0;
//	//}
//
//	Mat SrcMat = imread("��ֺ�.jpg");
//	//cout << "ͨ������" << SrcMat.channels() << endl;
//	////namedWindow("ԭͼ��", WINDOW_NORMAL);
//	//imshow("ԭͼ��", SrcMat);
//
//	//std::vector<cv::Mat>SrcMatpart(SrcMat.channels());      //������ͨ������Ŀ��ȵ�ͼ������
//	//cv::split(SrcMat, SrcMatpart);                          //�ֽ���ͨ������Ŀ��ȵ�ͼ������
//	//Mat img = SrcMatpart[0];
//
//	Mat gray;
//	cvtColor(SrcMat, gray, CV_BGR2GRAY);
//	Mat dst;
//	int thre = threshold(gray, dst, 0, 255, CV_THRESH_OTSU);
//	//threshold(gray, dst, 250, 255, CV_THRESH_BINARY);         //0�Ǻ�ɫ��1�ǰ�ɫ
//	cout << "��ǰ��ֵΪ��" << thre << endl;
//	imshow("src", SrcMat);
//	imshow("gray", gray);
//	imshow("dst", dst);
//	//imwrite("guangxian.jpg", dst);
//	waitKey(0);
//
//	return 0;
//}


/*********************4.ͼ����*********************/
/*********************4.ͼ����*********************/
/*********************4.ͼ����*********************/
//#include <opencv2\opencv.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//int main()
//{
//	Mat foreground = imread("foreground.bmp");
//	Mat background = imread("background.bmp");
//	Mat diff = foreground - background;
//	imshow("��ֺ�", diff);
//	imwrite("��ֺ�.jpg", diff);
//	waitKey(20171209);
//}
