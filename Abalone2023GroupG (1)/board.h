/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   board.h
 * Author: 220061867
 *
 * Created on 09 May 2023, 7:23 PM
 */

#ifndef BOARD_H
#define BOARD_H
#include "cell.h"
#include <string>
#include <map>
#include <sstream>
using namespace std;

class board{
    vector<cell*> rows;
    map<string,cell*> cells;
    int woc;//white marbles off the board count.
    int boc;//black marbles off the board count.
public:
    board();//create 61 cells on the heap, and connect them.
    ~board();//recycle 61 cells.
    operator std::string() const;//cast this object into a string.
    string traverseHorizontal() const;
    string traverseDiagonal() const;
    map<string,cell*> getCells() const;
    board(const board&);
    bool inPlay() const;
    void refreshOffboardCounts();
    bool validateMove(const char& m,const string& l,const int& n, const int& fd, const int& md,int& mtype,bool& scoreMove) const;
    bool executeMove(const char& m,const string& l,const int& n, const int& fd, const int& md);
};


#endif /* BOARD_H */

