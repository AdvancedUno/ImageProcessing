// MacaronStatic.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//
#include "pch.h"
#include <intelliz/intelliz_d.h>
#include <iostream>
#include <thread>
#include <vector>
#include "Macaron.h"
#include <string>
#include <fstream>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <Windows.h>
#include <chrono>
#include <filesystem>
#include <future>



using std::thread;

//#include <opencv2/opencv.hpp>
using namespace cv;

using namespace std;



//
//
//
//
//void tempFnc(cv::Mat* src) {
//
//	cv::Mat temp = src->clone();
//	cv::cuda::GpuMat tempCuda(temp);
//
//	//claheGammaGPU(tempCuda, 0.5, 10, 50);
//
//	hisEQGPU(tempCuda);
//
//	tempCuda.download(temp);
//	tempCuda.release();
//
//
//
//
//
//	*src = temp;
//	
//}


struct InferTask {
	int id;
	cv::Mat* image;
};

class Timer
{
public:

	using clock_t = std::chrono::high_resolution_clock;
	using duration_t = clock_t::duration;

private:

	clock_t::time_point start_time;

public:

	Timer() :
		start_time(clock_t::now()) { }

	duration_t get_elapsed_time() const { return (clock_t::now() - start_time); }

	long get_count() const { return get_elapsed_time().count(); }

	void reset() { start_time = clock_t::now(); }
};



using sysclock_t = std::chrono::system_clock;

cv::Mat RunInfer(const int& workerId, cv::Mat& sample)
{
	std::cout << "Start woker : " << workerId << std::endl;

	cv::Mat* outputsarray = new cv::Mat();

	std::cout << "wanted 1 " << std::endl;

	SetMultiProbabilityAll(0.399);
	float* pValue = new float();
	*outputsarray = InspectMultiGetP(workerId, &sample, pValue);

	std::cout << "wanted " << std::endl;

	/*InferTask outTask;

	outTask.id = workerId;
	outTask.image = outputsarray;*/

	std::cout << "Finish woker : " << workerId << std::endl;

	return *outputsarray;

}



// 트래쉬버스터즈용 추론 샘플
void InferSingExample(const char* path)
{
	
	// 로그 파일 생성
	//SetInferFileLogOn("intelliz_d_infer_logs.txt");
	//SetInferFileLogOn("d:\\temp\\trash\\intelliz_d_infer_logs.txt");
	std::string* arg2 = 0;

	std::cout << "InferSingExample start : " << *path << std::endl;
	std::cout << "InferSingExample start : " << path << std::endl;
	std::cout << "InferSingExample start : " << path+1 << std::endl;
	std::string arg2_str(path);
	arg2 = &arg2_str;
	std::cout << arg2_str << std::endl;
	std::string strDnnPath = *arg2;

	unsigned int maxThreadCount = 1;

	unsigned int maxTileWidth = 800;
	unsigned int maxTileHeight = 600;

	int gpuNo = 0;

	// Infer 쓰레드 초기화


	int retCode = InitInspectNet(maxThreadCount); //Thread를 할당한다.
	

	if (retCode > 0) {
		std::cout << "Error : " << retCode << std::endl;

		return;
	}

	//const char* dnnPath = path.c_str();
	//const char* dnnPath = "D:/training_tb/project/TB/default/images/TrainDataset/Caviarnet.dnn";

	// 쓰레드 별 설정시 ID 0으로 고정


	InitInferMultiMaxTile(0, maxTileWidth, maxTileHeight);  /// Max Tile을 할당함	
	

	SetInitImageSize(0, maxTileWidth, maxTileHeight);

	
	InitInferenceMulti(0, (char*)path); // dnn파일을 불러옴.	

	retCode = InitInferenceMultiGPU(0, gpuNo); //// gpu 0~1번 순차적으로 할당하여 초기화함

	if (retCode > 0) {
		std::cout << "Error : " << retCode << std::endl;

		return;
	}

	// p-value 임계치 설정
	




	//using namespace std::chrono;
	//bool bSaveImage = true;

	//std::wstring json = getClassJsonMulti(0);

	//InputIntellizClassFromWString(json);

	//Read_OCR_Info(json.c_str());
	

}




bool StartTest(cv::Mat* src, cv::Mat* outImg) {

	SetInferFileLogOn("intelliz_d_test_logs.txt");
	/*Mat tempImg = src->clone();*/
	//Mat output = imread("D:\\103109690_[3].bmp");
	Mat output;

	
	//std::cout << "try 0 " << std::endl;
	
	output = RunInfer(0, *src);
	//cv::imwrite("out.bmp", output);
	//cv::imshow("test", output);
	//waitKey(0);


	
	*outImg = output.clone();
	std::cout << "try 1 "  << std::endl;
	
	return true;


	
	int result = 1;
		//AnalyzeDefectInfo(&output, 1, 1.0);
	
		
	
	//std::vector<defect_rst> rsts = ParseDefectInfo(&tempImg, 1);
	
	if (result > 0) {

		std::cout << "defect size: " << result << std::endl;

		return false;
	}
	else
	{
		std::cout << "No defects........" << std::endl;
		return true;
	}
}


bool CloseNet() {
	DestoryAllNet();
	return true;
}

