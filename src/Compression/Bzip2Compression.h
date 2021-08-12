//
// Created by Sivasubramani on 10/08/21.
//

#ifndef FILEREADERDESIGN_BZIP2COMPRESSION_H
#define FILEREADERDESIGN_BZIP2COMPRESSION_H

#include "BoostHeaders.h"
#include <boost/iostreams/filter/bzip2.hpp>

class Bzip2Compression {

public:
    Bzip2Compression();
    ~Bzip2Compression();

    string getDecompressName(string sourceFile, string eraseCompressCode);
    string decompress(string sourceFile);

    string getCompressName(string sourceFile, string addCompressCode);
    string compress(string sourceFile);
};


#endif //FILEREADERDESIGN_BZIP2COMPRESSION_H
