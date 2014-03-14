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
#include <utility>
#include <stdio.h>
#include <iostream>

using namespace std;

/*********************** BoggleLexiconNode Class ***************************************/

/****************************************************************************************
 * Name:        BoggleLexiconNode Class
 *
 * Definition:  Create the data structure used to hold and minip
 *              ulate the boggle game lexicon
 *
 ****************************************************************************************
 */

class BoggleLexiconNode {

    //declares friend class
    friend class BoggleLexicon;

    /****CLASS FIELDS****/

    private:
    //3 poitners to other nodes
    BoggleLexiconNode *less;
    BoggleLexiconNode *greater;
    BoggleLexiconNode *equal;

    //Flag if this node signifies a word
    bool isaWord;

    //character the node holds
    char character;

    public:

    //default constructor
    BoggleLexiconNode();

    //constructor taking a character
    BoggleLexiconNode(char insert);

    //destructor
    ~BoggleLexiconNode();

    /*
     *****************************************************************************************
     * Functin Name:    isWord 
     *
     * RETURN VALUE:    Returns True if the Node symbolizes a word in the tree, else false
     * 
     *****************************************************************************************
     */
    bool isWord();

}; //end of BoggleLexiconNode Class

/******************************** End of BoggleLexiconNode Class ***********************/

/********************************* BoggleLexicon Class *********************************/


/****************************************************************************************
 * Name:        BoggleLexicon
 *
 * Definition:  Create the data structure used to hold and minip
 *              ulate the boggle game lexicon
 *
 ****************************************************************************************
 */
class BoggleLexicon {
    //TODO create a better data structure for this field 
    private:

        //root of the ternary trie
        BoggleLexiconNode *root;

        //Flag to signify Lexicon has been built
        bool built;

        //A helper method for the insert function
        BoggleLexiconNode* insertWholeWord(BoggleLexiconNode *&tempNode, string &word_to_insert);

    public:
        //constructor
        BoggleLexicon();

        //destructore
        ~BoggleLexicon();

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
         * Functin Name:    pair<bool,bool> isIn( const string& word_to_check);
         *
         * PARAMETERS -     Takes a reference fo a string to check
         *
         * PRECONDITION -   The lexicon is built prior to this call
         * 
         * POSTCONDITION -  if the word is in the lexicon return true,false pair
         *                  if the words prefix is in the lexicon returns tre,true pair
         *
         * RETURN VALUE -   returns a pair.
         *                  First bool - true if valid prefix
         *                  Second bool - true if valid word
         * 
         *****************************************************************************************
         */   
        pair<bool,bool> isIn( const string& word_to_check);

        /*
         *****************************************************************************************
         * Functin Name:   void insert( string word_to_insert );
         *
         * PARAMETERS -    Takes a word to insert into the lexicon 
         * 
         * POSTCONDITION -  The string passed in is added to the lexicon trie
         * 
         *****************************************************************************************
         */   
        void insert( string word_to_insert );


}; //End of BoggleLexicon Class


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
    BoggleNode* up;
    BoggleNode* down;
    BoggleNode* left;
    BoggleNode* right;
    BoggleNode* dul;
    BoggleNode* dur;
    BoggleNode* ddl;
    BoggleNode* ddr;

    //holds the string of the node
    string word;

    //unsigned integers to hold the row and column location of the node
    unsigned int row;
    unsigned int column;

    //Flag to mark if the node has been visited
    bool visited = false;

    public:
    //default
    BoggleNode() : word(0){}
    //set string constructor
    BoggleNode(string set_word);

    //Destructor
    ~BoggleNode();


    /*
     * ***************************************************************************************
     * Functin Name:    isVisited() 
     *
     * Description:     Returns true if the nodes visited flag has been set
     *
     * 
     *****************************************************************************************
     */ 
    bool isVisited();

    /*
     *****************************************************************************************
     * Functin Name:    unsigned int getColumn();
     *                  unsigned int getRow();
     *
     * POSTCONDITION -  Returns the column and row location of the node, nothing is changed
     * 
     *****************************************************************************************
     */  
    unsigned int getColumn();
    unsigned int getRow();


};

/************************ BoggleBoard Class *********************************************/

class BoggleBoard {
    private:
        /* Fields of the BoggleBoard */

        //multidemensional vector of strings
        vector< vector<BoggleNode*> > board;

        //Store the max and min rows and columns for use later
        unsigned int maxRow;
        unsigned int minRow;
        unsigned int minColumn;
        unsigned int maxColumn;
        bool built;

    public:
        //Constructor
        BoggleBoard();

        //Destructor
        ~BoggleBoard();

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
        void getAllValidWords(BoggleNode* node,string curr_word, BoggleLexicon &lexicon,
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
