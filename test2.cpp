#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/types_c.h> 
#include<vector>
//#include <unistd.h>
#include <string>
#include<random>
#include<strstream>

#define max_size 100

using namespace cv;
using namespace std;



int main(){
Mat  image1,img2,img3,img4;
Mat  Contour_out;
int i=0;
int  Contuor_lens[10000];
Vec3b Contuor_Colors[99][9999];
image1 = imread("./ans.jpg");
Contour_out=image1.clone();
if(image1.empty()==true){
    printf("画像を取り込めません\n");
    return -1;
}

img2 = ~image1.clone();

imshow("main",image1);
waitKey();

threshold(img2,img3,1.20,255,THRESH_BINARY_INV );
GaussianBlur(img3,img3,Size(3,3),10);
threshold(img3,img3,1.5,255,THRESH_BINARY_INV );
medianBlur(img3,img3,7);
//ノイズ除去

Mat output (img3.size(),CV_8UC3);
std :: vector<std::vector<Point>> contuors;
std :: vector <Vec4i> he;
cvtColor(img3,img3,CV_BGR2GRAY);
findContours(img3,contuors,he,CV_RETR_EXTERNAL ,CV_CHAIN_APPROX_NONE);//輪郭検出



for ( i = 0; i < contuors.size(); i++){
   if(100 < contourArea(contuors.at(i)){
       Contuor_lens[i]=i;
       cout << contourArea(contuors.at(i)) << endl;
   }
}










 return -1;
}