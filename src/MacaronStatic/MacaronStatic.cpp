// MacaronStatic.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//
#include "pch.h"
#include<opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
#include<opencv2/core.hpp> 
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/highgui.hpp> 
#include<opencv2/imgproc.hpp> 
#include <windows.h>
#include <iostream>
#include <opencv2/plot.hpp>
#include <thread>
#include <vector>
#include "Macaron.h"
#include "Rockey4_ND_64.h"


#pragma comment(lib, "C:\\CORE_D\\lib\\Rockey4ND_X64.lib")


// ----------------------------------------------------------------------------------------
#pragma comment(lib, "user32.lib")

bool m_bRegisterIntelliz = false;
float m_fLower = 0;
float m_fHIgh = 15;
int m_iHeatMapClass = 0;

int m_iCheckKey = 0;

using namespace std;



BOOL INTELLIZ(
)
{

	int i = 0, j;
	WORD handle, p1, p2, p3, p4, retcode;
	DWORD lp1, lp2;
	BYTE buffer[1024];
	WORD rc[4];


	int result = 0;

	try {
		

			if (!m_bRegisterIntelliz)
			{
				p1 = 0x26F8;
				p2 = 0xEAE6;
				p3 = 0x25EF;
				p4 = 0xD9E6;
				retcode = Rockey(RY_FIND, &handle, &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
				if (retcode)
				{
					std::cout << "DON'T HAVE INTELLIZ DONGLE KEY" << std::endl;
					MessageBoxA(NULL, "Check your INTELLIZ DONGLE KEY.", "Validation Error", MB_OK);

					//RY_READ_USERID
					return FALSE;
				}
				else
				{

					retcode = Rockey(RY_OPEN, &handle, &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);
					if (retcode) {        //ROCKEY4ND를 Open하지 못하면… 
						std::cout << "DON'T HAVE INTELLIZ DONGLE KEY" << std::endl;
						return FALSE;
					}
					retcode = Rockey(RY_READ_USERID, &handle, &lp1, &lp2, &p1, &p2, &p3, &p4, buffer);

					cout << retcode << ",Find INTELLIZ DONGLE USER ID:" << lp1 << "," << lp2 << "," << p1 << "," << p2 << "," << p3 << "," << buffer << endl;
					printf("read user ID:%08X\N", lp1);
					if (lp1 < 0x1000 || lp1 > 0x2000)
						return FALSE;
					
					//MessageBoxA(NULL, "good.", "GOOD", MB_OK);
					m_bRegisterIntelliz = true;
				}

			}

			
		return TRUE;
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
}





// TODO: 라이브러리 함수의 예제입니다.
void claheGammaGPU(cv::cuda::GpuMat& imgGpu, double m_GammaRate, double m_ClipLimit, int m_TilesGridSize) {

	//이미지 type 및 이미지 channel 변경 여부
	bool bCheckType = 0;
	bool bCheckChannel = 0;

	//Gamma value 설정
	float invGamma = 2.0 * m_GammaRate;


	//Gpu로 업로드 및 Gpu 객체 생성
	//cv::cuda::GpuMat imgGpu(img);


	//들어온 이미지가 1 channel 이미지인지 확인 및 변경
	if (imgGpu.channels() > 1) {
		//cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_BGR2GRAY);
		//bCheckChannel = true;
	}

	//들어온 이미지가 8 bit 이미지인지 확인 및 변경
	if (imgGpu.type() != CV_8UC1 & imgGpu.type() != CV_8UC3) {
		//imgGpu.convertTo(imgGpu, CV_8U);
		//bCheckType = true;
	}



	//Gamma 변환
	cv::Mat table(1, 256, CV_8U);
	uchar* p = table.ptr();
	#pragma omp parallel for num_threads(2)
	for (int i = 0; i < 256; i++) {
		p[i] = (pow((i / 255.0), 1.0 / invGamma) * 255.0);
	}

	cv::Ptr<cv::cuda::LookUpTable>temp;
	temp = cv::cuda::createLookUpTable(table);
	temp->transform(imgGpu, imgGpu);


	//CLAHE 적용
	std::vector<cv::cuda::GpuMat> lab_planes(3);
	cv::cuda::split(imgGpu, lab_planes);
	cv::Ptr<cv::cuda::CLAHE> clahe = cv::cuda::createCLAHE(30.0);
	clahe->setClipLimit(m_ClipLimit); //Threshold value set
	clahe->setTilesGridSize(cv::Size(m_TilesGridSize, m_TilesGridSize));
	clahe->apply(imgGpu, imgGpu);


	//이미지 기존 chanenl로 변환
	if (bCheckChannel) {
		cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_GRAY2BGR);
	}
	//이미지 기존 bit로 변환
	if (bCheckType) {
		//imgGpu.convertTo(imgGpu, CV_16U);
		double minVal, maxVal;
		
		cv::cuda::minMaxLoc(imgGpu, &minVal, &maxVal,0,0);
		imgGpu.convertTo(imgGpu, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
	}

	

	//이미지 다운로드
	//imgGpu.download(img);

	

}


void claheGammaCPU(cv::Mat& img, double m_GammaRate, double m_ClipLimit, int m_TilesGridSize) {

	//Gamma value 설정
	float invGamma = 2.0 * m_GammaRate;

	//이미지 type 및 이미지 channel 변경 여부
	bool bCheckType = 0;
	bool bCheckChannel = 0;

	//들어온 이미지가 8 bit 이미지인지 확인 및 변경
	if (img.type() != CV_8UC1 & img.type() != CV_8UC3) {
		//img.convertTo(img, CV_8U);
		//bCheckType = true;
	}


	//Gamma 적용
	cv::Mat table(1, 256, CV_8U);
	uchar* p = table.ptr();
	for (int i = 0; i < 256; i++) {
		p[i] = (pow((i / 255.0), 1 / invGamma) * 255);
	}
	cv::LUT(img, table, img);

	
	//들어온 이미지가 1 channel 이미지인지 확인 및 변경
	if (img.channels() < 3) {
		cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
		bCheckChannel = true;
	}
	//CLAHE 를 위해 이미지를 Lab 으로 변환
	cv::cvtColor(img, img, cv::COLOR_BGR2Lab);

	
	//CLAHE 적용
	std::vector<cv::Mat> lab_planes(3);
	cv::split(img, lab_planes); //이미지를 3 채널로 나눔
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();

	clahe->setClipLimit(m_ClipLimit); //Threshold value set
	clahe->setTilesGridSize(cv::Size(m_TilesGridSize, m_TilesGridSize));
	cv::Mat dst;
	clahe->apply(lab_planes[0], dst); //Clahe 적용
	dst.copyTo(lab_planes[0]);
	cv::merge(lab_planes, img);

	/////////////기존 이미지로 변환///////////////

	//이미지 기존 chanenl로 변환
	cv::cvtColor(img, img, cv::COLOR_Lab2BGR);
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	if (bCheckChannel) {
		//cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	}
	//이미지 기존 bit로 변환
	if (bCheckType) {
		//img.convertTo(img, CV_16U);
	}

	
}


void claheGPU(cv::cuda::GpuMat& imgGpu, double m_ClipLimit, int m_TilesGridSize) {

	//이미지 type 및 이미지 channel 변경 여부
	bool bCheckType = 0;
	bool bCheckChannel = 0;

	//Gpu로 업로드 및 Gpu 객체 생성
	//cv::cuda::GpuMat imgGpu(img);

	//들어온 이미지가 8 bit 이미지인지 확인 및 변경
	if (imgGpu.type() != CV_8UC1 & imgGpu.type() != CV_8UC3) {
		//imgGpu.convertTo(imgGpu, CV_8U);
		//bCheckType = true;
	}

	//들어온 이미지가 1 channel 이미지인지 확인 및 변경
	if (imgGpu.channels() > 1) {
		//cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_BGR2GRAY);
		//bCheckChannel = true;
	}

	//CLAHE 적용
	//std::vector<cv::cuda::GpuMat> lab_planes(3);
	//cv::cuda::split(imgGpu, lab_planes);
	cv::Ptr<cv::cuda::CLAHE> clahe = cv::cuda::createCLAHE();
	clahe->setClipLimit(m_ClipLimit); //Set Threshold value
	clahe->setTilesGridSize(cv::Size(m_TilesGridSize, m_TilesGridSize));
	clahe->apply(imgGpu, imgGpu);

	//이미지 기존 bit로 변환
	if (bCheckType) {
		imgGpu.convertTo(imgGpu, CV_16UC1);
	}

	//이미지 기존 chanenl로 변환
	if (bCheckChannel) {
		cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_GRAY2BGR);
	}

	//이미지 다운로드
	//imgGpu.download(img);


	
}

void claheCPU(cv::Mat& img, double m_ClipLimit, int m_TilesGridSize) {

	//이미지 type 및 이미지 channel 변경 여부
	bool bCheckType = 0;
	bool bCheckChannel = 0;

	//들어온 이미지가 1 channel 이미지인지 확인 및 변경
	/*if (img.channels() < 3) {
		cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
		bCheckChannel = true;
	}*/
	//CLAHE 를 위해 이미지를 Lab 으로 변환

	cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
	cv::cvtColor(img, img, cv::COLOR_BGR2Lab);

	//CLAHE 적용
	std::vector<cv::Mat> lab_planes(3);
	cv::split(img, lab_planes);
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(m_ClipLimit);
	clahe->setTilesGridSize(cv::Size(m_TilesGridSize, m_TilesGridSize));
	cv::Mat dst;
	clahe->apply(lab_planes[0], dst);
	dst.copyTo(lab_planes[0]);
	cv::merge(lab_planes, img);


	/////////////기존 이미지로 변환///////////////
	//이미지 기존 bit로 변환
	if (bCheckType) {
		img.convertTo(img, CV_16U);
	}

	//이미지 기존 chanenl로 변환
	cv::cvtColor(img, img, cv::COLOR_Lab2BGR);
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	if (bCheckChannel) {
		cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	}



}



void claheHiseqGPU(cv::cuda::GpuMat& imgGpu, double m_ClipLimit, int m_TilesGridSize) {

	//이미지 type 및 이미지 channel 변경 여부
	bool bCheckType = 0;
	bool bCheckChannel = 0;

	//Gpu로 업로드 및 Gpu 객체 생성
	//cv::cuda::GpuMat imgGpu(img);

	//들어온 이미지가 8 bit 이미지인지 확인 및 변경
	if (imgGpu.type() != CV_8UC1 & imgGpu.type() != CV_8UC3) {
		imgGpu.convertTo(imgGpu, CV_8U);
		bCheckType = true;
	}

	//들어온 이미지가 1 channel 이미지인지 확인 및 변경
	if (imgGpu.channels() > 1) {
		cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_BGR2GRAY);
		bCheckChannel = true;
	}

	//Histogram Equalization 적용
	//cuda::calcHist(imgGpu,mask,imgGpu);
	cv::cuda::equalizeHist(imgGpu, imgGpu);

	//CLAHE 적용
	cv::Ptr<cv::cuda::CLAHE> clahe = cv::cuda::createCLAHE();
	clahe->setClipLimit(m_ClipLimit);
	clahe->setTilesGridSize(cv::Size(m_TilesGridSize, m_TilesGridSize));
	clahe->apply(imgGpu, imgGpu);

	//이미지 기존 bit로 변환
	if (bCheckType) {
		imgGpu.convertTo(imgGpu, CV_16U);
	}

	//이미지 기존 chanenl로 변환
	if (bCheckChannel) {
		cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_GRAY2BGR);
	}

	//imgGpu.download(img);

}


