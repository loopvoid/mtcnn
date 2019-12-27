#include "mtcnn.h"
#include "network.h"
#include <time.h>

#ifdef DEBUG
#pragma comment(lib,"opencv_world341d.lib")
#endif // DEBUG
#ifndef DEBUG
#pragma comment(lib,"opencv_world341.lib")
#endif // !DEBUG
#pragma comment(lib,"libopenblas.lib")


int mtcnnDetect(cv::Mat &image)
{
	if (!image.data)
		return -1;
	static mtcnn find;
//    find.SetMinFaceSize(60);
	TickMeter tm;
	tm.start();
    std::vector<FaceInfo>fds;
	find.Detect(image,fds);
	tm.stop();
	cout << tm.getTimeMilli() << "ms" << endl;
	return 0;
}

int testimage(const string imgpath = "4.jpg")
{
	Mat image = cv::imread(imgpath);
	mtcnnDetect(image);
    imwrite("result.jpg",image);
	return 0;
}

int testcamera(int device=0)
{
	Mat image;
	VideoCapture cap(device);
	if (!cap.isOpened())
		cout << "fail to open!" << endl;
	while (1){
		cap >> image;
		if (!image.data)
			break;
		mtcnnDetect(image);
		imshow("mtcnn", image);
		if (waitKey(1) >= 0) break;
	}
    waitKey(0);
    image.release();
    return 0;
}

int testvideo(string path)
{
	Mat image;
	VideoCapture cap(path);
	if (!cap.isOpened())
		cout << "fail to open!" << endl;
	while (1) {
		cap >> image;
		if (!image.data)
			break;
		mtcnnDetect(image);
		imshow("mtcnn", image);
		if (waitKey(1) >= 0) break;
	}
	waitKey(0);
	image.release();
	return 0;
}

int main()
{
    //testimage();
	testcamera();
	//testvideo("output640x480.avi");
	return 0;
}
