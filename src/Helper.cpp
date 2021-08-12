//
// Created by Sivasubramani on 10/08/21.
//

#include "Helper.h"

Helper::Helper() {}

string Helper::resultOfCryption(bool encReadFlag, string cryptionFormat){
    if(cryptionFormat.size() ==0)
        return "Invalid Crypto format";

    if(encReadFlag && cryptionFormat[0] =='E')
        return "Encryption";

    else if (encReadFlag && cryptionFormat[0] =='D')
        return "Decryption";
    else
        return "Failed";
}

bool Helper::GzipCompress(string filename){
    GzipCompression *Gzipper = new GzipCompression();
    string str = Gzipper->compress(filename);
    delete(Gzipper);
    Gzipper = nullptr;
    if(!str.empty()) {
        AppLog::Logger(LOG_FORMAT,"ERROR","GzipCompress is failed");
        return true;
    }
    AppLog::Logger(LOG_FORMAT,"INFO","GzipCompress is Success");
    return false;
}

bool Helper::GzipDecompress(string filename){
    GzipCompression *GUnzipper = new GzipCompression();
    string str = GUnzipper->compress(filename);
    delete(GUnzipper);
    GUnzipper = nullptr;
    if(!str.empty()) {
        AppLog::Logger(LOG_FORMAT,"ERROR","GzipDecompress is failed");
        return true;
    }
    AppLog::Logger(LOG_FORMAT,"INFO","GzipDecompress is Success");
    return false;
}
bool Helper::Bzip2Compress(string filename){
    GzipCompression *Bz2Zipper = new GzipCompression();
    string str = Bz2Zipper->compress(filename);
    delete(Bz2Zipper);
    Bz2Zipper = nullptr;
    if(!str.empty()) {
        AppLog::Logger(LOG_FORMAT,"ERROR","Bzip2Compress is failed");
        return true;
    }
    AppLog::Logger(LOG_FORMAT,"INFO","Bzip2Compress is Success");
    return false;
}

bool Helper::Bzip2Decompress(string filename){
    GzipCompression *Bz2UnZipper = new GzipCompression();
    string str = Bz2UnZipper->compress(filename);
    delete(Bz2UnZipper);
    Bz2UnZipper = nullptr;
    if(!str.empty()) {
        AppLog::Logger(LOG_FORMAT,"ERROR","Bzip2Decompress is failed");
        return true;
    }
    AppLog::Logger(LOG_FORMAT,"INFO","Bzip2Decompress is Success");
    return false;
}
bool Helper::doCrypto(string cryptoType,FileHandler *fileHandler, string fileName){
    bool encReadFlag = false;

    if(fileHandler == nullptr){
        AppLog::Logger(LOG_FORMAT,"ERROR","fileHandler is invalid");
        return false;
    }
    if(cryptoType == "Encryption")
        encReadFlag = fileHandler->encrypt(fileName);
    else if(cryptoType == "Decryption")
        encReadFlag = fileHandler->decrypt(fileName);

    AppLog::Logger(LOG_FORMAT,"INFO","Cryption Type is "+cryptoType);
    encReadFlag==true ? AppLog::Logger(LOG_FORMAT,"INFO","Proceeding cryption"):
                        AppLog::Logger(LOG_FORMAT,"ERROR","Not able to process cryption");
    return encReadFlag;
}
bool Helper::doCompression(string cryptoType, string fileName, string compressionName){
    bool CompReadFlag = false;

    if(cryptoType == "Compression"){
        if(compressionName == "COM_GZIP" || compressionName == "COM_GZ"){
            CompReadFlag = GzipCompress(fileName);
            AppLog::Logger(LOG_FORMAT,"INFO","Compression name is "+ compressionName);
        }
        else if(compressionName == "COM_BZIP2" || compressionName == "COM_BZ2"){
            CompReadFlag= GzipDecompress(fileName);
            AppLog::Logger(LOG_FORMAT,"INFO","Compression name is "+ compressionName);
        }
    }

    else if(cryptoType == "Decompression"){
        if(compressionName == "DCOM_GZIP" || compressionName == "COM_GZ"){
            CompReadFlag = Bzip2Compress(fileName);
            AppLog::Logger(LOG_FORMAT,"INFO","DeCompression name is "+ compressionName);
        }
        else if(compressionName == "DCOM_BZIP2" || compressionName == "COM_BZ2"){
            CompReadFlag = Bzip2Decompress(fileName);
            AppLog::Logger(LOG_FORMAT,"INFO","DeCompression name is "+ compressionName);
        }
    }
    CompReadFlag==true ? AppLog::Logger(LOG_FORMAT,"INFO","Proceeding Compression"):
    AppLog::Logger(LOG_FORMAT,"ERROR","Not able to process Compression");

    return CompReadFlag;
}

