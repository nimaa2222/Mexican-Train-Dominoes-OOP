#include "stdafx.h"

//used to refer to a strategy used by computer to select a tile
enum tile_strategies
{
    one_double,
    highest_double,
    one_matching_double,
    most_matching_double,
    most_matching_double_maxPip,
    one_tile,
    highest_tile,
    one_double_played,
    double_played_maxPip
};

//used to refer to a strategy used by computer to select a train
enum train_strategies
{
    one_eligible_matching,
    other_opponent,
    personal_mexican,
};

//all possible explanations for computer tile selection
map<int, string> strategies_tile = {
    
    {one_double, "only playable double in hand. "},
    {highest_double, "playable double with the highest pip sum in hand. "},
    {one_matching_double, "only playable double that has another matching tile in hand. "},
    {most_matching_double, "playable double with the most number of tiles in hand that could match it. "},
    {most_matching_double_maxPip, "playable double with the most number of matching tiles in hand and highest pip sum. "},
    {one_tile, "only playable tile. "},
    {highest_tile, "playable tile with the highest pip sum. "},
    {one_double_played, "only playable non-double with its double(s) played. "},
    {double_played_maxPip,"playable non-double with its double(s) played and highest pip sum. "}
};

//all possible explanations for computer train selection
map<int, string> strategies_train = {
    {one_eligible_matching, "it is the only eligible train that matches the selected tile. "},
    {other_opponent, "the opponent train could be unmarked and not available in the next turn. "},
    {personal_mexican, "the mexican train is almost always available to opponent. "},
};


/* *********************************************************************
Function Name: isDoublePlayed
Purpose: To check if the double of one side of a non-double is played
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to access the game trains.
 
            tile_to_check, an object of the class tile passed by value.
            It refers to the non-double in our case.
 
Return Value:
                returns true if the double is played
                otherwise returns false
Algorithm:
            (1) record all the doubles played in all trains as candidates
            (2) if the front or back of the tile matches any of the doubles
                    the double is played
                end if
                otherwise the double is not played
 
Assistance Received: None
********************************************************************* */
bool computer::isDoublePlayed(round& this_round, tile tile_to_check) const
{
    //the doubles in all trains (each vector contains the doubles in one train)
    vector<vector<tile>> all_doubles_played;
    
    //go thorugh each train and record the doubles that have been played
    //record the doubles in each train
    for (int i=0; i<3; i++)
        all_doubles_played.push_back((this_round.getTrains()+i)->getDoubleTiles());
    
    //go through each train
    for (int i=0; i<all_doubles_played.size(); i++)
    {
        //go through all tiles in this train
        for (int j=0; j<all_doubles_played[i].size(); j++)
        {
            //if front or back of the tile matches any of the doubles
            if (all_doubles_played[i][j].getFrontEnd() == tile_to_check.getFrontEnd() || all_doubles_played[i][j].getFrontEnd() == tile_to_check.getBackEnd())
                return true;
        }
    }
    
    return false;
}

/* *********************************************************************
Function Name: printTileStrategy
Purpose: To display the logistics behind computer's tile selection
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to access the listed infromation.
 
            tile_index, an integer passed by value. It refers to the
            selected tile index.
 
            msg, a string passed by value. It refers to the message
            that will be displayed as computer reasoning.
 
Return Value: None
Assistance Received: None
********************************************************************* */
void computer::printTileStrategy(round& this_round, const int tile_index, const string msg) const
{
    cout<<endl<<endl;
    if (this_round.getCurrentPlayer() == comp_player)
        cout<<"Selection Reasoning:"<<endl;
    else
        cout<<"Computer Advice:"<<endl;
    
    cout<<"The computer ";
    
    if (this_round.getCurrentPlayer() == comp_player)
        cout<<"chose to play ";
    else
        cout<<"suggests playing ";
    
    (this_round.getPiles()+this_round.getCurrentPlayer())->getTile(tile_index).displayTile();
    cout<<" because this tile is the "<<msg;
}

/* *********************************************************************
Function Name: printTrainStrategy
Purpose: To display the logistics behind computer's train selection
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to access the listed infromation.
 
            train_index, an integer passed by value. It refers to the
            selected train index.
 
            msg, a string passed by value. It refers to the message
            that will be displayed as computer reasoning.
 
Return Value: None
Assistance Received: None
********************************************************************* */
void computer::printTrainStrategy(round& this_round, const int train_index, const string msg) const
{
    cout<<"The computer ";
    
    if (this_round.getCurrentPlayer() == comp_player)
        cout<<"played selected tile on ";
    else
        cout<<"suggests playing selected tile on ";
    
    if (train_index == comp_train)
        cout<<"computer";
    else if (train_index == human_train)
        cout<<"human";
    else
        cout<<"mexican";
    
    cout<<" train because "<<msg<<endl<<endl;
}


