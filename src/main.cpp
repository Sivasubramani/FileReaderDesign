#include <codecvt>
#include <fstream>
#include <iostream>
#include "Helper.h"
#include "Common/CommonFiles.h"

int main(int argc, char** argv) {
    Helper *helper =new Helper();
    bool execution =false;
    AppLog::Logger(LOG_FORMAT,"INFO","Received "+ to_string(argc)+ " arguments from Command Line:");

    for (int i = 0; i < argc; ++i)
        AppLog::Logger(LOG_FORMAT,"INFO",argv[i]);

    if(argc <= 1) {
        cout << "Null arguments passed so returning appilcation"<<"\n";
        AppLog::Logger(LOG_FORMAT,"INFO","Null arguments passed so returning appilcation");
        return 0;
    }
    string fileName =argv[1];

    if(argc == 2){
        AppLog::Logger(LOG_FORMAT,"INFO","Only Read process called for "+fileName);
        execution = helper->readFile(fileName);
    }

    if(argc == 3){
         AppLog::Logger(LOG_FORMAT,"INFO","Cryption or Compression command called for "+fileName);
         execution = helper->singleprocess(fileName,argv[2])  ;
         if(argv[2][0] =='D') execution = helper->readFile(fileName);

    }

    else if(argc == 4){
        AppLog::Logger(LOG_FORMAT,"INFO","Cryption and Compression command called for "+fileName);
        execution = helper->dualProcess(fileName,argv[2],argv[3]);
        if(argv[3][0] =='D') execution = helper->readFile(fileName);
    }

    AppLog::Logger(LOG_FORMAT,"INFO",execution== true? "Generic File Reader "+fileName+ " is Success" : "Invalid Command");

    string result = execution == true ? "Success\n" : "Failed\n";
    cout<<"Execution is "<<result<<"\n";
    delete(helper);
    return 0;
}


