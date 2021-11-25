
#include "stdafx.h"

//*** constructors ***//
player::player()
{
    m_score = 0;
}

player::player(const int score)
{
    m_score = score;
}

player::player(const player& other_player)
{
    m_score = other_player.m_score;
}

//*** destrcutor ***//
player::~player()
{
    //m_score --> static variable will be automatically destroyed
}


//*** getters and setters ***//

int player::getScore() const
{
    return m_score;
}

void player::updateScore(const int round_score)
{
    if (round_score < 0)
        return;
    
    m_score += round_score;
}

/* *********************************************************************
Function Name: takeTurn
Purpose: To allow player to take turn(s)
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is modified based on the events that occur during the
            turn.
 
            double_tiles, an integer passed by reference. It refers to
            the number of doubles played by a player before the next
            player goes. So it is modified based on player's move.
            
            boneyard_picked, a boolean passed by reference. It is
            set to true when player draws from the boneyard.
 
            empty_boneyard_hit, a boolean passed by reference. It is
            set to true when player attempts to draw from an empty
            boneyard
 
            players[], a pointer to an array of player objects. It is
            used to display the scores for the players
 
            round_number, an integer passed by value. It is used to
            display the current round number on the screen.
 
            tiles_placed, an integer passed by reference. It refers to
            the number of tiles played by a player before the next
            player goes. So it is modified based on player's move.
            
Return Value: the player's decision or the outcome of an event (decision enum)
Algorithm:
        (1) display the current game status
        (2)
            if the player has no more tiles to play
                the player wins the round
            end if
        (3) identify the player that is taking a turn
        (4) ask user whether they want to save game, continue playing, quit the game
            or get help (available for human)
        (5) if user asked for help
                if player has any possible moves
                    suggest a tile and a train
                end if
                else
                    inform user that there is no move to make
                end else
            end if
 
            if player wants to continue playing
                proceed
            end if
 
            if player cannot move
                if player has not yet picked from boneyard in this turn
                    if boneyard is not empty
                        add a tile from boneyard to player's hand
                        player has to go again
                    end if
 
                    else
                        note that boneyard is empty
                    end else
 
                end if
 
                else
                    mark the player's train
                emd else
            end if
 
            else
                prompt user for a tile and train selection (computer will choose its own)
                if player does not pick a correct match of tile and train
                    player has to go again
                end if
                
                if player placed a double
                    note that player has placed a double
                    unset the indicator for boneyard
                    player has to go again
                end if
            end else
        (6) return player's decision
 
Assistance Received: None
********************************************************************* */
int player::takeTurn(round& this_round, int& double_tiles, bool& boneyard_picked, bool& empty_boneyard_hit, player* players[], const int round_number, int& tiles_placed) const
{
    cout<<endl<<endl;
    
    //display current state of the game
    displayGame(this_round, round_number, players[comp_player]->getScore(), players[human_player]->getScore());
    
    //if player has no more tiles to play
    if (((this_round.getPiles()+this_round.getCurrentPlayer())->getSize()) == 0)
        return empty_hand;
    
    //maximum number of tiles that can be placed in consecutive turns
    const int max_tiles_placed = 3;
    
    if (tiles_placed == max_tiles_placed)
        return make_move;
    
    pressEnter();
    
    if (this_round.getCurrentPlayer() == comp_player)
        cout<<"Computer Turn"<<endl;
    else
        cout<<"Your Turn"<<endl;
    
    cout<<endl;

    //ask user what they intend to do
    int player_decision = players[this_round.getCurrentPlayer()]->selectAction();
    
    //only available to human
    if (player_decision == get_help)
    {
        //if player has at least one possible move
        if (playerCanMove(this_round, double_tiles))
        {
            //suggest player the tile and train to play
            int selected_tile = players[comp_player]->selectTileIndex(this_round);
            cout<<endl;
            players[comp_player]->selectTrainIndex(this_round, selected_tile);
        }
        
        //if player has no possible moves
        else
        {
            cout<<endl<<endl;
            cout<<"Computer Advice:"<<endl;
            cout<<"There are no playable tiles in your hand"<<endl;
        }
        
        //to allow picking from boneyard OR count player movement
        player_decision = make_move;
        
        displayGame(this_round, round_number, players[comp_player]->getScore(), players[human_player]->getScore());
    }
    
    //if player decicion is makaing a move, proceed
    if (player_decision != make_move && player_decision != get_help)
        return player_decision;
    
    //if player has no possible moves to make
    if (!playerCanMove(this_round, double_tiles))
    {
        //if player has not yet picked from boneyard in previous turn
        if (!boneyard_picked)
        {
            //if boneyard is not empty
            if ((this_round.getPiles()+boneyard)->getSize() != 0)
            {
                cout<<endl<<endl<<"Player Picked From Boneyard!"<<endl;
                
                boneyard_picked = true;
                
                //add a tile from boneyard to player's hand
                (this_round.getPiles()+this_round.getCurrentPlayer())->addToPile((this_round.getPiles()+boneyard)->getTileOnTop());
                
                //player goes again - to try placing the tile just picked from boneyard on trains
                takeTurn(this_round, double_tiles, boneyard_picked, empty_boneyard_hit, players, round_number, tiles_placed);
            }
            
            //if boneyard is empty
            else
            {
                cout<<endl<<endl<<"Boneyard is Empty. Player Skips Turn!"<<endl;
                empty_boneyard_hit = true;
            }
        }
        
        //if player has already picked from boneyard and can't play drawn tile - mark player's train
        else
        {
            cout<<endl<<endl;
            cout<<"Tile Drawn From Boneyard Cannot be Played!"<<endl;
            cout<<"The Player Train is Marked"<<endl;
            (this_round.getTrains()+this_round.getCurrentPlayer())->addMarker();
        }
        
    }
    
    //if player has at least one move to play
    else
    {
        //ask player to select a tile and a train
        int selection_result = tileTrainSelection(this_round);
        
        //if player does not pick a correct tile-train match
        if (selection_result == incorrect_placement)
        {
            //player goes again since there is a move to play and player has not identified it correctly
            takeTurn(this_round, double_tiles, boneyard_picked, empty_boneyard_hit, players, round_number, tiles_placed);
        }
        
        if (selection_result == double_placement || selection_result == non_double_placemnt)
            tiles_placed++;
        
        //if player successfully placed a double
        if (selection_result == double_placement)
        {
            double_tiles++;
            
            //to allow player to pick from boneyard even if this double is picked from boneyard
            boneyard_picked = false;
            
            //player goes again since a double is placed
            takeTurn(this_round, double_tiles, boneyard_picked, empty_boneyard_hit, players, round_number, tiles_placed);
        }
    }
    
    return player_decision;
}


