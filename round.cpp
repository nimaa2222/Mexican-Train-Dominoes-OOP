#include "stdafx.h"

round::round()
{
    m_engine = tile(0,0);
    m_current_player = comp_player;
    m_winner = draw;
}

round::round(const train roundTrains[], const pile roundPiles[], const tile engine, const int currentPlayer)
{
    for (int i=0; i<m_size; i++)
    {
        this->m_round_piles[i] = roundPiles[i];
        this->m_round_trains[i] = roundTrains[i];
    }
    
    this->m_engine = engine;
    this->m_current_player = currentPlayer;
    
    //to indicate that round is tied the moment
    m_winner = draw;
}

round::round(const round& other_round)
{
    //copying over the piles and the trains
    for (int i=0; i<m_size; i++)
    {
        this->m_round_piles[i] = other_round.m_round_piles[i];
        this->m_round_trains[i] = other_round.m_round_trains[i];
    }
    
    m_engine = other_round.m_engine;
    m_current_player = other_round.m_current_player;
    m_winner = other_round.m_winner;
}

//*** destrcutor ***//
round::~round()
{
    //m_size --> static variable will be automatically destroyed
    //m_round_piles --> static array destoyed + underlying object destructor called
    //m_round_trains --> static array destoyed + underlying object destructor called
    //m_engine --> underlying object destructor called
    //m_current_player --> static variable will be automatically destroyed
    //m_winner --> static variable will be automatically destroyed
}

//*** getters and setters ***//
int round::getSize() const
{
    return m_size;
}

int round::getCurrentPlayer() const
{
    return m_current_player;
}

int round::getNextPlayer() const
{
    if (m_current_player == comp_player)
        return human_player;
    
    return comp_player;
}

int round::getWinner() const
{
    return m_winner;
}

pile* round::getPiles()
{
    return m_round_piles;
}

train* round::getTrains()
{
    return m_round_trains;
}

tile round::getEngine() const
{
    return m_engine;
}

void round::setWinner(const int round_winner)
{
    m_winner = round_winner;
}

void round::switchToOtherPlayer()
{
    if (m_current_player == comp_player)
        m_current_player = human_player;
    else
        m_current_player = comp_player;
}


//*** other ***//

/* *********************************************************************
Function Name: displayRoundNumber
Purpose: To display the current round number with proper formatting
Parameters:
            round_num, an integer passed by value. It holds the
            round number.
Return Value: None
Assistance Received: None
********************************************************************* */
void round::displayRoundNumber(const int round_num) const
{
    char space = ' ';
    char dash = '-';
    
    //Display the round number in the center (first line)
    cout<<addChar(space, 65)<<"ROUND: "<<round_num<<endl;
    
    //Center the next line (second line)
    cout<<addChar(space, 65);
    
    //identify number of digits in the round
    int round_digits = (int)to_string(round_num).size();
    int num_lines = 8 + round_digits;

    //underline the round number based on number of digits
    cout<<addChar(dash, num_lines)<<endl;
}

/* *********************************************************************
Function Name: formatScore
Purpose: To display the player socres with proper formatting
Parameters:
            player, a string passed by value. It refers to the player
            whose score will be displayed.
 
            score, an integer passed by value. It holds the player
            score.
 
            space_nums, an integer passed by value. It holds the
            appropriate spacing between score and player name
 
Return Value: None
Assistance Received: None
********************************************************************* */
void round::formatScore(const string player, const int score, const int space_nums) const
{
    char space = ' ';
    
    //second line
    cout<<"| "<<player;
    
    //find number of digits in player score
    int score_size = (int)to_string(score).size() + 8;
    
    //caculate the number of spaces needed
    int spaces_needed = space_nums - score_size;
    
    //add space between player and score
    cout<<addChar(space, spaces_needed)<<"SCORE: "<<score<<" |";
}

