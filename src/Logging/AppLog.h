//
// Created by Sivasubramani on 11/08/21.
//

#ifndef FILEREADERDESIGN_APPLOG_H
#define FILEREADERDESIGN_APPLOG_H
#include <iostream>
using namespace std;

class AppLog {
private:
  int logLevel;

public:
    static bool matchLogLevels(string logLevel);
    static string getCurrentDateTime(string getString);
    static bool Logger( string fileName, int lineNumbber, string logLevel,string logMsg);
};


#endif //FILEREADERDESIGN_APPLOG_H
