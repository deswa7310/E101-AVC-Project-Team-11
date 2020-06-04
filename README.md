# E101-AVC-Project-Team-11
Team 11's AVC Project Repository for ENGR101.
For our plan visit https://github.com/deswa7310/E101-AVC-Project-Team-11/blob/master/Team%20Information.md

## Notes for members:
- Feel free to write in the Milestones and discussions wiki page - it's there to make suggestions.
- View and create new milestones by going the milestones tab in the issues and pull request tabs.
- When adding new issues, please detail thoroughly and add labels. After adding it to the project, wait a moment for it to be sorted.
- Always add description comments when making a new commit.
- Make changes by creating a new branch, not by merging it with the master.
- If you don't want to bother with Markdown (.md) Editors, send the SysAdmin (@Kaolinnite) the changes you want uploaded.
 
## Installation Instructions:
Windows

-Download the SFML Zip file and AVC_WIN10 Zip file from the repository
-Unzip the SFML file into a folder preferably C:\SFML
-Customize the Geany compiler by going to Build and then selecting Set Build Commands
-Where it says "make" enter mingw32-make
-Copy all dll files from the SFML download folder and into the same folder as your .cpp files
-Inside AVC_ROBOT open makefile, robot.cpp and robot.hpp in Geany
-Inside AVC_SERVER open makefile and server.cpp in Geany
-Instead of compiling the program select make under the build command in Geany

## Common Installation Issues:
Issue: Makefile does not make Possible fixes: Makefile may be seprated by multiple spaces instead of a tab when lines start with g++ Makefile may not be getting SFML files from right place. To get correct file location click on the SFML file in file expoler and where it says "This PC" right click on it and select "Copy address as text". Paste it where it says DIR and add another back slash so its in the format of "C:\SFML\SFML-2.5.1"