/* *********************************************************************
Function Name: displayGame
Purpose: To display the current state of the game
Parameters:
            this_round, an object of the class round passed by value.
            It holds the game trains, player hands, and the boneyard.
    
            round_number, an integer passed by value. It refers to the
            current round number of the game.
               
            computer_score, an integer passed by value. It refers to the
            current score of the computer in the game.
    
            human_score, an integer passed by value. It refers to the
            current score of the human in the game.
 
            all the above are used to make the displays
            
Return Value: None
Assistance Received: None
********************************************************************* */
void player::displayGame(round this_round, const int round_number, const int computer_score, const int human_score) const
{
    this_round.displayRoundNumber(round_number);
    this_round.displayPlayerHands(computer_score, human_score);
    this_round.displayBoneyard("BONEYARD");
    this_round.displayPlayerTrains();
    this_round.displayMexicanTrain();
    cout<<endl<<endl;
}

//ask user to press enter (display puposes)
void player::pressEnter() const
{
    cout<<"Press Enter to Continue..."<<endl<<endl<<endl;
    cin.get();
}

/* *********************************************************************
Function Name: playerCanMove
Purpose: To determine if player has at least one possible move to make
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
    
            double_tiles, an integer passed by value. It refers to the
            number of doubles played by the current player before
            the next player goes
Return Value:
                returns true if player has a move
                returns false otherwise
Algorithm:
        (1) identify tiles that match the end of at least one train
        (2) if there are no candidate tiles
                player has no move
            end if
        (3) if player has already placed a double in the previous turn
            and has no non-double this round
                if this is the last tile in player's hand
                    player has a move
                end if
                player has no move
            end if
            otherwise player has a move
 
Assistance Received: None
********************************************************************* */
bool player::playerCanMove(round& this_round, const int double_tiles) const
{
    //identify all the tiles that match the end of one of the eligible trains
    vector<tile> canditates = identifyTileCandidates(this_round);
    
    //if there are no candidate tiles
    if (canditates.size() == 0)
        return false;
    
    //if there is an eligible non-double, player can move
    for (int i=0; i<canditates.size(); i++)
    {
        if (!canditates[i].isDouble())
            return true;
    }
    
    //if player has already placed a double in previous round and has no non-doubles this round
    if (double_tiles == 1)
    {
        //the number of tiles in current player's hand
        int handSize = (this_round.getPiles()+this_round.getCurrentPlayer())->getSize();
        
        //if this is the last tile in player's hand
        if (handSize == 1)
            return true;
        
        //at ths point:
        //player will not be able to play the double here even though it is a match
        //because they will not have a non-double to place in the next round
        
        return false;
    }
    
    //if it's the first double being placed
    return true;
}


