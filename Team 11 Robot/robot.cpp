#include "robot.hpp" 
 
int main(){ 
    cameraView.width = 100;     
    cameraView.height = 100; 
    cameraView.data = new char[cameraView.width * cameraView.height*3]; 
    cameraView.n_bytes = cameraView.width * cameraView.height*3; 
     
    if (connectNetwork()!=0){ 
      return -1; 
   } 
    double vLeft = 0.0; 
    double vRight = 0.0; 
    
    while(1){ // runs forever 
      takePicture(); 
      double error = 0.0;
      unsigned char v_go = 10;
      unsigned char dv; 
      for (int i =0; i<100; i++){// loops through all pixels rows in camera
		  int pix = get_pixel(cameraView, 50, i, 3);// gets all pixels in view of the camera
		  int isWhite;
		  if (pix > 250){isWhite = 1;// If pixel value is greater than 250 replace value with one
			  error = error + i-79.5;// error for seeing how far white line is from center of camera //NOT CURRENTLY WORKING AS INTENDED
			  } else {isWhite = 0;} // replace other pixel values with zero
		  std::cout<<isWhite<< " ";
	  }
	  std::cout<<std::endl;
	  dv = 5*error;// depending on error value turns wheel with a direction and speed centering white line in camera
	  vLeft = v_go - dv;// calculation to see how fast wheels should move 
	  vRight = v_go + dv;
      setMotors(vLeft,vRight); //set motor speed 
      std::cout<<" vLeft="<<vLeft<<" vRight="<<vRight<<std::endl;
      usleep(10000);   
      
  } //while 
 
} // main 