void claheHiseqCPU(cv::Mat& img, double m_ClipLimit, int m_TilesGridSize) {

	////이미지 type 및 이미지 channel 변경 여부
	//bool bCheckType = 0;
	//bool bCheckChannel = 0;

	////들어온 이미지가 1 channel 이미지인지 확인 및 변경
	//if (img.channels() < 3) {
	//	cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
	//	bCheckChannel = true;
	//}
	////CLAHE 를 위해 이미지를 Lab 으로 변환
	//cv::cvtColor(img, img, cv::COLOR_BGR2Lab);

	cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
	cv::cvtColor(img, img, cv::COLOR_BGR2Lab);

	std::vector<cv::Mat> lab_planes(3);
	split(img, lab_planes);

	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(m_ClipLimit);
	clahe->setTilesGridSize(cv::Size(m_TilesGridSize, m_TilesGridSize));
	cv::Mat dst;
	clahe->apply(lab_planes[0], dst);

	dst.copyTo(lab_planes[0]);
	cv::merge(lab_planes, img);
	cv::cvtColor(img, img, cv::COLOR_Lab2BGR);
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

	cv::equalizeHist(img, img);
	

}



void gammaGPU(cv::cuda::GpuMat& imgGpu, double m_GammaRate)
{
	float invGamma = 2.0 * m_GammaRate;
	//cv::cuda::GpuMat imgGpu(img);

	


	cv::Mat table(1, 256, CV_8U);
	uchar* p = table.ptr();

#pragma omp parallel for num_threads(4)
	for (int i = 0; i < 256; i++) {
		p[i] = (pow((i / 255.0), 1.0 / invGamma) * 255.0);
	}

	cv::Ptr<cv::cuda::LookUpTable> temp = cv::cuda::createLookUpTable(table);

	temp->transform(imgGpu, imgGpu);

	//imgGpu.download(img);
	

}
void gammaCPU(cv::Mat& img, double m_GammaRate)
{
	float invGamma = 2.0 * m_GammaRate;

	cv::Mat table(1, 256, CV_8U);
	uchar* p = table.ptr();
	for (int i = 0; i < 256; i++) {
		p[i] = (pow((i / 255.0), 1 / invGamma) * 255);
	}
	cv::LUT(img, table, img);

}


