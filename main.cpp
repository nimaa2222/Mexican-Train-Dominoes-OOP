/*
************************************************************
* Name:     Nima Naghizadehbaee                            *
* Project:  Project 1 - C++ Mexican Train                  *
* Class:    CMPS 366 - OPL                                 *
* Date:     2/16/21                                        *
************************************************************
*/

#include "stdafx.h"

//To display a welcome message to user
void displayWelcomeMsg();

//To ask user whether they want to start a new game or load game
int displayFirstMenu();

//To determine the round's engine based on the round number
int identifyEngine(int round_number);

//To add a specific number of tiles to a player hand (randomly)
void createPlayerHand(deck& copyDeck, pile& player_hand, const int capacity);

//To identify the player starting the round
int identifyFirstPlayer(const int computer_score, const int human_score);

//To perform a coin toss called by human player
int performCoinToss();

//To read a previosuly saved state of the game from a file
void loadGame(game &myGame, train myTrains[], pile myPiles[], player* myPlayers[], tile& engine_tile, int &nextPlayer);

//To get the name of the file to read/write data
string getFileName();

//To mark the trains that end with a double as orphan double
void establishOrphanDoubles(round& thisRound);

//To write the current state of the game to a file
void saveGame(round this_round, const int round_number, const int comp_score, const int human_score);

//To write computer and human hands to the file
void writePiles(const pile* pile_to_write, ofstream& writeFile);

//To write human, computer and mexican train to the file
void writeTrains(const train* train_to_write, ofstream& writeFile, bool);

//To write boneyard to file
void writeBoneyard(const pile* pile_to_write, ofstream& writeFile);

//To display messages once player decides to quit
void displayQuitMessage();

//To display the current state of the game
void displayGame(const round this_round, const int round_number, const int computer_score, const int human_score);

//To display the result of a round
void printRoundResult(round& this_round, const pile* round_piles);

//To display the winner (of round or game) on the screen
void printWinner(const string winner, const string event);

//To display a tie outcome (for round or game)
void printDraw(const string event);

//To display player scores (for round or game)
void printScores(const string event, const int comp_score, const int human_score);

//To ask user about playing another round
int anotherRoundMenu();

//To display the result of the game
void printGameResult(const int computer_score, const int human_score);

//To identify winner (in round or game) based on score comparison
int compareScores(int comp_score, int human_score);


