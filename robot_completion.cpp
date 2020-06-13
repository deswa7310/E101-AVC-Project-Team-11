
#include "robot.hpp"

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	
  // declaring functions:
	bool containsWhite(int side);
	bool canSeeFinish();
	double error();
	
	double vGo = 25.0;
    double vLeft, vRight;
    bool finished = false; // set to true once finish line is detected

    while(1){
		
		takePicture(); // image is 150x100 (widthxheight)
		
		if (canSeeFinish()) {finished = true;} // disables turning once detected the finish line at top of cameraView
		
		if (finished) {vLeft = vRight = vGo;} // go straight ahead to finish line
    // if white at top (of cameraView), go towards it
		else if (containsWhite(2)) {double dv = 0.1*error(); vLeft = vGo + dv; vRight = vGo - dv;}
		else if (containsWhite(1)) {vLeft = 0.7*vGo; vRight = 1.3*vGo;} // else if white on left, turn left
		else if (containsWhite(3)) {vLeft = 1.3*vGo; vRight = 0.7*vGo;} // else if white on right, turn right
		else {vLeft = 0.5*vGo; vRight = -0.5*vGo;} // if no white detected, spin around on spot

		setMotors(vLeft,vRight);   
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		usleep(10000);
	} //while

} // main

// function returns true if there is a white pixel on that particular side
bool containsWhite(int side){ // 1 is left side of image, 2 is top, 3 is right
	int max = 100;
	int row = 0;
	int col = 0;
	if (side == 2){max = 150;} // if side is even (top or bottom)
	for (int i = 0; i < max; i++){
		if (side == 2){col = i;} else {row = i;}
		if (side == 3){col = 149;}
		int pix = get_pixel(cameraView, row, col, 3);
		if (pix > 250) {return true;}
	}
	return false;
}

// detects black pixels
bool canSeeFinish(){
	for (int i = 0; i < 150; i++){
		int pix = get_pixel(cameraView, 0, i, 3);
		if (pix < 5) {return true;}
	}
	return false;
}

// calculates error
double error(){
	int total_index = 0, white_pix_count = 0; // reset for next frame
	double average_index = 0.0;
		
	for (int i = 0; i < 150; i++){
		int pix = get_pixel(cameraView, 0, i, 3); // goes left to right on row 50
		if (pix > 250){ // if pixel is white
			total_index += i;
			white_pix_count++;
		}
	}
	average_index = total_index/white_pix_count; // centre of white pixels using mean
	std::cout<<(average_index - 74.5)<<std::endl;
	return (average_index - 74.5); // positive if line is to right
}
