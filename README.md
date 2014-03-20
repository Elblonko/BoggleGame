Program Name: Boggle

Description: This program implements the board game boggle on your computer against a computer generated player.
             Boggle is a game where a grid style board filled with tiles containting letters. The goal of 
             Boggle is to form as many words as you can on the board following paths from a letter to any
             adjacent letter. Adjacent letters are considered to be up,down,left,right and all diagnols. The
             player to correctly identify the most words wins.

Implementating: Boggle's grpahics are implemented using the Nokia QT graphics library. The game functoinality
                is created by several files. The most important of which are Boggleplayer and Boggleuetil which
                containt all of the data structure and minipulation needed for the program.
                
Data Structures: This implementation of boggle utalizes several interesting datastructures to function. First the
                 the dictionary file is converted into a ternary tri to enable prefix lookup for words on the
                 board. This implementation allow for complex searches through the graph with very little
                 time cost. Second the game board is represented as a graph with nodes pointing to all adjacent 
                 nodes. These nodes are then embedded in a multidimentionsal vector for easy intiuative access.
                 
Instruction To Run: To compile the files run 'make' in the terminal followed by ./p4 to run the game.



