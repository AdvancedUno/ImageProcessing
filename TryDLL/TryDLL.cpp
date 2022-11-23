
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

#include "TryDLL.h"
#include <bitset>

using namespace std;


int main()
{
    std::cout << "Hello World!\n";
    //cv::Mat test = cv::imread("C:/Users/sales/Desktop/PCR/3.jpg",0);
    cv::Mat test = cv::imread("C:/Users/sales/Desktop/TBR/3.jpg",0);
    //cv::resize(test, test, cv::Size(), 0.3, 0.05);
    bitset<9> mode;

    mode.set(0, 0); mode.set(1, 1); mode.set(2, 0); mode.set(3, 0);
    mode.set(4, 0); mode.set(5, 0); mode.set(6, 0); mode.set(7, 0);
    mode.set(8, 0);
    //cv::imshow("bb", test);

    cv::Mat before = test.clone();
    cv::imwrite("D:/TireData/Before.jpg", before);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j ++) {
            clock_t start = clock();
            test = before.clone();
            convert(test, mode, 3, 0.5, 10, i * 10 + 5, 5 + j * 10);
            cout << clock() - start << endl;
            cv::imwrite("D:/TireData/After_" + std::to_string(i) + std::to_string(j) + ".jpg", test);
        }

    }
    





    //cv::imshow("aa", test);

    

    //cv::waitKey(0);


    return 0;

}
