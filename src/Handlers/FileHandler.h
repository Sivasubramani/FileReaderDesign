//
// Created by Sivasubramani on 08/08/21.
//

#ifndef FILEREADERDESIGN_FILEHANDLER_H
#define FILEREADERDESIGN_FILEHANDLER_H

#include "../Common/CommonFiles.h"
#include <locale>
#include <codecvt>
#include "../AESCryption/AES.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>

#include "../Logging/AppLog.h"

using namespace std;
typedef bitset<8> byte;
typedef bitset<32> word;

class FileHandler: public AES{
private:
    fstream inFile;
    fstream outFile;
    fstream decFile;
    fstream encFile;
    string utfConversion(string utf8);
    AES *aesCryption;
    string failure_reason;

public:
    FileHandler();
    ~FileHandler();

    bool decryption(string basicString,string targetFile);

    bool encryption(string basicString,string targetFile);

    string reason();

    bool fileCopy(string sourceFile, string targetFile);

    bool encrypt(string sourceFile);

    bool decrypt(string sourceFile);
};


#endif //FILEREADERDESIGN_FILEHANDLER_H
