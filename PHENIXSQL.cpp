//
//  PHENIXSQL.cpp
//  
//
//  Created by Baranyai David on 2020. 06. 14..
//

#include <stdio.h>
#include <iostream>
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "SQLHandler.hpp"
#include <signal.h>

int running = 1;

void signalHandler(int signum) 
{ 
    running = 0;
}


int main(int argc, char* argv[])
{
    TApplication App("tapp", &argc, argv);

    SQLHandler sqlHandler;
    sqlHandler.QueryDetectors();
    sqlHandler.SelectDetector();
    sqlHandler.QueryDetector();
    sqlHandler.DrawDetectorData();
    
    //App.Run();
    
    while(running)
    {
        gSystem->ProcessEvents();
    }

    return 0;
}
