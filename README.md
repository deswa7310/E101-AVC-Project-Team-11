# E101-AVC-Project-Team-11
Team 11's AVC Project Repository for ENGR101.
For our plan visit https://github.com/deswa7310/E101-AVC-Project-Team-11/blob/master/Team%20Information.md

## Notes for members:
- Feel free to write in the Milestones wiki page - it's there to set goals.
- Discuss with other members during the week by writing in the Weekly Discussions Doc.md. At the end of every week, it will be wiped clean and uploaded to the discussions archive in the wiki
- View and create new milestones by going the milestones tab in the issues and pull request tabs.
- When adding new issues, please detail thoroughly and add labels. After adding it to the project, wait a moment for it to be sorted.
- Always add description comments when making a new commit.
- Make changes by creating a new branch, not by merging it with the master. 
- If you don't want to bother with Markdown (.md) Editors, send the SysAdmin (@Kaolinnite) the changes you want uploaded.
- **If you make a decent sized change (e.g. severals function long), please upload it whenever you can. Incremental changes are better than massive changes because we can all review it easier** 
 
## Installation Instructions: Windows only and using Geany
Downloading files
- Download the SFML, AVC_server, and robot zip files
 - **Note:** Install the SFML library that is the same version as your compiler e.g. SFML-64-bit with Mingw-64 and SFML-32-bit with Mingw-32
- Extract the SFML file into a folder, preferably (C:) and then extract both the server and robot into another folder.
**Important:** Don't extract zip files into new folders. This will interfere with how everything functions


**Setting up Geany**
- Open Geany and by going to Build and then selecting Set Build Commands. Where it says "make" enter mingw32-make or mingw64-make, (depending on which version of MinGW you are using).
- **IF you put the SFML library somewhere else or you renamed the .cpp files:**
 - Open the makefiles in each folder in Geany or in any text editor. Where C:\\SFML is, replace it with the file path of your own SFML library
 - If the name of any of your .cpp files are different, change the robot/server3 names used in the makefile to your new name (e.g. changing robot.o to robot2.o)
- Open robot.cpp and server3.cpp in Geany in two different windows. Instead of compiling the program select make under the build command in Geany to create new executables 
- Execute server3 first then robot to run the program

## Trouble Shooting for Issues:
- SFML library works best when installed in C:\\. Check to see that SFML folder you extracted is A: the correct one for your complier version, B: the file path of the SFML folder is 
- Sometimes the preinstalled libraries sometimes fail. Copy all dll files from the SFML download folder and into the same folder as your .cpp files
- If using the makefile fails for no discernable reason, delete the robot.exe and robot.o and then run make
- Makefile may be seprated by multiple spaces instead of a tab when lines start with g++ - replaces them with a tab
- Don't worry about depreciated method messages - the programs will still work

