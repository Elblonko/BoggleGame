/**
 *  CSE 100 C++ Boggle
 *  Authors: Matthew Schwegler 
 */

#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <set>
#include <stdio.h>
#include <iostream>
#include <utility>
#include "boggleutil.h"
#include "boggleplayer.h"

#include<fstream>
#include<iterator>


using namespace std;


/*
static const char* DEFAULTLEXFILENAME = "boglex.txt";
static unsigned int DEFAULTMINWORDLENGTH = 4;
static unsigned int DEFAULTROWS = 4;
static unsigned int DEFAULTCOLS = 4;
*/

int main(int argc, char *argv[])
{
    cerr << "START OF MAIN:" << endl;

    /*
    const char* lexfilename = DEFAULTLEXFILENAME;
    unsigned int rows = DEFAULTROWS;
    unsigned int cols = DEFAULTCOLS;
    unsigned int minwordlength = DEFAULTMINWORDLENGTH;
    if(argc > 1) lexfilename = argv[1];
    if(argc > 2) minwordlength = atoi(argv[4]);
    if(argc > 3) rows = atoi(argv[2]);
    if(argc > 4) cols = atoi(argv[3]);
    */

    /**** Testing the Lexicon Class ***/
    BoggleLexicon lexicon;
    
    string wordto = "tell";

    lexicon.insert(wordto);
    lexicon.insert("abys");
    lexicon.insert("amid");
    lexicon.insert("ahoy");
    lexicon.insert("bell");
    lexicon.insert("bells");
    lexicon.insert("amylletaa");
    lexicon.insert("taaahoydsllebmi");
    //should not find this
    lexicon.insert("tebat");

    cerr<< "INSERTING INTO LEXICON FINISHED" <<endl;

    pair<bool,bool> retPair;

    retPair = lexicon.isIn("abys");
    if( ! retPair.first )
    {
        cerr << "abys: was not a prefix" <<endl;
    }
    if( ! retPair.second )
    {
        cerr << "abys: was not a word" <<endl;
    }




    //Check to see if the isIn functions works
    



    BoggleBoard board;


    unsigned int rows = 4;
    unsigned int cols = 4;

    //string diceArray[rows][cols];
    
    //Create 2 demensional array
    /*
    diceArray = new string*[rows];
    for(unsigned int i = 0; i<rows; i++){
        diceArray[rows] = new string[cols];
    }
    */

    string **diceArray = new string*[rows];
    for(unsigned int i = 0; i<rows;i++){
        diceArray[i] = new string[cols];
    }
    

    diceArray[0][0] = "t";
    diceArray[0][1] = "e";
    diceArray[0][2] = "l";
    diceArray[0][3] = "l";

    diceArray[1][0] = "a";
    diceArray[1][1] = "B";
    diceArray[1][2] = "y";
    diceArray[1][3] = "s";

    diceArray[2][0] = "a";
    diceArray[2][1] = "m";
    diceArray[2][2] = "i";
    diceArray[2][3] = "d";

    diceArray[3][0] = "a";
    diceArray[3][1] = "h";
    diceArray[3][2] = "o";
    diceArray[3][3] = "y";

    board.setBoard(rows, cols, diceArray);

    cerr << "CREATED BOARD WITH SETBOARD" << endl;


    //Now test the get all valid words function
    set<string>* words = new set<string>;
    string curr_word;
    for (unsigned int row = 0; row < board.getMaxRow(); row++)
    {
        for(unsigned int column = 0; column < board.getMaxColumn(); column++)
        {
	  cerr << "finding words starting at row=" << row << ", column=" << column << endl;
            //create empty string to pass as current word
            string curr_word;
            //Make a call to recursive function for each node in the board
            board.getAllValidWords( board.getNode(row,column), curr_word, lexicon,
                    3, words);

        }
    }

    cerr << "BOARD HAS BEEN FILLED" << endl;

    //check to make sure visited was reset correctly
    for (unsigned int row = 0; row < board.getMaxRow(); row++)
    {
        for(unsigned int column = 0; column < board.getMaxColumn(); column++)
        {

         BoggleNode* temp = board.getNode(row,column);
         if(temp->isVisited())
            {
                cerr << "row: " << row << " column: " << column << " was not reset" <<endl;
            }
        }
    }

    cerr << "BOARD DOES NOT HAVE ANY ISVISITED FIELDS SET " << endl;

    
    //print through the set
    for(set<string>::iterator it = words->begin(); it != words->end(); it++)
    {
        cout << *it << endl;
    }

    //now to check isOnBoard
    bool isword;
    const string looking = "bell";
    string curr_word2;
    stack<int> path;

    cerr << "ABOUT TO CALL ISONBOARD" << endl;
    
    board.isOnBoard(board.getNode(1,1), curr_word2,looking, isword, path);
    
    if( ! isword )
    {
        cout << "bell was not found" << endl;
    }

    while( ! path.empty() )
    {

        int print = path.top();
        path.pop();
        cout << print <<endl;
    }

    ifstream myfile("boglex.txt");

    //read in a file and put it into a vector
    vector<string> myDict;
    copy(istream_iterator<string>(myfile),
        istream_iterator<string>(),
        back_inserter(myDict) );

    //Now try and insert the whole fucker into a lexicon
    for(unsigned int i = 0; i < myDict.size(); i++)
    {
        string key = myDict[i];
        lexicon.insert(key);
    }

    //mark lexicon as built
    lexicon.markBuilt();
    
  
    //Now test the get all valid words function
    //set<string>* words = new set<string>;
    //string curr_word;
    for (unsigned int row = 0; row < board.getMaxRow(); row++)
    {
        for(unsigned int column = 0; column < board.getMaxColumn(); column++)
        {
            //create empty string to pass as current word
            string curr_word;
            //Make a call to recursive function for each node in the board
            board.getAllValidWords( board.getNode(row,column), curr_word, lexicon,
                    3, words);

        }
    }


    //check to make sure visited was reset correctly
    for (unsigned int row = 0; row < board.getMaxRow(); row++)
    {
        for(unsigned int column = 0; column < board.getMaxColumn(); column++)
        {

         BoggleNode* temp = board.getNode(row,column);
         if(temp->isVisited())
            {
                cerr << "row: " << row << " column: " << column << " was not reset" <<endl;
            }
        }
    }

    /*
    //print through the set
    for(set<string>::iterator it = words->begin(); it != words->end(); it++)
    {
        cout << *it << endl;
    }
    */

    cout << "The number of words found is: " << words->size() << endl;


    //NOW test the file from moodle
    //read in a file and put it into a vector
    ifstream myfile2("lex.txt");

    vector<string> myDict2;

    copy(istream_iterator<string>(myfile2),
        istream_iterator<string>(),
        back_inserter(myDict2) );

    //Create new lexicon object
    BogglePlayer player;

    player.buildLexicon(myDict2);

    ifstream myfile3("brd.txt");

    vector<string> newBoard;

    //get the new board demensions
    /*
    copy(istream_iterator<string>(myfile3),
        istream_iterator<string>(),
        back_inserter(newBoard) );
    */

    //pull the size of the rows from the file
    string temp;
    unsigned int crows;
    unsigned int ccolumns;
    getline(myfile3,temp);
    cerr << temp << endl;
    crows = atoi( temp.c_str() );
    getline(myfile3,temp);
    ccolumns = atoi( temp.c_str() );

    cerr <<"the value of crows and ccolumns are: " << crows << " and " << ccolumns << endl;

    string **customdiceArray = new string*[crows];
    for(unsigned int i = 0; i<crows;i++){
        customdiceArray[i] = new string[ccolumns];
    }

       /*
       temp.erase(remove_if(temp.begin(), temp.end(), ::isspace ), temp.end() );

        newBoard.push_back(temp);

        cerr <<" temp is equal too: " << temp << endl;
        cerr << (newBoard.back() ) <<endl;
        */
    for(unsigned int i = 0; i < crows; i++)
    {
        for(unsigned int j = 0; j <ccolumns; j++)
        {
            getline(myfile3,temp);

            //cerr << "temp = "<< temp <<endl;
            customdiceArray[i][j] = temp;

            //cerr << "Custome dice equals[" << i << "][" << j << "] with: " << customdiceArray[i][j] <<endl;
        }
    }

    player.getCustomBoard(customdiceArray,&crows,&ccolumns); 

    set<string> wordsFound;

    cerr << "Getting all valid words: " << endl;
    player.getAllValidWords( 2, &wordsFound);

    //check to see if valid words is working
    cerr << "The size of word set found was: " << wordsFound.size() <<endl;


    //Deallocate create objects
    for(unsigned int j = 0; j < rows; j++)
    {
        delete[] diceArray[j];
    }
    delete[] diceArray;
    //delete *diceArray;
    diceArray = 0;
    //set<string>* words = new set<string>;
    delete words;
    words = 0;
    //string **customdiceArray = new string*[crows];
    for( unsigned int j = 0; j < crows; j++)
    {
        delete[] customdiceArray[j];
    }
    delete[] customdiceArray;
    //delete *customdiceArray;
    customdiceArray = 0;



    //now need to create tmhe vector

}
