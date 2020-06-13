#include "robot.hpp" 
 
int main(){
	
    if (initClientRobot() !=0){
	std::cout<<" Error initializing robot"<<std::endl;
    }
	
    double v_go = 30.0;
    double vRight, vLeft;
    int image_width = 150;
    double image_centre = (image_width-1)/2.0; // centre of width
    
    while(1){ // runs forever 
      takePicture(); 
      int total_index = 0, white_pix_count = 0;
      double average_index = 0.0; // the mean index
	    
      for (int i = 0; i < image_width; i++){// loops through all pixels rows in camera
		  int pix = get_pixel(cameraView, 50, i, 3);// gets all pixels in view of the camera
		  if (pix > 250){ // if pixel is white
			  total_index += i; // counts total value of indices
			  white_pix_count++; // counts number of indices containing white pixels
		  }
	  }
	  average_index = total_index / white_pix_count; // finds central index (centre of white line)
	  double error = average_index - image_centre; // finds distance from central white pixel to centre of image
	  
	  double dv = 0.5*error; // depending on error value turns wheel with a direction and speed centering white line in camera
	  vLeft = v_go + dv; // calculation to see how fast wheels should move 
	  vRight = v_go - dv;
      setMotors(vLeft,vRight); //set motor speed 
      std::cout<<" vLeft="<<vLeft<<" vRight="<<vRight<<std::endl;
      usleep(10000);   
      
  } //while 
 
} // main 
