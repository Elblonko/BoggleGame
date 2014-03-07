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
 * Functin Name:   
 
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



/********************BoggleNode Class Functions******************************************/


