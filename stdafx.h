// stdafx.h
//include file for standard system include files
//project specific include files that are used frequently, but are changed infrequently

#pragma once

//standard include files
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

//project include files
#include "tile.h"
#include "deck.h"
#include "pile.h"
#include "train.h"
#include "round.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "game.h"


//the game component indices

//to use index to refer to each player
enum gamePlayers
{
    comp_player,
    human_player
};

//to use index to refer to each pile
enum gamePiles
{
    comp_hand,
    human_hand,
    boneyard
};

//to use index to refer to each train
enum gameTrains
{
    comp_train,
    human_train,
    mexican_train
};

//to indicate a draw
enum gameResult
{
    draw = -1
};


//menu options

//to indicate whether user wants to start a new round or load game
enum firstMenu
{
    new_game = 1,
    load_game = 2
};

//to indicate whether user wants to play another round or not
enum anotherRound
{
    yes = 1,
    no = 2
};

//to indicate occurence of different events when a player takes turn
enum decision
{
    save_game = 1,
    make_move = 2,
    get_help = 3,
    quit = 4,
    empty_hand = 5
};

//other

//to indicate the result of user input validation
enum input_validation
{
    invalid_input = -1,
    min_input = 1
};

//to indicate the result of placing a tile at the end of a train
enum placement
{
    incorrect_placement,
    non_double_placemnt,
    double_placement
};


/* *********************************************************************
Function Name: validateInput
Purpose: To check whether a numeric user input is valid
Parameters:
            input, a string passed by value. It holds the user input.
            
            max_selection, an integer passed by value. It holds the
            maximum number that user can enter in a menu selection.
            
Return Value: a valid user selection (integer) or invalid_input (enum)
Assistance Received: None
********************************************************************* */
inline int validateInput(const string input, const int max_selection)
{
    int input_size = (int)input.size();
    
    //all inputs must be 2 characters at most and a minimum of 1 character long
    if (input_size > 2 || input_size == 0)
        return invalid_input;
        
    //input must be numeric
    for (int i=0; i<input_size; i++)
    {
        if (!isdigit(input[i]))
            return invalid_input;
    }
        
    //input must be within the range of given options
    int selection = stoi(input);
    
    if (selection > max_selection || selection < min_input)
        return invalid_input;
        
    return selection;
}


/* *********************************************************************
Function Name: addChar
Purpose: To put together a series of repetitive characters for
            displaying purposes
Parameters:
            ch, a character passed by value. It holds the character that
            will be put together.
            
            nums, an integer passed by value. It refers to the number of
            times ch will be added to the string.
            
Return Value: repetitive series of ch, a string
Assistance Received: None
********************************************************************* */
inline string addChar(const char ch, const int nums)
{
    string formatting;
    for (int i=0; i<nums; i++)
        formatting += ch;
    
    return formatting;
}