/* *********************************************************************
Function Name: main
Purpose: To play the meixcan train game
Parameters: None
Return Value: 0, illustrating successful program termination
Algorithm:
        (1) create the game players
        (2) create the deck
        (3) create the game
        (4) display welcome message to user
        (5) ask user to start a new round or load game
        (6)
            while user wants to play another round
                create the trains
                create the piles
 
                if user wants to start a new round
                    identify and record round number
                    identify and record round engine
                    make a copy of the game deck
                    make a copy of the engine
                    take out the engine from the deck
                    add engine to the player' hands
                    shuffle the deck for this round
                    add 16 random tiles to computer hand from deck
                    add 16 random tiles to human hand from deck
                    add the remaining tiles to the boneyard
                    identify the first player to start the round
                end if
 
                else (if user wants to load game)
                    read a previosuly saved state of the game from a file
                end else
 
                start a new round
                
                while round is not completed and user has not quit
 
                    if both computer and human skip turns because of empty boneyard
                        the round is completed
                    end  if
    
                    if the player played all their possible eligble moves
                        reset the settings for the next player
                        identify orphan doubles for next player
                    end if
    
                    player takes its turn
 
                    if player has no more tiles in hand
                        record player as the winner of the round
                        the ronud is completed
                    end if
 
                    if player attempeted to draw from an empty boneyard
                        identify the player that attempted this
                    end if
                    
                    if user wants to save the game
                        write the current game status into a file
                    end if
 
                    if user wants to quit
                        display goodbye messages
                        the round is incomplete
                    end if
                        
                    if user did not save game or recieved help in this turn
                        it is the other player's turn to go
                    end if
 
                    else
                        the same player goes again
                    end else
                end while
 
                if user did not quit during the round
                    display the final status of the round
                    display the result of the round
                    display the player scores for the round
                    add the scores for the current round to the game
                    display the overall scores in the game
                    note that one round has been played
                    ask user wther they want to play another round
 
                    if user does not want to play another round
                        display the final results of the game
                    end if
 
                end if
 
                else
                    the user does not want to play another round
                end else
 
        end while
 
    (7) terminate the program
        
Assistance Received: None
********************************************************************* */
int main()
{
    //initialize random seed for randomization
    srand((unsigned)time(NULL));
    
    const int num_trains = 3;
    const int num_piles = 3;
    const int num_players = 2;
    
    //create the game players
    player* players[num_players];
    
    players[comp_player] = new computer;
    players[human_player] = new human;
 
    //create the deck
    deck game_deck;
    
    //create the game
    game the_game(players[comp_player], players[human_player], game_deck);
    
    int first_player;
    tile engine_tile;
    
    //WELCOME TO THE MEXICAN TRAIN GAME!
    displayWelcomeMsg();
    
    //ask user whether they want to start a new game or load game
    int selected_option = displayFirstMenu();
    
    //set to "NO" when user does not want to play another round
    int play_another_round = yes;
    
    //number of rounds played since the exeution of program
    //used to distinguish between loading game and starting a new round
    int num_rounds_played = 0;
    
    //as long as human wants to play another round
    while (play_another_round == yes)
    {
        //create the trains (personal, opponent, mexican)
        train round_trains[num_trains];

        //create the piles (computer hand, human hand, boneyard)
        pile round_piles[num_piles];
        
        //to prevent user from loading after first round
        if (num_rounds_played != 0)
            selected_option = new_game;
        
        if (selected_option == new_game)
        {
            //identify and record the round number
            int round_number = the_game.getRoundNumber() + 1;
            the_game.setRoundNumber(round_number);
            
            //identify and record the round engine
            int engine = identifyEngine(round_number);
            
            //make a copy of the game deck
            deck copy_deck = game_deck;
            
            //make a copy of the engine
            engine_tile.setTile(engine, engine);
            
            //take out the engine from the deck
            copy_deck.removeTile(engine_tile);
            
            //add engine to the player trains
            round_trains[comp_train].addTile(engine_tile);
            round_trains[human_train].addTile(engine_tile);
            
            //shuffle the deck for this round
            copy_deck.Shuffle();
            
            //add 16 random tiles to each player's hand
            const int player_hand_cap = 16;
            createPlayerHand(copy_deck, round_piles[comp_hand], player_hand_cap);
            createPlayerHand(copy_deck, round_piles[human_hand], player_hand_cap);
            
            //add the remaining tiles to the boneyard
            for (int i=0; i<copy_deck.getCurrentSize(); i++)
                round_piles[boneyard].addToPile(copy_deck.getTile(i));
            
            //identify first player of the round
            first_player = identifyFirstPlayer(players[comp_player]->getScore(), players[human_player]->getScore());
        }
        
        //if (selected_option == LOAD_GAME)
        else
        {
            //read a previosuly saved state of the game from a file
            loadGame(the_game, round_trains, round_piles, players, engine_tile, first_player);
        }
        
        //start a new round
        round this_round(round_trains, round_piles, engine_tile, first_player);
        the_game.addRound(this_round);
        cout<<endl<<endl;

        //set to true when a player takes all its possible eligible turns
        bool player_took_turn = true;
        
        //set to true when a player draws from boneyard during their turn
        bool boneyard_picked = false;
        
        //set to true when a player attempts to draw from an empty boneyard
        bool empty_boneyard_hit = false;
        
        //set to true when computer attempts to draw from an empty boneyard
        int computer_skips = false;
        
        //set to true when human attempts to draw from an empty boneyard
        int human_skips = false;
        
        //set to true when the game ends either by a player emptying their hand
        //or when players skip turns because boneyard is empty
        bool round_completed = false;
        
        //set to true if user decides to quit the game during the round
        bool player_quits = false;
        
        //the number of doubles played by a player before next player goes
        int double_tiles_played = 0;
        
        //the number of tiles played by a player before next player goes
        int tiles_placed = 0;
        
        //as long as the round is not completed and user has not decided to quit the game
        while(!round_completed && !player_quits)
        {
            //empty boneyard hit by both players signals the end of a round
            if (computer_skips && human_skips)
            {
                round_completed = true;
                continue;
            }
            
            if (player_took_turn)
            {
                //reset indicators for next player
                tiles_placed  = 0;
                boneyard_picked = false;
                empty_boneyard_hit = false;
                double_tiles_played = 0;
                
                //identify orphan doubles before the next player goes
                establishOrphanDoubles(this_round);
            }
            
            //player takes turn
            int turn_result = players[this_round.getCurrentPlayer()]->takeTurn(this_round, double_tiles_played, boneyard_picked, empty_boneyard_hit, players, the_game.getRoundNumber(), tiles_placed);
            
            //if player has no more tiles during consecutive turns or after taking all the their available turns
            if (turn_result == empty_hand || (((this_round.getPiles()+this_round.getCurrentPlayer())->getSize()) == 0))
            {
                //record the winner
                this_round.setWinner(this_round.getCurrentPlayer());
                
                round_completed = true;
                continue;
            }
            
            //if player attempted to draw from an empty boneyard
            if (empty_boneyard_hit)
            {
                //identify the player that hit the empty boneyard
                if (this_round.getCurrentPlayer())
                    computer_skips = true;
                
                else
                    human_skips = true;
            }
            
            //if user wants to save the current state of the game
            if (turn_result == save_game)
            {
                //write current game status into a file
                saveGame(this_round, the_game.getRoundNumber(), players[comp_player]->getScore(),  players[human_player]->getScore());
            }
            
            //if user wants to leave the game
            if (turn_result == quit)
            {
                displayQuitMessage();
                player_quits = true;
                continue;
            }
            
            //the user has not taken a turn if game was saved or help was recieved
            if (turn_result != save_game && turn_result != get_help)
            {
                player_took_turn = true;
                
                //the other player has to take a turn now
                this_round.switchToOtherPlayer();
            }
            
            else
                player_took_turn = false;
        }
        
        
        //if user did not quit during the round
        if (round_completed)
        {
            //display the final status of the round
            displayGame(this_round, the_game.getRoundNumber(), players[comp_player]->getScore(), players[human_player]->getScore());
            
            //display the result of the round
            printRoundResult(this_round, round_piles);
            
            //display the player scores for the round
            printScores("ROUND", (this_round.getPiles()+comp_hand)->getTileSums(), (this_round.getPiles()+human_hand)->getTileSums());
            
            //add the scores for the current round to the game
            players[comp_player]->updateScore((this_round.getPiles()+comp_hand)->getTileSums());
            players[human_player]->updateScore((this_round.getPiles()+human_hand)->getTileSums());
            
            //display the overall scores in game
            printScores("TOTAL", players[comp_player]->getScore(), players[human_player]->getScore());
            cout<<endl;
            
            //note that one round has been played since program execution
            num_rounds_played++;
            
            //ask user whether they want to play another round
            play_another_round = anotherRoundMenu();
            
            if (play_another_round == no)
            {
                //display the final results of the game
                printGameResult(players[comp_player]->getScore(), players[human_player]->getScore());
                cout<<endl;
            }
            
            //otherwise play another round
            cout<<endl<<endl;
        }
        
        //if user quit during the round
        else
        {
            //end game
            play_another_round = no;
        }
    }
    

    cout<<endl<<endl;
    return 0;
}





