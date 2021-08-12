//
// Created by Sivasubramani on 08/08/21.
//

#include "EncryptionList.h"

EncryptionList::EncryptionList() {
    root_node = NULL;
    AppLog::Logger(LOG_FORMAT,"INFO","Load Cryption List");
    loadListFromXML("EncryptionList", "Name", encList);
}


void EncryptionList::loadListFromXML(string parent, string child, set<string> &result) {

    if(parent.size()==0 || child.size()==0) return;

    AppLog::Logger(LOG_FORMAT,"INFO","********Loading/Parsing "+parent+" from XML********");
    // Read the ../EnumList/encryptListConf.xml (path) file

    ifstream xmlFile;
    xmlFile.open("/Users/siva-6452/FileReaderDesign/src/EnumList/encryptListConf.xml");
    if(!xmlFile) {
        AppLog::Logger(LOG_FORMAT,"CRITICAL","xmlFile not found for Cryption load" );
        xmlFile.close();
        return;
    }
    vector<char> buffer((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse the buffer
    doc.parse<0>(&buffer[0]);

    // Find out the root node
    root_node = doc.first_node((const char*)parent.c_str());

    if(root_node == NULL){
        AppLog::Logger(LOG_FORMAT,"CRITICAL","root node is null in Cryption load" );
        return;
    }
    for(xml_node<> * child_node = root_node->first_node((const char*)child.c_str()); child_node; child_node = child_node->next_sibling())
    {
        AppLog::Logger(LOG_FORMAT,"DEBUG",parent +" = "+ child_node->value() );
            result.insert(child_node->value());
    }
    AppLog::Logger(LOG_FORMAT,"INFO","*******Ending Parsing "+ parent+ " from XML************");
    xmlFile.close();
//    return result;
}

bool EncryptionList::checkCryptionFromList(string encName){
    if(!encList.empty() && encList.find(encName) != encList.end()){
        return true;
    }
    return false;
}
string EncryptionList::getCryptionType(string encName){
    if(encName.empty()) return "";
    if(encName[0]=='E') return "Encryption";
    else if(encName[0]=='D') return "Decryption";
    return "";
}

EncryptionList::~EncryptionList() {

}


