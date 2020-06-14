//
//  SQLHandler.cpp
//  DB_Track
//
//  Created by Baranyai David on 2020. 06. 14..
//

#include "SQLHandler.hpp"

SQLHandler::SQLHandler()
{
    server = mysql_init(NULL);
    try
    {
        if (!mysql_real_connect(server, "localhost", SQL_USER, SQL_PASSWORD, SQL_DATABASE, 0, NULL, 0))
        {
            throw "Can't connect to the server";
        }
        else
        {
            std::cout << "-----------------------------" << std::endl;
            std::cout << "Successfully connected" << std::endl;
            std::cout << "Host info: " << mysql_get_host_info(server) << std::endl;
            std::cout << "Client info: " << mysql_get_client_info() << std::endl;
            std::cout << "-----------------------------" << std::endl << std::endl;
        }
    } 
    catch (char const* s)
    {
        std::cout << s <<std::endl;
    }
}

SQLHandler::~SQLHandler()
{
    mysql_close(server);
    delete server;
}

void SQLHandler::SelectDetector()
{
    std::cout << "Enter an ID...\n";
    std::string input;
    int id;

    getline(std::cin, input);

    while (true)
    {
        if(!tryParse(input, id))
        {
            std::cout << "Bad entry. Enter a NUMBER: ";
            getline(std::cin, input);
        }
        else if(id < 0 || id >= detectorList.size())
        {  
            std::cout << "Enter a valid number from the list!" << std::endl;
            getline(std::cin, input);
        }
        else
        {
            selected_id = id;
            break;
        }
    }
}

void SQLHandler::QueryDetectors()
{
    std::cout << "Getting detectors list..." << std::endl;
    std::stringstream query;
    unsigned int nRow = 0;
    query << "SELECT detector_table, detector_description FROM detectors;";
    if (!mysql_query(server, query.str().c_str())) //Start query
    {
        MYSQL_RES *result = mysql_store_result(server); //store result
        unsigned int nColumn = mysql_num_fields(result); //store column number
        if (nColumn == 2) //3 oszlop, se több, se kevesebb
        {
            MYSQL_ROW row;
            nRow = mysql_num_rows(result); 
            for(int i = 0; i < nRow; i++)
            {
                row = mysql_fetch_row(result);
                detectorList.push_back(row[0]);
            }
            std::cout << "Detectors:\nID\t|\tName\n";
            for(int j = 0; j < detectorList.size(); j++)
            {
                std::cout << j << "\t|\t" << detectorList[j] << std::endl;
            }
            queryDone = true;
        }
        else
        {
            std::cout << "Column error on QueryDetectors();\n";
        }
    }
}

void SQLHandler::QueryDetector()
{
    if(selected_id >= detectorList.size() || selected_id < 0)
    {
        std::cout << "Detector index error!\n";
        return;
    }
    if(!queryDone)
    {
        std::cout << "Run QueryDetectors() first!\n";
        return;
    }
    std::cout << "Querying detector " << detectorList[selected_id] << "...\n";
    std::stringstream query;
    unsigned int nRow = 0;

    query << "SHOW COLUMNS FROM " << detectorList[selected_id] << ";";
    if (!mysql_query(server, query.str().c_str())) //Start query
    {
        MYSQL_RES *result = mysql_store_result(server); //store result
        unsigned int nColumn = mysql_num_fields(result); //store column number
        if (nColumn > 0) //at least 1
        {
            MYSQL_ROW row;
            nRow = mysql_num_rows(result); 
            for(int i = 0; i < nRow; i++)
            {
                row = mysql_fetch_row(result);
                //column_names.push_back(row[0]);
                histograms.push_back(new TH1D(row[0], row[0], 10000, 0, 500));
            }
        }
        else
        {
            std::cout << "Column error on QueryDetectors() (Column names)\n";
        }
    }
    query.str("");
    query << "SELECT * FROM " << detectorList[selected_id] << ";";
    std::cout << query.str() << std::endl;
    if (!mysql_query(server, query.str().c_str())) //Start query
    {
        MYSQL_RES *result = mysql_store_result(server); //store result
        unsigned int nColumn = mysql_num_fields(result); //store column number
        if (nColumn > 0) //at least 1
        {
            MYSQL_ROW row;
            nRow = mysql_num_rows(result); 
            //std::cout << "Found " << nRow << " rows\n";
            for(int i = 0; i < nRow; i++)
            {
                row = mysql_fetch_row(result);
                for(int j = 0; j < nColumn; j++)
                {
                    //std::cout << atof(row[j]) << ", ";
                    histograms[j]->Fill(atof(row[j]));
                }
                //std::cout << std::endl << std::endl;
            }
        }
        else
        {
            std::cout << "Column error on QueryDetectors() (Fill)\n";
        }
    }
}

void SQLHandler::DrawDetectorData()
{
    std::cout << "Draw histograms...\n";
    for(int j = 0; j < histograms.size(); j++)
    {
        canvases.push_back(new TCanvas(std::to_string(j).c_str(), std::to_string(j).c_str(), 300, 300));
        histograms[j]->Draw();
    }
    std::cout << "Drawing done\n";
}

bool SQLHandler::tryParse(std::string& input, int& output) 
{
    try
    {
        output = std::stoi(input);
    } 
    catch(std::invalid_argument) 
    {
        return false;
    }
    return true;
}
