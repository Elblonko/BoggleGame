/*
 * Name: Matthew Schwegler
 * Login: cs100way
 *
 * File: boggleutil.h
 * Desscription: Helper function to the boggle game program 
 *               
 *
 */
#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <stdio.h>
#include <iostream>

using namespace std;

/*********************** BoggleLexicon Class *********************************/

/******************************************************************************
 * Name:        BoggleLexicon
 *
 * Definition:  Create the data structure used to hold and minip
 *              ulate the boggle game lexicon
 *
 *
 *
 ******************************************************************************
 */
class BoggleLexicon {
    //TODO create a better data structure for this field 
    public:
        set<string> lexicon;

        //constructor
        BoggleLexicon(){}

        //destructore
        ~BoggleLexicon(){}
        

/*
 *****************************************************************************************
 * Functin Name:   
 
 * PARAMETERS -     
 *
 * PRECONDITION -  
 * 
 * POSTCONDITION -  
 * 
 *****************************************************************************************
 */   
bool isIn( const string& word_to_check);

/*
 *****************************************************************************************
 * Functin Name:   
 
 * PARAMETERS -     
 *
 * PRECONDITION -  
 * 
 * POSTCONDITION -  
 * 
 *****************************************************************************************
 */   
void insert( string word_to_insert );


};


/****************************** BoggleNode Class *****************************************/

/******************************************************************************
 * Name:        BoggleNode
 *
 * Definition:  Holds the data neccisary to create each sqaure on the boggle
 *              to include pointers to up too 8 other nodes. And contains
 *              the string for that boggle tyle
 *
 *
 *
 ******************************************************************************
 */

class BoggleNode {

    /* Fields of BoggleNode */

    public:

    //Pointers to other nodes
    BoggleNode* up = NULL;
    BoggleNode* down = NULL;
    BoggleNode* left = NULL;
    BoggleNode* right = NULL;
    BoggleNode* dul = NULL;
    BoggleNode* dur = NULL;
    BoggleNode* ddl = NULL;
    BoggleNode* ddr = NULL;

    //holds the string of the node
    string word;

    //Flag to mark if the node has been visited
    bool visited = false;

    //Constructors
    //default
    BoggleNode() : word(0){}
    //set string constructor
    BoggleNode(string set_word) : word(set_word){}

    //Destructor
    ~BoggleNode(){};

};

/************************ BoggleBoard Class *********************************************/

class BoggleBoard {

    /* Fields of the BoggleBoard */

    //multidemensional vector of strings
    vector< vector<BoggleNode*> > board;

    //Store the max and min rows and columns for use later
    unsigned int maxRow = 0;
    unsigned int minRow = 0;
    unsigned int minColumn = 0;
    unsigned int maxColumn = 0;



    //constructor
    BoggleBoard( unsigned int rows, unsigned int columns, string** diceArray){

        //Set values for max

        
        //resize board to fit the rows
        board.resize(rows);
        //now resize the columns for each row
        for(unsigned int i = 0; i < rows; i++)
        {
            board[i].resize(columns);
        }

        //now use the array of arrays to fill the boggleboard
        for(unsigned int i = 0; i < rows; i++)
        {
            for(unsigned int j = 0; j < columns; j++)
            {
                //get string matching the diceArray position
                string curr_string = diceArray[i][j];
                //case the string to lowercase
                transform(curr_string.begin(), curr_string.end(), curr_string.begin(), ::tolower);

                //generate a new BoggleNode
                BoggleNode* node = new BoggleNode(curr_string);
                board[i][j] = node;

            }
        }

        //Now that the board is created, must now set the pointers correctly within each node
        for(unsigned int i = 0; i < rows; i++)
        {
            for(unsigned int j = 0; j < columns; j++)
            {
                //Min Row Case, will have no up pointers
                if ( i == minRow )
                {

                }
                else if ( i == maxRow )
                {

                }
                else
                {
                    // i -1 is up
                    board[i][j]->up = board[ i -1 ][j];
                }

            }
        }


    }



    




};












#endif