/* *********************************************************************
Function Name: displayWelcomeMsg
Purpose: To display a welcome message to user
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void displayWelcomeMsg()
{
    char space = ' ';
    int num_spaces = 55;
    cout<<endl<<endl<<addChar(space, num_spaces)<<"WELCOME TO THE MEXICAN TRAIN GAME!"<<endl;
}


/* *********************************************************************
Function Name: displayFirstMenu
Purpose: To ask user whether they want to start a new game or load game
Parameters: None
Return Value: user's valid selection, an integer
Assistance Received: None
********************************************************************* */
int displayFirstMenu()
{
    //set to true once a valid selection is made
    bool valid_input = false;
    
    //user's selection
    int selection = 0;
    
    while (!valid_input)
    {
        //display menu to user and ask for a selection
        string player_selection;
        cout<<"Select One of the Following Options:"<<endl;
        cout<<"1) Start a New Game"<<endl;
        cout<<"2) Load Game"<<endl;
        getline(cin, player_selection);
        
        //make sure input is valid (the maximum selection is 2)
        selection = validateInput(player_selection, 2);
        
        //prompt user to select again if input was invalid
        if (selection != invalid_input)
            valid_input = true;
    }
    
    
    return selection;
}


/* *********************************************************************
Function Name: identifyEngine
Purpose: To determine the round's engine based on the round number
Parameters:
            round_number, an integer passed by value. It refers to
            to the round number of the game of which we are attempting
            to find the engine for.
 
Return Value: the numerical value of the engine tile, an integer
Assistance Received: None
********************************************************************* */
int identifyEngine(int round_number)
{
    if (round_number > 10)
        round_number -= 10;
    
    int engine_num = 10 - round_number;
    return engine_num;
}


/* *********************************************************************
Function Name: createPlayerHand
Purpose: To add a specific number of tiles to a player hand (randomly)
Parameters:
            game_deck, an object of the deck class passed by reference.
            It holds all the tiles in the game deck with the exception
            of the engine tile. Here, tiles are removed from game_deck.
            
            player_hand, an object of the pile class passed by reference.
            It holds the tiles in the player's hand. Tiles are added to
            player_hand from game_deck.
            
            tiles_to_add, an integer which indicates how many tiles
            are added from the game deck to the player's hand.
 
Return Value: None
Assistance Received: None
********************************************************************* */
void createPlayerHand(deck& game_deck, pile& player_hand, const int tiles_to_add)
{
    //as long as all the specified tiles are not added to the player's hand
    while (player_hand.getSize() < tiles_to_add)
    {
        //generate a random number between 0 and (new size of the deck - 1)
        int rand_num = rand() % game_deck.getCurrentSize();
        
        //add the tile matching the index to the player's hand from the deck
        player_hand.addToPile(game_deck.getTile(rand_num));
        
        //remove the tile from the deck
        game_deck.removeTile(game_deck.getTile(rand_num));
    }
}


