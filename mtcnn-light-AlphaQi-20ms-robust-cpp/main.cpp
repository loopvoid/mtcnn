//openBLAS、opencv

#include "network.h"
#include "mtcnn.h"
#include <time.h>

#ifdef DEBUG
#pragma comment(lib,"opencv_world341d.lib")
#endif // DEBUG
#ifndef DEBUG
#pragma comment(lib,"opencv_world341.lib")
#endif // !DEBUG
#pragma comment(lib,"libopenblas.lib")


int main() {
	//VideoCapture cap("output540x540.avi");
	//VideoCapture cap("output640x480.avi");
	VideoCapture cap(0);
	Mat img;
	cap >> img;
	//cout << "img: " << img.cols << "," << img.rows << endl;
	mtcnn find(img.rows, img.cols);
	//mtcnn find(img.rows/2, img.cols/2);
	//cout << "img: " << img.cols/2 << "," << img.rows/2 << endl;
	clock_t start;
	while (cap.isOpened())
	{
		cap >> img;
		//resize(img, img, Size(img.cols / 2, img.rows / 2));
		start = clock();
		//cout << "img: " << img.cols << "," << img.rows << endl;
		find.findFace(img);
		start = clock() - start;
		cout << "Time:" << start << " ms" << endl;
		//resize(img, img, Size(img.cols / 2,img.rows / 2));
		imshow("result", img);
		if (waitKey(1) >= 0) break;
	}
	waitKey(0);
	img.release();
	return 0;
}

int main1()
{
    Mat image = imread("./4.jpg");
    mtcnn find(image.rows, image.cols);
    clock_t start;
    start = clock();
    find.findFace(image);
	start = clock() - start;

	cout << "time is  " << start << endl;
    imshow("result", image);
    imwrite("result.jpg",image);
   
    // Mat image;
    // VideoCapture cap(0);
    // if(!cap.isOpened())  
    //     cout<<"fail to open!"<<endl; 
    // cap>>image;
    // if(!image.data){
    //     cout<<"读取视频失败"<<endl;  
    //     return -1;
    // }

    // mtcnn find(image.rows, image.cols);
    // clock_t start;
    // int stop = 1200;
    // while(stop--){
    //     start = clock();
    //     cap>>image;
    //     find.findFace(image);
    //     imshow("result", image);
    //     if( waitKey(1)>=0 ) break;
    //     start = clock() -start;
    //     cout<<"time is  "<<start/10e3<<endl;
    // }

    waitKey(0);
    image.release();
    return 0;
}