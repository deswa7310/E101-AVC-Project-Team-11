
#include "robot.hpp"

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}

	/** Functions: */
	bool approachingWall();
	bool wallOnSide(int side);
	bool containsWhite(int side);
	bool canSeeFinish();
	double error();
	
	double vGo = 50.0;
    double vLeft, vRight;
    bool finished = false; // true once finish flag is detected
    bool challenge = false; // true if detects red walls (knows it is challenge)
	int startDelay = 5; // goes straight this no. of times to give it time to detect walls or not
    
    /** For challenge: */
    double turn = 168.5; // the velocity for a 90 degree turn (did lots of testing)
    bool turningLeft = false; // true if going to turn left
    int turningDelay = 7; // number of movements forward before turning left
    int delayCount = turningDelay; // movements left

    while(1){
		
		takePicture(); // image is 150x100 (widthxheight)
		vLeft = vRight = vGo; // go straight by default		
		if (canSeeFinish() && !challenge) {finished = true;} // if finished, just goes straight ahead to finish line
		bool leftWall = wallOnSide(1); // true if red wall on left (for convenience)
		if (leftWall && challenge == false) {challenge = true;} // knows it is challenge if it detects a red left wall
		
		if (!finished && startDelay == 0){ // goes straight if finished or initial start delay
			if (challenge){ // if challenge:
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
			}
			else { // if core or completion:
				if (containsWhite(1)) {vLeft = 0.7*vGo; vRight = 1.3*vGo;}
				else if (containsWhite(2)) {double dv = 0.2*error(); vLeft = vGo + dv; vRight = vGo - dv;}
				else if (containsWhite(3)) {vLeft = 1.3*vGo; vRight = 0.7*vGo;}
				else if (!containsWhite(4)) {vLeft = 0.5*vGo; vRight = -0.5*vGo;}
			}
		}
		else if (startDelay > 0) {startDelay--;}
		setMotors(vLeft,vRight);
		usleep(10000);
	} //while

} // main

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
	return (average_index - 74.5); // positive if line is to right
}

// returns true if horizontal red line across middle of cameraView (wall ahead);
bool approachingWall(){
	int redPixCount = 0;
	for (int i = 0; i < 150; i++){
		int red = get_pixel(cameraView, 50, i, 0);
		int white = get_pixel(cameraView, 50, i, 3);
		if (red > 250 && white < 250){redPixCount++;}
	}
	return redPixCount > 100;
}

// returns true if wall on that side (left is 1, right is 2):
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
