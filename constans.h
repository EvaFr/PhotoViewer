#ifndef CONSTANS_H
#define CONSTANS_H

#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <list>

enum FileOrderingType {byName, byTime, fileOrderingTypeNum};
enum DisplayType {toStretch, toCenter, toFit, DisplayTypeNum};

const std::string ImageFileTypes[6]{"*.png", "*.jpg", "*.PNG", "*.JPG", "*.jpeg", "*.JPEG"};
const int  ImageFileTypesNum = 6;

const std::string orderingName = "byName";
const std::string orderingTime = "byTime";
const std::string displayToStretch = "toStretch";
const std::string displayToCenter = "toCenter";
const std::string displayToFit = "toFit";

const std::string helpText = "Help Photo Viewer\n"\
        "Key Functions\n Next Image: left key, page Up\n"\
        " Previous Image: right key, page down\n"\
        " First Image: Home\n"\
        " Last Image: End\n\n"\
        "Tolbar:\n Open: open directory\n Name: ordering by name\n Time: ordering by time\n"\
        " Strecht: Stretch to window\n Center: display to the center\n Fit: Fit to window (preserve aspect ratio)\n"\
        " Next: next image\n Prev: previous image\n";

#endif // CONSTANS_H
