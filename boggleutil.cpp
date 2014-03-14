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


/*********************** BoggleLexiconNode Class *****************************************/

/****************************************************************************************
 * Name:        BoggleLexiconNode Class
 *
 * Definition:  Create the data structure used to hold and minip
 *              ulate the boggle game lexicon
 *
 ****************************************************************************************
 */

/*
 *****************************************************************************************
 * Functin Name:   Default Constructor 
 *
 *****************************************************************************************
 */

BoggleLexiconNode::BoggleLexiconNode(){
    //Set the pointers to null to start
    less = NULL;
    greater = NULL;
    equal = NULL;

    //set flag equal to false
    isaWord = false;

    //set char to default 0
    character = 0;

}

/*
 *****************************************************************************************
 * Functin Name:   Constructor 
 *
 * PARAMETERS: Takes in a string to set the word field in the BoggleLexiconNode
 *
 *****************************************************************************************
 */

BoggleLexiconNode::BoggleLexiconNode(char insert) : character(insert){

    //Set the pointers to null to start
    less = NULL;
    greater = NULL;
    equal = NULL;

    //set flag equal to false
    isaWord = false;
}

/*
 *****************************************************************************************
 * Functin Name:    Destructor
 *
 *****************************************************************************************
 */

BoggleLexiconNode::~BoggleLexiconNode(){

    //delete all allocated notes
    if(less){
        delete less;
        less = 0;
    }
    if(greater){::
        delete greater;
        greater = 0;
    }
    if(equal){
        delete equal;
        equal = 0;
    }
}

/*
 *****************************************************************************************
 * Functin Name:    isWord 
 *
 * RETURN VALUE:    Returns True if the Node symbolizes a word in the tree, else false
 * 
 *****************************************************************************************
 */
bool BoggleLexiconNode::isWord(){
    return isaWord;
}

/*********************** END BoggleLexiconNode Class *************************************/


/*********************BoggleLexicon Class Functions**************************************/

/*
 *****************************************************************************************
 * Functin Name:    Constructor
 *
 *****************************************************************************************
 */
BoggleLexicon::BoggleLexicon(){

    //Set root to NULL to start
    root = NULL;

    //Set built equal to false to start
    built = false;

}

/*
 *****************************************************************************************
 * Functin Name:    Destructor
 *
 *****************************************************************************************
 */
