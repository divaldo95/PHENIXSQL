//
//  SQLHandler.hpp
//  DB_Track
//
//  Created by Baranyai David on 2020. 06. 14..
//

#ifndef SQLHandler_hpp
#define SQLHandler_hpp

#include <stdio.h>
#include <iostream>
#include <mysql.h>
#include <vector>
#include <sstream>
#include <string>
#include "TH1D.h"
#include "TCanvas.h"
#include "CommonData.hpp"

class SQLHandler
{
public:
    SQLHandler();
    ~SQLHandler();

    void QueryDetectors();
    void SelectDetector();
    void QueryDetector();
    void DrawDetectorData();
    bool tryParse(std::string&, int&);
private:
    std::vector<std::string> detectorList;

    MYSQL *server;

    bool queryDone = false;

    std::vector<TH1D*> histograms;
    std::vector<TCanvas*> canvases;

    int selected_id = 0;
};

#endif /* SQLHandler_hpp */
