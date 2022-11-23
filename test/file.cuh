#pragma once
#include <cuda_runtime.h>
//void Image_Inversion(unsigned char* Input_Image, int Height, int Width, int Channels);


#ifdef __cplusplus
extern "C" {
#endif
	class TEMP {
	public:
		//int sum_cuda(int a, int b, int* c);
		void Image_Inversion(float* saveMat, unsigned char* Input_Image, unsigned char* Input_Image2, int Height, int Width, int Channels, bool bLast, double min1, double max1, double min2, double max2 );
};
}

