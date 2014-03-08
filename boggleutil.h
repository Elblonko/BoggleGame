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

    //friends class for private data access
    friend class BoggleBoard;

    /* Fields of BoggleNode */

    private:

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

    public:
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
    private:
    /* Fields of the BoggleBoard */

    //multidemensional vector of strings
    vector< vector<BoggleNode*> > board;

    //Store the max and min rows and columns for use later
    unsigned int maxRow = 0;
    unsigned int minRow = 0;
    unsigned int minColumn = 0;
    unsigned int maxColumn = 0;

    /*
 *****************************************************************************************
 * Functin Name:     setPointers 
 
 * PARAMETERS -      Takes in the rows and columns of the current boggle board, then uses
 *                   the boggleboard fields to determine how the pointers in the grid
 *                   should be set
 *
 * PRECONDITION -    Function is called form the BoggleBoard Constructor after the Nodes
 *                   have been correctly placed in the grid
 * 
 * POSTCONDITION -  All nodes in the grid have correctly set up pointers to adjacent boggle
 *                  tiles
 * 
 *****************************************************************************************
 */   
    void setPointers(unsigned int rows, unsigned int columns);

    public:
    
    //Constructor
    BoggleBoard(){};
 /*
 *****************************************************************************************
 * Functin Name:    setBoard
 *
 * PARAMETERS -     Takes the rows, columns and the string array needed to create the
 *                  boggle game board
 *
 * PRECONDITION -   The string array passed in is valid and row major
 * 
 * POSTCONDITION -  The boggle game board is created with all proper pointers set in each
 *                  node of the board with the proper string stored.
 * 
 *****************************************************************************************
 */      
    void setBoard( unsigned int rows, unsigned int columns, string** diceArray);
    
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

    void isOnBoard(BoggleNode* node,string curr_word, BoggleLexicon lexicon,
            unsigned int minimum_word_length, set<string>* words);

};












#endif
