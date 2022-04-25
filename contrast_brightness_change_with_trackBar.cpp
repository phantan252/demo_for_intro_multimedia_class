#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std; 
using namespace cv; 

int alpha = 110; 
int beta = 110; 

Mat src_img, out_img; 

void linearTransform (const Mat &original_img, const double input_alpha, const int input_beta){
  Mat new_img; 
  original_img.convertTo(new_img, -1,input_alpha, input_beta); //calculate new_img = input_alpha * original_img + input_beta
  hconcat(original_img, new_img, output_img); 
  imshow ("changing brightness and contrast", output_img); 
}

void alpha_trackbar (int, void*){
  double alpha_value = alpha/100.0; 
  int beta_value = beta - 100; 
  linearTransform (src_img, alpha_value, beta_value); 
}

void beta_trackbar (int, void*){
  double alpha_value = alpha/100.0; 
  int beta_value = beta - 100; 
  linearTransform (src_img, alpha_value, beta_value); 
}

int main (){
  src_img = imread ("tskukuba.png", IMREAD_COLOR); //read an image
  if(src_img.empty()){
    cout << "Cannot load the image" << endl; 
    return -1; 
  }
  
  output_img = Mat (src_img.rows, src_img.cols*2, src_img.type()); 
  hconcat (src_img, src_img, output_img); 
  
  namedWindow ("changing brightness and contrast");
  createTrackbar("alpha gain (contrast)", "Brightness and contrast adjustments",&alpha,500, alpha_trackbar); 
  createTrackbar("Beta bias (brightness)","Brightness and contrast adjustments",&beta, 200, beta_trackbar);

  alpha_trackbar (0,0); 
 
  waitKey();
  imwrite("output.png", output_img);
  return 0; 
}
