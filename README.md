Program Name: Boggle

Description: This program implements the board game boggle on your computer against a computer generated player.
             Boggle is a game where a grid style board filled with tyles containting letters. The goal of 
             Boggle is to form as many words as you can on the board following paths from a letter to any
             adjacent letter. Adjacent letters are considered to be up,down,left,right and all diagnols. The
             player to correctly identify the most words wins.

Implementating: Boggle's grpahics are implemented using the Nokia QT graphics library. The game functoinality
                is created by several files. The most important of which are Boggleplayer and Boggleuetil which
                containt all of the data structure and minipulation needed for the program.

How to Compile testers:
 for myMain.cpp type
 g++ -g -std=c++11  myMain.cpp boggleutil.h boggleutil.cpp

 for bogtest.cpp type
 g++ -g -std=c++11  bogtest.cpp boggleutil.h boggleutil.cpp boggleplayer.h boggleplayer.cpp