/* *********************************************************************
Function Name: tileTrainSelection
Purpose: To select a tile-train pair and place the tile at the train end
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to access the trains here.
Return Value:
            returns incorrect_placement, non-double_placement
            or double_placement (integer - enum)
Assistance Received: None
********************************************************************* */
int player::tileTrainSelection(round& this_round) const
{
    //choose a tile
    int selected_tile = selectTileIndex(this_round);
    
    cout<<endl;
    
    //choose a train
    int selected_train = selectTrainIndex(this_round, selected_tile);
    
    //check if tile matches the train
    int placement_result = matchTileTrain(this_round, selected_tile, selected_train);
    
    //if tile matches the train
    if (placement_result != incorrect_placement)
    {
        //add the tile to the train
        appendTileToTrain(this_round, selected_tile, selected_train);
        
        //if player places a tile on their own train successfuly, any marker on personal train will be removed
        if (selected_train == this_round.getCurrentPlayer())
            (this_round.getTrains()+this_round.getCurrentPlayer())->removeMarker();
    }
    
    return placement_result;
}


/* *********************************************************************
Function Name: matchTileTrain
Purpose: To determine if a tile matches a train end
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
 
            selected_tile_index, an integer passed by value. It refers
            to the index of the selected tile.
            
            selected_train_index, an integer passed by value. It refers
            to the index of the selected train.
Return Value:
            returns incorrect_placement, non-double_placement
            or double_placement (integer - enum)
Algorithm:
        (1)
            if the selected train is mexican train and mexican train is empty
                the train end is the engine
            end if
            else
                the train end is the value of the tile the train ends with
            end else
 
            if the selected tile is a double
                if the front of the tile matches the train end
                    there is a double placement
                end if
            end if
 
            else
                if the front or back of tile matches the train end
                    there is a non-double placement
                end if
            end else
            
            otherwise there is an incorrect placement
 
Assistance Received: None
********************************************************************* */
int player::matchTileTrain(round& this_round, const int selected_tile_index, const int selected_train_index) const
{
    tile selected_tile = (this_round.getPiles()+this_round.getCurrentPlayer())->getTile(selected_tile_index);
    
    int train_end_val;
    
    // if the selected train is mexican train and mexican train is empty
    if (selected_train_index == mexican_train && ((this_round.getTrains()+mexican_train)->getSize() == 0))
    {
        //when mexican train is empty, train end is the engine
        train_end_val = this_round.getEngine().getFrontEnd();
    }
    
    else
    {
        //train end is the value the train ends with
        train_end_val = (this_round.getTrains()+selected_train_index)->getEndVal();
    }
    
    //if the selected tile is a double
    if (selected_tile.isDouble())
    {
        if (selected_tile.getFrontEnd() == train_end_val)
            return double_placement;
    }
    
    else
    {
        if (selected_tile.getFrontEnd() == train_end_val || selected_tile.getBackEnd() == train_end_val)
            return non_double_placemnt;
    }
    
    return incorrect_placement;
}


