//
// Created by Sivasubramani on 10/08/21.
//

#ifndef FILEREADERDESIGN_COMPRESSIONLIST_H
#define FILEREADERDESIGN_COMPRESSIONLIST_H
#include "../Common/CommonFiles.h"
#include "../../XmlParser/rapidxml.hpp"

using namespace rapidxml;

class CompressionList {
private:
    xml_document<> doc;
    xml_node<> * root_node;
    set<string> compressList;
    void loadListFromXML(string parent, string child, set<string> &result);

public:
    CompressionList();
    ~CompressionList();
    bool checkCompressionFromList(string compressName);

    string getCompressionType(string encName);
};


#endif //FILEREADERDESIGN_COMPRESSIONLIST_H
