# E101-AVC-Project-Team-11
Team 11's AVC Project Repository for ENGR101.
For our plan visit https://github.com/deswa7310/E101-AVC-Project-Team-11/wiki/Milestones

## Notes for members:
- Feel free to write in the Milestones wiki page - it's there to set goals.
- Discuss with other members during the week by writing in the Weekly Discussions Doc.md. At the end of every week, it will be wiped clean and uploaded to the discussions archive in the wiki
- View and create new milestones by going the milestones tab in the issues and pull request tabs.
- When adding new issues, please detail thoroughly and add labels. After adding it to the project, wait a moment for it to be sorted.
- Always add description comments when making a new commit.
- Make changes by creating a new branch, not by merging it with the master. 
- If you don't want to bother with Markdown (.md) Editors, send the SysAdmin (@Kaolinnite) and (@modishiv) the changes you want uploaded.
- **If you make a decent sized change (e.g. severals function long), please upload it whenever you can. Incremental changes are better than massive changes because we can all review it easier** 
 
## Installation Instructions: Windows only and using Geany
Downloading files:
- Download the SFML, AVC_server, and the team 11 robot zip files
 - **Note:** Install the SFML library that is the same version as your compiler e.g. SFML-64-bit with Mingw-64 and SFML-32-bit with Mingw-32.
- Extract the SFML file into a folder, preferably (C:).
- Extract both the server and robot into another folder.
**Important:** Don't extract zip files into new folders. This will interfere with how everything functions.


**Setting up Geany**
- Open Geany, then by choosing *Build* and then selecting *Set Build Commands*. Where it says "make" enter mingw32-make or mingw64-make, (depending on which version of MinGW you are using).
- **IF you put the SFML library somewhere else or you renamed the .cpp files:**
 - Open the makefiles in each folder in Geany or in any text editor. Where C:\\SFML is, replace it with the file path of your own SFML library.
 - If the name of any of your .cpp files are different, change the robot/server3 names used in the makefile to your new name (e.g. changing robot.o to robot2.o).
- Open robot.cpp and server3.cpp in Geany in two different tabs. Instead of compiling the program, select "Make" under the build command in Geany to create new executables .
- Execute server3.cpp first then robot.cpp to run the program.

## Trouble Shooting for Issues:
- It is best to extract the SFML library into C:\\ so you don't have to edit the makefiles. Check to see that the SFML folder you extracted is A: the correct one for your complier version, and B: in the right file path you are using in your makefiles.
- If the preinstalled dll libraries within AVC_robot and AVC_server fail, there is an easy fix. Copy all .dll files from the SFML folder into the same folder as your .cpp files (the AVC_robot and AVC_server folders) and replace the old ones. You can find all these .dll files inside the "bin" folder in "SFML".
- If the makefile fails for no reason, delete the files *robot.exe* and *robot.o* inside the AVC_robot folder and then run make.
- The text inside each makefile may contain multiple spaces instead of a tab before the lines start with g++ - this should be replaced with a tab.
- If your makefile cannot find your SFML file open the file explorer open your SFML file and then right click where it says "This PC" and press "copy address as text". Paste this address where you have your old address
- Don't worry about any depreciated method messages - the programs will still work. 
- Make sure that any antivirus software on your computer is not stopping the download of important files for SFML to work on windows 

