/*
 * Name: Matthew Schwegler
 * Login: cs100way
 *
 * File: boggleutil.cpp
 * Desscription: implements the functions defined in the boggleutil.h
 *               
 *
 */


#include "boggleutil.h"

/*********************BoggleLexicon Class Functions**************************************/

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
void BoggleLexicon::markBuilt(){
    built = true;
}

bool BoggleLexicon::isBuilt(){
    return built;
}

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
bool BoggleLexicon::isIn( const string& word_to_check){

    //iterator to take finds return value
    set<string>::iterator isTrue;

    isTrue = this->lexicon.find(word_to_check);

    if ( isTrue == this->lexicon.end()  )
    {
        return false;
    }
    else
    {
        return true;
    }

} //end search

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
void BoggleLexicon::insert( string word_to_insert ){
    this->lexicon.insert(word_to_insert); 

} //end insert


/********************End of BoggleLexicon Functions**************************************/

/********************Start of BoggleNode Functions**************************************/
/*****************************************************************************************
 * Functin Name:    isVisited() 
 *
 * Description:     Returns true if the nodes visited flag has been set
 *
 * 
 *****************************************************************************************
 */ 
bool BoggleNode::isVisited(){
    if(visited){
        return true;
    }
    else{
        return false;
    }
}


/********************End of Boggle Node Functions******************************************/

/********************BoggleBoard Class Functions******************************************/
/*
 *****************************************************************************************
 * Functin Name: markBuilt() 
 *               isBuilt()
 *
 * Descriptions: MarkBuilt() - Marks the BoggleBoard flag as built
 *               isBuilt() -   Returns true if the BoggleBoard has been built
 *
 *****************************************************************************************
 */   
void BoggleBoard::markBuilt(){
    built = true;
}

bool BoggleBoard::isBuilt(){
    return built;
}
 /*
 *****************************************************************************************
 * Functin Name:     unsigned int getMinRow();
 *                   unsigned int getMaxRow();
 *                   unsigned int getMaxColumn();
 *                   unsigned int getMinColumn();
 *
 * Description:     Getter Methods for the Row and Column Max/Min Fields
 * 
 *****************************************************************************************
 */ 
    unsigned int BoggleBoard::getMinRow(){
        return minRow;
    }
    unsigned int BoggleBoard::getMaxRow(){
        return maxRow;
    }
    unsigned int BoggleBoard::getMaxColumn(){
        return maxColumn;
    }
    unsigned int BoggleBoard::getMinColumn(){
        return minColumn;
    }

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
    BoggleNode* BoggleBoard::getNode(unsigned int row, unsigned int column){

        if( board[row][column] )
        {
        return board[row][column];
        }
        else
        {
            cerr << "BoggleBoard::getNode - The Node requested does not exist" << endl;
        }
    }
/*
 *****************************************************************************************
 * Functin Name:    Constructor

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
void BoggleBoard::setBoard( unsigned int rows, unsigned int columns, string** diceArray){

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

    //call to helper function set points to set the boggleboards pointers
    setPointers(rows, columns);


}//end of constructor

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
void BoggleBoard::setPointers (unsigned int rows, unsigned int columns){

    //Now that the board is created, must now set the pointers correctly within each node
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < columns; j++)
        {
            //Tests to set the correct up and down pointers (rows)
            if ( i == minRow )
            {
                // i - 1 is down
                board[i][j]->down = board[ i - 1 ][j];

                //Set the diagnols
                // i - 1 down j - 1 left
                board[i][j]->ddl = board[ i - 1 ][ j - 1];
                // i - 1 down j + 1 right
                board[i][j]->ddr = board[ i - 1 ][ j + 1];

            }
            else if ( i == maxRow )
            {
                // i + 1 is up
                board[i][j]->up = board[ i + 1 ][j];

                //Set the diagnols
                // i + 1 up j - 1 left
                board[i][j]->dul = board[ i + 1 ][ j - 1];
                // i + 1 up j + 1 right
                board[i][j]->dur = board[ i + 1 ][ j + 1];
            }
            else
            {
                // i + 1 is up
                board[i][j]->up = board[ i + 1 ][j];
                // i - 1 is down
                board[i][j]->down = board[ i - 1 ][j];

                //Set the diagnols
                // i - 1 down j - 1 left
                board[i][j]->ddl = board[ i - 1 ][ j - 1];
                // i - 1 down j + 1 right
                board[i][j]->ddr = board[ i - 1 ][ j + 1];
                // i + 1 up j - 1 left
                board[i][j]->dul = board[ i + 1 ][ j - 1];
                // i + 1 up j + 1 right
                board[i][j]->dur = board[ i + 1 ][ j + 1];
            }

            //Tests to set the correct left and right pointers (columns)
            if ( j == minColumn )
            {
                //j + 1 is right
                board[i][j]->right = board[i][ j + 1 ];

                //Set the diagnols
                //If min Columon no left diagnols
                board[i][j]->ddl = NULL;
                board[i][j]->dul = NULL;
                //other diagnols already set

            }
            else if ( j == maxColumn )
            {
                //j -1 is left
                board[i][j]->left = board[i][ j -1];

                //Set the diagnols
                //If min Columon no right diagnols
                board[i][j]->ddr = NULL;
                board[i][j]->dur = NULL;

            }
            else
            {
                //j + 1 is right
                board[i][j]->right = board[i][ j + 1 ];
                //j -1 is left
                board[i][j]->left = board[i][ j -1];

            }

        }
    }
}

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
void BoggleBoard::getAllValidWords(BoggleNode* node,string curr_word, BoggleLexicon lexicon,
        unsigned int minimum_word_length, set<string>* words)
{
    //Base case for recursion if this node as been visited
    if ( node->isVisited() )
    {
        return;
    }

    //Check the flag to indicate this node has been visited
    node->visited = true;

    //Append the current word with the current nodes word
    curr_word += node->word;

    //check to see if the new word is of min length and in the current lexicon
    if ( curr_word.length() >= minimum_word_length )
    {
        if ( lexicon.isIn(curr_word) )
        {
            words->insert(curr_word);
        }
    }

    //Now do up to 8 recursive calls in clockwise order
    if( ! node->up )
    {
        getAllValidWords(node->up, curr_word, lexicon, minimum_word_length, words);
    }
    if( ! node->dur )
    {
        getAllValidWords(node->dur, curr_word, lexicon, minimum_word_length, words);
    }
    if( ! node->right )
    {
        getAllValidWords(node->right, curr_word, lexicon, minimum_word_length, words);
    }
    if( ! node->ddr )
    {
        getAllValidWords(node->ddr, curr_word, lexicon, minimum_word_length, words);
    }
    if( ! node->down )
    {
        getAllValidWords(node->down, curr_word, lexicon, minimum_word_length, words);
    }
    if( ! node->ddl )
    {
        getAllValidWords(node->ddl, curr_word, lexicon, minimum_word_length, words);
    }
    if( ! node->left )
    {
        getAllValidWords(node->left, curr_word, lexicon, minimum_word_length, words);
    }
    if( ! node->dul )
    {
        getAllValidWords(node->dul, curr_word, lexicon, minimum_word_length, words);
    }

    //after all recursive calls return the visited node back to false
    node->visited = false;
}
