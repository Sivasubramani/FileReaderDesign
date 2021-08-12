//
// Created by Sivasubramani on 10/08/21.
//

#include "GzipCompression.h"

GzipCompression::GzipCompression(){

}
GzipCompression::~GzipCompression(){

}
string GzipCompression::getCompressName(string sourceFile,string addCompressCode){
    if(sourceFile.empty() ){
        AppLog::Logger(LOG_FORMAT,"ERROR","Source file name is empty");
        return "";
    }
    if(addCompressCode.empty() ){
        AppLog::Logger(LOG_FORMAT,"ERROR","Adding Compression Code name is empty");
        return "";
    }
    string target = sourceFile+addCompressCode;
    AppLog::Logger(LOG_FORMAT,"INFO","Gzip getCompressName is done... Source file name:"+sourceFile+" and Target file name:"+target );
    return target;
}

string GzipCompression::compress(string sourceFile){
    string target =getCompressName(sourceFile,".gz");
    if(target.empty()){
        AppLog::Logger(LOG_FORMAT,"ERROR","Target file name is empty");
        return "";
    }
    ifstream inFile(sourceFile.c_str(), std::ios_base::in);
    ofstream outFile(target.c_str(), std::ios_base::binary);
    boost::iostreams::filtering_streambuf< boost::iostreams::input> in2;
    in2.push( boost::iostreams::gzip_compressor());
    in2.push( inFile );
    boost::iostreams::copy(in2, outFile);
    AppLog::Logger(LOG_FORMAT,"INFO","Gzip Compression is done... Source file name:"+sourceFile+" and Target file name:"+target );
    return target;
}

string GzipCompression::getDecompressName(string sourceFile,string eraseCompressCode){
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
    AppLog::Logger(LOG_FORMAT,"INFO","Gzip getDecompressName is done... Source file name:"+sourceFile+" and Target file name:"+target );
    return target;
}

string GzipCompression::decompress(string sourceFile){
    string target =getDecompressName(sourceFile,".gz");
    if(target.empty()){
        AppLog::Logger(LOG_FORMAT,"ERROR","Target file is empty");
        return "";
    }
    ifstream inFile(sourceFile.c_str(), std::ios_base::in);
    ofstream outFile(target.c_str(), std::ios_base::out);
    boost::iostreams::filtering_streambuf< boost::iostreams::input> in2;
    in2.push( boost::iostreams::gzip_decompressor());
    in2.push( inFile );
    boost::iostreams::copy(in2, outFile);
    AppLog::Logger(LOG_FORMAT,"INFO","Gzip Decompression is done... Source file name:"+sourceFile+" and Target file name:"+target );
    return target;
}