void hisEQGPU(cv::cuda::GpuMat& imgGpu) {

	//cv::cuda::GpuMat imgGpu(img);


	//cv::cuda::GpuMat hist_equalized_image;

	cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_GRAY2BGR);
	cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_BGR2YCrCb);

	std::vector<cv::cuda::GpuMat> vec_channels;
	cv::cuda::split(imgGpu, vec_channels);

	cv::cuda::equalizeHist(vec_channels[0], vec_channels[0]);

	cv::cuda::merge(vec_channels, imgGpu);

	cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_YCrCb2BGR);
	cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_BGR2GRAY);

	//hist_equalized_image.download(img);

}

void hisEQCPU(cv::Mat& img) {

	cv::Mat hist_equalized_image;
	cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);
	cv::cvtColor(img, img, cv::COLOR_BGR2YCrCb);

	std::vector<cv::Mat> vec_channels;
	cv::split(img, vec_channels);

	cv::equalizeHist(vec_channels[0], vec_channels[0]);

	cv::merge(vec_channels, img);

	cv::cvtColor(img, img, cv::COLOR_YCrCb2BGR);
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

}

void sharpening(cv::Mat& img, double m_SharpeningFactor) {
	
	double centre = 9.5 * m_SharpeningFactor;

	cv::Mat kernel = (cv::Mat_<double>(3, 3) << -1.0, -1.02, -1.0,
		-1.01, centre, -1.01,
		-1.0, -1.02, -1.0);
	filter2D(img, img, -1, kernel);
	

}

