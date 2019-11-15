#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include "constans.h"
#include "settingsmanagement.h"

/*fileManagement.h
  fileManagement.cpp:
       FileType class: it contains the properties of one image file
       FileManagementType class: the list of the images, ordering functions
*/

class FileType{
public:
    FileType(){reset();}
    FileType(std::string Path, std::string Name,  uint Time){set(Path, Name, Time);}

    void reset(){path.clear(); name.clear(); time = 0;}

    void setCreationTime(std::string a){creationTime = a;}
    void setNames(std::string Path, std::string Name){path = Path; name = Name;}
    void setName(std::string Name){name = Name;}
    void setPath(std::string Path){path = Path;}
    void setTime(uint Time){time = Time;}
    void set(std::string Path,std::string Name, uint Time){setNames(Path, Name); time = Time;}

    std::string getName() const {return name;}
    std::string getPath() const {return path;}
    uint getTime() const {return time;}
    std::string getCreationTime()const {return creationTime;}

    void print(){std::cout << "path: " << path << " name: " << name << " time: " << time << '\n';}

private:
  std::string creationTime;
  std::string path;
  std::string name;
  uint time;
};

class FileManagementType{
public:
    FileManagementType(){reset();}

    void reset(){files.clear();}
    int getNumOfFiles(){return files.size(); itF = files.begin();}
    std::string getImageName(int num);
    std::string getCreationTime(int num);
    std::string getName(int num);
    std::string getPath(int num);

    bool isFirst(int num);
    bool isLast(int num);
    bool isEmpty();
    bool isValid(int num);


    bool compNames(const FileType& a, const FileType& b) { return a.getName() < b.getName(); }
    bool compTimes(const FileType& a, const FileType& b) { return a.getTime() < b.getTime(); }
    void push_back(FileType a){files.push_back(a);}

    void orderFiles(FileOrderingType Ordering);
    void print();


private:
   std::list<FileType> files;
   std::list<FileType>::iterator itF;
};

#endif // FILEMANAGEMENT_H
