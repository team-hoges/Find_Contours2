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
#include <fstream>


#define max_size 100

using namespace cv;
using namespace std;


Point max(std::vector<Point> P){
    double max_x = P.at(0).x;
    double max_y = P.at(0).y;

    for (size_t i = 0; i < P.size(); i++)
    {
        if(max_x < P.at(i).x){
            max_x=P.at(i).x;
        }

        if(max_y < P.at(i).y){
            max_y=P.at(i).y;
        }
    }
    return Point(max_x,max_y);
}

Point min(std::vector<Point> P){
    double min_x = P.at(0).x;
    double min_y = P.at(0).y;

    for (size_t i = 0; i < P.size(); i++)
    {
        if(min_x > P.at(i).x){
            min_x=P.at(i).x;
        }

        if(min_y > P.at(i).y){
            min_y=P.at(i).y;
        }
    }
    return Point(min_x,min_y);
}




int main(){
Mat  image1,img2,img3,img4;
Mat  Contour_out,Contour_out2;
Mat Rect_output;
int count=0;
int i=0,t=0;
int  Contuor_lens[10000];
random_device rng;     // 非決定的な乱数生成器

Mat outputs[10];//テスト

Mat output (img3.size(),CV_8UC3);
vector<vector<Point>> contuors;//初期輪郭
vector<vector<Point>> contour_list;//選別済み輪郭
vector <Vec4i> he;
vector <Vec4i>he_list;
vector<vector<Vec3b>> Contour_Colors;
random_device seed_gen;
default_random_engine engine(seed_gen());
std::uniform_int_distribution<> dist(0, 255);
image1 = imread("./ans2.jpg");
Contour_out=image1.clone();
Contour_out2 = image1.clone();
Rect_output = image1.clone();
if(image1.empty()==true){
    printf("画像を取り込めません\n");
    return -1;
}

img2 = ~image1.clone();
Mat3b image_color = image1.clone(); 
imshow("main",image1);
waitKey();

threshold(img2,img3,1.20,255,THRESH_BINARY_INV );
GaussianBlur(img3,img3,Size(3,3),10);
threshold(img3,img3,1.5,255,THRESH_BINARY_INV );
medianBlur(img3,img3,7);
//ノイズ除去
 
 imshow("test",img3);
 waitKey();

cvtColor(img3,img3,CV_BGR2GRAY);
findContours(img3,contuors,he,CV_RETR_TREE  ,CV_CHAIN_APPROX_NONE);//輪郭検出



for ( i = 0,t=0; i < contuors.size(); i++){
   if(2000 < contourArea(contuors.at(i)) && he[i][3] != -1      ){
       t++;
       cout << contourArea(contuors.at(i)) << endl;
       contour_list.push_back(contuors.at(i));
       he_list.push_back(he.at(i));
   }
}
cout << he_list.size()  << endl;
for (auto contour = contour_list.begin(); contour != contour_list.end(); contour++){
    cv::polylines(Contour_out, contour_list, true, cv::Scalar(0, 255, 0), 2);
}

Contour_Colors.resize(contour_list.size());
for ( i = 0; i < contour_list.size(); i++){
    
   for ( t = 0; t < contour_list[i].size(); t++)
    {
      Contour_Colors[i].push_back(image_color(contour_list[i][t]));
    }
}
imshow("out",Contour_out);
waitKey();

for ( t = 0; t < contour_list.size(); t++){
    Point minP = min(contour_list.at(t) );
    Point maxP = max(contour_list.at(t) );
    Rect rect(minP, maxP);
   rectangle(Rect_output, rect, cv::Scalar(0, 255, 0), 2, 8);
   outputs[t] = image1(rect);
  imshow("2",outputs[t]);
  waitKey();
}

cout << "Num Contours "  << i << "\n" << endl;

 imshow("output",Rect_output);
 waitKey();

return 0;
}