/* *********************************************************************
Function Name: displayPlayerHands
Purpose: To display the tiles in players' hands
Parameters:
            computer_score, an integer passed by value. It refers to the
            computer score in this round.
 
            human_score, an integer passed by value. It refers to the
            human score in this round.
Return Value: None
Algorithm:
        (1) open the box line for both player hands
        (2) display player scores on the top right of each box
        (3) display the top element of tiles in player hands (first row)
        (4) display the middle element of tiles in player hands (first row)
        (5) display the bottom element of tiles in player hands (frist row)
        (6)
            if computer hand has more than 16 tiles
                record the tiles after the 16th tile in this hand
                display the top element of the tiles in computer hand (second row)
                if human hand has more than 16 tiles
                    record the tiles after the 16th tile in this hand
                    display the top element of the the tiles in human hand (second row)
                    display the middle element of the the tiles in player hands (second row)
                    display the bottom element of the the tiles in player hands (second row)
                    close the player hand boxes
                end if
                else (i.e. if only computer has more than 16 tiles in hand)
                    close the box for human hand
                    display the middle element of the tiles in computer hand (second row)
                    display the bottom element of the tiles in computer hand (second row)
                    close the box for human hand
                end else
            end if
            else if human hand has more than 16 tiles
                close the box for computer hand
                record the tiles after the 16th tile in human hand
                display the top element of the tiles in human hand (second row)
                display the middle element of the tiles in human hand (second row)
                display the bottom element of the tiles in human hand (second row)
                close the box for human hand
            end else if
            else
                close the box for human and computer hand
            end else
Assistance Received: None
********************************************************************* */
void round::displayPlayerHands(const int computer_score, const int human_score) const
{
    //max space needed = max tile numbers in hand * 3 + (max number of tiles in hand - 1)
    //max space needed = 63 + 2 = 65
    
    //placing only 16 tiles in each row for each player
    int row_max = 16;
    
    char space = ' ';
    char dash = '-';
    char under_score = '_';
    
    //open the box line for both player hands (first line)
    cout<<space<<addChar(under_score, 65)<<addChar(space, 7)<<addChar(under_score, 65)<<endl;
    
    //display player socres on the top right of each box (second line)
    formatScore("COMPUTER", computer_score, 56);
    cout<<addChar(space, 5);
    formatScore("HUMAN", human_score, 59);
    cout<<endl;
   
    //display the top element of the tiles in player hands (third line)
    displayOuterHandElements(m_round_piles[comp_hand]);
    cout<<addChar(space, 5);
    displayOuterHandElements(m_round_piles[human_hand]);
    cout<<endl;
    
    //display the middle element of the tiles in player hands (fourth line)
    displayInnerHandElements(m_round_piles[comp_hand]);
    cout<<addChar(space, 5);
    displayInnerHandElements(m_round_piles[human_hand]);
    cout<<endl;
    
    //display the bottom element of the tiles in player hands (fifth line)
    displayOuterHandElements(m_round_piles[comp_hand]);
    cout<<addChar(space, 5);
    displayOuterHandElements(m_round_piles[human_hand]);
    cout<<endl;
    
    //if computer hand has more than 16 tiles
    if (m_round_piles[comp_hand].getSize() > row_max)
    {
        pile post_sixteen_computer;
        
        //record the tiles after the 16th tile in computer's hand
        for (int i=0; i<m_round_piles[comp_hand].getSize() - row_max; i++)
            post_sixteen_computer.addToPile(m_round_piles[comp_hand].getTile(i));
        
        //display the top element of the tiles in player hands
        //(first line of 2nd row of tiles) - computer
        displayOuterHandElements(post_sixteen_computer);
        
        //add proper spacing
        if (m_round_piles[human_hand].getSize() > row_max)
            cout<<addChar(space, 5);
        else
            cout<<addChar(space, 6);
        
        //if human hand has more than 16 tiles
        if (m_round_piles[human_hand].getSize() > row_max)
        {
            pile post_sixteen_human;
            
            //record the tiles after the 16th tile in human's hand
            for (int i=0; i<m_round_piles[human_hand].getSize() - row_max; i++)
                post_sixteen_human.addToPile(m_round_piles[human_hand].getTile(i));
            
            //display the top element of the tiles in player hands
            //(first line of 2nd row of tiles) - human
            displayOuterHandElements(post_sixteen_human);
            cout<<endl;
            
            //display the middle element of the tiles in player hands
            //(second line of 2nd row of tiles)
            displayInnerHandElements(post_sixteen_computer);
            cout<<addChar(space, 5);
            displayInnerHandElements(post_sixteen_human);
            cout<<endl;
            
            //display the bottom element of the tiles in player hands
            //(third line of 2nd row of tiles)
            displayOuterHandElements(post_sixteen_computer);
            cout<<addChar(space, 5);
            displayOuterHandElements(post_sixteen_human);
            cout<<endl;
            
            //close the boxes
            cout<<space<<addChar(dash, 65)<<addChar(space, 7)<<addChar(dash, 65)<<endl;
        }
        
        //if only computer hand has more than 16 tiles
        else
        {
            //close the box for human hand
            cout<<addChar(dash, 65)<<endl;
            
            //display the middle element of the tiles in computer hand
            //second line of 2nd row of tiles - computer
            displayInnerHandElements(post_sixteen_computer);
            cout<<endl;
            
            
            //display the bottom element of the tiles in computer hand
            //(third line of 2nd row of tiles) - computer
            displayOuterHandElements(post_sixteen_computer);
            cout<<endl;
            
            //close the box for computer hand
            cout<<space<<addChar(dash, 65)<<endl;
        }
    }
    
    
    //if only human hand has more than 16 tiles
    else if (m_round_piles[human_hand].getSize() > row_max)
    {
        //close the box for computer hand
        cout<<space<<addChar(dash, 65)<<addChar(space, 6);
        
        pile post_sixteen_human;
        
        //record the tiles after the 16th tile in human hand
        for (int i=0; i<m_round_piles[human_hand].getSize() - row_max; i++)
            post_sixteen_human.addToPile(m_round_piles[human_hand].getTile(i));
        
        //display the top element of the tiles in human hand
        //(first line of 2nd row of tiles) - human
        displayOuterHandElements(post_sixteen_human);
        cout<<endl;
        
        //add empty space instead of computer hand
        cout<<addChar(space, 65)<<addChar(space, 7);
        
        //display the middle element of the tiles in human hand
        //second line of 2nd row of tiles - human
        displayInnerHandElements(post_sixteen_human);
        cout<<endl;
        
        //add empty space instead of computer hand
        cout<<addChar(space, 65)<<addChar(space, 7);
        
        //display the bottom element of the tiles in human hand
        //(third line of 2nd row of tiles) - human
        displayOuterHandElements(post_sixteen_human);
        cout<<endl;
        
        //close the box for human hand
        cout<<space<<addChar(space, 65)<<addChar(space, 7)<<addChar(dash, 65)<<endl;
    }
    
    //regular case (there are less than 16 tiles in both player hands)
    else
    {
        //close the box for human and computer hand
        cout<<space<<addChar(dash, 65)<<addChar(space, 7)<<addChar(dash, 65)<<endl;
    }
}

