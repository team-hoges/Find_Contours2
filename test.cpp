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

using namespace cv;


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

int main(int argc, const char* argv[]) 
{
    Mat  image1,img2,img3,img4;
    Mat binarys ;
   // Mat labe ;
    Mat stats;
    Mat cen;
    double area;//塗りつぶし範囲卍
    std::vector<std::vector<Point>>imgs_points;//輪郭座標系二次元配列
   // std::vector<Vec4i> hi;
	//double points_len; //これなに
	image1 = imread("./ans.jpg");
    Mat back_up = image1.clone();
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
    threshold(img2,img3,1.20,255,THRESH_BINARY_INV );
    GaussianBlur(img3,img3,Size(3,3),10);
    threshold(img3,img3,1.5,255,THRESH_BINARY_INV );
    medianBlur(img3,img3,7);

    //int n=connectedComponentsWithStats(img3,img3,stats,cen,4,CV_32S);  
    //ノイズ除去
    
  //  imshow("image",img3);
    //waitKey();
    Mat labes = img3 ;//ラベリング対象画像の生成
    Mat find  = img3;
   // Mat labelImaage (labes.size(),CV_32S); //ラベリング用画像の生成

    ///ラベリング実行size_
    /*
    int nlabel = connectedComponents(labes,labelImaage,8); //int nlabelがラベル数になる。

    std::cout << nlabel << std :: endl;
    std::vector<Vec3b>colors_1(nlabel);
        colors_1[0] =   Vec3b(0,0,0);
    for (int lacont = 1; lacont < nlabel; lacont++)
    {
        colors_1[lacont] =   Vec3b((rand()&255),(rand()&255),(rand()&255));
    }

    Mat output (img3.size(),CV_8UC3);//ラベリング結果出力

    for (int i = 0; i < output.rows; i++)
    {
        for (int j = 0; j < output.cols; j++)
        {
            int labels = labelImaage.at<int>(i,j);
            Vec3b &pixel = output.at<Vec3b>(i,j);
            pixel = colors_1[labels];
        }
        
    }
    */
   Mat output (img3.size(),CV_8UC3);//ラベリング結果出力

    
   // Mat sabun_bg;//膨張後差分
    output = img3;
    //cvtColor(img3,output,CV_BGR2GRAY);
    //threshold(output,output,20,255,THRESH_BINARY );
    morphologyEx(output, output,MORPH_CLOSE, Mat(), Point(-1, -1), 1);
  //  morphologyEx(output, output,MORPH_DILATE, Mat(), Point(-1, -1), 1);
   
    //imshow("a",output);
    //waitKey();
    
    std :: vector<std::vector<Point>> contuors;
    std :: vector <Vec4i> he;
    
    imshow("a",output);
    waitKey();

    findContours(output,contuors,he,CV_RETR_EXTERNAL ,CV_CHAIN_APPROX_NONE);
 
 //輪郭四角表示部
 /*
    Point MinP;
    Point MaxP;
    for (int i = 0; i < contuors.size(); i++)
    {
        MinP = min(contuors.at(i));
        MaxP = max(contuors.at(i));

        Rect rect(MinP,MaxP);

        rectangle( image1, rect, Scalar(0,255,0),2,8);
    }
    
    //std::cout << contuors.size()  << std :: endl;

*/

    std::vector<std::vector<Point> > contours_subset;
    
    for (long unsigned int i = 0; i < contuors.size(); i++)//マスク処理
    {
        area = contourArea(contuors.at(i));
        printf("%f\n",area);
        if(area > 1000){
            contours_subset.push_back(contuors.at(i));//面積が小さい群を全部消し去って抽出する。
        }
    }
    
    
    Mat mask_data = Mat::zeros(image1.rows, image1.cols, CV_8UC3);
    drawContours(mask_data,contours_subset,-1,Scalar(255,255,255),-1);//ここでマスク処理を行う
  
    
    //cv::namedWindow("Source", cv::WINDOW_AUTOSIZE );
    //cv::imshow("Source", mask_data);//これを使う
    //waitKey();
    
    Mat sure_bg;
    Mat kernel(3, 3, CV_8U, cv::Scalar(1));
//     morphologyEx(mask_data, sure_bg,MORPH_CLOSE, Mat(), Point(-1, -1), 1);
    dilate(mask_data,sure_bg,kernel,Point(-1,-1),2);
    
//cv::namedWindow("f", WINDOW_AUTOSIZE );
    cv::imshow("f", sure_bg);
    waitKey();

    Mat dist_transform;
    distanceTransform(mask_data,dist_transform,CV_DIST_L2,5);
   
    namedWindow("dis",WINDOW_AUTOSIZE);
    imshow("dist",dist_transform);



 
 
 return 0;
}
