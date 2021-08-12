//
// Created by Sivasubramani on 11/08/21.
//

#include <fstream>
#include "AppLog.h"

string AppLog::getCurrentDateTime(string getString){
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    if(getString=="now"){
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return string(buf);
    }
    else if(getString=="date"){
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
        return string(buf);
    }
    return "";
}

bool AppLog::matchLogLevels(string logLevel){
    if(logLevel == "INFO" || logLevel == "WARNING" || logLevel == "ERROR" || logLevel == "CRITICAL" || logLevel == "DEBUG" )
        return true;
    return false;
}
bool AppLog::Logger(string fileName,int lineNumber,string logLevel,string logMsg){

    if(fileName.empty() || logMsg.empty()) return false;
    if(lineNumber < 1) return false;
    if(!matchLogLevels(logLevel)) return false;

    string filePath = "./logs/FileReader_"+getCurrentDateTime("date")+".log";
    string now = getCurrentDateTime("now");
    ofstream logFile(filePath.c_str(), std::ios_base::out | std::ios_base::app );
    if(!logFile) {
        cout<<"Log file not able to open\n";
        return false;
    }
    string linuNumberCasted =to_string(lineNumber);
    logFile << now << '\t' <<fileName<<":"<<lineNumber<<" ["+logLevel+"]"<<" "<<logMsg << '\n';
    logFile.close();
    return true;
}