/* *********************************************************************
Function Name: displayOuterHandElements
Purpose: To display the top and bottom element of tiles in a player hand
Parameters:
            pile_to_display, an object of the pile class passed by value.
            It refers to the player hand that will be displayed.
Return Value: None
Assistance Received: None
********************************************************************* */
void round::displayOuterHandElements(const pile pile_to_display) const
{
    int pile_size = pile_to_display.getSize();
    
    //there can only be 16 tiles in one row
    const int row_max_tiles = 16;
    char space = ' ';
     
    cout<<"| ";
    
    //if there is less than 16 tiles in hand
    int tiles_to_display = pile_size;
    
    //if there is more than 16 tiles in hand - only display 16
    if (pile_size > row_max_tiles)
        tiles_to_display = row_max_tiles;
    
    //display the top section of each tile
    for (int i=0; i<tiles_to_display; i++)
    {
        displayOuterTileElement(pile_to_display.getTile(i));
        cout<<space;
    }
    
    //empty spots filled with 3-space charcatres
    for (int i=0; i<row_max_tiles - pile_size; i++)
        cout<<addChar(space, 4);
    
    cout<<"|";
}


/* *********************************************************************
Function Name: displayInnerHandElements
Purpose: To display the middle element of tiles in a player hand
Parameters:
            pile_to_display, an object of the pile class passed by value.
            It refers to the player hand that will be displayed.
Return Value: None
Assistance Received: None
********************************************************************* */
void round::displayInnerHandElements(const pile pile_to_display) const
{
    int pile_size = pile_to_display.getSize();
    char space = ' ';
    
    //there can only be 16 tiles in one row
    const int row_max_tiles = 16;
    
    cout<<"| ";
    
    //if there is less than 16 tiles in hand
    int tiles_to_display = pile_size;
    
    //if there is more than 16 tiles in hand - only display 16
    if (pile_size > row_max_tiles)
        tiles_to_display = row_max_tiles;
    
    //display the middle section of each tile
    for (int i=0; i<tiles_to_display; i++)
    {
        displayInnerTileElement(pile_to_display.getTile(i));
        cout<<space;
    }
    
    for (int i=0; i<row_max_tiles-pile_size; i++)
        cout<<addChar(space, 4);
    
    cout<<"|";
}