/* *********************************************************************
Function Name: selectAction
Purpose: To ask user to choose an option before computer makes a move
Parameters: None
Return Value: the user's selection, an integer
Assistance Received: None
********************************************************************* */
int computer::selectAction() const
{
    //set to ture once a valid selection is made
    bool valid_input = false;
    
    //user's selection
    int selection = 0;
    
    while (!valid_input)
    {
        string menu_selection;
        cout<<"Select One of the Following Options:"<<endl;
        cout<<"1) Save the Game"<<endl;
        cout<<"2) Let Computer Make a Move"<<endl;
        cout<<"3) Quit the Game"<<endl;
        getline(cin, menu_selection);
        cout<<endl;
        
        //make sure input is valid (the maximum selection is 3)
        selection = validateInput(menu_selection, 3);
        
        if (selection != invalid_input)
            valid_input = true;
    }
    
    //quitGame is a global enum that equals 4
    //must increment selection if option "Quit the Game" is selected
    if (selection == 3)
        selection++;
    
    return selection;
}



/* *********************************************************************
Function Name: selectTileIndex
Purpose: To allow computer to select a tile from its hand
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to select the tile.
 
Return Value: the index of the selected tile, an integer
Algorithm:
        (1) identify the number of double tiles
        (2)
            if there is at least one double
                if there is more than one double
                    if there is at least one double with a matching tile(s)
                        if there is more than one double with a matching tile(s)
                            find the frequency of matching tiles for each double
                            if there is more than one tile with highest frequency
                                pick the double with the higher pip sum
                            end if
                            else
                                pick the double with the highest matching frequency
                            end else
                        end if
                        else
                            pick the double with the matching tile(s)
                        end else
                    end if
                    else
                        pick the double with the highest pip sum
                    end else
                end if
                else
                    pick the double tile
                end else
            end if
 
            else
                if there is more than one non-double
                    if there is at least one non-double for which its double is played
                        if there is more than one non-double for which its double is played
                            if there is more than one tile with its sum = highest
                                pick the first non-double
                            end if
                            else
                                pick the non-double with highest pip sum
                            end else
                        end if
                        else
                            pick the non-double for which its double is played
                        end else
                    end if
                    else
                        if there is more than one non-double with its sum = highest
                            pick the first non-double
                        end if
                        else
                            pick the non-double with highest pip sum
                        end else
                    end else
                end if
                else
                    pick the non-double
                end else
            end else
            
Assistance Received: None
********************************************************************* */

