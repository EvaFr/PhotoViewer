The task:
//**************************
Create a picture viewer application. The program shall take 3 command line arguments:
- Path to a directory that contains the pictures
  - *.png and *.jpg files
  - Scan recursively
- File ordering
  - By name, alphabetically
  - By creation, date/time, oldest first
- Display fill mode
  - Stretch to window
  - Center
  - Fit to window (preserve aspect ratio)

The photos shall be displayed one-by-one, filling the whole window. The user may quit the application by closing the window. One can switch between displayed images using the keys Page Down/Left and Page Up/Right. Alternatively, mouse click on the left side goes back, on the right side goes forward.

Please display the file name and the file creation date/time on the bottom of the window.

The window title shall be the directory that contains the pictures.
//*****************************

The environment:
Qt Creator 4.0.2
GCC (x86 64bit in /usr/bin)

//*****************************

Functions of the program:

 Key Functions:
      Next Image: left key, page Up
      Previous Image: right key, page down
      First Image: Home
      Last Image: End

 Tolbar:
      Open: open directory 
      Name: ordering by name 
      Time: ordering by time
      Strecht: Stretch to window 
      Center: display to the center 
      Fit: Fit to window (preserve aspect ratio)
      Next: next image\n Prev: previous image

//*********************************
     
 Files of the project:

   constans.h: it contains basic variables of the project

   settingsManagement.h
   settingsManagement.cpp: it contains the SettingsType class, its variables are 
        FileOrderingType ordering;
        DisplayType display;
        (FileOrderingType and DisplayType are enums in the constans.h file)

   fileManagement.h
   fileManagement.cpp: 
       FileType class: it contains the properties of one image file
       FileManagementType class: the list of the images, ordering functions
   
   These files do not contains Qt dependecies.
   
   mainwindow.h
   mainwindow.cpp: it contains Qt dependencies only. Slots, Widgets and image drawing.  
       


