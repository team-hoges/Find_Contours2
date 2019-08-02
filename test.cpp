#include <iostream>
#include <opencv2/core.hpp>
//#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h> // for CV_BGR2GRAY constant
#include<vector>
//#include <unistd.h>
#include <string>
#include<random>
#include<strstream>

using namespace cv;


Point max(std::vector<Point> P){
    double max_x = P.at(0).x;
    double max_y = P.at(0).y;

    for (size_t i = 0; i < P.size(); i++)
    {
        if(max_x < P.at(i).x){
            max_x=P.at(0).x;
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
            min_x=P.at(0).x;
        }

        if(min_y > P.at(i).y){
            min_y=P.at(i).y;
        }
    }
    return Point(min_x,min_y);
}
int main(int argc, const char* argv[]) 
{
    Mat  image1,img2,img3,img4;
    Mat labe;
    Mat stats;
    Mat cen;
    std::vector<std::vector<Point>>imgs_points;//輪郭座標系二次元配列
   // std::vector<Vec4i> hi;
	double points_len; //これなに
	image1 = imread("./ans.jpg");
    if(image1.empty()==true){
        return -1;
    }

    //imshow("image",image1);
    //waitKey();
    //img2 = image1;
    //img4 = image1;
    cvtColor(image1,img2,CV_BGR2GRAY);
    img4 = img2;
    img2 = ~img2;
    threshold(img2,img3,1.5,255,THRESH_BINARY_INV );
    GaussianBlur(img3,img3,Size(3,3),10);
    threshold(img3,img3,1.5,255,THRESH_BINARY_INV );
    medianBlur(img3,img3,7);

int n=connectedComponentsWithStats(img3,img3,stats,cen,4,CV_32S);  
//ノイズ除去

    std::vector<Vec3b> colors(n);
    colors[0]=Vec3b(0,0,0);
    for(int i = 1;i < n;i++){
        colors[i]=Vec3b((rand()&255),(rand()&255),(rand() &255));
    }

    Mat Dst(img3.size(),CV_8UC1);//ラベリング結果の出力。

    
    for (size_t i = 0; i < Dst.rows; i++)
    {
            int *lb = labe.ptr<int>(i);
            Vec3b *pix = Dst.ptr<Vec3b>(i);
            for (size_t j = 0; j < Dst.cols; j++)
            {
                pix[j]=colors[lb[j]];
            }
    }

    //ROIの設定まで書く
    //imshow("image",img3);

    ///
    std::vector<Vec4i> hierarchy;
//	findContours(img3, imgs_points, hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//輪郭検出
	int size = imgs_points.size();


    std :: cout << imgs_points.size() << std::endl;
    for (size_t i = 0; i < imgs_points.size(); i++)

    {
        Point MaxP = max(imgs_points.at(i));
        Point MinP = min(imgs_points.at(i));
        std::cout << MaxP <<  MinP << std::endl;
        Rect rect(MinP,MaxP);

        rectangle(img3,rect,Scalar(200,0,0),-1,CV_AA);
    }

    //*/

    imshow("image2",img3);
    waitKey();

    return 0;
}
