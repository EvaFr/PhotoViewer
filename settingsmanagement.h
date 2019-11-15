#ifndef SETTINGSMANAGEMENT_H
#define SETTINGSMANAGEMENT_H

#include "constans.h"
/*
 it contains the SettingsType class, its variables are
        FileOrderingType ordering;
        DisplayType display;
        (FileOrderingType and DisplayType are enums in the constans.h file)
*/
class SettingsType{
public:
   SettingsType(){reset();  loadSettings();}

   void reset(){}
   void setFileOrdering(FileOrderingType Ordering){ordering = Ordering;}
   void setDisplayType(DisplayType  Display){display = Display;}
   void setScale(int Scale){scale = Scale;}

   FileOrderingType getFileOrdering()const{return ordering;}
   DisplayType getDisplayType()const{return display;}
   int getScale()const{return scale;}

   void saveSettings(){}
   void loadSettings(){}

private:
   FileOrderingType ordering;
   DisplayType display;
   int scale;

};


#endif // SETTINGSMANAGEMENT_H
