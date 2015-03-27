#include <iostream>
#include <string>
#include <sstream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

const int CAMERAS = 5;
const int PICTURES = 360;

//give arguent of mask dir
int main(int argc,char** argv){
	string dir = argv[1];
	for (int cam = 0; cam < CAMERAS; cam++){
		for (int i = 0; i < PICTURES; i+=3){ 
			string file_name = dir+"/N"+to_string(cam+1)+"_"+to_string(i)+"_mask.pbm";
			Mat I = imread(file_name,0);

			//cout << "file_name: " << file_name << endl;
			//cout << "size: " << I.size() << endl;

			I = I > 0;

			int max_x = 0;
			int max_y = 0;
			int min_y = 5000;
			int min_x = 5000;

			for (int row = 0; row < I.rows; ++row){
				uchar* p = I.ptr(row);
				for (int col = 0; col < I.cols; ++col){
					if (int(*p++) == 0 && col > 1000 && row > 700
									   && col < (I.cols-1000) && row < (I.rows-700)){
						max_x = max(max_x,col);
						min_x = min(min_x,col);
						max_y = max(max_y,row);
						min_y = min(min_y,row);
					}
				}
			}

			//padding
			int width = max_x-min_x;
			int height = max_y-min_y;
			int padding_x = width/10;
			int padding_y = height/10;

			max_x = max_x + padding_x;
			min_x = min_x - padding_x;

			max_y = max_y + padding_y;
			min_y = min_y - padding_y;

			int paddedWidth = max_x-min_x;
			int paddedHeight = max_y-min_y;

			int newSize = max(paddedHeight,paddedWidth);

			if (newSize == paddedWidth){
				min_y -= (paddedWidth-paddedHeight)/2;
			}else{
				min_x -= (paddedHeight-paddedWidth)/2;
			}

			Rect boundary(min_x,min_y,newSize,newSize);

			//Mat croppedImage = I(boundary);

			string real_file_name = dir+"/../N"+to_string(cam+1)+"_"+to_string(i)+".jpg";
			string real_file_name_cropped = dir+"/../cropped/N"+to_string(cam+1)+"_"+to_string(i)+".jpg";
			Mat real = imread(real_file_name);
			Mat croppedImage = real(boundary);

			Size thesize(256,256);
			resize(croppedImage,croppedImage,thesize);

			// imshow("Cropped Image",croppedImage);

			imwrite(real_file_name_cropped,croppedImage);

		}
	}
	// waitKey(0); 
	return 0;
}