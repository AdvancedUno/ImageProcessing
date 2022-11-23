#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#include "file.cuh"
#include "cuda.h"

#include <iostream>

#include <cufft.h>

#include "cublas_v2.h"

#include <stdio.h>

#include <stdlib.h>
#include <nppdefs.h>
#include "device_launch_parameters.h"
#include "npp.h"
#include "nppi.h"


__global__ void Inversion(float* ImageNorm, unsigned char* Image, unsigned char* Image2, int Channels, double minValue1, double maxValue1, double minValue2, double maxValue2) {

    int idx = (blockIdx.x +blockIdx.y * gridDim.x) * Channels;

    for (int i = 0; i < Channels; i++) {

		//ImageNorm[idx + i] = ((Image2[idx + i] - minValue1) * (1.0/(maxValue1 - minValue1))) + ((Image[idx + i] - minValue2) * (1.0 / (maxValue2 - minValue2)));
		//ImageNorm[idx + i] = ((Image2[idx + i]) - minValue1 * 255.0 / (maxValue1 - minValue1))*255.0 / (maxValue1 - minValue1) + ((Image[idx + i] ) - minValue2 * 255.0 / (maxValue2 - minValue2)) * 255.0 / (maxValue2 - minValue2);
		ImageNorm[idx*2 + i] = (ImageNorm[idx + i] + Image2[idx + i]);

    }

}

__global__ void NormImage(float* ImageNorm, unsigned char* Image, int Channels) {

	int idx = (blockIdx.x + blockIdx.y * gridDim.x) * Channels;

	for (int i = 0; i < Channels; i++) {

		Image[idx + i] = ImageNorm[idx + i]/50;
		//Image[idx + i] = 255;

	}

}


void TEMP:: Image_Inversion(float* Input_Norm, unsigned char* Input_Image, unsigned char* Input_image2, int Height, int Width, int Channels, bool bLast, double minValue1, double maxValue1, double minValue2, double maxValue2)
{
	unsigned char* Dev_Input_Image = NULL;
	unsigned char* Dev_Input_Image1 = NULL;
	float* Dev_Input_Norm = NULL;


	//allocate the memory in gpu
	cudaMalloc((void**)&Dev_Input_Image, Height * Width * Channels);

	//copy data from CPU to GPU
	cudaMemcpy(Dev_Input_Image, Input_Image, Height * Width * Channels, cudaMemcpyHostToDevice);


	cudaMalloc((void**)&Dev_Input_Image1, Height * Width * Channels);

	//copy data from CPU to GPU
	cudaMemcpy(Dev_Input_Image1, Input_Image, Height * Width * Channels, cudaMemcpyHostToDevice);



	cudaMalloc((void**)&Dev_Input_Norm, Height * Width * Channels);

	//copy data from CPU to GPU
	cudaMemcpy(Dev_Input_Norm, Input_Norm, Height * Width * Channels, cudaMemcpyHostToDevice);



	dim3 Grid_Image(Width, Height);

	Inversion << <Grid_Image, 1 >> > (Dev_Input_Norm, Dev_Input_Image, Dev_Input_Image1, Channels, minValue1, maxValue1, minValue2, maxValue2);

	if (bLast) {
		NormImage << <Grid_Image, 1 >> > (Dev_Input_Norm, Dev_Input_Image, Channels);
	}

	//copy processed data back to cpu from gpu
	cudaMemcpy(Input_Image, Dev_Input_Image, Height * Width * Channels, cudaMemcpyDeviceToHost);
	cudaMemcpy(Input_Norm, Dev_Input_Norm, Height * Width * Channels, cudaMemcpyDeviceToHost);


	

	//free gpu mempry
	cudaFree(Dev_Input_Image);
	cudaFree(Dev_Input_Image1);
	cudaFree(Dev_Input_Norm);
}

//__global__ void sum(int a, int b,int* c) {
//	int tid = blockIdx.x * blockDim.x + threadIdx.x;
//	c[tid] = a + b;
//}
//
//int TEMP::sum_cuda(int a, int b, int* c) {
//
//	int* f;
//	
//	cudaMalloc((void**)&f, sizeof(int) * 1);
//	cudaMemcpy(f, c, sizeof(int) * 1, cudaMemcpyHostToDevice);
//
//	sum << <1,1 >> > (a, b, f);
//
//	cudaMemcpy(c, f, sizeof(int) * 1, cudaMemcpyDeviceToHost);
//
//	cudaFree(f);
//
//	return true;
//
//
//}


