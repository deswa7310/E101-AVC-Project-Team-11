
#include "robot.hpp"

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	
	bool approachingWall();
	bool wallOnSide(int side);
	bool containsWhite(int side);
	
	double vGo = 50.0; // 40.0 works
    double vLeft, vRight;
    double turn = 168.5; // the velocity for a 90 degree turn (did lots of testing)
    bool turningLeft = false;
    
    // delay is for turning left (our robot relies on the left wall for guidance and
    // must keep it on the left side of cameraView when it turns, no matter the direction)
    
    int turningDelay = 7; // number of movements forward before turning left
    int delayCount = turningDelay; // movements left

    while(1){ /** Make it follow the left wall: */ 
		
		takePicture(); // image is 150x100 (widthxheight)
		vLeft = vGo;
		vRight = vGo;
		
		bool leftWall = wallOnSide(1);
		
		if (!containsWhite(4)){ // go straight if white line in view, else:
			if (delayCount == 0){ // if delay for left turn is over, turn left:
				delayCount = turningDelay; // resets delay
				turningLeft = false;
				vLeft = 0;
				vRight = turn; // turns left
			}
			else if (!leftWall && turningLeft){ // counts down till left turn:
				delayCount--;
			}
			else if (leftWall && turningLeft){ // prevents false positives:
				delayCount = turningDelay;
				turningLeft = false; // prevents left turn if there is now a wall on the left
			}
			else if (!leftWall){ // if no wall on left, start count-down:
				turningLeft = true;
			}
			else if (approachingWall() && leftWall && wallOnSide(2)){ // if dead end:
				vLeft = turn; 
				vRight = -turn; // turns 180 degrees
			}
			else if (approachingWall()){ // if there is a wall in front: (and a left wall)
				vLeft = turn;  // turns right
				vRight = 0;
			}
		}
		
		setMotors(vLeft,vRight);   
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		usleep(10000);
	} //while

} // main

// returns true if horizontal red line across middle of cameraView:
bool approachingWall(){
	int redPixCount = 0;
	for (int i = 0; i < 150; i++){
		int red = get_pixel(cameraView, 50, i, 0);
		int white = get_pixel(cameraView, 50, i, 3);
		if (red > 250 && white < 250){redPixCount++;}
	}
	if (redPixCount > 100){return true;}
	return false;
}

// returns number of red pixels on that side (left is 1, right is 2):
bool wallOnSide(int side){
	int col;
	if (side == 1) {col = 0;}
	else {col = 140;}
	int redPixCount = 0;
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 10; j++){
			int red = get_pixel(cameraView, i, col+j, 0);
			if (red > 250){redPixCount++;}
		}
	}
	return redPixCount > 250;
}

// function returns true if there is a white pixel on that particular side
bool containsWhite(int side){ // 1 is left side of image, 2 is top, 3 is right, 4 is bottom
	int max = 100;
	int row = 0;
	int col = 0;
	if (side % 2 == 0){max = 150;} // if top or bottom
	for (int i = 0; i < max; i++){
		if (side % 2 == 0){col = i;} else {row = i;}
		if (side == 3){col = 149;} // if right
		if (side == 4){row = 99;} // if bottom
		int pix = get_pixel(cameraView, row, col, 3);
		if (pix > 250) {return true;}
	}
	return false;
}
