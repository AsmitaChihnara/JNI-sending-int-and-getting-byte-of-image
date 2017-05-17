// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <jni.h>
#include "fileTransfer_FileTransfer.h"
#include <iostream>
#include <opencv2\opencv.hpp>


using namespace std;
using namespace cv;
typedef unsigned char byte;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

JNIEXPORT jbyteArray JNICALL Java_fileTransfer_FileTransfer_fileTransfer(JNIEnv *env, jobject obj, jint width, jint height, jintArray arr){
	jint *carr;
	carr = env->GetIntArrayElements(arr, NULL);
	if (carr == NULL) {
		return 0; /* TODO: exception occurred */
	}
	Mat img(height, width, CV_8UC4, carr);
	imshow("result", img);
	env->ReleaseIntArrayElements(arr, carr, 0);
	waitKey(0);

	Mat gray_image;
	cvtColor(img, gray_image, CV_BGR2GRAY);
	namedWindow("Gray image", CV_WINDOW_AUTOSIZE);
	imshow("Gray image", gray_image);
	waitKey(0);

	vector<unsigned char> imageDesV;
	imencode(".jpg", gray_image, imageDesV);

	//convert vector<char> to jbyteArray
	jbyte* result_e = new jbyte[imageDesV.size()];
	jbyteArray result = env->NewByteArray(imageDesV.size());
	for (int i = 0; i < imageDesV.size(); i++) {
		result_e[i] = (jbyte)imageDesV[i];
	}
	env->SetByteArrayRegion(result, 0, imageDesV.size(), result_e);
	return result;

}