void convertColor(cv::Mat& img) {

	#pragma omp parallel for num_threads(4)
	for (int i = 0; i < img.cols; i++) {
		for (int k = 0; k < img.rows; k++) {
			img.at<uchar>(cv::Point(i, k)) *= 255.0;
		}
	}
}






std::vector<int> containValues;
cv::Point pt1(1, 1);
cv::Point pt2(1, 1);
int cnt = 0;
bool m_bMouseClick1 = false;
bool m_bMouseClick2 = false;
double dFactor = 1.0;

void mouse_callback(int  event, int  x, int  y, int  flag, void* param)
{
	if (event == cv::EVENT_LBUTTONDOWN && cnt == 0)
	{
		pt1.x = 1/ dFactor * x;
		pt1.y = 1/ dFactor * y;
		cnt++;
		//cout << "pt1 :" << pt1.x << " And " << pt1.y << endl;
		m_bMouseClick1 = true;
	}
	else if (event == cv::EVENT_LBUTTONDOWN && cnt == 1)
	{
		pt2.x = 1/ dFactor * x;
		pt2.y = 1/ dFactor * y;
		cnt++;
		//cout << "pt2:" << pt2.x << " AND " << pt2.y << endl;
		m_bMouseClick2 = true;
	}


}





void drawGraph(cv::Mat& image, double dSizeFactor, double m_Width, double m_Height) {

	
	dFactor = dSizeFactor;

	cv::Mat img = image.clone();

	cv::Mat xData, yData, display, scaled;
	double xgap = 0;
	cv::Ptr<cv::plot::Plot2d> plot;



	resize(img, scaled, cv::Size(), dSizeFactor, dSizeFactor);


	imshow("image", scaled);
	cv::namedWindow("image", 1);


	cv::setMouseCallback("image", mouse_callback);

	

	while (true)
	{
		if (cv::getWindowProperty("image", cv::WND_PROP_VISIBLE) < 1) {
			return;
			//break;
		}
		//cout << "LOOP " << m_bMouseClick1 << " and " << m_bMouseClick2 << endl;
		if (m_bMouseClick1 == true && m_bMouseClick2 == true)
		{
			if (pt1.x < pt2.x) {
				break;
			}
			else {
				std::printf("Try again, First pt = left, and Second pt = right");
				cnt = 0;
				m_bMouseClick1 == false;
				m_bMouseClick2 == false;
			}
		}

		cv::waitKey(1);
		Sleep(10);
		
	}
	cv::destroyWindow("image");


	//xgap = (double)(pt2.x - pt1.x);

	xData.create(1, m_Width, CV_64F);//1 Row, 100 columns, Double
	yData.create(1, m_Width, CV_64F);




	int slope = (int)((pt2.y - pt1.y) / (pt2.x - pt1.x));



	for (int i = 0; i < m_Width; i++) {
		xData.at<double>(i) = i;

	}

	int tempPt2Y = pt1.y;

	for (int i = pt1.x; i < pt2.x; i++) {
		yData.at<double>(i) = ((int)img.at<uchar>(cv::Point(i, tempPt2Y))) * -1;

		containValues.push_back(yData.at<double>(i));

		tempPt2Y += slope;

		//cout << "Value :" << yData.at<double>(i) << endl;

	}

	std::vector<int>::iterator itor = containValues.begin();

	//cout << "Image Width:" << (double)image.size().width << endl;






	plot = cv::plot::Plot2d::create(xData, yData);
	plot->setPlotSize(800, 800);
	plot->setMaxX((int)pt2.x - 1);
	plot->setMinX((int)pt1.x + 1);
	plot->setMaxY(0);
	plot->setMinY(-300);
	plot->render(display);


	putText(display, "255", cv::Point(0, 115), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1);
	line(display, cv::Point(0, 118), cv::Point(2352, 118), cv::Scalar(0, 0, 255), 2);

	//cout << "Time of operation: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	imshow("Plot", display);



	cv::Point p1(pt1.x, pt1.y), p2(pt2.x, pt2.y);

	int thickness = 6;


	line(img, p1, p2, cv::Scalar(0, 100, 100),
		thickness);




	cv::resize(img, img, cv::Size(), dSizeFactor, dSizeFactor);

	cv::imshow("img", img);

	pt1.x = 1;
	pt1.y = 1;
	pt2.x = 1;
	pt2.y = 1;
	cnt = 0;
	m_bMouseClick1 = false;
	m_bMouseClick2 = false;

	cv::waitKey(0);
	cv::destroyAllWindows();



}