BoggleLexicon::~BoggleLexicon(){

    if(root){
        //delete the root
        delete root;
    }
    root = 0;

}

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
pair<bool,bool> BoggleLexicon::isIn( const string& word_to_check){

    //checks if the root is null
    if( root == NULL )
    {
        cerr << "The Lexicon has not been created yet" << endl;
    }

    //create the pair to return later
    pair<bool,bool> returnPair;

    //create copy of string
    string find_word = word_to_check;

    //Create temp node starting at root
    BoggleLexiconNode *tempNode = root;

    while( ! find_word.empty() )
    {
        char tempChar = find_word.at(0);

        //CASE 1 current character match take equal pointer
        if ( tempNode->character == tempChar )
        {
            //erase character that just matched
            find_word.erase(0,1);
            //SubCase 1 This was the last character in the string
            if( find_word.empty() )
            {
                if(tempNode->isaWord)
                {
                    //Sets the returnPair to true, true for valid word found
                    returnPair = make_pair(true, true);
                    return returnPair;
                }
                else
                {
                    //Sets the returnPair to true, false for prefix found
                    returnPair = make_pair(true,false);
                    return returnPair;
                }
            }
            //SubCase 2 this is not a valid prefix
            else if( ! tempNode->equal )
            {
                //Sets the returnPair to false,false, prefix is not valid
                returnPair = make_pair(false,false);
                return returnPair;

            }
            //subCase 3 this is a prefix keep searching
            else
            {
                tempNode = tempNode->equal;
            }
        }
        //CASE 2 current character is less than current node
        else if ( tempChar < tempNode->character )
        {
            //Subcase 1 the prefix is invalid, not in lexicon
            if( ! tempNode->less )
            {
                returnPair = make_pair(false,false);
                return returnPair;
            }
            //Subcase 2 keep searching tree
            else
            {
                tempNode = tempNode->less;
            }
        }
        //CASE 3 current character is greater than current node
        else
        {
            //Subcase 1 the prefix is invalid not in lexicon
            if( ! tempNode->greater )
            {
                returnPair = make_pair(false,false);
                return returnPair;
            }
            //Subcase 2 keep searching tree
            else
            {
                tempNode = tempNode->greater;
            }
        }

    }

    //if it reaches here thats not good
    returnPair = make_pair(false,false);
    return returnPair;


} //end search

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
void BoggleLexicon::insert(string word_to_insert ){

    //Check if the string passed in is empty
    if( word_to_insert.empty() )
    {
        cerr << "String to insert into Lexicon is empty" << endl;
    }

    //CASE 1 first insert root is null
    if( root == NULL )
    {

        //Get the first character of a string
        char insertChar = word_to_insert.at(0);

        //Erase the first char of a string
        word_to_insert.erase(0,1);

        //Generate a new BoggleLexiconNode for root
        BoggleLexiconNode *tempNode = new BoggleLexiconNode(insertChar);

        root = tempNode;

        if( ! word_to_insert.empty() )
        {
            tempNode = insertWholeWord(tempNode, word_to_insert);
        }

        //set end of the word
        tempNode->isaWord = true;

        return;

    }

    //CASE 2 root has been created

    //create a temp node
    BoggleLexiconNode *tempNode = root;

    while( ! word_to_insert.empty() )
    {
        //CASE 1 move to next character already in the tree
        if( tempNode->character == word_to_insert.at(0) )
        {
            //erase matched node
            word_to_insert.erase(0,1);

            if( word_to_insert.empty() )
            {
                break;
            }
            else if( tempNode->equal )
            {
                tempNode = tempNode->equal;
            }
            else
            {
                tempNode = insertWholeWord(tempNode,word_to_insert);
            }

        }

        //CASE 2 next character is less than current node character
        else if( word_to_insert.at(0) < tempNode->character )
        {
            //if less than is null
            if( ! tempNode->less )
            {
                char insertChar = word_to_insert.at(0);
                word_to_insert.erase(0,1);
                tempNode->less = new BoggleLexiconNode(insertChar);
                tempNode = tempNode->less;

                if( ! word_to_insert.empty() )
                {
                    //Call helper function to insert rest of characters
                    tempNode = insertWholeWord(tempNode, word_to_insert);
                }
            }
            else
            {
                tempNode = tempNode->less;
            }
        }
        //CASE 3 next character is greater than current node character
        else 
        {

            if( ! tempNode->greater )
            {
                char insertChar = word_to_insert.at(0);
                word_to_insert.erase(0,1);
                tempNode->greater = new BoggleLexiconNode(insertChar);
                tempNode = tempNode->greater;

                if( ! word_to_insert.empty() )
                {
                    //Call helper function to insert rest of characters
                    tempNode = insertWholeWord(tempNode, word_to_insert);
                }
            }
            else
            {
                tempNode = tempNode->greater;
            }
        }



    }
    //Mark the last node touched as a word
    tempNode->isaWord = true;

} //end insert

/*****************************************************************************************
 * Functin Name:    insertWholeWord 
 *
 * Description:     Helper function for when it is identfied the rest of the word must be
 *                  inserted. When funcitons returns string_to_insert is empty.
 *
 * 
 *****************************************************************************************
 */ 

BoggleLexiconNode* BoggleLexicon::insertWholeWord( BoggleLexiconNode *&tempNode, string &word_to_insert)
{

    while( ! word_to_insert.empty() )
    {
        //Get the first character of a string
        char insertChar = word_to_insert.at(0);

        //Erase the first char of a string
        word_to_insert.erase(0,1);

        tempNode->equal = new BoggleLexiconNode(insertChar);

        tempNode = tempNode->equal;

    }

    return tempNode;
}




/*********************End of BoggleLexicon Functions**************************************/



/********************Start of BoggleNode Functions****************************************/

/*
 *****************************************************************************************
 * Functin Name: Constructor
 *
 * PARAMETERS:   Takes in a string to set the Node string variable
 *
 *****************************************************************************************
 */  

BoggleNode::BoggleNode(string set_word) : word(set_word){
    //set the initial row and col position to 0
    row = 0;
    column = 0;

    //set the visited bool to false
    visited = false;

    //set all the pointers to null to start
    up = NULL;
    down = NULL;
    left = NULL;
    right = NULL;
    dul = NULL;
    dur = NULL;
    ddl = NULL;
    ddr = NULL;

}

