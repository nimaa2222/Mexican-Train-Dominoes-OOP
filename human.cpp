#include "stdafx.h"

/* *********************************************************************
Function Name: displayTrainEligiblity
Purpose: To display the eligiblity of the trains
Parameters:
            eligible_trains, a vector of integers passed by value.
            It holds the index of the eligible trains.
 
Return Value: None
Assistance Received: None
********************************************************************* */
void human::displayTrainEligiblity(const vector<int> eligible_trains) const
{
    cout<<"Select an Eligible Train to Place Tile"<<endl;
    
    for(int i=0; i<3; i++)
    {
        cout<<i+1<<") ";
        
        if (i == comp_train)
            cout<<"Computer";
        else if (i == human_train)
            cout<<"Your";
        else
            cout<<"Mexican";
            
        cout<<" Train";
        
        //if this train is not eligilbe
        if (find(eligible_trains.begin(), eligible_trains.end(), i) == eligible_trains.end())
            cout<<" - NOT ELIGIBLE";
        
        cout<<endl;
    }
    cout<<endl;
}



/* *********************************************************************
Function Name: selectAction
Purpose: To ask user to choose an option from the menu
Parameters: None
Return Value: the user's decision, an integer (decision enum)
Assistance Received: None
********************************************************************* */
int human::selectAction() const
{
    //set to true once a valid selection is made
    bool valid_input = false;
    
    //user's selection
    int selection = 0;
    
    while (!valid_input)
    {
        //display a menu to the user
        string menu_selection;
        cout<<"Select One of the Following Options:"<<endl;
        cout<<"1) Save the Game"<<endl;
        cout<<"2) Make a Move"<<endl;
        cout<<"3) Ask for Help"<<endl;
        cout<<"4) Quit the Game"<<endl;
        getline(cin, menu_selection);
        cout<<endl;
        
        //check if input is valid (the maximum selection is 4)
        selection = validateInput(menu_selection, 4);
        
        if (selection != invalid_input)
            valid_input = true;
    }
    
    return selection;
}


/* *********************************************************************
Function Name: selectTileIndex
Purpose: To ask player to choose a tile in their hand to play
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to access player hand.
 
Return Value: the selected tile's index, an integer
Algorithm:
            (1) prompt user to select a tile
            (2) make sure input is valid
            (3) make sure the tile matches an eligible train
            (4) if not, ask user for another tile selection
Assistance Received: None
********************************************************************* */
int human::selectTileIndex(round& this_round) const
{
    //set to true when a valid selection is made
    bool valid_input = false;
    
    //the index of the selected tile in player's hand
    int tile_index = 0;
    
    //establish the highest tile index in player's hand
    int max_tile_index = ((this_round.getPiles()+this_round.getCurrentPlayer())->getSize()) - 1;
    
    while (!valid_input)
    {
        //inform user about how to select a tile
        string selected_tile;
        cout<<"Your Turn - Select a Tile From Your Hand ";
        cout<<"(Count From Left to Right Starting At 1)"<<endl;
        getline(cin, selected_tile);
        cout<<endl;
        
        //max_tile_index + 1 because we are making index of first tile = 1
        tile_index = validateInput(selected_tile, max_tile_index + 1);
        
        if (tile_index != invalid_input)
            valid_input = true;
    }
    
    //to match index with the way it is stored in player's hand
    tile_index--;
    
    //at this point we have a valid tile selection that exists in player hand
    vector<tile> candidates = identifyTileCandidates(this_round);
    tile tile_to_check = (this_round.getPiles()+this_round.getCurrentPlayer())->getTile(tile_index);
    
    //set to true if tile matches the end of an eligible train
    bool found_match = false;
    
    for (int i=0; i<candidates.size(); i++)
    {
        if (tile_to_check == candidates[i])
            found_match = true;
    }
        
    //if there is no eligible train that matches the tile
    if (!found_match)
        selectTileIndex(this_round);
    
    return tile_index;
}


/* *********************************************************************
Function Name: selectTrainIndex
Purpose: To ask player to choose a train to place their selected tile on
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is used to identify eligible trains.
 
            selected_tile, an integer passed by reference. It refers
            to the selected tile index.
 
Return Value: the selected train's index, an integer
Algorithm:
            (1) prompt user to select one of the eligible trains
            (2) make sure user input is valid
            (3) make sure user selected an eligible train
            (4) if not, user has to select again
Assistance Received: None
********************************************************************* */
int human::selectTrainIndex(round& this_round, int& selected_tile) const
{
    //set to true once a valid option is selected
    bool valid_input = false;
    
    //the index of the seleted train by user
    int train_index = 0;
    
    vector<int> eligilbe_trains = identifyEligibleTrains(this_round);
    
    //there are only 3 trains in the game
    int train_max_selection = 3;
    
    while (!valid_input)
    {
        string selected_train;
        displayTrainEligiblity(eligilbe_trains);
        getline(cin, selected_train);
        
        train_index = validateInput(selected_train, train_max_selection);
        
        if (train_index != invalid_input)
            valid_input = true;
        
        //make sure index matches how the trains are stored
        train_index--;
        
        //make sure player selected an eligible train
        bool train_exists = false;
        for (int i=0; i<eligilbe_trains.size(); i++)
        {
            if (eligilbe_trains[i] == train_index)
                train_exists = true;
        }
        
        if (!train_exists)
            valid_input = false;
    }
    
    return train_index;
}