/* *********************************************************************
Function Name: identifyFirstPlayer
Purpose: To identify the player starting the round
Parameters:
            computer_score, an integer passed by value. It refers to
            the total score of the computer so far in the game.
            
            human_score, an integer passed by value. It refers to the
            total score of the human so far in the game.
 
Return Value: the player to start the round, an integer (enum)
Algorithm:
         if human score is lower than computer score
                human player goes first
         if computer score is lower than human score
                computer goes first
         otherwise
                game is tied (coin toss will decide)
 
Assistance Received: None
********************************************************************* */
int identifyFirstPlayer(const int computer_score, const int human_score)
{
    //will hold the player that should start the round
    int first_player;
    
    cout<<endl;
    
    if (human_score < computer_score)
    {
        cout<<"Since Your Score is Lower Than Computer Score, You Will Start the Round :)"<<endl;
        first_player = human_player;
    }
    
    else if (human_score > computer_score)
    {
        cout<<"Since Computer Score is Lower Than Your Score, Computer Will Start the Round :("<<endl;
        first_player = comp_player;
    }
    
    //if socres are tied up
    else
    {
        //a coin toss will determine the first player
        first_player = performCoinToss();
    }
    
    return first_player;
}


/* *********************************************************************
Function Name: performCoinToss
Purpose: To perform a coin toss called by human player
Parameters: None
Return Value: the player to start the round, an integer (enum)
Algorithm:
        1) ask human for a heads or tails call
        2) generate a random heads/tails (1 or 2)
        3)
            if human gussed right
                human goes first
            otherwise
                computer goes first
           
Assistance Received: None
********************************************************************* */
int performCoinToss()
{
    //set to true once a valid selection is made
    bool valid_input = false;
    
    //user's call on the coin toss
    int selection = 0;
    
    while (!valid_input)
    {
        //ask user for a heads or tails call
        string coin_selection;
        cout<<"The Game is Tied at the Moment. Coin is Tossed to Choose First Player."<<endl;
        cout<<"1) Heads"<<endl;
        cout<<"2) Tails"<<endl;
        getline(cin, coin_selection);
        
        //make sure input is valid (the maxium selection is 2)
        selection = validateInput(coin_selection, 2);
        
        //prompt user to select again if input was invalid
        if (selection != invalid_input)
            valid_input = true;
    }
    
    //generates either the number 1 or 2
    int coin_toss = rand() % 2 + 1;
    
    //if human guessed right
    if (selection == coin_toss)
    {
        cout<<"You Made the Right Call"<<endl;
        cout<<"You Will Start the Round"<<endl;
        return human_player;
    }
    
    else
    {
        cout<<"You Made the Wrong Call"<<endl;
        cout<<"Computer Will Start the Round"<<endl;
        return comp_player;
    }
}


