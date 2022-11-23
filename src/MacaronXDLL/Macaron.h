#pragma once
#include <bitset>
//#include "Header.h"


//void convert(cv::Mat& src, std::bitset<9> mode,
//	double, double, double, double, int);

//extern "C" __declspec(dllexport) void tempFnc(unsigned char* img_pointer, long data_len, cv::Mat * &res, int& img_count, int& mat_type_size, int h, int w);
extern "C" __declspec(dllexport) void tempFnc(cv::Mat* src);
extern "C" __declspec(dllexport) bool StartTest(cv::Mat * src, cv::Mat*);
extern "C" __declspec(dllexport) void InferSingExample(const char*);
extern "C" __declspec(dllexport) bool CloseNet();


//void claheGammaGPU(cv::Mat&, double);
//void claheGammaCPU(cv::Mat&, double);
//void claheGPU(cv::Mat&);
//void claheCPU(cv::Mat&);
//void claheHiseqGPU(cv::Mat&);
//void claheHiseqCPU(cv::Mat&);
//void gammaGPU(cv::Mat&, double);
//void gammaCPU(cv::Mat&, double);
//void hisEQGPU(cv::Mat&);
//void hisEQCPU(cv::Mat&);
//void sharpening(cv::Mat&, double);
//void convertColor(cv::Mat&);
//void drawGraph(cv::Mat&,double,double,double);