/* *********************************************************************
Function Name: displayOuterTileElement
Purpose: To display the outer element of a tile
Parameters:
            tile_to_display, an object of the tile class passed by value.
            It refers to the tile that will be displayed.
Return Value: None
Assistance Received: None
********************************************************************* */
void round::displayOuterTileElement(const tile tile_to_display) const
{
    char space = ' ';
    
    if (tile_to_display.isDouble())
        cout<<space<<tile_to_display.getFrontEnd()<<space;
    else
        cout<<space<<space<<space;
}

/* *********************************************************************
Function Name: displayInnerTileElement
Purpose: To display the middle element of a tile
Parameters:
            tile_to_display, an object of the tile class passed by value.
            It refers to the tile that will be displayed.
Return Value: None
Assistance Received: None
********************************************************************* */
void round::displayInnerTileElement(const tile tile_to_display) const
{
    char space = ' ';
    
    if (tile_to_display.isDouble())
        cout<<space<<'|'<<space;
    else
        cout<<tile_to_display.getFrontEnd()<<'-'<<tile_to_display.getBackEnd();
}


/* *********************************************************************
Function Name: displayBoneyard
Purpose: To display the top tile in boneyard with proper formatting
Parameters:
            pile_name, a string passed by value. It refers to the
            name of the pile to be diplayed.
Return Value: None
Algorithm:
        (1) display the name of the pile
        (2)
            if the pile is empty
                display empty
            end if
            else
                if tile is a double
                    display the top section of tile in a double style
                    display the middle section of tile in a double style
                    display the bottom section of tile in a double style
                end if
                else
                    display the top section of tile in a non-double style
                    display the middle section of tile in a non-double style
                    display the bottom section of tile in a non-double style
                end else
            end else
                    
Assistance Received: None
********************************************************************* */
void round::displayBoneyard(const string pile_name) const
{
    int pile_size = m_round_piles[boneyard].getSize();
    char space = ' ';
    char under_score = '_';
    char dash = '-';
      
    //add the top part of box (first line)
    cout<<addChar(space, 65)<<addChar(under_score, 8)<<endl;
      
    //display the name of the pile (second line)
    cout<<addChar(space, 64)<<"|"<<pile_name<<"|"<<endl;
    
    if (pile_size == 0)
    {
        //third line
        cout<<addChar(space, 64)<<"| EMPTY  |";
    }
    
    else
    {
        //determine whether top tile is a double or non-double
        bool double_tile = m_round_piles[boneyard].getTile(pile_size-1).isDouble();
        
        //third line
        cout<<addChar(space, 64)<<"|  ";
        
        if (double_tile)
        {
            //display the top section of tile (first line of tile - third line)
            cout<<space<<m_round_piles[boneyard].getTile(pile_size-1).getFrontEnd();
            cout<<addChar(space, 4)<<"|"<<endl;
              
            //display the middle section of tile (second line of tile - fourth line)
            cout<<addChar(space, 64)<<"|"<<addChar(space, 3)<<"|"<<addChar(space, 4)<<"|"<<endl;
       
            //display the bottom section of tile (third line of tile - fifth line)
            cout<<addChar(space, 64)<<"|  ";
            cout<<space<<m_round_piles[boneyard].getTile(pile_size-1).getFrontEnd();
            cout<<addChar(space, 4)<<"|";
        }
        
        //top tile is a non-double
        else
        {
            //display the top section of tile (first line of tile - third line)
            cout<<addChar(space, 6)<<"|"<<endl;
            
            cout<<addChar(space, 64)<<"|  ";
       
            //display the middle section of tile (second line of tile - fourth line)
            cout<<m_round_piles[boneyard].getTile(pile_size-1).getFrontEnd()<<"-"<<m_round_piles[boneyard].getTile(pile_size-1).getBackEnd()<<"   |"<<endl;

            //display the bottom section of tile (third line of tile - fifth line)
            cout<<addChar(space, 64)<<"|  "<<addChar(space, 6)<<"|";
        }
    }
    
    //last line
    cout<<endl<<addChar(space, 65)<<addChar(dash, 8)<<endl;
}



