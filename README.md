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
- If you don't want to bother with Markdown (.md) Editors, send the SysAdmin (@Kaolinnite) and @modishiv) the changes you want uploaded.
- **If you make a decent sized change (e.g. severals function long), please upload it whenever you can. Incremental changes are better than massive changes because we can all review it easier** 
 
## Installation Instructions: Windows only and using Geany
**Downloading / Extracting Files:**
- Download the *AVC_Win10.zip* file and the correct SFML library zip file that matches your compiler version:
	- **E.g.** SFML-64-bit with MinGW-w64 and SFML-32-bit with MinGW-w32. Your version can be found by looking for MinGW in your Program Files/Program Files (x86) and checking the number.
- Extract the *SFML-x-bit.zip* file into a folder preferably directly in (C:\\\\) but anywhere works.
- Extract the *AVC_Win10.zip* file into another folder.
- **Important:** 
- After extracting the SMFL-x-bit.zip file, the extracted folder will be called "SFML-64-bit" or "SFML-32-bit". The actual "SFML" library/folder you want will be inside of this, and is the one that your makefile needs to locate. Copy the "SFML" folder, and paste it in the same location as "SFML-x-bit" then delete the "SFML-x-bit" folder.
- This makes it possible for the makefile to find the SFML library that opens directly into the right folders (bin, doc, examples,...) and doesn't contain another folder which has to be opened to access them, like this: ![filepath](Misc/filepath.jpg?raw=true "As you can see, the SFML file is open and all the files are stored directly in them") <br>


**Setting up Geany to use makefiles:**
- Open Geany and at the top, click the *Build* tab (between "Project" and "Tools") and select *Set Build Commands*. Where it says "make" enter **mingw32-make** or **mingw64-make**, (depending on which version of MinGW you are using). Now by clicking the *Build* tab, then *Make*, Geany will use the makefile within the same folder as the .cpp file to compile and build that program.
- The makefiles inside each folder within AVC_Win10 (AVC_robot and AVC_server) are pre-written to locate the SFML library in C:\\\\ and work with the "robot.cpp" and "server3.cpp" files.
- As a precaution, open each makefile using Geany or a text editor, and make sure there is a tab before each line starting with "g++". If it contains multiple spaces instead, then replace these spaces with a tab.


**If you put the SFML library somewhere else (not in C:\\\\):**
- Open the makefiles inside each folder (AVC_robot and AVC_server) using Geany or any text editor. Here is the makefile for server3:    ![server3 makefile](Misc/server3_make.jpg?raw=true "Opened using Geany, but Notepad works fine")
- Where C:\\\\SFML is, replace it with the file path to your own SFML library.
- To get the file path: open the file explorer, find and open your SFML file and right click where it says "This PC". Click "copy address as text". Finally, replace "C:\\\\SFML" in the makefiles with this copied address.


**If you renamed the "robot.cpp" or "server3.cpp" files:**
- If the name of your robot.cpp file is different, open the makefile in AVC_robot using Geany or any text editor. Here is what you will see: ![robot makefile](Misc/robot_make.jpg?raw=true "Note: Don't change the file type i.e. don't remove '.cpp' from robot.cpp")
- Change all instances of "robot" to the new name of the file. (e.g. if the file is now called *newrobot.cpp*, changing **robot.o** to **newrobot.o**).
- If the name of your server3.cpp file is different, do the same but with the makefile in AVC_server, and change all instances of "server3" to the new name of the file. (e.g. if the file is now called *newserver.cpp*, changing **server3.o** to **newserver.o**).



**Compiling / Building and Running the programs using Geany:**
- Once the makefiles are set up, open robot.cpp (in AVC_robot folder) and server3.cpp (in AVC_server folder) in Geany in two different windows. (Or whatever names you have given the .cpp files.)
- Instead of clicking compile and build, just click the *Build* tab and select *Make* for Geany to use the makefiles and compile/build the program. Do this for each program. If you still experience issues, read below.
- Now execute/run server3.cpp first then robot.cpp to run the program.
- **Note:** Your PC's security (firewall, antivirus software etc.) might block communications between the robot and server3 program. If this happens, give it permission as an administrator.


**To Change the Maze/Map:**
- Inside the AVC_server folder, there is a text file called *config.txt*. Open it using a text editor.
- There are 3 different mazes/maps to choose from: core, completion, and challenge.
- By default, the map will be set to core.
- To change map, change where it says "core" in the top line to "completion" or "challenge" and save the file.
- The map will then be different the next time you run the server3.cpp program.


## Trouble Shooting for Issues:
- It is best to extract the SFML library into C:\\\\ so you don't have to edit the makefiles. Check to see that the SFML folder you extracted is A: the correct one for your complier version, and B: in the right file path you are using in your makefiles.
- If the pre-downloaded dll libraries within AVC_robot and AVC_server fail, there is an easy fix. Copy all .dll files from the SFML folder into the same folder as your .cpp files (the AVC_robot and AVC_server folders) and replace the old ones. You can find all these .dll files inside the "bin" folder in "SFML".
- If the makefile fails for no reason, delete the files *robot.exe*, *robot.o*, and *robot* inside the AVC_robot folder and then try *Make* again.
- Don't worry about any depreciated method messages - the programs will still work. 
- Make sure that any antivirus software on your computer is not stopping the download of important files for SFML to work on Windows.