int computer::selectTileIndex(round& this_round) const
{
    
    //identify all the tiles that match the end of at least one eligible train (eligible matching tiles)
    vector<tile> candidates = identifyTileCandidates(this_round);
    
    //extract double candidates in here
    vector<tile> doubles;
    
    //identify double candidates
    for (int i=0; i<candidates.size(); i++)
    {
        if (candidates[i].isDouble())
            doubles.push_back(candidates[i]);
    }
    
    //if there is at least one double
    if (doubles.size() > 0)
    {
        //if there is more than one double
        if (doubles.size() > 1)
        {
            //extract doubles with matching tiles and the number of their matching tiles in here <tile, frequency>
            map<tile, int> double_matchings;
            
            for (int i=0; i<doubles.size(); i++)
            {
                int frequency_for_double = 0;
                for (int j=0; j<(this_round.getPiles()+this_round.getCurrentPlayer())->getSize(); j++)
                {
                    tile hand_tile = (this_round.getPiles()+this_round.getCurrentPlayer())->getTile(j);
                    
                    if (doubles[i].getFrontEnd() == hand_tile.getFrontEnd() || doubles[i].getFrontEnd() == hand_tile.getBackEnd())
                        frequency_for_double++;
                }
                
                double_matchings.insert(pair<tile, int>(doubles[i], frequency_for_double));
            }
            
            //if there is at least one double with matching tile(s)
            if (double_matchings.size() > 0)
            {
                //if there is more than one double with matching tile(s)
                if (double_matchings.size() > 1)
                {
                    map<tile, int>::iterator itr; 
                    
                    //find the max frequency of matching non-doubles in hand
                    int max = 0;
                    for (itr = double_matchings.begin(); itr != double_matchings.end(); ++itr)
                    {
                        if (itr->second > max)
                            max = itr->second;
                    }
                    
                    //extract doubles with matching tiles of euqal max <tile, max>
                    map<tile, int> double_matchings_equal_max;
                    
                    for (itr = double_matchings.begin(); itr != double_matchings.end(); ++itr)
                    {
                        if (itr->second == max)
                            double_matchings_equal_max.insert(pair<tile, int>(itr->first, itr->second));
                    }
                    
                    //if there is more than one double with matching tile(s) of equal max
                    if (double_matchings_equal_max.size() > 1)
                    {
                        //find the pip sum for each tile
                        map<tile, int> double_matchings_equal_max_pipSum;
                        
                        for (itr = double_matchings_equal_max.begin(); itr != double_matchings_equal_max.end(); ++itr)
                        {
                            tile x = (itr->first);
                            double_matchings_equal_max_pipSum.insert(pair<tile, int>(itr->first, x.getTileSum()));
                        }
                        
                        //find the max pip sum among these tiles
                        int max = 0;
                        for (itr = double_matchings_equal_max_pipSum.begin(); itr != double_matchings_equal_max_pipSum.end(); ++itr)
                        {
                            if (itr->second > max)
                                max = itr->second;
                        }
                        
                        //identify double with highest pip sum  (there should be only one because no 2 doubles have the same pip sum)
                        for (itr = double_matchings_equal_max_pipSum.begin(); itr != double_matchings_equal_max_pipSum.end(); ++itr)
                        {
                            if (itr->second == max)
                            {
                                int tile_index = (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(itr->first);
                                printTileStrategy(this_round, tile_index, strategies_tile[most_matching_double]);
                                return tile_index;
                            }
                        }
                    }
                    
                    else
                    {
                        //return the one and only tile found with most number of matching tiles (only element of map)
                        int tile_index = (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(double_matchings_equal_max.begin()->first);
                        printTileStrategy(this_round, tile_index, strategies_tile[most_matching_double]);
                        
                        return tile_index;
                    }
                }
                
                else
                {
                    //return the one and only double with matching tile(s) - only element of map
                    int tile_index = (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(double_matchings.begin()->first);
                    
                    printTileStrategy(this_round, tile_index, strategies_tile[one_matching_double]);
                    
                    return tile_index;
                }
            }
            
            
            else
            {
                //there is no double with matching tile(s), but there is more than one double
                
                //find the max pip sum among these tiles
                int max = 0;
                for (int i=0; i<doubles.size(); i++)
                {
                    if (doubles[i].getTileSum() > max)
                        max = doubles[i].getTileSum();
                }
                
                //identify double with highest pip sum (there should be only one because no 2 doubles have the same pip sum)
                for (int i=0; i<doubles.size(); i++)
                {
                    if (doubles[i].getTileSum() == max)
                    {
                        int tile_index = (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(doubles[i]);
                        printTileStrategy(this_round, tile_index, strategies_tile[highest_double]);
                        
                        return tile_index;
                    }
                }
            }
        }
        
        else
        {
            int tile_index = (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(doubles[0]);
            
            //there is only one double
            printTileStrategy(this_round, tile_index, strategies_tile[one_double]);
            
            return tile_index;
        }
    }
    
    
    //there is no doubles in hand if program reaches this point
    //so the hand is consisted of only non-doubles (no extraction needed) - all non-doubles are in candidates vector
    
    //if there is more than one non-double
    if (candidates.size() > 1)
    {
        //identify non-doubles that one of their doubles has been played - each non-double matches 2 doubles (the front & back)
        vector<tile> non_double_played;
        
        for (int i=0; i<candidates.size(); i++)
        {
            //if one of the 2 doubles of a non-double is played
            if (isDoublePlayed(this_round, candidates[i]))
                non_double_played.push_back(candidates[i]);
        }
        
        //if there is at least one non-double for which one of its doubles is played
        if (non_double_played.size() > 0)
        {
            //if there is more than one non-double for which one of its doubles is played
            if (non_double_played.size() > 1)
            {
                //find the non-double with its double played and highest pip sum
                
                //find the max pip sum among these non-double tiles
                int max = 0;
                for (int i=0; i<non_double_played.size(); i++)
                {
                    if (non_double_played[i].getTileSum() > max)
                        max = non_double_played[i].getTileSum();
                }
                
                //find all tiles with pipsum = max
                vector<tile> non_doubles_maxpipsum;
                
                //find the non-double(s) with highest pip sum (if there is multiple ones, return the first one)
                for (int i=0; i<non_double_played.size(); i++)
                {
                    if (non_double_played[i].getTileSum() == max)
                        non_doubles_maxpipsum.push_back(non_double_played[i]);
                }
                
                int tile_index = (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(non_doubles_maxpipsum[0]);
                printTileStrategy(this_round, tile_index, strategies_tile[double_played_maxPip]);
                
                //return the first tile with pipsum=max (even if there is multiple tiles with pipsum = max)
                return tile_index;
            }
            
            else
            {
                //if there is only one non-double for which one of its double is played
                int tile_index = (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(non_double_played[0]);
                printTileStrategy(this_round, tile_index, strategies_tile[one_double_played]);
                
                return (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(non_double_played[0]);
            }
        }
        
        else
        {
            //but there are multiple non-doubles
            
            //find the max pip sum among these non-double tiles
            int max = 0;
            for (int i=0; i<candidates.size(); i++)
            {
                if (candidates[i].getTileSum() > max)
                    max = candidates[i].getTileSum();
            }
            
            vector<tile> non_doubles_maxpipsum;
            
            //find the non-double(s) with highest pip sum
            for (int i=0; i<candidates.size(); i++)
            {
                if (candidates[i].getTileSum() == max)
                    non_doubles_maxpipsum.push_back(candidates[i]);
            }
            
            int tile_index = (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(non_doubles_maxpipsum[0]);
            printTileStrategy(this_round, tile_index, strategies_tile[highest_tile]);
            
            //return the first tile with pipsum=max (even if there is multiple tiles with pipsum = max)
            return tile_index;
        }
    }
    
    //if there is only one non-double
    else
    {
        //this is the only playable tile
        int tile_index = (this_round.getPiles()+this_round.getCurrentPlayer())->getTileIndex(candidates[0]);
        printTileStrategy(this_round, tile_index, strategies_tile[one_tile]);
        
        return tile_index;
    }
}


/* *********************************************************************
Function Name: selectTrainIndex
Purpose: To allow computer to select a train to play tile on
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to select the train.
 
            selected_tile, an integer passed by reference. It refers to
            the selected tile to place on a train
 
Return Value: the index of the selected train, an integer
Algorithm:
        (1)
            if there is only one matching eligible train
                pick this train
            end if
            else if there is 2 matching eligible trains
                if the trains are personal and opponent
                    pick opponent train
                end if
                else if trains are opponent and mexican
                    pick opponent train
                end else if
                else if trains are personal and mexican
                    pick mexican train
                end else if
            end else if
            else (3 matching eligible trains)
                pick opponent train
            end else
Assistance Received: None
********************************************************************* */
int computer::selectTrainIndex(round& this_round, int& selected_tile) const
{
    //find the train that matches the selected tile
    
    //identify eligible trains
    vector<int> eligible_train_indecies = identifyEligibleTrains(this_round);
    vector<int> eligible_matching_trains;
    
    //extract the train(s) matching selected tile from eligible trains
    for (int i=0; i<eligible_train_indecies.size(); i++)
    {
        if ((matchTileTrain(this_round, selected_tile, eligible_train_indecies[i])) != incorrect_placement)
            eligible_matching_trains.push_back(eligible_train_indecies[i]);
    }
    
    //now we only have matching eligible trains
    
    //if there is only one matching eligible train
    if (eligible_matching_trains.size() == 1)
    {
        int selected_train = eligible_matching_trains[0];
        printTrainStrategy(this_round, selected_train, strategies_train[one_eligible_matching]);
        
        return selected_train;
    }
    
    //if there is 2 matching eligible trains
    else if (eligible_matching_trains.size() == 2)
    {
        int first_train = eligible_matching_trains[0];
        int second_train = eligible_matching_trains[1];
        
        //if personal and opponent are eligible matching
        if ( (first_train == comp_train && second_train == human_train) || (first_train == human_train && second_train == comp_train) )
        {
            //select opponent train
            printTrainStrategy(this_round, this_round.getNextPlayer(), strategies_train[other_opponent]);
            return this_round.getNextPlayer();
        }
        
        //if opponent and mexican are eligible matching
        if ( (first_train == this_round.getNextPlayer() && second_train == mexican_train) || (first_train == mexican_train && second_train == this_round.getNextPlayer()) )
        {
            //select opoonent train
            printTrainStrategy(this_round, this_round.getNextPlayer(), strategies_train[other_opponent]);
            return this_round.getNextPlayer();
        }
        
        //if personal and mexican are eligible matching
        else
        {
            //select mexican train
            printTrainStrategy(this_round, mexican_train, strategies_train[personal_mexican]);
            return mexican_train;
        }
    }
    
    //if there is 3 eligible matching trains
    else
    {
        //select opponent train (best option)
        printTrainStrategy(this_round, this_round.getNextPlayer(), strategies_train[other_opponent]);
        return (this_round.getNextPlayer());
    }
}