/* *********************************************************************
Function Name: displayPlayerTrains
Purpose: To display the personal and opponent train
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
void round::displayPlayerTrains() const
{
    cout<<"REGULAR TRAIN"<<endl<<endl;
    
    //display the top section of the trains (first line)
    printOuterPlayerTrain();
    cout<<endl;
    
    //display the middle section of the trains (second line)
    printInnerPlayerTrain();
    cout<<endl;
    
    //display the bottom section of the trains (third line)
    printOuterPlayerTrain();
    cout<<endl;
    
    cout<<endl;
}


/* *********************************************************************
Function Name: printOuterPlayerTrain
Purpose: To display the outer section of the personal and opponent train
Parameters: None
Return Value: None
Algorithm:
        (1)
            if computer train is marked
                add appropriate space
            end if
        (2) display the outer section of computer train
        (3) display the outer section of the engine
        (4) display the outer section of human train
        (5)
            if human train is marked
                add appropriate space
            end if
                
Assistance Received: None
********************************************************************* */
void round::printOuterPlayerTrain() const
{
    int computer_size = m_round_trains[comp_train].getSize();
    int human_size = m_round_trains[human_train].getSize();
    
    char space = ' ';
    
    //if computer train is marked
    if (m_round_trains[comp_train].hasMarker())
    {
        cout<<space;
        cout<<addChar(space, 3);
    }
    
    //display the outer section of computer train
    for (int i=computer_size-1; i>0; i--)
    {
        cout<<space;
         
        if (m_round_trains[comp_train].getTile(i).isDouble())
            cout<<space<<m_round_trains[comp_train].getTile(i).getFrontEnd()<<space;
        else
            cout<<addChar(space, 3);
    }
    
    //display engine's top section
    cout<<space<<space<<m_engine.getFrontEnd()<<space<<space;
    
    //display the outer section of human train
    //(i=1 because 9|9 is part of train and should not be displayed)
    for (int i=1; i<human_size; i++)
    {
        if (m_round_trains[human_train].getTile(i).isDouble())
            cout<<space<<m_round_trains[human_train].getTile(i).getFrontEnd()<<space;
        else
            cout<<addChar(space, 3);
        
        cout<<space;
    }
    
    //if human train is marked
    if (m_round_trains[human_train].hasMarker())
        cout<<addChar(space, 3);
}

