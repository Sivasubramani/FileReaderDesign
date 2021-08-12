//
// Created by Sivasubramani on 10/08/21.
//

#include "Bzip2Compression.h"

Bzip2Compression::Bzip2Compression(){

}
Bzip2Compression::~Bzip2Compression(){

}
string Bzip2Compression::getCompressName(string sourceFile,string addCompressCode){
    if(sourceFile.empty() ){
        AppLog::Logger(LOG_FORMAT,"ERROR","Source file name is empty");
        return "";
    }
    if(addCompressCode.empty() ){
        AppLog::Logger(LOG_FORMAT,"ERROR","Adding Compression Code name is empty");
        return "";
    }
    string target = sourceFile+addCompressCode;
    AppLog::Logger(LOG_FORMAT,"INFO","Bzip2 getCompressName is done... Source file name:"+sourceFile+" and Target file name:"+target );
    return target;
}

string Bzip2Compression::compress(string sourceFile){
    string target =getCompressName(sourceFile,".gz");
    if(target.empty()){
        cout<<"Target file name is empty\n";
        AppLog::Logger(LOG_FORMAT,"ERROR","Target file is empty");
        return "";
    }
    ifstream inFile(sourceFile.c_str(), std::ios_base::in);
    ofstream outFile(target.c_str(), std::ios_base::binary);
    boost::iostreams::filtering_streambuf< boost::iostreams::input> in2;
    in2.push( boost::iostreams::bzip2_compressor());
    in2.push( inFile );
    boost::iostreams::copy(in2, outFile);
    AppLog::Logger(LOG_FORMAT,"INFO","Bzip2 Compression is done... Source file name:"+sourceFile+" and Target file name:"+target );
    return target;
}

string Bzip2Compression::getDecompressName(string sourceFile,string eraseCompressCode){
    if(sourceFile.empty() ){
        AppLog::Logger(LOG_FORMAT,"ERROR","Source file name is empty");
        return "";
    }
    if(eraseCompressCode.empty() ){
        AppLog::Logger(LOG_FORMAT,"ERROR","Erasing Compression Code name is empty");
        return "";
    }
    string target = sourceFile;
    size_t pos = target.find(eraseCompressCode);
    if (pos != std::string::npos) target.erase(pos, eraseCompressCode.length());
    AppLog::Logger(LOG_FORMAT,"INFO","Bzip2 getDecompressName is done... Source file name:"+sourceFile+" and Target file name:"+target );
    return target;
}

string Bzip2Compression::decompress(string sourceFile){
    string target =getDecompressName(sourceFile,".gz");
    if(target.empty()){
        AppLog::Logger(LOG_FORMAT,"ERROR","Target file is empty");
        return "";
    }
    ifstream inFile(sourceFile.c_str(), std::ios_base::in);
    ofstream outFile(target.c_str(), std::ios_base::out);
    boost::iostreams::filtering_streambuf< boost::iostreams::input> in2;
    in2.push( boost::iostreams::bzip2_decompressor());
    in2.push( inFile );
    boost::iostreams::copy(in2, outFile);
    AppLog::Logger(LOG_FORMAT,"INFO","Bzip2 Decompression is done... Source file name:"+sourceFile+" and Target file name:"+target );

    return target;
}

