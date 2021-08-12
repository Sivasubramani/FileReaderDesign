//
// Created by Sivasubramani on 10/08/21.
//

#ifndef FILEREADERDESIGN_GZIPCOMPRESSION_H
#define FILEREADERDESIGN_GZIPCOMPRESSION_H
#include "BoostHeaders.h"
#include <boost/iostreams/filter/gzip.hpp>

class GzipCompression {
public:
    GzipCompression();
    ~GzipCompression();
    string getDecompressName(string sourceFile, string eraseCompressCode);
    string decompress(string sourceFile);

    string getCompressName(string sourceFile, string addCompressCode);
    string compress(string sourceFile);
};


#endif //FILEREADERDESIGN_GZIPCOMPRESSION_H
