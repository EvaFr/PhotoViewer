#include "filemanagement.h"

void FileManagementType::orderFiles(FileOrderingType Ordering){
    if (!isEmpty()){
        if (Ordering == byName){
          files.sort([](const FileType& a, const FileType& b) { return a.getName() < b.getName(); });
        //    files.sort(compNames);
        }
        else if (Ordering == byTime){
            files.sort([](const FileType& a, const FileType& b) {return a.getTime() < b.getTime();});
             //    files.sort(compTimes);
        }
    }
}

void FileManagementType::print(){
    std::list<FileType>::iterator it;
    std::cout << "images\n";
    for (it = files.begin(); it != files.end(); ++it){
        std::cout << it->getPath() << "  " << it->getName() << "  " << it->getTime() << '\n';
    }
    std::cout << '\n\n';
}

std::string FileManagementType::getImageName(int num){
    std::string s;
    s.clear();
    if ((num >= 0)&&(num < files.size())){
       itF = files.begin();
       std::advance(itF, num);
       s = itF->getPath();
    }
    return s;
}
std::string FileManagementType::getCreationTime(int num){
    std::string s;
    s.clear();
    if ((num >= 0)&&(num < files.size())){
       itF = files.begin();
       std::advance(itF, num);
       s = itF->getCreationTime();
     }
    return s;
}

std::string FileManagementType::getName(int num){
    std::string s;
    s.clear();
    if ((num >= 0)&&(num < files.size())){
       itF = files.begin();
       std::advance(itF, num);
       s = itF->getName();
    }
    return s;
}
std::string FileManagementType::getPath(int num){
    std::string s;
    s.clear();
    if ((num >= 0)&&(num < files.size())){
       itF = files.begin();
       std::advance(itF, num);
       s = itF->getPath();
    }
    return s;
}
bool FileManagementType::isFirst(int num){
    if ((num == 0)&&(!isEmpty())) return true;
    else return false;
}
bool FileManagementType::isLast(int num){
    if ((!isEmpty())&&(num == files.size() - 1)) return true;
    else return false;
}
bool FileManagementType::isEmpty(){
    if (files.size() == 0) return true;
    else return false;
}
bool FileManagementType::isValid(int num){
    if ((!isEmpty())&&(num >= 0)&&(num < files.size())) return true;
    else return false;
}