/*
 *****************************************************************************************
 * Functin Name: Destructor
 *****************************************************************************************
 */  

BoggleNode::~BoggleNode(){
}

/*****************************************************************************************
 * Functin Name:    isVisited() 
 *
 * Description:     Returns true if the nodes visited flag has been set
 *
 * 
 *****************************************************************************************
 */ 
bool BoggleNode::isVisited(){
    return visited;
}

/*
 *****************************************************************************************
 * Functin Name:    unsigned int getColumn();
 *                  unsigned int getRow();
 *
 * POSTCONDITION -  Returns the column and row location of the node, nothing is changed
 * 
 *****************************************************************************************
 */  
unsigned int BoggleNode::getColumn(){
    return column;
}
unsigned int BoggleNode::getRow(){
    return row;
}

/********************End of Boggle Node Functions******************************************/



/********************BoggleBoard Class Functions******************************************/

/*
 *****************************************************************************************
 * Functin Name: Constructor
 *
 * PARAMETERS:   Takes in a string to set the Node string variable
 *
 *****************************************************************************************
 */  
BoggleBoard::BoggleBoard(){

    //set the size values
    minRow = 0;
    maxRow = 0;
    minColumn = 0;
    maxColumn = 0;

    //set built bool to false to start
    built = false;

}

/*
 *****************************************************************************************
 * Functin Name: Destructor
 *****************************************************************************************
 */  
