//#include <opencv2\opencv.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//int main()
//{
//	Mat foreground = imread("��3��ˮƽ��\\foreground.jpg");
//	Mat background = imread("��3��ˮƽ��\\background.jpg");
//	Mat diff = foreground - background;
//	namedWindow("��ֺ�", WINDOW_NORMAL);
//	moveWindow("��ֺ�",0,0);
//	imshow("��ֺ�", diff);
//
//	//ͨ�������R��G��B
//	std::vector<cv::Mat>SrcMatpart(diff.channels());      //������ͨ������Ŀ��ȵ�ͼ������
//	cv::split(diff, SrcMatpart);                          //�ֽ���ͨ������Ŀ��ȵ�ͼ������
//	Mat diff_b = SrcMatpart[0];
//	Mat diff_g = SrcMatpart[1];
//	Mat diff_r = SrcMatpart[2];
//
//	//����Rͨ����Gͨ����Ϸָ��Ч��
//	Mat dst_g, dst_r, dst;
//	int thre = threshold(diff_g, dst_g, 0, 255, CV_THRESH_OTSU);
//	//threshold(gray, dst, 250, 255, CV_THRESH_BINARY);         //0�Ǻ�ɫ��1�ǰ�ɫ
//	cout << "��ǰ��ֵΪ��" << thre << endl;
//
//	//������һ��OTSU�Զ��ָ����ֵ��Gͨ���ָ������ȡ����Rͨ���ָ�����Ľ���������
//	threshold(diff_g, dst_g, thre, 255, CV_THRESH_BINARY_INV);   
//
//	//��Rͨ������OTSU��ֵ�ָ�
//	threshold(diff_r, dst_r, 0, 255, CV_THRESH_OTSU);
//
//	//������õ���������
//	bitwise_and(dst_g, dst_r, dst);
//	imshow("dst", diff_r);
//
//	//Mat gray;
//	//cvtColor(diff, gray, CV_BGR2GRAY);
//	//Mat dst;
//	//int thre = threshold(gray, dst, 0, 255, CV_THRESH_OTSU);
//	////threshold(gray, dst, 250, 255, CV_THRESH_BINARY);         //0�Ǻ�ɫ��1�ǰ�ɫ
//	//cout << "��ǰ��ֵΪ��" << thre << endl;
//	//imshow("src", diff);
//	//imshow("gray", gray);
//	//imshow("dst", dst);
//	////imwrite("guangxian.jpg", dst);
//	//waitKey(0);
//
//	cout << "diff_r��ͨ������" << diff_r.channels() << endl;
//	cvtColor(diff_r, diff_r, CV_GRAY2BGR);
//	cout << "diff_r��ͨ������" << diff_r.channels() << endl;
//	imwrite("��ֺ�.jpg", diff_r);
//	waitKey(20171209);
//}


//��ȡ��������
#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	Mat img0 = imread("��ֺ�.jpg", 1);
	imshow("ԭͼ", img0);
	Mat img;
	cvtColor(img0, img0, CV_BGR2GRAY);
	img = img0.clone();

	//��˹�˲�
	img.convertTo(img, CV_32FC1);
	GaussianBlur(img, img, Size(0, 0), 6, 6);

	//һ��ƫ����
	Mat m1, m2;
	m1 = (Mat_<float>(1, 2) << 1, -1);  //xƫ��
	m2 = (Mat_<float>(2, 1) << 1, -1);  //yƫ��

	Mat dx, dy;
	filter2D(img, dx, CV_32FC1, m1);
	filter2D(img, dy, CV_32FC1, m2);

	//����ƫ����
	Mat m3, m4, m5;
	m3 = (Mat_<float>(1, 3) << 1, -2, 1);   //����xƫ��
	m4 = (Mat_<float>(3, 1) << 1, -2, 1);   //����yƫ��
	m5 = (Mat_<float>(2, 2) << 1, -1, -1, 1);   //����xyƫ��

	Mat dxx, dyy, dxy;
	filter2D(img, dxx, CV_32FC1, m3);
	filter2D(img, dyy, CV_32FC1, m4);
	filter2D(img, dxy, CV_32FC1, m5);

	//hessian����
	double maxD = -1;
	int imgcol = img.cols;
	int imgrow = img.rows;
	vector<double> Pt;
	for (int i = 0; i<imgcol; i++)
	{
		for (int j = 0; j<imgrow; j++)
		{
			if (img0.at<uchar>(j, i)>50)           //��ֵ����
			{
				Mat hessian(2, 2, CV_32FC1);
				hessian.at<float>(0, 0) = dxx.at<float>(j, i);
				hessian.at<float>(0, 1) = dxy.at<float>(j, i);
				hessian.at<float>(1, 0) = dxy.at<float>(j, i);
				hessian.at<float>(1, 1) = dyy.at<float>(j, i);

				Mat eValue;				   //����ֵ
				Mat eVectors;              //��������
				eigen(hessian, eValue, eVectors);

				//cout << "����ֵΪ��" << eValue << endl;
				//cout << "��������Ϊ��" << eVectors << endl;

				double nx, ny;				 //����������x��y����
				double fmaxD = 0;            //�������ֵ
				if (fabs(eValue.at<float>(0, 0)) >= fabs(eValue.at<float>(1, 0)))  //������ֵ���ʱ��Ӧ����������
				{
					nx = eVectors.at<float>(0, 0);
					ny = eVectors.at<float>(0, 1);
					fmaxD = eValue.at<float>(0, 0);
				}
				else
				{
					nx = eVectors.at<float>(1, 0);
					ny = eVectors.at<float>(1, 1);
					fmaxD = eValue.at<float>(1, 0);
				}

				double t = -(nx*dx.at<float>(j, i) + ny*dy.at<float>(j, i)) / (nx*nx*dxx.at<float>(j, i) + 2 * nx*ny*dxy.at<float>(j, i) + ny*ny*dyy.at<float>(j, i));

				//cout << "i = " << i << endl;
				//cout << "j = " << j << endl;
				//cout << "t*nx:" << t*nx << endl;
				//cout << "t*ny:" << t*ny << endl;
				if (fabs(t*nx) <= 0.5 && fabs(t*ny) <= 0.5)
				{
					Pt.push_back(i);
					Pt.push_back(j);
				}
			}
		}
	}
	Mat result;
	cvtColor(img0, result, COLOR_GRAY2BGR);
	//result = imread("��3��ˮƽ��\\foreground.jpg");
	for (int k = 0; k<Pt.size() / 2; k++)
	{
		Point rpt;
		rpt.x = Pt[2 * k + 0];
		rpt.y = Pt[2 * k + 1];
		result.at<Vec3b>(rpt.y, rpt.x)[0] = 255;
		result.at<Vec3b>(rpt.y, rpt.x)[1] = 0;
		result.at<Vec3b>(rpt.y, rpt.x)[2] = 0;
		//circle(result, rpt, 1, Scalar(0, 0, 255));
	}
	//namedWindow("result", WINDOW_NORMAL);
	imshow("result", result);
	waitKey(0);
	waitKey(20171209);
}