cv::Mat tempFnc(cv::Mat src) {

	claheGammaCPU(src, 2.2, 3, 5);

	return src;
}

void convert(cv::Mat& src, std::bitset<9> mode, double dSizeFactor, double dGammaValue, double dSharpeningFactor, double m_ClipLimit, int m_TilesGridSize) {

	//INTELLIZ();
	if (!m_bRegisterIntelliz) {

		//return;
	}
	
	if (m_iCheckKey == 1000) {
		m_bRegisterIntelliz = false;
		m_iCheckKey = 0;
	}
	m_iCheckKey++;

	


	cv::Mat temp;

	cv::Mat kernel = (cv::Mat_<double>(3, 3) << 1, -2, 1,
		-2, 4, -2,
		1, -2, 1);
	double pi = 2 * acos(0.0);
	cv::filter2D(src.clone(), temp, -1, kernel, cv::Point(-1, -1), (0, 0), 4);
	double sum = cv::sum(abs(temp))[0];
	sum = sum * sqrt(0.9 * pi) / (5.0 * temp.rows * temp.rows);


	if (sum > 1.18) {

		m_ClipLimit = m_ClipLimit * 0.2;

		dGammaValue *= 0.65;

		m_TilesGridSize += m_TilesGridSize / 2;

	}




	if (mode[6])
		sharpening(src, dSharpeningFactor);

	if (mode[0]) {

		if (mode[1])
			claheGammaCPU(src, dGammaValue, m_ClipLimit, m_TilesGridSize);
		if (mode[5])
			hisEQCPU(src);
		if (mode[3])
			claheHiseqCPU(src, m_ClipLimit, m_TilesGridSize);
		if (mode[4])
			gammaCPU(src, dGammaValue);
		if (mode[2])
			claheCPU(src, m_ClipLimit, m_TilesGridSize);
	}
	else if(!mode[0]) {

		cv::cuda::GpuMat temp(src);

		if (mode[1])
			claheGammaGPU(temp, dGammaValue , m_ClipLimit, m_TilesGridSize);
		if (mode[5])
			hisEQGPU(temp);
		if (mode[3])
			claheHiseqGPU(temp, m_ClipLimit, m_TilesGridSize);
		if (mode[4])
			gammaGPU(temp, dGammaValue);
		if (mode[2])
			claheGPU(temp, m_ClipLimit, m_TilesGridSize);

		temp.download(src);
		temp.release();
	}

	if (mode[7]) {
		convertColor(src);
	}

	if (mode[8]) {
		drawGraph(src, dSizeFactor, src.cols, src.rows);
	}

	//m_bRegisterIntelliz = false;


}