/* *********************************************************************
Function Name: loadGame
Purpose: To read a previosuly saved state of the game from a file
Parameters:
            the_game, an object of the game class passed by reference.
            It holds all the game information (the deck, the players,
            and the rounds). It is modified in that the current round
            number is recorded.
            
            game_trains[], an array of objects of the train class
            passed by reference. Each hold the tiles in one of the
            trains.They are modified in that tiles are added to them
            and they may be marked with a marker if noted.
 
            game_piles[], an array of objects of the pile class passed
            by reference. Each hold the tiles in either the computer
            hand, human hand, or the boneyard. They are modified in that
            tiles are added to them.
 
            game_players[], a pointer to an array of objects of the
            player class passed by reference. Each hold the score of
            the human player or computer player. They are modified in
            that the player's game scores are updated.
 
            engine_tile, an object of the tile class passed by reference.
            It is the engine tile of the current round. It is modified
            in that it is identified and set.
 
            next_player, an integer passed by reference. It refers to the
            player who plays next in the round. It is modified
            in that it is identified and set.
            
Return Value: None
Algorithm:
        1) ask user for the name of the file to read data from
        2)
            while the end of the file is not reached
                read one line from the file
                process the first word of the line
 
                if the first word = "Round:"
                    read in the next word from the line
                    record this number as the round number
                end if
 
                else if the first word = "Score:"
                    read in the next word from the line
 
                    if the computer data has not been yet recorded
                        record this score for computer
                    end if
            
                    else
                        record this score for human
                    end else
                end else if
 
                else if the first word = "Hand:"
 
                    if the computer data has not been yet recorded
                        player hand will be recorded
                    end if
                    
                    else
                        computer hand will be recorded
                    end else
                    
                    while there are still words to read on this line
                        read in the next word
                        add this word as a tile to player hand
                    end while
                end else if
 
                else if the first word = "Train:"
                    if computer train is being processed
                        read in the second word
                        if the second word = 'M'
                            add a marker to the train
                        end if
                        else
                            add the second word as a tile to player train
                        end else
                        
                        read in the remaining tiles (flipped version)
                        add remaining tiles to player train
                        reverse the train
                    end if
 
                    if human train is being processed
                        record the first tile as round engine
                        read in the remaining tiles
                        add marker if necessary
                    end if
                end else if
 
                else if the first word = "Mexican"
                    read in the second word
                    if the second word = "Train:"
                        while there are still words to read on this line
                            read in the next word
                            add this word as a tile to mexican train
                        end while
                    end if
                    else
                        there is invalid informatting
                    end else
                end else if
 
 
                else if the word = "Boneyard:"
                    while there are still words to read on this line
                        read in the next word
                        add this word as a tile to a temporary container
                    end while
    
                    add the elements from temporary container to boneyard in reverse order
 
                end else if
 
 
                else if the word = "Next"
                    read in the second word
                    if the second word = "Player:"
                        read in the third word
                            if the third word = "Computer"
                                record computer as next player
                            end if
                            else if third word = "Human"
                                record human as next player
                            end else if
                            else
                                there is invalid formatting
                            end else
                    end if
 
                    else
                        there is invalid formatting
                    end else
                end else if
 
 
                else if the first word = "Human:"
                    note that all computer data has been read
                end else if
 
                else
                    if there are empty lines
                        skip them
                    end if
                    else
                        there is invalid formatting
                    end else
                end else
        end while
 
    (4) close the file
 
    (5)
        if there is a formatting error
            inform user about this
            prompt user to load another file
        end if
 
Assistance Received: None
********************************************************************* */
void loadGame(game &the_game, train game_trains[], pile game_piles[], player* game_players[], tile& engine_tile, int &next_player)
{
    //ask user for the name of the file where the game information is stored
    string filename = getFileName();
    ifstream file(filename);
    
    if (!file)
    {
        cout<<"File Was Not Found"<<endl;
        loadGame(the_game, game_trains, game_piles, game_players, engine_tile, next_player);
    }
    
    if (!file.is_open())
    {
        cout<<"File Did Not Successfuly Open"<<endl<<endl;
        loadGame(the_game, game_trains, game_piles, game_players, engine_tile, next_player);
    }
    
    //used to indicate that reading of the information about computer player is completed
    bool comp_data_read = false;
    
    //set to true if file is not properly formatted
    bool invalid_data = false;
    
    //converion value to convert a numeric character to a number
    int conv_val = 48;
    
    //used to read lines from the file
    string fileLine;
    
    while (!file.eof())
    {
        //read one line from file
        getline(file, fileLine);
        
        stringstream lineReader(fileLine);
        
        //read in the first word of the line
        string first_word;
        lineReader >> first_word;
        
        //used in certain conditions when processing a line
        string second_word;
        
        //record round number
        if (first_word == "Round:")
        {
            lineReader >> second_word;
            the_game.setRoundNumber(stoi(second_word));
        }
        
        //record player scores
        else if (first_word == "Score:")
        {
            lineReader >> second_word;
            
            if (!comp_data_read)
                game_players[comp_player]->updateScore(stoi(second_word));
            
            else
                game_players[human_player]->updateScore(stoi(second_word));
        }
        
        //record player hand tiles
        else if (first_word == "Hand:")
        {
            int player_hand;
            
            if (!comp_data_read)
                player_hand = comp_player;
            else
                player_hand = human_player;
            
            string hand_tile;
    
            while (lineReader >> hand_tile)
            {
                tile newTile(hand_tile[0] - conv_val, hand_tile[2] - conv_val);
                game_piles[player_hand].addToPile(newTile);
            }
        }
        
        //record player train tiles
        else if (first_word == "Train:")
        {
            int personal_train;
            
            if (!comp_data_read)
                personal_train = comp_player;
            else
                personal_train = human_player;
            
            
            if (personal_train == comp_player)
            {
                lineReader >> second_word;
                
                //if train is marked
                if (second_word == "M")
                    game_trains[personal_train].addMarker();
                
                else
                {
                    //record the tile that was read (flipped version)
                    tile new_tile(second_word[2] - conv_val, second_word[0] - conv_val);
                    game_trains[personal_train].addTile(new_tile);
                }
                
                //read in the remaining tiles (flipped version)
                string train_tile;
                while (lineReader >> train_tile)
                {
                    tile new_tile(train_tile[2] - conv_val, train_tile[0] - conv_val);
                    game_trains[personal_train].addTile(new_tile);
                }
                
                //reverse the tile ordering of train
                game_trains[personal_train].reverseTrain();
            }
            
            
            //personal_train = human_player
            else
            {
                //the first tile is the engine
                lineReader >> second_word;
                tile new_tile(second_word[0] - conv_val, second_word[2] - conv_val);
                game_trains[personal_train].addTile(new_tile);
                engine_tile = new_tile;
                
                //read in the remaining tiles
                string train_tile;
                while (lineReader >> train_tile)
                {
                    if (train_tile != "M")
                    {
                        tile new_tile(train_tile[0] - conv_val, train_tile[2] - conv_val);
                        game_trains[personal_train].addTile(new_tile);
                    }
                    
                    else
                        game_trains[personal_train].addMarker();
                }
            }
        }
        
        //record mexican train tiles
        else if (first_word == "Mexican")
        {
            lineReader >> second_word;
            
            if (second_word == "Train:")
            {
                string train_tile;
                while (lineReader >> train_tile)
                {
                    tile newTile(train_tile[0] - conv_val, train_tile[2] - conv_val);
                    game_trains[mexican_train].addTile(newTile);
                }
            }
            
            else
                invalid_data = true;
        }
        
        //record boneyard
        else if (first_word == "Boneyard:")
        {
            //used to reverse the ordering of the boneyard
            vector<tile> temp;
            
            //get the boneyard elements from file
            string boneyard_tile;
            while (lineReader >> boneyard_tile)
            {
                tile new_tile(boneyard_tile[0] - conv_val, boneyard_tile[2] - conv_val);
                temp.push_back(new_tile);
            }
            
            //record the reverse ordering of the boneyard
            int j = (int)temp.size() - 1;
            for (int i=0; i<temp.size(); i++)
            {
                game_piles[boneyard].addToPile(temp[j]);
                j--;
            }
        }
        
        //identify the next player
        else if (first_word == "Next")
        {
            string third_word;
            lineReader >> second_word;
            
            if (second_word == "Player:")
            {
                lineReader >> third_word;
                if (third_word == "Computer")
                    next_player = comp_player;
                
                else if (third_word == "Human")
                    next_player = human_player;
                
                else
                    invalid_data = true;
            }
            
            else
                invalid_data = true;
        }
        
        
        else if (first_word == "Human:")
        {
            //note that human game information should be read now
            comp_data_read = true;
        }
        
        else
        {
            //skip empty lines
            if (first_word.size() != 0 && first_word != "Computer:")
                invalid_data = true;
        }
    }
    
    file.close();
    
    //if there is a formatting error
    if (invalid_data)
    {
        cout<<"The file is not properly formatted!"<<endl;
        loadGame(the_game, game_trains, game_piles, game_players, engine_tile, next_player);
    }
}


