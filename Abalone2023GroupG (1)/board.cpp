/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "board.h"
#include <iostream>
#include <iomanip>
void setMarbles(cell* row,const int& rcells,const char& marble,const int& rowAt){ //set state of marbles in board 
  for(int i=0;i<rcells;i++){
     row[i].setMarble(marble);
  }
     if(rcells==8){
        char position[4] = {4,5,6,7};
        for(int k=0; k<4; k++){
           row[position[k]].setMarble('+');
        }
     }
     if(rcells==7){
         char position[3] = {4,5,6};
         for(int k=0; k<3; k++){
           row[position[k]].setMarble('+');
         }
     }
     if(rcells==6){  //row 2 and 5
        if( rowAt ==2){
           char position[2] = {4,5};
           for(int k=0; k<2; k++){
             row[position[k]].setMarble('+');
           }
        }
        if(rowAt==5){
           char position[4] = {2,3,4,5};
           for(int k=0; k<4; k++){
             row[position[k]].setMarble('+');
           }
        }
     }
     //row is 8 and 9 cells add + at position 4,5,6,7,8
     if(rcells==9){
        char position[5] = {4,5,6,7,8};
        for(int k=0; k<5; k++){
           row[position[k]].setMarble('+');
        }
     }
     //row 3 
     if(rowAt==3 && rcells==5){
         char position[3] = {2,3,4};
         for(int k=0; k<3; k++){
           row[position[k]].setMarble('+');
         }
      }   
  
}

void connectHorizontal(cell* row, int rcells){
 for(int i=0;i< rcells-1;i++){
  row[i].setAdjacent(row+i+1,1);
 }
}

//connect diagonally
void connectDiagonal(cell* row,cell* pRow,const int& rcells){
   for(int i=0;i<8;i++){
       for(int k=0;k<rcells;k++){
         row[k].setAdjacent(pRow,2);
         row[k].setAdjacent(pRow,3);
       }
   }
}



void mapCells(cell* row ,map<string,cell*>& cm,const char& cellLocation,const int& rcells){
   int f;
   if(cellLocation>='A' && cellLocation<='E'){
      f = 5;
    }else if(cellLocation>='F' && cellLocation<='I'){
       f= cellLocation-'F'+6;
    }
    for(int i=0;i<rcells;i++){
      stringstream ss;
      if(cellLocation=='A' && i>4){
        for(int k=0;k<3;k++){
          f = 13;
        }
      }
      if(cellLocation=='B' && i>4){
        for(int k=1;k<3;k++){
          f = 12;
        }
      }
      if(cellLocation=='C' && i>4){
         f = 11;
      }
      ss<<cellLocation;
      ss<<(f-i);
      string lc = ss.str();
      row[i].setLocation(lc);
      cm[lc] = row+i;
    }
}
map<string,cell*> board::getCells() const{
    return cells;
}

board::board(){ //making the board 
char clc = 'A';
  for(int i=0;i<9;i++){
   //Top part of the board 
     if(i<4){
       rows.push_back(new cell[8-i]); //rowsVector add( a 8-rowNumber cells)
       connectHorizontal(rows[i],8-i);
       mapCells(rows[i],cells,clc++,8-i);
       setMarbles(rows[i],8-i,'O',i);
      }
     if(i==4){  //innermost row 
       rows.push_back(new cell[8-i+1]);
       connectHorizontal(rows[i],8-i+1);
       mapCells(rows[i],cells,clc++,8-i+1);
       setMarbles(rows[i],8-i+1,'+',i);
     }
     //bottom part of the board
     else if(i>4){
       rows.push_back(new cell[i+1]); //add cells to the row
       connectHorizontal(rows[i],i+1);
       mapCells(rows[i],cells,clc++,i+1);
       setMarbles(rows[i],i+1,'@',i);   //set Marbles of each row 
       //setMarbles(rowNumber,numberOfCells,Marble,RowIndex)
      }
  }
  for(int i=0;i<8;i++){
        /*
        connectDiagonal(current row , next row ,cells in the current row )
        */
        connectDiagonal(rows[i],rows[i+1],8-i);
        connectDiagonal(rows[i],rows[i+1],8-i);
   }
   
   cell* linep=rows[0];
    while(linep!= nullptr){
        cell* cellp=linep;
        while(cellp!=nullptr){
           for(int i=0;i<6;i++){
               //setDistanceToEdge(cellp,i);
               cellp->setDistanceToEdge(i);
           }
            cellp=cellp->getAdjacent(1);
                
        }
        if(linep->getAdjacent(3)==nullptr)
            linep=linep->getAdjacent(2);
        else
            linep=linep->getAdjacent(3);

    }
}

board::board(const board& b): board(){ //board Copy constructor
    woc = b.woc;
    boc = b.boc;
    map<string,cell*>::const_iterator it = b.cells.begin();
    while(it!=b.cells.end()){
        (cells[it->first])->setMarble((*(it->second)).getMarble());
        it++;
    }
}

board::~board(){ //board destructor
    for(int i=0;i<9;i++){
        delete[] rows[i];
        rows[i]=nullptr;
    }
    cells.clear();
}
board::operator std::string() const{
   stringstream ss;
   char z = 'A';
   int d=9;
   ss<<"Woc="<<woc<<" Boc="<<boc<<endl;
   for (int i =0;i<9;i++){
      if(i<4){
         ss<<setw(i+2)<<z<<(" "); 
         for(int k=0;k<8-i;k++){
                ss << rows[i][k].getMarble() << " ";
        }
         ss<<endl;
         z++;
      }else if(i==4){
          ss<<setw(i+2)<<z<<(" "); 
         for(int k=0;k<5;k++){
                ss << rows[i][k].getMarble() << " ";
        }
         ss<<endl;
         z++;
      }
      else if(i>=5){
        ss<<setw(8-i+2)<<z<<(" ");
        for(int k=0;k<i+1;k++){
           if (rows[i][k].getMarble() == '+' || rows[i][k].getMarble() == '@') {
                ss << rows[i][k].getMarble() << " ";
            }   
          }
         ss<<endl;
         z++;
      }

   }
   ss<<setw(5)<<d--<<" ";
   for(;d>0;d--)
      ss<<d<<" ";
   ss<<endl;
   return ss.str();
}


