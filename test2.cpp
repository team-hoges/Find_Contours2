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



int main(){
Mat  image1,img2,img3,img4;
Mat  Contour_out,Contour_out2;
int count=0;
int i=0,t=0;
int  Contuor_lens[10000];
random_device rng;     // 非決定的な乱数生成器

Mat output (img3.size(),CV_8UC3);
vector<vector<Point>> contuors;//初期輪郭
vector<vector<Point>> contour_list;//選別済み輪郭
vector <Vec4i> he;
vector <Vec4i>he_list;
vector<vector<Vec3b>> Contour_Colors;
random_device seed_gen;
default_random_engine engine(seed_gen());
std::uniform_int_distribution<> dist(0, 255);
image1 = imread("./ans.jpg");
Contour_out=image1.clone();
Contour_out2 = image1.clone();
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


cvtColor(img3,img3,CV_BGR2GRAY);
findContours(img3,contuors,he,CV_RETR_TREE  ,CV_CHAIN_APPROX_NONE);//輪郭検出



for ( i = 0,t=0; i < contuors.size(); i++){
   if(300 < contourArea(contuors.at(i))){
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


for ( t = 0; t < Contour_Colors[1].size(); t++){
 //        cout << Contour_Colors[1][t] << endl;
     }
     
  for( int i = 0; i< contour_list.size(); i++ )
     {
       Scalar color = Scalar( 0, dist(engine), dist(engine) );
       
       drawContours( Contour_out2, contour_list, i, color, 2, 8, he_list, 0, Point() );
     }



cout << "Num Contours "  << i << "\n" << endl;

 imshow("output",Contour_out2);
 waitKey();

return 0;
}