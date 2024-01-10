/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cell.h
 * Author: 220061867
 *
 * Created on 09 May 2023, 7:22 PM
 */

#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;
int getAdjacentIndex(const int& i);
class cell{
    char marble;
    string location;
    vector<cell*> adjacent;
    vector<int> distanceToEdge;
public:
    cell();
    void setMarble(const char&);
    char getMarble() const;
    void setLocation(const string& lc);
    static bool validateLocation(const string& l);
    string getLocation() const;
    void setAdjacent(cell*,const int&);
    cell* getAdjacent(const int&) const;
    void setDistanceToEdge(const int&);
    int getDistanceToEdge(const int&) const;
    
};


#endif /* CELL_H */

