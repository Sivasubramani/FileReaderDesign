//
// Created by Sivasubramani on 08/08/21.
//

#ifndef FILEREADERDESIGN_ENCRYPTIONLIST_H
#define FILEREADERDESIGN_ENCRYPTIONLIST_H
#include "../Common/CommonFiles.h"
#include "../../XmlParser/rapidxml.hpp"

using namespace rapidxml;


class EncryptionList {
private:
    xml_document<> doc;
    xml_node<> * root_node;
    set<string> encList;
    void loadListFromXML(string parent, string child, set<string> &result);

public:
    EncryptionList();
    ~EncryptionList();
    bool checkCryptionFromList(string encName);

    string getCryptionType(string encName);
};


#endif //FILEREADERDESIGN_ENCRYPTIONLIST_H