/* *********************************************************************
Function Name: printInnerPlayerTrain
Purpose: To display the middle section of the personal and opponent train
Parameters: None
Return Value: None
Algorithm:
        (1)
            if computer train is marked
                add the marker
            end if
        (2) display the middle section of computer train
        (3) display the middle section of the engine
        (4) display the middle section of human train
        (5)
            if human train is marked
                add the marker
            end if
Assistance Received: None
********************************************************************* */
void round::printInnerPlayerTrain() const
{
    int computer_size = m_round_trains[comp_train].getSize();
    int human_size = m_round_trains[human_train].getSize();
    char space = ' ';
    
    //if computer train is marked, add the marker
    if (m_round_trains[comp_train].hasMarker())
    {
        cout<<space;
        cout<<space<<'M'<<space;
    }
    
    //display the middle section of computer train
    for (int i= computer_size - 1; i>0; i--)
    {
        cout<<space;
         
        if (m_round_trains[comp_train].getTile(i).isDouble())
            cout<<space<<'|'<<space;
        else
            cout<<m_round_trains[comp_train].getTile(i).getBackEnd()<<"-"<<m_round_trains[comp_train].getTile(i).getFrontEnd();
    }
    
    //add engine
    cout<<space<<space<<"|"<<space<<space;
    
    //display the middle section of human train
    //(i=1 because 9|9 is part of train and should not be displayed)
    for (int i=1; i<human_size; i++)
    {
        if (m_round_trains[human_train].getTile(i).isDouble())
            cout<<space<<'|'<<space;
        else
            cout<<m_round_trains[human_train].getTile(i).getFrontEnd()<<"-"<<m_round_trains[human_train].getTile(i).getBackEnd();
        
        cout<<space;
    }
    
    //if human train is marked, add the marker
    if (m_round_trains[human_train].hasMarker())
        cout<<space<<'M'<<space;
}


/* *********************************************************************
Function Name: displayMexicanTrain
Purpose: To display the mexican train
Parameters: None
Return Value: None
Algorithm:
        (1) display the top section of the train
        (2) display the middle section of the train
        (3) display the bottom section of the train
Assistance Received: None
********************************************************************* */
void round::displayMexicanTrain() const
{
    cout<<"MEXICAN TRAIN"<<endl<<endl;
    int mexican_train_size = m_round_trains[mexican_train].getSize();
    char space = ' ';
    
    cout<<space;

    //print the top section of the train (first line)
    for (int i=0; i<mexican_train_size; i++)
    {
        if (m_round_trains[mexican_train].getTile(i).isDouble())
            cout<<space<<m_round_trains[mexican_train].getTile(i).getFrontEnd()<<space;
        else
            cout<<addChar(space, 3);
        
        cout<<space;
    }
    
    
    cout<<endl;
    cout<<space;
    
    //print the middle section of the train (second line)
    for (int i=0; i<mexican_train_size; i++)
    {
        if (m_round_trains[mexican_train].getTile(i).isDouble())
            cout<<space<<"|"<<space;
        else
            cout<<m_round_trains[mexican_train].getTile(i).getFrontEnd()<<"-"<<m_round_trains[mexican_train].getTile(i).getBackEnd();
        
        cout<<space;
    }
    
    cout<<endl;
    cout<<space;
    
    //print the bottom section of the train
    for (int i=0; i<mexican_train_size; i++)
    {
        if (m_round_trains[mexican_train].getTile(i).isDouble())
            cout<<space<<m_round_trains[mexican_train].getTile(i).getFrontEnd()<<space;
        else
            cout<<addChar(space, 3);
        
        cout<<space;
    }
    
    cout<<endl;
}
