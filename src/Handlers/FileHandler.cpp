//
// Created by Sivasubramani on 08/08/21.
//

#include "FileHandler.h"


FileHandler::FileHandler() {
    aesCryption= new AES(128);

}

bool FileHandler::fileCopy(string sourceFile,string targetFile)
{
    fstream inputFile;
    fstream outputFile;
    char ch;
    unsigned char in[128+1];

    inputFile.open(sourceFile);
    outputFile.open(targetFile,ios::out);

    if(!inputFile) {
        AppLog::Logger(LOG_FORMAT,"ERROR","Not able to open Input File");
        return false;
    }
    if(!outputFile){
        AppLog::Logger(LOG_FORMAT,"ERROR","Not able to open Output File");
        return false;
    }

    int i=0;
    while (inputFile.get(ch)) {
        if(i==128){
            outputFile.write((char *) &in[0], 128);
            i=0;
        }
        in[i++]=ch;
    }
    if(i>0){
        in[i]='\0';
        outputFile.write((char *) &in[0], i);
        i=0;
    }

    inputFile.seekg(0, ios::beg);
    inputFile.close();
    outputFile.close();
    return true;
}

bool FileHandler::encrypt(string sourceFile){
    string bufferFile = sourceFile+".enc.txt";
    if(!fileCopy(sourceFile,bufferFile)) {
        AppLog::Logger(LOG_FORMAT,"ERROR","File copy is failed in Encrypt function");
        return false;
    }
    if(!encryption(bufferFile,sourceFile)){
        AppLog::Logger(LOG_FORMAT,"ERROR","Encryption is failed in Encrypt function");
        return false;
    }
        AppLog::Logger(LOG_FORMAT,"INFO","Encryption is success for file:"+sourceFile+" and buffer file used is "+bufferFile);
    return true;
}
bool FileHandler::encryption(string sourceFile,string targetFile){
    fstream inputFile;
    fstream outputFile;
    char ch;
    unsigned char in[128+1];

    inputFile.open(sourceFile);
    outputFile.open(targetFile,ios::out);

    if(!inputFile) {
        failure_reason ="Not able to open Input File in encryption\n";
        AppLog::Logger(LOG_FORMAT,"ERROR",failure_reason);
        return false;
    }
    if(!outputFile){
        failure_reason="Not able to open Output File in encryption\n";
        AppLog::Logger(LOG_FORMAT,"ERROR",failure_reason);
        return false;
    }

    int i=0;
    while (inputFile.get(ch)) {
        if(i==128){
            unsigned int outLen=0;
            unsigned char *enc = aesCryption->EncryptECB(in, i, aesCryption->key, outLen);
            enc[128]='\0';
            outputFile.write((char *) &enc[0], 128);
            i=0;
        }
        in[i++]=ch;
    }

    if(i>0){
        unsigned int outLen=0;
        unsigned char *enc = aesCryption->EncryptECB(in, i, aesCryption->key, outLen);
        int l=strlen((const char *)enc);
        enc[l]='\0';
        outputFile.write((char *) &enc[0], l);
        i=0;
    }

    inputFile.seekg(0, ios::beg);
    inputFile.close();
    outputFile.close();
    AppLog::Logger(LOG_FORMAT,"INFO","Encryption function passed success");
    return true;
}

bool FileHandler::decrypt(string sourceFile){
    string bufferFile = sourceFile+".dec.txt";
    if(!fileCopy(sourceFile,bufferFile)) {
        failure_reason = "File copy is failed in Encrypt function\n";
        AppLog::Logger(LOG_FORMAT,"ERROR","File copy is failed in Encrypt function");
        cout<<"File copy is failed in Encrypt function\n";
        return false;
    }
    if(!decryption(bufferFile,sourceFile)){
        failure_reason = "Encryption is failed in Encrypt function\n";
        AppLog::Logger(LOG_FORMAT,"ERROR","Encryption is failed in Encrypt function");
        return false;
    }
    AppLog::Logger(LOG_FORMAT,"INFO","Encryption is success for file:" +sourceFile+ " and buffer file used is " + bufferFile);
    return true;
}
bool FileHandler::decryption(string sourceFile,string targetFile){
    fstream inputFile;
    fstream outputFile;
    char ch;
    unsigned char in[128+1];

    inputFile.open(sourceFile);
    outputFile.open(targetFile,ios::out);

    if(!inputFile) {
        failure_reason = "Not able to open Input File in encryption\n";
        AppLog::Logger(LOG_FORMAT,"ERROR",failure_reason);
        return false;
    }
    if(!outputFile){
        failure_reason = "Not able to open Output File in encryption\n";
        AppLog::Logger(LOG_FORMAT,"ERROR",failure_reason);
        return false;
    }

    int i=0;
    while(inputFile.get(ch)) {
        if(i==128){
            in[128]='\0';
            unsigned char *dec = aesCryption->DecryptECB(in, i, aesCryption->key);
            outputFile.write((char *) &dec[0], 128);
            i=0;
        }
        in[i++]=ch;
    }
    if(i>0){
        unsigned int outLen=0;
        unsigned char *dec = aesCryption->DecryptECB(in, i, aesCryption->key);
        int l=strlen((const char *)dec);
        cout<<"\nsize: "<<l<<endl;
        dec[l]='\0';
        outputFile.write((char *) &dec[0], l);
        i=0;
    }

    inputFile.seekg(0, ios::beg);
    inputFile.close();
    outputFile.close();
    AppLog::Logger(LOG_FORMAT,"INFO","Decryption function passed success");
    return true;
}



string FileHandler::reason(){
    return failure_reason;
}
string FileHandler::utfConversion(string utf8){
    string output;
    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
    u16string utf16 = utf16conv.from_bytes(utf8);
    AppLog::Logger(LOG_FORMAT,"INFO","UTF16 conversion produced "+ to_string(utf16.size())+ " code units");
//    cout << "UTF16 conversion produced " << utf16.size() << " code units:\n";
    vector<char16_t> cc;

    for (char16_t c : utf16){
//        std::cout << std::hex << std::showbase << c;
        output+=to_string(c);
    }
    AppLog::Logger(LOG_FORMAT,"INFO","utfConversion output:"+output);
    return output;
}

FileHandler::~FileHandler() {
    delete(aesCryption);
}
