#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/opencv.hpp>

#include<opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
#include<opencv2/cudafilters.hpp>
#include<opencv2/cudabgsegm.hpp>
#include<opencv2/cudacodec.hpp>
#include<opencv2/cudaobjdetect.hpp>
#include<opencv2/cudaoptflow.hpp>
#include<opencv2/cudastereo.hpp>
#include<opencv2/cudawarping.hpp>
#include<opencv2/cudafeatures2d.hpp>
#include "Macaron.h"
#include "file.cuh"

#include <string>
#include <vector>
#include <algorithm>
#include<iterator>
#include <io.h>
#include <Windows.h>




//void Image_Inversion(unsigned char* Input_Image, int Height, int Width, int Channels);


void conv2(cv::Mat& src, int kernel_size)
{
	cv::Mat dst, kernel;
	kernel = cv::Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(25);

	/// Apply filter
	filter2D(src, src, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	imshow("filter2D Demo", src);
}



//cv::Mat_<float> spatialConvolution(const cv::Mat_<float>& src, const cv::Mat_<float>& kernel)
//{
//	cv::Mat dst(src.rows, src.cols, src.type());
//
//	cv::Mat_<double>(3, 3) flipped_kernel;
//	flip(kernel, flipped_kernel, -1);
//
//	const int dx = kernel.cols / 2;
//	const int dy = kernel.rows / 2;
//
//	for (int i = 0; i < src.rows; i++)
//	{
//		for (int j = 0; j < src.cols; j++)
//		{
//			float tmp = 0.0f;
//			for (int k = 0; k < flipped_kernel.rows; k++)
//			{
//				for (int l = 0; l < flipped_kernel.cols; l++)
//				{
//					int x = j - dx + l;
//					int y = i - dy + k;
//					if (x >= 0 && x < src.cols && y >= 0 && y < src.rows)
//						tmp += src.at<float>(y, x) * flipped_kernel.at<float>(k, l);
//				}
//			}
//			dst.at<float>(i, j) = saturate_cast<float>(tmp);
//		}
//	}
//	return dst.clone();
//}


void main() {

	struct _finddata_t fd;
	bool bDevice = cv::cuda::getCudaEnabledDeviceCount();
	bDevice = 0;

	//cv::Mat img = cv::imread("C:/Users/sales/Desktop/EunHo/Presentation(SR)/Image Enhancement/Image/x-ray Original/(1,16).bmp",0);
	//cv::resize(img, img, cv::Size(), 0.3, 0.3);
	//cv::Mat temp;
	//cv::Mat image;
	//std::cout << "type: " << (img.type() == CV_8U) << std::endl;
	clock_t start;
	//temp = cv::imread("C:/Users/sales/Desktop/EunHo/Presentation(SR)/Image Enhancement/Image/x-ray Original/(1,16).bmp");
	cv::Mat testT;
	
	
	for (int i = 0; i < 1; i++) {
	
		//temp = cv::imread("C:/Users/sales/Desktop/EunHo/Presentation(SR)/Image Enhancement/Image/x-ray Original/(1,16).bmp");
		//temp = cv::imread("C:/Users/sales/Desktop/EunHo/Presentation(SR)/Image Enhancement/Image/Sample/(1,16).raw",-1);
		//cv::resize(temp, temp, cv::Size(), 0.1, 0.1);


		//convert(testT, NULL, 1, 1, 1, 1, 1);
		
		cv::Mat Img_Source16Bit_Gray(1024, 1024, CV_16UC1);
		cv::Mat Img_Destination8Bit_Gray(1024, 1024, CV_8UC1);
		

		std::vector<cv::Mat> Avg0;
		std::vector<cv::Mat> Avg1;
		std::vector<cv::Mat> Avg2;
		std::vector<cv::Mat> Avg3;
		std::vector<cv::Mat> Avg4;
		std::vector<cv::Mat> Avg5;
		std::vector<cv::Mat> Avg6;
		std::vector<cv::Mat> Avg7;
		std::vector<cv::Mat> Avg8;
		std::vector<cv::Mat> Avg9;

		std::vector<std::vector<cv::Mat>> Average;
		Average.push_back(Avg0);
		Average.push_back(Avg1);
		Average.push_back(Avg2);
		Average.push_back(Avg3);
		Average.push_back(Avg4);
		Average.push_back(Avg5);
		Average.push_back(Avg6);
		Average.push_back(Avg7);
		Average.push_back(Avg8);
		Average.push_back(Avg9);
		
		

		std::string path = "D:\\Wintec\\data\\norm\\3\\*";
		FILE* f;
		intptr_t handle;
		if ((handle = _findfirst(path.c_str(), &fd)) == -1L)
			std::cout << "No file in directory!" << std::endl;	

		int cnt = 0;
		int totalCnt = 0;
		int placeCnt = 0;
		do {
			//std::cout << fd.name << std::endl;
			std::string oneS = "D:/Wintec/data/norm/3/";
			oneS += (char *)fd.name;
			//std::cout << oneS << std::endl;
			//oneS += '.raw';
			
			//std::cout << oneS.c_str() << std::endl;

			
			f = std::fopen(oneS.c_str(), "rb");
			if (!f)
			{
				//MessageBox(L"File Not Found");
				//return;
			}
			else {

				

				char16_t* pY16Pixels;//w-2592 h- 1944
				pY16Pixels = new char16_t[1024 * 1024];

				fread(pY16Pixels, 1024 * 1024 * 2, 1, f);
				Img_Source16Bit_Gray.data = reinterpret_cast<uchar*>(pY16Pixels);


				double minVal, maxVal;
				minMaxLoc(Img_Source16Bit_Gray, &minVal, &maxVal); //find minimum and maximum intensities

				Img_Source16Bit_Gray.convertTo(Img_Destination8Bit_Gray, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

				//temp = Img_Destination8Bit_Gray;

				Average[placeCnt].push_back(Img_Destination8Bit_Gray.clone());




				if (cnt == 5) {
					cnt = 0;
					placeCnt++;
				}

				cnt++;

				totalCnt++;

				//std::cout << totalCnt << std::endl;

				if (totalCnt == 51)
					break;
				//std::string outFile = "C:/Users/sales/Desktop/asddas/" + (std::string)fd.name;
				//outFile.replace(outFile.find(".raw"), 4, ".bmp");

				//std::cout << "C:/Users/sales/Desktop/asddas/" + (std::string)fd.name  << std::endl;

				//cv::imwrite(outFile, Img_Destination8Bit_Gray);


				//Img_Destination8Bit_Gray.convertTo(Img_Source16Bit_Gray, CV_16U);

			}

	
		
		
		
		} while (_findnext(handle, &fd) == 0);
		_findclose(handle);

		
		cv::Mat noiseImage = cv::imread("D:/Wintec/data/finaldata/norm/2/202245_14h19m43s_ImgeSize_1024_1024_99.97Kv_3.99Watt_35.307FOD_51.540Tilt__5.966_5.966Fov(x16.994)_XiiCapture_0.bmp", cv::IMREAD_GRAYSCALE);
		//cv::Mat noiseResultImage = cv::imread("C:/Users/sales/source/repos/onnxTest/onnxTest/denoisedImage.bmp", cv::IMREAD_GRAYSCALE);
		cv::Mat noiseResultImage = cv::imread("D:/Wintec/ADL/PyTorch/test.bmp", cv::IMREAD_GRAYSCALE);
		cv::Mat noiseResultImage1 = cv::imread("D:/Wintec/ADL/PyTorch/test1.bmp", cv::IMREAD_GRAYSCALE);
		cv::Mat noiseResultImage2 = cv::imread("D:/Wintec/ADL/PyTorch/test2.bmp", cv::IMREAD_GRAYSCALE);
		cv::Mat gtImage = cv::imread("D:/Wintec/data/finaldata/original/2/202245_14h19m44s_ImgeSize_1024_1024_100.02Kv_3.99Watt_35.307FOD_51.540Tilt__5.966_5.966Fov(x16.994)_XiiCapture_9.bmp", cv::IMREAD_GRAYSCALE);
		
		cv::resize(noiseImage, noiseImage, cv::Size(512, 512));
		cv::resize(gtImage, gtImage, cv::Size(512, 512));


		

		//std::cout << cv::PSNR(noiseImage, noiseImage) << std::endl;
		

		//start = clock();
		//cv::Mat kernel = (cv::Mat_<double>(5, 5) << 1, 2,-3, 2, 1,
		//	0,1,-2, 1, 0,
		//	-1, -2, 4, -2, -1,
		//	1, 1, -2, 1, 1,
		//	1, 2, -3, 2, 1);

		cv::Mat kernel = (cv::Mat_<double>(2, 2) << 0.5,-0.5,
			-0.5,0.5);

		//cv::Mat kernel = (cv::Mat_<double>(3, 3) << 1, -2, 1,
		//	-2, 4, -2,
		//	1, -2, 1);

		//double pi = 2 * acos(0.0);
		//cv::filter2D(Average[0][0], Average[0][0], -1, kernel, cv::Point(-1, -1), (0, 0), 4);
		//double sum = cv::sum(cv::sum(abs(Average[0][0]))[0])[0];
		//sum = sum * sqrt(0.9 * pi) / (5.0 * 1024.0 * 1024.0);

		//std::cout << sum << std::endl;

		//cv::imshow("bbbb", Average[0][0]);






		//cv::Mat acc0_0(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc0_1(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc0_2(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc0_3(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc0_4(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc0_5(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc0_6(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc0_7(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc0_8(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc0_9(Average[0][0].size(), CV_64F, cv::Scalar(0));

		//cv::Mat acc1_0(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc1_1(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//
		//cv::Mat ACC(Average[0][0].size(), CV_64F, cv::Scalar(0));



		//std::vector<cv::Mat> AccMat1;
		//AccMat1.push_back(acc0_0);
		//AccMat1.push_back(acc0_1);
		//AccMat1.push_back(acc0_2);
		//AccMat1.push_back(acc0_3);
		//AccMat1.push_back(acc0_4);
		//AccMat1.push_back(acc0_5);
		//AccMat1.push_back(acc0_6);
		//AccMat1.push_back(acc0_7);
		//AccMat1.push_back(acc0_8);
		//AccMat1.push_back(acc0_9);

		///*cv::Mat acc1_2(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc1_3(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc1_4(Average[0][0].size(), CV_64F, cv::Scalar(0));
		//cv::Mat acc1_1(Average[0][0].size(), CV_64F, cv::Scalar(0));*/

		//cv::Mat NormalMat(Average[0][0].size(), CV_16U);

		//TEMP TT;


		//for (int i = 0; i < 10; i++) {
		//	for (int k = 0; k < 5; k++) {

		//		

		//		double minVal1, maxVal1;
		//		minMaxLoc(Average[0][0], &minVal1, &maxVal1);

		//		double minVal2, maxVal2;
		//		minVal2 = 0;
		//		maxVal2 = 255;
		//		minMaxLoc(Average[i][k], &minVal2, &maxVal2);

		//		//std::cout << minVal2  << std::endl;


		//		float saveMat[1048576] = { 0, };



		//		if (i == 9 && k == 4) {
		//			std::cout << maxVal1 << std::endl;
		//			std::cout << maxVal2 << std::endl;
		//			TT.Image_Inversion(saveMat, Average[0][0].data, Average[i][k].data, Average[0][0].rows, Average[0][0].cols, 1, true, minVal1, maxVal1, minVal2, maxVal2);
		//			//cv::imshow("aa" + char(i), Average[0][0]);
		//			//std::cout << NormalMat.data << std::endl;
		//		}
		//		else {
		//			//std::cout << "aaaaaaaa" << std::endl;
		//			TT.Image_Inversion(saveMat, Average[0][0].data, Average[i][k].data, Average[0][0].rows, Average[0][0].cols, 1, false, minVal1, maxVal1, minVal2, maxVal2);
		//			//cv::imshow("aa" + char(i), NormalMat);
		//			
		//		}
		//	}
		//}

		

		

		/*for (int i = 0; i < 10; i++) {
			for (int k = 0; k < 5; k++) {
				
				cv::accumulate(Average[i][k], AccMat1[i]);
			}
		}


		for (int i = 0; i < 1; i++) {
			for (int k = 0; k < 5; k++) {
				cv::accumulate(AccMat1[i], acc1_0);
			}
		}

		for (int i = 0; i < 1; i++) {
			for (int k = 5; k < 10; k++) {
				cv::accumulate(AccMat1[i], acc1_1);
			}
		}

		cv::accumulate(acc1_0, ACC);
		cv::accumulate(acc1_1, ACC);*/





		cv::Mat temp1 = cv::imread("D:/Wintec/data/1.bmp", cv::COLOR_BGR2GRAY);
		cv::Mat temp2 = cv::imread("D:/Wintec/data/2.bmp", cv::COLOR_BGR2GRAY);
		cv::Mat temp3 = cv::imread("D:/Wintec/data/3.bmp", cv::COLOR_BGR2GRAY);
		cv::Mat temp4 = cv::imread("D:/Wintec/data/4.bmp", cv::COLOR_BGR2GRAY);
		cv::Mat temp5 = cv::imread("D:/Wintec/data/5.bmp", cv::COLOR_BGR2GRAY);
		temp1.convertTo(temp1, CV_64FC1);
		temp2.convertTo(temp2, CV_64FC1);
		temp3.convertTo(temp3, CV_64FC1);
		temp4.convertTo(temp4, CV_64FC1);
		temp5.convertTo(temp5, CV_64FC1);

		noiseResultImage.convertTo(noiseResultImage, CV_64FC1);
		noiseResultImage1.convertTo(noiseResultImage1, CV_64FC1);
		noiseResultImage2.convertTo(noiseResultImage2, CV_64FC1);
		//cv::Mat noiseResultImage1 = noiseResultImage.clone();
		//cv::Mat noiseResultImage2 = noiseResultImage.clone();
		//cv::Mat noiseResultImage3 = noiseResultImage.clone();
		//cv::Mat noiseResultImage4 = noiseResultImage.clone();

		cv::accumulate(noiseResultImage1, noiseResultImage);
		cv::accumulate(noiseResultImage2, noiseResultImage);
		//cv::accumulate(noiseResultImage3, noiseResultImage);
		//cv::accumulate(noiseResultImage4, noiseResultImage);
		// 
		//cv::Mat First(temp1.size(), CV_64F, cv::Scalar(0));
		//cv::Mat Second(temp2.size(), CV_64F, cv::Scalar(0));
		//cv::Mat Third(temp3.size(), CV_64F, cv::Scalar(0));



		cv::accumulate(temp1, temp2);
		cv::accumulate(temp3, temp2);
		cv::accumulate(temp2, temp4);
		cv::accumulate(temp5, temp4);


		noiseResultImage.convertTo(noiseResultImage, CV_8UC1, 1. / 3.0);

		//cv::accumulate(temp1, temp3);
		
		temp2.convertTo(temp2, CV_8UC1, 1. / 3.0);
		temp4.convertTo(temp4, CV_8UC1, 1. / 5.0);
		cv::resize(temp2, temp2, cv::Size(512, 512));
		cv::resize(temp4, temp4, cv::Size(512, 512));
		//double minVal, maxVal;
		//Average[0][0].convertTo(temp, CV_16U, 1.0/2.0);
		//minMaxLoc(temp, &minVal, &maxVal);
		
		//Average[0][0].convertTo(temp, CV_8U, 1.0);
		//std::cout << "Time: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

		//std::cout << cv::PSNR(temp2, gtImage) << std::endl;
		//std::cout << cv::PSNR(noiseImage, gtImage) << std::endl;
		//std::cout << cv::PSNR(noiseResultImage, gtImage) << std::endl;
		//std::cout << cv::PSNR(temp4, gtImage) << std::endl;

		//cv::imwrite("Avg5.bmp", temp4);
		cv::imwrite("noiseResult.bmp", noiseResultImage);

		//cv::imshow("Aaaa", temp2);
		//cv::imshow("bbbb", gtImage);
		cv::imshow("ccc", noiseResultImage);
		//cv::imshow("ddd", temp4);
		cv::waitKey(0);


	
		

		
		
		//std::cout << "Time: " << (clock() - start) << std::endl;
		

		
		//resize(temp, temp, cv::Size(), 0.3, 0.3);


		//testT = cv::Mat(2352, 2944, CV_16UC1, pY16Pixels).clone();

		/*cv::Mat kernel = (cv::Mat_<int>(3, 3) << 1, 1, 1,
			1, 1, 1,
			1, 1, 1);*/

		//test(temp);
		//imgGpu.convertTo(imgGpu, CV_8U);

		//if (temp.channels() == 3) {
		
		//}
		//cv::cuda::cvtColor(imgGpu, imgGpu, cv::COLOR_BGR2GRAY);
		//conv2(temp, 5);
		//cv::medianBlur(temp, temp, 3);
		//if(temp.type() == CV_8U) 
		//img = cv::Mat(temp.rows, temp.cols, CV_16UC1, temp).clone();
		//sharpening(temp, 0.99);

		
		//cv::imshow("1", temp);
		//claheGammaGPU(temp,1.7);
		//sharpening(temp, 0.99);
		//sharpening(img, 0.99);
		//claheGammaGPU(img,1.7);

		//cv::erode(temp, temp, kernel);
		//cv::dilate(temp, temp, kernel);
		//claheHiseqGPU(temp);
		//temp = claheGPU(temp);
		//temp = gammaCPU(temp);
		//temp = claheGPU(temp);
		//t emp = gammaGPU(temp);
		//temp.convertTo(temp, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
		
		
		 //resize(temp, temp, cv::Size(), 0.2, 0.2);
		//temp = Img_Source16Bit_Gray;

	
		
		//convertColor(temp);

		
		
		//std::cout << (double)temp.at<uchar>(cv::Point(100, 100)) << std::endl;

		//minMaxLoc(temp, &minVal, &maxVal);
		//convertTo(Img_Destination8Bit_Gray, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

		

		//temp.convertTo(temp, CV_16U, 255.0, 0);
		//temp = Img_Source16Bit_Gray;
		/*std::cout << maxVal << " " << minVal <<  std::endl;
		std::cout << "Time: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;*/


	}
	//cv::resize(temp, temp, cv::Size(), 0.2, 0.2);
	//cv::resize(img, img, cv::Size(), 0.2, 0.2);
	//std::cout << img.cols << std::endl;


	/*TEMP TT;
	TT.Image_Inversion(img.data, img.rows, img.cols, 1);*/
	
	//Image_Inversion(img.data, img.cols, img.rows, 1);
	
	//drawGraph(img,0.3,img.cols, img.rows);

	//sharpening(img, 0.99);
	//claheGammaGPU(img,1.7);
	//cv::imwrite("sample.bmp", img);
	//cv::imshow("Img_Source16Bit_Gray", temp);
	//cv::imshow("ori", img);
	//std::cout << d << std::endl;
	//cv::imshow("Img_Destination8Bit_Gray", Img_Destination8Bit_Gray);
	//cv::imshow("d", temp);

	/*cv::imshow("ddd", img);
	cv::waitKey(0);*/

}