/* *********************************************************************
Function Name: appendTileToTrain
Purpose: To add an already matched tile to a selected train
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
 
            selected_tile_index, an integer passed by value. It refers
            to the index of the selected tile.
            
            selected_train_index, an integer passed by value. It refers
            to the index of the selected train.
Return Value: None
Algorithm:
        (1)
            if the selected train is mexican train and it is empty
                the train end is the engine
            end if
            else
                the train end is the value of the tile the train ends with
            end else
 
        (2)
            if the back of a non-double tile matches the end of the train
                flip the tile to match the train end
            end if
            
        (3) add the selected tile from player's hand to the train
        (4) remove the selected tile from player's hand
 
Assistance Received: None
********************************************************************* */
void player::appendTileToTrain(round& this_round, const int selected_tile_index, const int selected_train_index) const
{
    tile tile_to_add = (this_round.getPiles()+this_round.getCurrentPlayer())->getTile(selected_tile_index);
    int train_end_val;
    
    //if mexican train is the selected train and it's empty
    if (selected_train_index == mexican_train && ((this_round.getTrains()+mexican_train)->getSize() == 0))
    {
        //when mexican train is empty, train end is the engine
        train_end_val = this_round.getEngine().getFrontEnd();
    }
    
    else
    {
        //train end is the value the train ends with
        train_end_val = (this_round.getTrains()+selected_train_index)->getEndVal();
    }
    
    //if back of a non-double matches the end of train
    if (!tile_to_add.isDouble() && tile_to_add.getFrontEnd() != train_end_val)
    {
        //flip the tile to match train end
        tile_to_add.flip();
    }
    
    //add the tile from player's hand to the train
    (this_round.getTrains()+selected_train_index)->addTile(tile_to_add);
    
    //remove the tile from the player's hand
    (this_round.getPiles()+this_round.getCurrentPlayer())->removeFromPile(tile_to_add);
}


/* *********************************************************************
Function Name: identifyEligibleTrains
Purpose: To identify the eligible trains for player to place tile
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to identify the eligible trains.
Return Value:
            returns eligible train indices, a vector of integers
Algorithm:
        (1)
            if any of the three trains is an orphan double
                if orphan double is not the engine
                    record these trains as eligible
                end if
            end if
 
            if there is any orphan doubles
                only these will be eligible
            end if
        
        (2) record personal train as eligible
        (3) record mexican train as eligible
        
        (4) if opponent train is marked
                opponent train is also eligible
            end if
            
Assistance Received: None
********************************************************************* */
vector<int> player::identifyEligibleTrains(round& this_round) const
{
    vector<int> eligible_trains;
    
    //checking the 3 trains (personal, opponent, mexican)
    for (int i=0; i<this_round.getSize(); i++)
    {
        int train_size = (this_round.getTrains()+i)->getSize();
        
        if ((this_round.getTrains()+i)->isOrphanDouble())
        {
            //if orphan double is not the engine
            if ((this_round.getTrains()+i)->getTile(train_size - 1) != this_round.getEngine())
                eligible_trains.push_back(i);
        }
    }
    
    //if we have any orphan doubles, no other train is eligible
    if (eligible_trains.size() != 0)
        return eligible_trains;
    
    //otherwise (personal train and mexican train are eligible)
    eligible_trains.push_back(this_round.getCurrentPlayer());
    eligible_trains.push_back(mexican_train);
    
    //if opponent train is marked, that is another eligible train
    if ((this_round.getTrains()+this_round.getNextPlayer())->hasMarker())
        eligible_trains.push_back(this_round.getNextPlayer());
    
    return eligible_trains;
}



/* *********************************************************************
Function Name: identifyTileCandidates
Purpose: To identify tiles that match the end of an eligible train(s)
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to identify the tile candidates.
 
Return Value: all unqiue tile candidates, a vector of class tile
Algorithm:
        (1) if any of the tiles match the end of an eligible train
                record them as candidates
            end if
        (2) remove duplicate candidates
 
Assistance Received: None
********************************************************************* */
vector<tile> player::identifyTileCandidates(round& this_round) const
{
    vector<tile> canditates;
    vector<int> eligible_trains = identifyEligibleTrains(this_round);
    int hand_size = (this_round.getPiles()+this_round.getCurrentPlayer())->getSize();
      
    //identify all tiles that match the end of at least one eligible train
    for (int i=0; i<eligible_trains.size(); i++)
    {
        for (int j=0; j<hand_size; j++)
        {
            if (matchTileTrain(this_round, j, eligible_trains[i]))
                canditates.push_back((this_round.getPiles()+this_round.getCurrentPlayer())->getTile(j));
        }
    }
    
    
    //remove duplicates
    //(tiles that macth more than one train are recorded more than once)
    vector<tile> unique_candidates;
    
    for (int i=0; i<canditates.size(); i++)
    {
        bool found = false;
        for (int j=0; j<unique_candidates.size(); j++)
        {
            if (canditates[i] == unique_candidates[j])
                found = true;
        }
        
        if (!found)
            unique_candidates.push_back(canditates[i]);
    }
    
    return unique_candidates;
}


player& player::operator = (player& other_player)
{
    this->m_score = other_player.m_score;
    return *this;
}

