void Helper::deleteAllEntities(EncryptionList *cryptionManager,CompressionList *compressionManager,FileHandler *fileHandler){
    AppLog::Logger(LOG_FORMAT,"INFO","Deleting all Entities");
    delete(cryptionManager);
    delete(compressionManager);
    delete(fileHandler);
    cryptionManager = nullptr;
    compressionManager = nullptr;
    fileHandler =nullptr;
}
bool Helper::singleprocess(string fileName, string Command){

    EncryptionList *cryptionManager = new EncryptionList();
    CompressionList *compressionManager = new CompressionList();
    FileHandler *fileHandler = new FileHandler();
    AppLog::Logger(LOG_FORMAT,"INFO",Command+" is given for "+fileName);
    if(cryptionManager->checkCryptionFromList(Command)){
        string cryptoType =cryptionManager->getCryptionType(Command);
        cout<<Command+" is given for "+fileName<<endl;
        AppLog::Logger(LOG_FORMAT,"INFO",fileName+" is given for "+cryptoType);
        bool cryptionReadFlag=doCrypto(cryptoType,fileHandler,fileName);
        if(cryptionReadFlag) {
            AppLog::Logger(LOG_FORMAT,"INFO",cryptoType+" is Completed for "+fileName);
            deleteAllEntities(cryptionManager,compressionManager,fileHandler);
            return true;
        }
        else {
            AppLog::Logger(LOG_FORMAT,"ERROR",cryptoType+" is failed for "+fileHandler->reason());
            deleteAllEntities(cryptionManager,compressionManager,fileHandler);
            return false;
        }
    }
    else if(compressionManager->checkCompressionFromList(Command)){
        string compressionType =compressionManager->getCompressionType(Command);
        string compressionName= Command;
        AppLog::Logger(LOG_FORMAT,"INFO",fileName+" is given for "+compressionType);
        bool CompressionReadFlag= doCompression(compressionType,fileName,compressionName);
        if(CompressionReadFlag){
            AppLog::Logger(LOG_FORMAT,"INFO",compressionType+" is Completed for "+fileName);
            deleteAllEntities(cryptionManager,compressionManager,fileHandler);
            return true;
        }
        else {
            AppLog::Logger(LOG_FORMAT,"ERROR",compressionType+" is failed for "+fileName);
            deleteAllEntities(cryptionManager,compressionManager,fileHandler);
            return false;
        }

    }
    return false;

}
bool Helper::dualProcess(string fileName, string Command1, string Command2) {
    bool dualprocessResult=false;
    if(Command2[0]== 'E'){
        return dualProcessDoEncryptFirst(fileName,Command1,Command2);
    }
    else if(Command2[0]== 'D'){
        return dualProcessDoCompressFirst(fileName,Command1,Command2);
    }
    return false;
}
bool Helper::dualProcessDoEncryptFirst(string fileName, string Command1, string Command2){
    EncryptionList *cryptionManager = new EncryptionList();
    CompressionList *compressionManager = new CompressionList();
    FileHandler *fileHandler = new FileHandler();

    if(cryptionManager->checkCryptionFromList(Command2)){
        string cryptoType =cryptionManager->getCryptionType(Command2);
        AppLog::Logger(LOG_FORMAT,"INFO",fileName+" is given for "+cryptoType);

        bool cryptionReadFlag=doCrypto(cryptoType,fileHandler,fileName);
        if(cryptionReadFlag) {
            AppLog::Logger(LOG_FORMAT,"INFO",cryptoType+" is Completed for "+fileName);
        }
        else {
            AppLog::Logger(LOG_FORMAT,"ERROR",cryptoType+" is failed for "+fileHandler->reason());
        }
    }

    if(compressionManager->checkCompressionFromList(Command1)){
        string compressionType =compressionManager->getCompressionType(Command1);
        string compressionName= Command1;
        AppLog::Logger(LOG_FORMAT,"INFO",fileName+" is given for "+compressionType);
        bool CompressionReadFlag= doCompression(compressionType,fileName,compressionName);
        if(CompressionReadFlag){
            AppLog::Logger(LOG_FORMAT,"INFO",compressionType+" is Completed for "+fileName);
            deleteAllEntities(cryptionManager,compressionManager,fileHandler);
            return true;
        }
        else {
            AppLog::Logger(LOG_FORMAT,"ERROR",compressionType+" is failed for "+fileName);
            deleteAllEntities(cryptionManager,compressionManager,fileHandler);
            return false;
        }

    }

    return false;
}

bool Helper::dualProcessDoCompressFirst(string fileName, string Command1, string Command2){
    EncryptionList *cryptionManager = new EncryptionList();
    CompressionList *compressionManager = new CompressionList();
    FileHandler *fileHandler = new FileHandler();

    if(compressionManager->checkCompressionFromList(Command1)){
        string compressionType =compressionManager->getCompressionType(Command1);
        string compressionName= Command1;
        AppLog::Logger(LOG_FORMAT,"INFO",fileName+" is given for "+compressionType);

        bool CompressionReadFlag= doCompression(compressionType,fileName,compressionName);
        if(CompressionReadFlag){
            AppLog::Logger(LOG_FORMAT,"INFO",compressionType+" is given for "+fileName);
        }
        else {
            AppLog::Logger(LOG_FORMAT,"ERROR",compressionType+" is failed for "+fileName);
        }

    }
    if(cryptionManager->checkCryptionFromList(Command2)){
        string cryptoType =cryptionManager->getCryptionType(Command2);
        AppLog::Logger(LOG_FORMAT,"INFO",fileName+" is given for "+cryptoType);
        bool cryptionReadFlag=doCrypto(cryptoType,fileHandler,fileName);
        if(cryptionReadFlag) {
            AppLog::Logger(LOG_FORMAT,"INFO",cryptoType+" is given for "+fileName);
            deleteAllEntities(cryptionManager,compressionManager,fileHandler);
            return true;
        }
        else {
            AppLog::Logger(LOG_FORMAT,"ERROR",cryptoType+" is failed for "+fileHandler->reason());
            deleteAllEntities(cryptionManager,compressionManager,fileHandler);
            return false;
        }
    }
    return false;

}

bool Helper::readFile(string fileName){
    FileHandler *fileHandler = new FileHandler();
    string parseAsCSV =fileName+".csv";
    AppLog::Logger(LOG_FORMAT,"INFO","readFile process started for "+fileName);
    return fileHandler->fileCopy(fileName,parseAsCSV);
}

Helper::~Helper() {
}
