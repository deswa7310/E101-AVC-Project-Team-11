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
      for (int i =0; i<150; i++){
		  int pix = get_pixel(cameraView, 50, i, 3);
		  int isWhite;
		  if (pix > 250){isWhite = 1;
			  error = error + i-79.5;
			  } else {isWhite = 0;}
		  std::cout<<isWhite<< " ";
	  }
	  std::cout<<std::endl;
	  dv = 5*error;
	  vLeft = v_go - dv;
	  vRight = v_go + dv;
      setMotors(vLeft,vRight); 
      std::cout<<" vLeft="<<vLeft<<" vRight="<<vRight<<std::endl;
      usleep(10000);   
      
  } //while 
 
} // main 