/* *********************************************************************
Function Name: getFileName
Purpose: To get the name of the file to read/write data
Parameters: None
Return Value: the name of the file, a string
Assistance Received: None
********************************************************************* */
string getFileName()
{
    //ask user for the name of the file
    string filename;
    cout<<"Enter the Name of The File"<<endl;
    getline(cin, filename);
    
    //make sure user input meets the requirement
    if (filename.size() > 10)
    {
        cout<<endl<<"Filename Name Must be At Most 10 Characters"<<endl;
        getFileName();
    }
    
    return filename;
}

/* *********************************************************************
Function Name: establishOrphanDoubles
Purpose: To mark the trains that end with a double as orphan double
Parameters:
            this_round, an object of the class round passed by reference.
            It holds the game trains, player hands, and the boneyard.
            It is modified in that its trains that end with a double
            tile will be marked as orphan double.
            
Return Value: None
Assistance Received: None
********************************************************************* */
void establishOrphanDoubles(round& this_round)
{
    for (int i=0; i<this_round.getSize(); i++)
        (this_round.getTrains()+i)->setOrphanDouble();
}

/* *********************************************************************
Function Name: saveGame
Purpose: To write the current state of the game to a file
Parameters:
            this_round, an object of the class round passed by value.
            It holds the game trains, player hands, and the boneyard.
            It is used to write the listed information to the file.
 
            round_number, an integer passed by value. It refers to the
            current round number of the game.
            
            computer_score, an integer passed by value. It refers to the
            current score of the computer in the game.
 
            human_score, an integer passed by value. It refers to the
            current score of the human in the game.
 
Return Value: None
Algorithm:
        (1) Get the name of the file to write the game information into
        (2) Open the file
        (3) Write the round number information to the file
        (4) Write the computer score to the file
        (5) Write the computer hand to the file
        (6) Write the computer train backwards to the file (mark if necessary)
        (7) Write the human score to the file
        (8) Write the human hand to the file
        (9) Write the human train to the file (mark if necessary)
        (10) Write the Mexican train to the file
        (11) Write the boneyard to the file
        (12) Write the next player to the file
        (13) Close the file
 
Assistance Received: None
********************************************************************* */
void saveGame(round this_round, const int round_number, const int computer_score, const int human_score)
{
    //used to distinguish between writing of computer train and other trains
    bool computer_train;
    
    //ask user for the name of the file to save the game into
    string file_name = getFileName();
    ofstream writeFile;
    
    writeFile.open(file_name);
    string spacing = "   ";
    
    //write round number to file
    writeFile<<"Round: "<<round_number<<endl<<endl;
    
    //write computer score to file
    writeFile<<"Computer:"<<endl;
    writeFile<<spacing<<"Score: "<<computer_score<<endl;
    
    //write computer hand to file
    writeFile<<spacing<<"Hand: ";
    writePiles(this_round.getPiles()+comp_player, writeFile);
    writeFile<<endl;
    
    //write computer train to file (mark if necessary)
    writeFile<<spacing<<"Train: ";
    
    if ((this_round.getTrains()+comp_player)->hasMarker())
        writeFile<<"M ";
    
    computer_train = true;
    writeTrains(this_round.getTrains()+comp_player, writeFile, computer_train);
    writeFile<<endl<<endl;
    
    //write the human score to file
    writeFile<<"Human:"<<endl;
    writeFile<<spacing<<"Score: "<<human_score<<endl;
    
    //write human hand to file
    writeFile<<spacing<<"Hand: ";
    writePiles(this_round.getPiles()+human_player, writeFile);
    writeFile<<endl;
    
    //write human train to file (mark if necessary)
    writeFile<<spacing<<"Train: ";
    computer_train = false;
    writeTrains(this_round.getTrains()+human_player, writeFile, computer_train);
    
    if ((this_round.getTrains()+human_player)->hasMarker())
        writeFile<<"M ";
    
    writeFile<<endl<<endl;
    
    //write the mexican train to file
    writeFile<<"Mexican Train: ";
    writeTrains(this_round.getTrains()+mexican_train, writeFile, computer_train);
    writeFile<<endl<<endl;
    
    //write the boneyard to file
    writeFile<<"Boneyard: ";
    writeBoneyard(this_round.getPiles()+boneyard, writeFile);
    writeFile<<endl<<endl;
    
    //write the next player to file
    writeFile<<"Next Player: ";
    if (this_round.getCurrentPlayer() == 0)
        writeFile<<"Computer";
    else
        writeFile<<"Human";
    cout<<endl;
    
    writeFile.close();
    
    cout<<"Game is Successfully Saved!"<<endl;
}

