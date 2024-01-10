/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: 220061867
 *
 * Created on 09 May 2023, 7:22 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include "board.h"
#include "agent.h"

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    /*board abalone;
    string da(abalone);
    cout<<"Display Abalone Board:"<<endl;
    cout<<da;    
    cout<<"Traverse NW-SE Diagonally From A5:"<<endl;
    cout<<abalone.traverseDiagonal()<<endl;
    cout<<"Traverse W-E Horizontally From :"<<endl;
    cout<<abalone.traverseHorizontal()<<endl;
    char marble;  string lc ; 
    
    
    */
   time_t now = time(NULL);
        srand(now);
        cout<<"Seed: "<<now<<endl;
        board abalone;
        string state(abalone);
        cout<<"Initial State:"<<endl<<state;
        agent* w = new randAgent('O');
        agent* b = new distAgent('@');
        movement* pom=nullptr;//previous opponent's move
        movement* mym=nullptr;//player's chosen move
        char c='O';
        
         for(int i=0;i<200;i++){
            try{
                if(c=='O'){
                    movement mm = w->move(pom,abalone);
                    mym = new movement(mm);
                    if(pom)
                        delete pom;
                    pom = new movement(mm);

                }
                else{
                    movement mm = b->move(pom,abalone);
                    mym = new movement(mm);
                    if(pom)
                        delete pom;
                    pom = new movement(mm);
                }
            }
             catch(const string& s){
                cout<<s;
                return 1;
            }        
            bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
            cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
            if(valid){
                string state(abalone);         
                cout<<"Next State:"<<endl<<state; 
            }
            else{
                cout<<"Invalid move!!"<<endl;
            }
            if(c=='O') 
                c='@';
            else
                c='O'; 
            delete mym;
            SLP(1);
            //system(CL);
        }
        if(pom)
            delete pom;
        delete w;
        delete b;

    return 0;
}

