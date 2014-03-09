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
#include <stack>
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
        bool built = false;

        //constructor
        BoggleLexicon(){}

        //destructore
        ~BoggleLexicon(){}
        
/*
 *****************************************************************************************
 * Functin Name: markBuilt() 
 *               isBuilt()
 *
 * Descriptions: MarkBuilt() - Marks the lexicon flag as built
 *               isBuilt() -   Returns true if the lexicon has been built
 *
 *****************************************************************************************
 */   
void markBuilt();

bool isBuilt();
/*
 *****************************************************************************************
 * Functin Name:   
 *
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
 *
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

    //unsigned integers to hold the row and column location of the node
    unsigned int row;
    unsigned int column;

    //Flag to mark if the node has been visited
    bool visited = false;

    public:
    //Constructors
    //default
    BoggleNode() : word(0){}
    //set string constructor
    BoggleNode(string set_word) : word(set_word){}

 /*
 *****************************************************************************************
 * Functin Name:   
 *
 * PARAMETERS -     
 *
 * PRECONDITION -  
 * 
 * POSTCONDITION -  
 * 
 *****************************************************************************************
 */  
    bool isVisited();

 /*
 *****************************************************************************************
 * Functin Name:   
 *
 * PARAMETERS -     
 *
 * PRECONDITION -  
 * 
 * POSTCONDITION -  
 * 
 *****************************************************************************************
 */  
    unsigned int getColumn();
    unsigned int getRow();

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
    bool built = false;

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
 * Functin Name: markBuilt() 
 *               isBuilt()
 *
 * Descriptions: MarkBuilt() - Marks the lexicon flag as built
 *               isBuilt() -   Returns true if the lexicon has been built
 *
 *****************************************************************************************
 */   
void markBuilt();

bool isBuilt();

 /*****************************************************************************************
 * Functin Name:     unsigned int getMinRow();
 *                   unsigned int getMaxRow();
 *                   unsigned int getMaxColumn();
 *                   unsigned int getMinColumn();
 *
 * Description:     Getter Methods for the Row and Column Max/Min Fields
 * 
 *****************************************************************************************
 */ 
    unsigned int getMinRow();
    unsigned int getMaxRow();
    unsigned int getMaxColumn();
    unsigned int getMinColumn();

 /*
 *****************************************************************************************
 * Functin Name:    getNode
 *
 * PARAMETERS:      Takes in a row and column in that order
 *
 * Description:     Returns the node at the row and column specified
 * 
 *****************************************************************************************
 */ 
    BoggleNode* getNode(unsigned int row, unsigned int column);
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
 * Functin Name:   GetAllValidWords
 *
 * PARAMETERS -    Takes in a pointer to a BoggleNode* to check all possible words from
 *                 node, the curr_word built thus far, a lexicon of valid words, the
 *                 minimium word length accepted and a set of words found so far
 *
 * PRECONDITION -  setBoard and BuildLexicon have been called to make the searches
 *                 possible. all nodes visited fields are set to false
 * 
 * POSTCONDITION - All nodes visited fields are set back to false on return, and the
 *                 set words is filled with all valid words found starting from passed
 *                 in node
 * 
 *****************************************************************************************
 */ 
    void getAllValidWords(BoggleNode* node,string curr_word, BoggleLexicon lexicon,
            unsigned int minimum_word_length, set<string>* words);

/*
 *****************************************************************************************
 * Functin Name:     isOnBoard
 *
 * PARAMETERS -     takes a node to start from and a string to search for  
 *
 * PRECONDITION -   Setboard has been called
 * 
 * POSTCONDITION -  board is unchanged after call
 * 
 *****************************************************************************************
 */  
    void isOnBoard(BoggleNode* node, string curr_word, string const &search_word, bool &isFound, stack<int> &path); 


};












#endif