/* *********************************************************************
Function Name: writePiles
Purpose: To write player hands to the file
Parameters:
            pile_to_write, an object of the pile class passed by value.
            It holds a collection of tiles to be written to the file.
            
            writeFile, an object of the ofstream class passed by
            reference. It is modified in that the pile is written to it.
            
Return Value: None
Assistance Received: None
********************************************************************* */
void writePiles(const pile* pile_to_write, ofstream& writeFile)
{
    for (int i=0; i<pile_to_write->getSize(); i++)
        writeFile<<(pile_to_write->getTile(i)).getFrontEnd()<<"-"<<(pile_to_write->getTile(i)).getBackEnd()<<" ";
}

/* *********************************************************************
Function Name: writeTrains
Purpose: To write human, computer and mexican train to the file
Parameters:
            train_to_write, an object of the train class passed by
            value. It holds the tiles of one of the game trains
            listed above. This will be written to the file.
            
            writeFile, an object of the ofstream class passed by
            reference. It is modified in that the train is written
            to it.
 
            computer_train, a boolean passed by value. It is used
            to indicate if computer train is being written.
            
Return Value: None
Assistance Received: None
********************************************************************* */
void writeTrains(const train* train_to_write, ofstream& writeFile, bool computer_train)
{
    if (computer_train)
    {
        //write computer train backwards
        for (int i = train_to_write->getSize() - 1; i > -1; i--)
            writeFile<<(train_to_write->getTile(i)).getBackEnd()<<"-"<<(train_to_write->getTile(i)).getFrontEnd()<<" ";
    }
    
    else
    {
        //write human and mexican train forward
        for (int i=0; i<train_to_write->getSize(); i++)
            writeFile<<(train_to_write->getTile(i)).getFrontEnd()<<"-"<<(train_to_write->getTile(i)).getBackEnd()<<" ";
    }
}

/* *********************************************************************
Function Name: writeBoneyard
Purpose: To write the boneyard to the file
Parameters:
            pile_to_write, an object of the pile class passed by value.
            It holds the tiles of the boneyard.
            
            writeFile, an object of the ofstream class passed by
            reference. It is modified in that the boneyard is written
            to it.
            
Return Value: None
Assistance Received: None
********************************************************************* */
void writeBoneyard(const pile* pile_to_write, ofstream& writeFile)
{
    for (int i = pile_to_write->getSize() - 1; i > -1; i--)
        writeFile<<(pile_to_write->getTile(i)).getFrontEnd()<<"-"<<(pile_to_write->getTile(i)).getBackEnd()<<" ";
}