string traverse(const cell* start,const int& pd,const int& sd,const int& td){
    string ts;
    const cell* linep = start;
    while(linep!=nullptr){
        const cell* cellp = linep;
        while(cellp!=nullptr){
            ts+=(cellp->getLocation()+' ');
            cellp=cellp->getAdjacent(td);
        }
        if(linep->getAdjacent(pd)==nullptr)
            linep=linep->getAdjacent(sd);
        else
            linep=linep->getAdjacent(pd);
    }
    return ts;
}

string board::traverseHorizontal() const{
    map<string,cell*>::const_iterator it = cells.find(string("I9"));
    cell* start = it->second;
    return traverse(start,0,5,1);
} 
string board::traverseDiagonal() const{
    map<string,cell*>::const_iterator it = cells.find(string("A5"));
    cell* start = it->second;
    return traverse(start,2,3,1);
}

/*void pushMarble(marble , location){
   check if location of marble at md is in edge board

   rows[0] edge  (5+i) makes a row  ; i=0
   from Row D to  A 
   row[n-1] edge location  
}*/


bool board::inPlay() const{
    if((woc<6) && (boc<6))
        return true;
    return false;
}


void board::refreshOffboardCounts(){
    int wOnBoard = 0;
    int bOnBoard = 0;
    
    map<string,cell*>::const_iterator it = cells.begin();
    while(it!= cells.end()){
        if((cells[it->first])->getMarble() == 'O'){
            wOnBoard++;
        }
        if((cells[it->first])->getMarble() == '@'){
            bOnBoard++;
        }
        it++;
    }
    
    woc = 14 - wOnBoard;
    boc = 14 - bOnBoard;
}

bool board::validateMove(const char& m,const string& l,const int& n, const int& fd, const int& md, int& mtype, bool& scoreMove) const{  
    if( !cell::validateLocation(l))  
       return false;
    else{   
    cell* cp = cells.at(l);//initialize to leading cell
    const char marble = cp->getMarble();
        if(marble!=m)//trying to move a space or a marble that is not yours
            return false;
        for(int i=1;i<n;i++){
            cp=cp->getAdjacent(fd);
            if(cp==nullptr || marble!=cp->getMarble())//confirm availability and type of claimed resources
                return false;
        }
        if(fd==getAdjacentIndex(md)){//in-line move
            cp = cells.at(l);//initialize to leading cell
            mtype=0;//how many opponent marbles are in front of the leading marble i.e in the move direction
            for(int i=0;i<n;i++){
                cp=cp->getAdjacent(md);
                if(cp!=nullptr){//confirm availability of required resources
                    if(marble==cp->getMarble())//met own marble instead of space
                        return false;
                    if('+'!=cp->getMarble())//if it belongs to opponent
                        mtype++;//count opponent marbles
                    else
                        break;
                }
                else{
                    if(mtype>0)//opponent's marble will be pushed off the board
                        scoreMove=true;
                    else//if trying to push your own marble off the board
                        return false;
                    break;
                }
            }
            if(mtype>=n)//should only push fewer than n of the opponent's marbles
                return false;
        }
        else{//broad-side move
            mtype=-1;
            if(n<=1)//broad-side move must use at least 2 marbles
                return false;
            cp = cells.at(l);
            for(int i=0;i<n;i++){
                cell* dp=cp->getAdjacent(md);//destination pointer
                if(dp!=nullptr && '+' == dp->getMarble())//is there an empty space to move to?
                    cp=cp->getAdjacent(fd);
                else
                    return false;
            }
        }
        return true;
    }
}

bool board::executeMove(const char& m,const string& l,const int& n, const int& fd, const int& md){
   int moveType = 0;//default to in-line with no following marbles
    bool scoreMove = false;
    bool valid = validateMove(m,l,n,fd,md,moveType,scoreMove);
    if(valid){
        if(moveType==-1){//broad-side
            if(cells.find(l)==cells.end()) return false;
            cell* cp = cells.at(l);
            for(int i=0;i<n;i++){
                if(cp==nullptr) return false;
                cell* dp=cp->getAdjacent(md);//destination pointer
                if(dp==nullptr) return false;
                dp->setMarble(cp->getMarble());
                cp->setMarble('+');
                cp=cp->getAdjacent(fd); 
            }
        }
        else{//in-line
            cell* cp = cells.at(l), *rearp=cp;
            const char marble = cp->getMarble();
            cell* frontp=cp->getAdjacent(md);
            for(int i=1;i<n;i++){
                rearp=rearp->getAdjacent(fd);
            }
            if(scoreMove){                
                frontp->setMarble(rearp->getMarble());
                rearp->setMarble('+');
                if(marble=='O')
                    boc++;
                if(marble=='@')
                    woc++;
            }
            else{
                cell* tipp = frontp;
                for(int i=0;i<moveType;i++){
                    tipp=tipp->getAdjacent(md);//looking for empty space
                }
                if(moveType!=0)//tipp is already equal to frontp
                    tipp->setMarble(frontp->getMarble());
                frontp->setMarble(rearp->getMarble());
                rearp->setMarble('+');
            }
        }
    }
    return valid;
}

