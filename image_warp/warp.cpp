#include <cstdlib>
#include <iostream>
#include <cstdio>
#include "time.h"

#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
 
int main(int argc, const char *argv[]) {
  srand(time(NULL));
  if(argc != 5) {
    printf("Usage: warp <file_name_minus_exstenios> <start_idx> <end_idx> <jump_size>\n");
  }
  string prefix = argv[1], name;
  char numstr[21];
  int start = atoi(argv[2]);
  int end = atoi(argv[3]);
  int jump = atoi(argv[4]);
  for (int i = start; i < end + 1; i += jump) {
    sprintf(numstr, "%d", i);
    name = prefix + "_" + numstr;
    Mat I = imread(name + ".jpg");
    Mat I_horz_scale, I_vert_scale, I_noise, I_chroma;
    int t = rand() % 120;
    t += (t % 2 ? 1 : 0);
    resize(I, I_horz_scale, Size(256-t, 256));
    copyMakeBorder(I_horz_scale, I_horz_scale, 0, 0, t/2, t/2, BORDER_REPLICATE, Scalar(255, 255, 255));

    resize(I, I_vert_scale, Size(256, 256-t));
    copyMakeBorder(I_vert_scale, I_vert_scale, t/2, t/2, 0, 0, BORDER_REPLICATE, Scalar(255, 255, 255));

    I_noise = I.clone();
    I_chroma = I.clone();
    for (int h = 0; h < I.rows; ++h) {
      for (int w = 0; w < I.cols; ++w) {
        int r = (rand() % 30) - 15;
        int red = rand() % 256;
        int blu = rand() % 256;
        int gre = rand() % 256;
        I_noise.at<Vec3b>(h,w)[0] = (I_noise.at<Vec3b>(h,w)[0] + r) % 255;
        I_noise.at<Vec3b>(h,w)[1] = (I_noise.at<Vec3b>(h,w)[1] + r) % 255;
        I_noise.at<Vec3b>(h,w)[2] = (I_noise.at<Vec3b>(h,w)[2] + r) % 255;

        Vec3b color = I.at<Vec3b>(h,w);
        if(color[0] <= 255 && color[0] > 199 && 
          color[1] <= 255 && color[1] > 199 &&
          color[2] <= 255 && color[2] > 199
          ) {
          I_chroma.at<Vec3b>(h,w)[0] = red;
          I_chroma.at<Vec3b>(h,w)[1] = blu;
          I_chroma.at<Vec3b>(h,w)[2] = gre;
        }
      }    
    }

    imwrite(name + "_h.jpg", I_horz_scale);
    imwrite(name + "_v.jpg", I_vert_scale);
    imwrite(name + "_n.jpg", I_noise);
    imwrite(name + "_c.jpg", I_chroma);
  }
  return 0;
}