//
// Created by Sivasubramani on 10/08/21.
//

#include "CompressionList.h"

CompressionList::CompressionList() {
    root_node = NULL;
    AppLog::Logger(LOG_FORMAT,"INFO","Load compression List");
    loadListFromXML("CompressList", "Name", compressList);
}

void CompressionList::loadListFromXML(string parent, string child, set<string> &result) {

    if(parent.size()==0 || child.size()==0) return;

    AppLog::Logger(LOG_FORMAT,"INFO","********Loading/Parsing "+parent+" from XML********");
    // Read the ../EnumList/encryptListConf.xml (path) file

    ifstream xmlFile;
//    xmlFile.open("./src/EnumList/encryptListConf.xml");
xmlFile.open("/Users/siva-6452/FileReaderDesign/src/EnumList/encryptListConf.xml");

    if(!xmlFile) {
        AppLog::Logger(LOG_FORMAT,"CRITICAL","xmlFile not found for Compression load" );
        cout<<"xmlFile not found"<<endl;
        return;
    }
    vector<char> buffer((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    doc.parse<0>(&buffer[0]);

    root_node = doc.first_node((const char*)parent.c_str());

    if(root_node == NULL){
        AppLog::Logger(LOG_FORMAT,"CRITICAL","root node is null in Compression load" );
        xmlFile.close();
        return;
    }
    for(xml_node<> * child_node = root_node->first_node((const char*)child.c_str()); child_node; child_node = child_node->next_sibling())
    {
        AppLog::Logger(LOG_FORMAT,"DEBUG",parent +" = "+ child_node->value() );
        result.insert(child_node->value());
    }
    AppLog::Logger(LOG_FORMAT,"INFO","*******Ending Parsing "+ parent+ " from XML************");
    xmlFile.close();
}
bool CompressionList::checkCompressionFromList(string compressName){
    if(!compressList.empty() && compressList.find(compressName) != compressList.end()){
        return true;
    }
    return false;
}

string CompressionList::getCompressionType(string compressName){
    if(compressName.empty()) return "";
    if(compressName[0]=='C') return "Compression";
    else if(compressName[0]=='D') return "Decompression";
    return "";
}

CompressionList::~CompressionList() {

}

