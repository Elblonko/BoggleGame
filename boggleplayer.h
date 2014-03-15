/*
 * Name: Matthew Schwegler
 * Login: cs100way
 *
 * File: boggleplayer.h
 * Desscription: Defintes the functions to be implemented by boggleplayer.cpp. This class will create a computer
 *               Boggle player that can beat any human boggle player.
 *
 */
#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <stdio.h>
#include <iostream>
#include "iboggleplayer.h"
#include "boggleutil.h"




using namespace std;




class BogglePlayer : public IBogglePlayer {
    private:
        /**** Class Fields ****/

        //c++ set to store the lexicon build for now
        //set<string> lexicon;
        BoggleLexicon lexicon;
        BoggleBoard board;

    public:
        //constructor
        BogglePlayer();

        //destructor
        ~BogglePlayer();



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
        void buildLexicon(const vector<string>& word_list);

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
        void setBoard(unsigned int rows, unsigned int cols, string** diceArray);

        /*
         *********************************************************************************************************
         * Function Name: bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words)
         *
         * PARAMETERS -    Takes in a minium word length and a pointed to a set of strings to be filled by
         *                 this funciton.
         *
         * PRECONDITION -  setBoard and buildLexicon must have been called proir to this function to function
         * 
         * POSTCONDITION - Returns a set of strings representing all words in the lexicon, of the minimum 
         *                 length specified and can be found in a simple acyclic path on the board created
         *                 by setboard
         *
         **********************************************************************************************************
         */
        bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);

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
        bool isInLexicon(const string& word_to_check);

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
        vector<int> isOnBoard(const string& word_to_check);

        /*
         *********************************************************************************************************
         * Function Name:  void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols)
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
        void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

};




#endif