/* *********************************************************************
Function Name: displayQuitMessage
Purpose: To display messages once player decides to quit
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void displayQuitMessage()
{
    cout<<endl<<endl;
    cout<<"You have Successfully Left the Game"<<endl;
    cout<<"Hope to See You Soon!"<<endl;
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
void displayGame(const round this_round, const int round_number, const int computer_score, const int human_score)
{
    this_round.displayRoundNumber(round_number);
    this_round.displayPlayerHands(computer_score, human_score);
    this_round.displayBoneyard("BONEYARD");
    this_round.displayPlayerTrains();
    this_round.displayMexicanTrain();
    cout<<endl<<endl;
}

/* *********************************************************************
Function Name: printRoundResult
Purpose: To display the result of a round
Parameters:
            this_round, an object of the class round passed by
            reference. It holds the game trains, player hands, and the
            boneyard. It is modified in that the winner of the round
            is set for this_round.
    
            round_piles, a pointer to an array of pile objects.
            It holds the player hands which is used to identify winner
            if both players have tiles left in their hand once
            the round is over.
            
Return Value: None
Algorithm:
        (1)
            if one player finished the round with no tiles in their hand
                that player wins
            end if
 
            else
                the player with the lower pip sum of tiles in hand wins
            end else
                
Assistance Received: None
********************************************************************* */
void printRoundResult(round& this_round, const pile* round_piles)
{
    //used for displaying purposes
    string comp = "COMPUTER";
    string humn = "HUMAN";
    string rnd = "ROUND";
    
    //if one player finished the round with no tiles left in their hand
    if (this_round.getWinner() != draw)
    {
        if (this_round.getWinner() == comp_player)
            printWinner(comp, rnd);
            
        else
            printWinner(humn, rnd);
    }
    
    //if both players have tiles in their hand and the round is completed
    else
    {
        //find winner of the round based on pip sum of tiles left in the players' hands
        int winner = compareScores((round_piles+comp_hand)->getTileSums(), (round_piles+human_hand)->getTileSums());
        
        //record the winner of the round
        this_round.setWinner(winner);
        
        //display the winner (or a draw) on the screen
        if (winner == comp_player)
            printWinner(comp, rnd);
        
        else if (winner == human_player)
            printWinner(humn, rnd);
        
        else
            printDraw(rnd);
    }
}

/* *********************************************************************
Function Name: printWinner
Purpose: To display the winner (of round or game) on the screen
Parameters:
            winner, a string passed by value. It holds the
            game (or round) winner.
    
            event, a string passed by value. It refers to either a
            round or the game.
            
Return Value: None
Assistance Received: None
********************************************************************* */
void printWinner(const string winner, const string event)
{
    cout<<winner<<" WINS THE "<<event<<"!"<<endl;
}

/* *********************************************************************
Function Name: printDraw
Purpose: To display a tie outcome (for round or game)
Parameters:
            event, a string passed by value. It refers to either a
            round or the game.
 
Return Value: None
Assistance Received: None
********************************************************************* */
void printDraw(const string event)
{
    cout<<"THE "<<event<<" ENDS IN A TIE"<<endl<<endl;
}

/* *********************************************************************
Function Name: printScores
Purpose: To display player scores (for round or game)
Parameters:
            event, a string passed by value. It refers to either a
            round or the game.
 
            computer_score, an integer passed by value. It refers to the
            computer score at the end of a round (or the game).
 
            human_score, an integer passed by value. It refers to the
            human score at the end of a round (or the game).
 
Return Value: None
Assistance Received: None
********************************************************************* */
void printScores(const string event, const int computer_score, const int human_score)
{
    cout<<event<<" SCORES: COMPUTER("<<computer_score<<") - HUMAN("<<human_score<<")"<<endl;
}


/* *********************************************************************
Function Name: anotherRoundMenu
Purpose: To ask user about playing another round
Parameters: None
Return Value: player's selection, an integer
Assistance Received: None
********************************************************************* */
int anotherRoundMenu()
{
    //ask user whether they would like to play another round
    string player_selection;
    cout<<"Would You Like to Play Another Round?"<<endl;
    cout<<"1) YES"<<endl;
    cout<<"2) NO"<<endl;
    getline(cin, player_selection);
    
    //make sure input is valid (the maximum selection is 2)
    int selection = validateInput(player_selection, 2);
    
    if (selection == invalid_input)
    {
        //prompt user to select again if input is invalid
        anotherRoundMenu();
    }
    
    return selection;
}


/* *********************************************************************
Function Name: printGameResult
Purpose: To display the result of the game
Parameters:
            computer_score, an integer passed by value. It refers to the
            computer score at the end of the game.
 
            human_score, an integer passed by value. It refers to the
            human score at the end of the game.
 
Return Value: None
Assistance Received: None
********************************************************************* */
void printGameResult(const int computer_score, const int human_score)
{
    //check if either player has a lower score compared to the other
    int result = compareScores(computer_score, human_score);
    string event = "GAME";
    
    cout<<endl;
    
    if (result != draw)
    {
        if (result == comp_player)
            printWinner("COMPUTER", event);
        else
            printWinner("HUMAN", event);
    }
    
    else
        printDraw(event);
}


/* *********************************************************************
Function Name: compareScores
Purpose: To identify winner (in round or game) based on score comparison
Parameters:
            computer_score, an integer passed by value. It refers to the
            computer score at the end of a round or the game.
 
            human_score, an integer passed by value. It refers to the
            human score at the end of a round or the game.
 
Return Value: the player with lower score, or a tie (an integer) - enum
Assistance Received: None
********************************************************************* */
int compareScores(const int computer_score, const int human_score)
{
    if (computer_score > human_score)
        return human_player;
    
    if (computer_score < human_score)
        return comp_player;
    
    return draw;
}
