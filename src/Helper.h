//
// Created by Sivasubramani on 10/08/21.
//

#ifndef FILEREADERDESIGN_HELPER_H
#define FILEREADERDESIGN_HELPER_H
#include "Common/CommonFiles.h"
#include "Handlers/FileHandler.h"
#include "Compression/Bzip2Compression.h"
#include "Compression/GzipCompression.h"
#include "EnumList/EncryptionList.h"
#include "EnumList/CompressionList.h"
#include "Handlers/FileHandler.h"
class Helper {
    string resultOfCryption(bool encReadFlag, string cryptionFormat);
    bool Bzip2Compress(string filename);
    bool Bzip2Decompress(string filename);
    bool GzipCompress(string filename);
    bool GzipDecompress(string filename);

public:
    Helper();
    ~Helper();


    bool doCrypto(string cryptoType, FileHandler *fileHandler, string fileName);

    bool doCompression(string cryptoType, string fileName,string compressionName);

    bool singleprocess(string fileName, string Command);

    void deleteAllEntities(EncryptionList *cryptionManager, CompressionList *compressionManager, FileHandler *fileHandler);

    bool dualProcessDoEncryptFirst(string fileName, string Command1, string Command2);

    bool dualProcessDoCompressFirst(string fileName, string Command1, string Command2);

    bool dualProcess(string fileName, string Command1, string Command2);

    bool readFile(string fileName);
};


#endif //FILEREADERDESIGN_HELPER_H
