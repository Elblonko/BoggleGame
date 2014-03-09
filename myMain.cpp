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
#include "boggleutil.h"


using namespace std;


/*
static const char* DEFAULTLEXFILENAME = "boglex.txt";
static unsigned int DEFAULTMINWORDLENGTH = 4;
static unsigned int DEFAULTROWS = 4;
static unsigned int DEFAULTCOLS = 4;
*/

int main(int argc, char *argv[])
{
    cerr << "start of main\n\n" << endl;

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
    lexicon.insert("tebat");

    //Check to see if the isIn functions works
    if(! lexicon.isIn("tell" ) ) {
        cerr << "String tell not found" <<endl;
    }
    if(! lexicon.isIn("abys" ) ) {
        cerr << "String abys not found" <<endl;
    }
    if(! lexicon.isIn("amid" ) ) {
        cerr << "String amid not found" <<endl;
    }
    if(! lexicon.isIn("ahoy" ) ) {
        cerr << "String ahoy not found" <<endl;
    }
 


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

    cerr << "Created the board with setBoard" << endl;


    //Now test the get all valid words function
    set<string>* words = new set<string>;
    string curr_word;
    board.getAllValidWords(board.getNode(0,0), curr_word, lexicon, 3, words);
    board.getAllValidWords(board.getNode(1,0), curr_word, lexicon, 3, words);
    board.getAllValidWords(board.getNode(1,1), curr_word, lexicon, 3, words);
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


    

    //now need to create the vector

}