BoggleBoard::~BoggleBoard(){

    for (unsigned int i = 0; i < maxRow; i++)
    {
        for(unsigned int j = 0; j < maxColumn; j++)
        {
            delete board[i][j];
        }
    }


}



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
        return NULL;
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

    //set the max rows columns
    maxRow = rows;
    maxColumn = columns;

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

            //set the nodes row and column field
            node->row = i;
            node->column = j;

        }
    }

    //call to helper function set points to set the boggleboards pointers
    setPointers(rows, columns);

    built = true; 

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
            if ( i == 0 )
            {
                // i + 1 is down
                board[i][j]->down = board[ i + 1 ][j];

                //Set the diagnols
                // i + 1 down j - 1 left
                if (j != 0 )
                {
                    board[i][j]->ddl = board[ i + 1 ][ j - 1];
                }
                // i - 1 down j + 1 right
                if (j != (columns - 1) )
                {
                    board[i][j]->ddr = board[ i + 1 ][ j + 1];
                }

            }
            else if ( i == (rows - 1) )
            {
                // i - 1 is up
                board[i][j]->up = board[ i - 1 ][j];

                //Set the diagnols
                // i - 1 up j - 1 left
                if ( j != 0  )
                {
                    board[i][j]->dul = board[ i - 1 ][ j - 1];
                }
                // i - 1 up j + 1 right
                if( j!= (columns - 1) )
                {
                    board[i][j]->dur = board[ i - 1 ][ j + 1];
                }
            }
            else
            {
                // i + 1 is up
                board[i][j]->up = board[ i - 1 ][j];
                // i - 1 is down
                board[i][j]->down = board[ i + 1 ][j];

                //Set the diagnols
                // i - 1 down j - 1 left
                if( j != minColumn )
                {
                    board[i][j]->ddl = board[ i - 1 ][ j - 1];
                    // i + 1 up j - 1 left
                    board[i][j]->dul = board[ i + 1 ][ j - 1];
                }
                if( j != (maxColumn -1) )
                {
                    // i - 1 down j + 1 right
                    board[i][j]->ddr = board[ i - 1 ][ j + 1];
                    // i + 1 up j + 1 right
                    board[i][j]->dur = board[ i + 1 ][ j + 1];
                }
            }


            //Tests to set the correct left and right pointers (columns)
            if ( j == 0 )
            {
                //j + 1 is right
                board[i][j]->right = board[i][ j + 1 ];

            }
            else if ( j == (columns - 1) )
            {
                //j -1 is left
                board[i][j]->left = board[i][ j -1];

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
void BoggleBoard::getAllValidWords(BoggleNode* node,string curr_word, BoggleLexicon &lexicon,
        unsigned int minimum_word_length, set<string>* words)
{

    //Base case for recursion if this node as been visited
    if ( node->isVisited() )
    {
        return;
    }

    //Append the current word with the current nodes word
    curr_word += node->word;

    //create Pair to check for lexicon conditions, bool 1 is prefix, bool 2 is word
    pair<bool,bool> isInLex;

    //check to see if the new word is of min length and in the current lexicon
    if ( curr_word.length() >= minimum_word_length )
    {
        isInLex = lexicon.isIn(curr_word);

        //CASE 1 the word is a prefix and is a word
        if ( isInLex.first && isInLex.second )
        {
            words->insert(curr_word);
        }
        //CASE 2 word is a prefix but not a word
        else if( isInLex.first)
        {
            //Might be able to optimize here
        }
        //CASE 3 three word is not a valid prefix stop searching this path
        else
        {
            return;
        }
    }


    //Check the flag to indicate this node has been visited
    node->visited = true;

    //Now do up to 8 recursive calls in clockwise order
    if(  node->up )
    {
        getAllValidWords(node->up, curr_word, lexicon, minimum_word_length, words);
    }
    if(  node->dur )
    {
        getAllValidWords(node->dur, curr_word, lexicon, minimum_word_length, words);
    }
    if(  node->right )
    {
        getAllValidWords(node->right, curr_word, lexicon, minimum_word_length, words);
    }
    if(  node->ddr )
    {
        getAllValidWords(node->ddr, curr_word, lexicon, minimum_word_length, words);
    }
    if(  node->down )
    {
        getAllValidWords(node->down, curr_word, lexicon, minimum_word_length, words);
    }
    if(  node->ddl )
    {
        getAllValidWords(node->ddl, curr_word, lexicon, minimum_word_length, words);
    }
    if(  node->left )
    {
        getAllValidWords(node->left, curr_word, lexicon, minimum_word_length, words);
    }
    if(  node->dul )
    {
        getAllValidWords(node->dul, curr_word, lexicon, minimum_word_length, words);
    }

    //after all recursive calls return the visited node back to false
    node->visited = false;
}
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
void BoggleBoard::isOnBoard(BoggleNode* node,string curr_word, const string &search_word, bool &isFound, stack<int> &path)
{

    //Base case for recursion if this node as been visited
    if ( node->isVisited() || isFound )
    {
        return;
    }

    //Append the current word with the current nodes word
    curr_word += node->word;

    //Loop to check character by character for match, allow early exit 
    for (unsigned int i = 0; i < curr_word.size(); i++)
    {
        if (curr_word.at(i) == search_word.at(i) )
        {
            //If words match all the way up to the end, word found
            if( i == (search_word.size() -1) )
            {
            isFound = true; 
            unsigned int row = node->getRow();
            unsigned int column = node->getColumn();
            //push position to stack using formula row*width+column
            path.push(row*maxColumn + column);
            return;
            }
        }
        //substring did not match
        else
        {
            return;
        }
    }


        //Check the flag to indicate this node has been visited
        node->visited = true;




        //Now do up to 8 recursive calls in clockwise order
        if(  node->up )
        {
            isOnBoard(node->up, curr_word,search_word,isFound, path);
        }
        if(  node->dur )
        {
            isOnBoard(node->dur, curr_word,search_word,isFound, path);
        }
        if(  node->right )
        {
            isOnBoard(node->right, curr_word, search_word,isFound, path);
        }
        if(  node->ddr )
        {
            isOnBoard(node->ddr, curr_word, search_word,isFound, path);
        }
        if(  node->down )
        {
            isOnBoard(node->down, curr_word, search_word,isFound, path);
        }
        if(  node->ddl )
        {
            isOnBoard(node->ddl, curr_word, search_word,isFound, path);
        }
        if(  node->left )
        {
            isOnBoard(node->left, curr_word, search_word,isFound, path);
        }
        if(  node->dul )
        {
            isOnBoard(node->dul, curr_word, search_word,isFound, path);
        }

    //if statement to check if the word is found and record the path
    if(isFound)
    {
        unsigned int row = node->getRow();
        unsigned int column = node->getColumn();
        //push position to stack using formula row*width+column
        path.push(row*maxColumn + column);
    }


    //after all recursive calls return the visited node back to false
    node->visited = false;


}

