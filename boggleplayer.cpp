/*
 * Name: Matthew Schwegler
 * Login: cs100way
 *
 * File: boggleplayer.cpp
 * Desscription: Implements the functions defined in boggleplayer.h
 *
 */

#include "boggleplayer.h"

using namespace std;


/*
 *********************************************************************************************************
 * Constructor
 *********************************************************************************************************
 */

BogglePlayer::BogglePlayer(){
}

/*
 *********************************************************************************************************
 * Destructor
 *********************************************************************************************************
 */

BogglePlayer::~BogglePlayer(){
    
}


/*
 *********************************************************************************************************
 * Functions Name:   void buildLexicon(const vector<string>& word_list);
 *
 * PARAMETERS - takes a vector of strings that will comprise the lexicon for
 *              the boggle game
 *
 * PRECONDITION - Is passed a valid vector of strings
 *
 * POSTCONDITION - A data structure that stores the strings is built for easy
 *                 lookup
 *********************************************************************************************************
 */

void BogglePlayer::buildLexicon(const vector<string>& word_list){

    //Check if the passed list has words
    if( word_list.empty())
    {
        cerr << "buildLexicon:: The passed in string is empty" << endl;
       //return from function
       return;
    }

    //Create the map to be filled and the 
    //set<string> lexicon;
    for(unsigned int i = 0; i < word_list.size(); i++)
    {
        string key = word_list[i];
        lexicon.insert(key);
    }

    //mark lexicon as built
    lexicon.markBuilt();


  } //end of buildLexicon

/*
 *********************************************************************************************************
 * Function Name:    void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
 *
 * PARAMETERS -    takes in number of rows and columns to create a boggle board of any rectangular size
 *                 the diceArray is an array of arrays representing the strings to be placed on the baord
 *
 * PRECONDITION -  Rows > 0, Cols > 0, The diceArray contains only those words that will
 *                 correctly fit in the given demensions of the board
 *
 * POSTCONDITION - A rectangular board is constructed of height = #rows width = #cols
 *                 this board is then filled with lowercase letters a-z in the
 *                 correct spaces
 *********************************************************************************************************
 */
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray){
    

    //calls function to set the board object up
    board.setBoard(rows, cols, diceArray);


} //end setBoard

/*
 *********************************************************************************************************
 * Function Name: bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words)
 *
 * PARAMETERS -    Takes in a minium word length and a pointed to a set of strings to be filled by
 *                 this funciton.
 *
 * PRECONDITION -   setBoard and buildLexicon have been called
 *
 * POSTCONDITION - Returns a set of strings representing all words in the lexicon, of the minimum 
 *                 length specified and can be found in a simple acyclic path on the board created
 *                 by setboard
 *
 **********************************************************************************************************
 */
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words){


    //Checks Preconditions
    
    if ( ! board.isBuilt() )
    {
        cerr << "The player board as not been created yet" << endl;
        return false;
    }
    if ( ! lexicon.isBuilt() )
    {
        cerr << "The player lexicon has not been built yet" << endl;
        return false;
    }
    

    //Make a call to BoggleBoards recursive find all valid words for EACH node in the board
    for (unsigned int row = 0; row < board.getMaxRow(); row++)
    {
        for(unsigned int column = 0; column < board.getMaxColumn(); column++)
        {
            //create empty string to pass as current word
            string curr_word;
            //Make a call to recursive function for each node in the board
            board.getAllValidWords( board.getNode(row,column), curr_word, lexicon,
                    minimum_word_length, words);

        }
    }


    //if everything ran smoothly return true
    return true;

} //end getAllValidWords

/*
 *********************************************************************************************************
 * Function Name:  bool BogglePlayer::isInLexicon(const string& word_to_check)
 *
 * PARAMETERS -    Takes in a reference to a string to be searched for
 *
 * PRECONDITION -  Build Lexicon must have been called prior to this function
 * 
 * POSTCONDITION - The function returns true if the word is found in the lexicon or returns
 *                 false if the word is not found or the lexicon is not yet built
 *
 **********************************************************************************************************
 */
bool BogglePlayer::isInLexicon(const string& word_to_check){

    pair<bool,bool> returnPair;

    returnPair = lexicon.isIn( word_to_check );

    if(returnPair.second)
    {
        return true;
    }
    else
    {
        return false;
    }

} //end isInLexicon

/*
 *********************************************************************************************************
 * Functin Name:   vector<int> BogglePlayer::isOnBoard(const string& word_to_check)
 *
 * PARAMETERS -    Takes in a string to determine if the string is possibly formed via acyclic
 *                 cycles on the current board
 *
 * PRECONDITION -  setBoard must have been called prior to this function.
 * 
 * POSTCONDITION - Returns a vector representing positions on the board of the letters that form the
 *                 the word being searched for. Example if the letter is in row R and column C
 *                 the location integer stored would be R*Width+C. If the word is not in the board
 *                 or setBoard has not been called return the empty vector
 *
 **********************************************************************************************************
 */

vector<int> BogglePlayer::isOnBoard(const string& word_to_check){

    //Checks Preconditions
    //Create a vector to fill with the path
     vector<int> pathVector;

    if ( ! board.isBuilt() )
    {
        cerr << "The player board has not been created yet" << endl;
        return pathVector;
    }
    if ( ! lexicon.isBuilt() )
    {
        cerr << "The player lexicon has not been built yet" << endl;
        return pathVector;
    }


    //create to set when the word is found
    bool isFound = false;
    stack<int> path;
    

    //Make a call to BoggleBoards recursive find all valid words for EACH node in the board
    for (unsigned int row = 0; row < board.getMaxRow(); row++)
    {
        if(isFound){
            break;
        }
        for(unsigned int column = 0; column < board.getMaxColumn(); column++)
        {
            //create empty string to pass as current word
            string curr_word;
            //Make a call to recursive function for each node in the board
           board.isOnBoard(board.getNode(row,column), curr_word, word_to_check , isFound, path);

        }
    }

    //Now take the stack and place the items in a vector
    while ( ! path.empty() )
    {
        pathVector.push_back( path.top() );
        path.pop();
    }
    
    return pathVector;

} //end isOnBoard

/*
 *********************************************************************************************************
 * Function Name:  void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows,
 *                 unsigned int *cols)
 *
 * PARAMETERS -    First argument is an array of arrays that is used to populate the game board
 *                 Second argument is the ints for col and row used to populate the gameboard
 *                 in the fashion of setboard
 *
 * PRECONDITION -  Lexicon must be built, Memmory must be allocatd for the array of arrays representing
 *                 the game board
 * 
 * POSTCONDITION - The specified game board is created
 *
 **********************************************************************************************************
 */
void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){

 unsigned int nonPointercol = *cols;
 unsigned int nonPointerrow = *rows;

 board.setBoard(nonPointerrow, nonPointercol, new_board);

} //end getCustomeBoard




