#include "robot.hpp"

/** Functions: (at bottom of program) */
bool approachingWall();
bool wallOnSide(int side);
bool containsWhite(int side);
bool detectFlag();
double error();

static double vGo = 50.0; // default velocity
static int turningDelay = 7; // number of movements forward before turning left (challenge)
static double turn = 168.5; // the velocity for a 90 degree turn (challenge)

int main(){ /** Has 38 semicolons: */
	
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
		return -1; // Kills program if server3 is not detected
	}
	
	double vLeft, vRight;
	int startDelay = 5; // goes straight this no. of times to give it time to detect walls or not
	
	/** For challenge: */
	bool challenge = false; // true if detects red walls (knows it is challenge)
	bool turningLeft = false; // true if going to turn left
    int delayCount = turningDelay; // movements left
	
    while(1){
		takePicture(); // image is 150x100 (widthxheight)
		vLeft = vRight = vGo; // go straight by default
		
		/** If finish flag is detected: end program. */
		if (detectFlag()){
			setMotors(0, 0);
			std::cout<<" Flag reached!"<<std::endl;
			return 0;
		}

		bool leftWall = wallOnSide(1); // true if red wall on left (for convenience)
		
		if (leftWall && !challenge) {
			challenge = true;
		} // knows it is challenge if it detects a red left wall
		
		if (startDelay == 0){ // just goes straight during start delay
			if (challenge){ /** If challenge: */
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
					else if (!leftWall){ // if no wall on left, start count-down till left turn:
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
			} // challenge
			
			else { /** If core or completion: */
				if (containsWhite(1)) { // if white on left side, turn left
					vLeft = 0.7*vGo; vRight = 1.3*vGo;
					}
				else if (containsWhite(2)) { // if white ahead, go straight and adjust for error
					double dv = 0.2*error(); vLeft = vGo + dv; vRight = vGo - dv;
					}
				else if (containsWhite(3)) { // if white on right side, turn right
					vLeft = 1.3*vGo; vRight = 0.7*vGo;
					}
				else if (!containsWhite(4)) { // if no white on any side of cameraView (including bottom), spin clockwise
					vLeft = 0.5*vGo; vRight = -0.5*vGo;
					}
			} // core/completion
		}
		else if (startDelay > 0) { // counts down the start delay (goes straight until it is 0)
			startDelay--;
		}
		setMotors(vLeft,vRight);
		usleep(10000);
	} //while
	
} // main


/** Checks a side of the image if white pixels are present. Side is chosen using an integer (for Core/Completion) */
bool containsWhite(int side){ // 1 is left side of image, 2 is top, 3 is right, 4 is bottom
	int max = 100; // if left or right (goes down 100 rows)
	int row = 0;
	int col = 0;
	if (side % 2 == 0){
		max = 150;
	} // if top or bottom (goes across 150 columns)
	
	for (int i = 0; i < max; i++){
		if (side % 2 == 0){
			col = i;
		} else {
			row = i;
		}
		
		if (side == 3){
			col = 149;
		} // if right
		
		if (side == 4){
			row = 99;
		} // if bottom
		
		int pix = get_pixel(cameraView, row, col, 3);
		
		if (pix > 250) { // if white
			return true; // returns true if one white pixel is detected
		}
	}
	return false;
}


/** Detects whether the robot can see the flag in front of it by detecting the number of black pixels near the bottom row 
* (General Function)
*/ 
bool detectFlag(){
	int count = 0;
	for (int i = 0; i < 150; i++){
		int pix = get_pixel(cameraView, 75, i, 3); // scans pixels along row near bottom
		if (pix < 5) { // if black
			count++;
		}
	}
	return count > 10; // Returns true if number of detected black pixels are over the threshold
}


/** Calculates error i.e how far the white line is from the middle of the camera and returns that value 
* (for Core/Completion) 
*/
double error(){
	int total_index = 0, white_pix_count = 0; // reset for next frame
	double average_index = 0.0;
	
	for (int i = 0; i < 150; i++){
		int pix = get_pixel(cameraView, 0, i, 3); // goes left to right on top row
		
		if (pix > 250){ // if pixel is white
			total_index += i;
			white_pix_count++;
		}
	}
	average_index = total_index/white_pix_count; // centre of white pixels using mean
	return (average_index - 74.5); // positive if line is to right of centre
}


/** Detects whether the robot is heading towards a red wall (for Challenge) */
bool approachingWall(){
	int redPixCount = 0;
	
	for (int i = 0; i < 150; i++){
		int red = get_pixel(cameraView, 50, i, 0);
		int white = get_pixel(cameraView, 50, i, 3);
		
		// distinguishes between red and white pixels (both have R of 255)
		if (red > 250 && white < 250){
			redPixCount++;
		}
	}
	return redPixCount > 100; // returns true if horizontal red line across middle of cameraView (wall ahead)
}


/** Checks the sides of the image if a red wall is present. Uses an integer to choose which side is checked (for Challenge) */
bool wallOnSide(int side){ // 1 is left side, 2 is right
	int col;
	
	if (side == 1) { // if left, scan leftmost 10 columns
		col = 0;
	}
	else { // if right, scan rightmost 10 columns
		col = 140;
	}
	int redPixCount = 0;
	for (int i = 0; i < 100; i++){ // for each row
		for (int j = 0; j < 10; j++){ // scan leftmost or rightmost 10 pixels
			int red = get_pixel(cameraView, i, col+j, 0);
			if (red > 250){
				redPixCount++;
			}
		}
	}
	return redPixCount > 250; // returns true if wall on that side (left is 1, right is 2)
}
