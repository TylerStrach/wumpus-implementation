/*
	Program 2: Wumpus, version 2 (dynamic size array)
	CS 211, UIC, Fall 2022
	System: Clion using Mac OS
	Author: Tyler Strach (using program 1 solution code by Prof Kidane and Prof Reed)

	Hunt the Wumpus is a classic text-based adventure game by Gregory Yob from 1972.
	The Wumpus lives in a completely dark cave of 20 rooms.  Each room has 3 tunnels leading to other rooms.
	This program implements this game, with superbats and arrows, using a dynamically allocated array.
*/

#include <stdio.h>
#include <stdlib.h>		// for srand
#include <ctype.h>		// for toupper()

// global constants
#define MAX_LINE_LENGTH 81
#define NUMBER_OF_ROOMS 20

// Used to more conveniently pass all game information between functions
struct GameInfo {
    int moveNumber;  // Counts up from 1, incrementing for each move
    int personRoom;  // Room 1..20 the person currently is in
    int wumpusRoom;  // Room 1..20 the Wumpus is in
    int pitRoom1;    // Room 1..20 the first pit is in
    int pitRoom2;    // Room 1..20 the second pit is in
    int batsRoom1;   // Room 1..20 the first bats room
    int batsRoom2;   // Room 1..20 the second bats room
    int arrowRoom;   // Room 1..20 the arrow room
};

// dynamically allocates memory to hold all the rooms' adjacent rooms using malloc and pointer arithmetic
int *initializeRooms(){
    int *roomsArray = (int *)malloc(3 * 21 * sizeof(int)); // creates array of 63 integers
    for(int i = 1; i < 21; i++){ // for the rooms 1-20
        switch(i){ // allocates each room with correct nearby rooms
            case 1:
                *(roomsArray+i*3 + 0) = 2;
                *(roomsArray+i*3 + 1) = 5;
                *(roomsArray+i*3 + 2) = 8;
                break;
            case 2:
                *(roomsArray+i*3 + 0) = 1;
                *(roomsArray+i*3 + 1) = 3;
                *(roomsArray+i*3 + 2) = 10;
                break;
            case 3:
                *(roomsArray+i*3 + 0) = 2;
                *(roomsArray+i*3 + 1) = 4;
                *(roomsArray+i*3 + 2) = 12;
                break;
            case 4:
                *(roomsArray+i*3 + 0) = 3;
                *(roomsArray+i*3 + 1) = 5;
                *(roomsArray+i*3 + 2) = 14;
                break;
            case 5:
                *(roomsArray+i*3 + 0) = 1;
                *(roomsArray+i*3 + 1) = 4;
                *(roomsArray+i*3 + 2) = 6;
                break;
            case 6:
                *(roomsArray+i*3 + 0) = 5;
                *(roomsArray+i*3 + 1) = 7;
                *(roomsArray+i*3 + 2) = 15;
                break;
            case 7:
                *(roomsArray+i*3 + 0) = 6;
                *(roomsArray+i*3 + 1) = 8;
                *(roomsArray+i*3 + 2) = 17;
                break;
            case 8:
                *(roomsArray+i*3 + 0) = 1;
                *(roomsArray+i*3 + 1) = 7;
                *(roomsArray+i*3 + 2) = 9;
                break;
            case 9:
                *(roomsArray+i*3 + 0) = 8;
                *(roomsArray+i*3 + 1) = 10;
                *(roomsArray+i*3 + 2) = 18;
                break;
            case 10:
                *(roomsArray+i*3 + 0) = 2;
                *(roomsArray+i*3 + 1) = 9;
                *(roomsArray+i*3 + 2) = 11;
                break;
            case 11:
                *(roomsArray+i*3 + 0) = 10;
                *(roomsArray+i*3 + 1) = 12;
                *(roomsArray+i*3 + 2) = 19;
                break;
            case 12:
                *(roomsArray+i*3 + 0) = 3;
                *(roomsArray+i*3 + 1) = 11;
                *(roomsArray+i*3 + 2) = 13;
                break;
            case 13:
                *(roomsArray+i*3 + 0) = 12;
                *(roomsArray+i*3 + 1) = 14;
                *(roomsArray+i*3 + 2) = 20;
                break;
            case 14:
                *(roomsArray+i*3 + 0) = 4;
                *(roomsArray+i*3 + 1) = 13;
                *(roomsArray+i*3 + 2) = 15;
                break;
            case 15:
                *(roomsArray+i*3 + 0) = 6;
                *(roomsArray+i*3 + 1) = 4;
                *(roomsArray+i*3 + 2) = 16;
                break;
            case 16:
                *(roomsArray+i*3 + 0) = 15;
                *(roomsArray+i*3 + 1) = 17;
                *(roomsArray+i*3 + 2) = 20;
                break;
            case 17:
                *(roomsArray+i*3 + 0) = 7;
                *(roomsArray+i*3 + 1) = 16;
                *(roomsArray+i*3 + 2) = 18;
                break;
            case 18:
                *(roomsArray+i*3 + 0) = 9;
                *(roomsArray+i*3 + 1) = 17;
                *(roomsArray+i*3 + 2) = 19;
                break;
            case 19:
                *(roomsArray+i*3 + 0) = 11;
                *(roomsArray+i*3 + 1) = 18;
                *(roomsArray+i*3 + 2) = 20;
                break;
            case 20:
                *(roomsArray+i*3 + 0) = 13;
                *(roomsArray+i*3 + 1) = 16;
                *(roomsArray+i*3 + 2) = 19;
                break;
            default:
                break;
        }
    }
    return roomsArray; // returns the pointer to the array to be used throughout the program.
}

// displays cave
void displayCave()
{
    printf( "\n"
            "       ______18______             \n"
            "      /      |       \\           \n"
            "     /      _9__      \\          \n"
            "    /      /    \\      \\        \n"
            "   /      /      \\      \\       \n"
            "  17     8        10     19       \n"
            "  | \\   / \\      /  \\   / |    \n"
            "  |  \\ /   \\    /    \\ /  |    \n"
            "  |   7     1---2     11  |       \n"
            "  |   |    /     \\    |   |      \n"
            "  |   6----5     3---12   |       \n"
            "  |   |     \\   /     |   |      \n"
            "  |   \\       4      /    |      \n"
            "  |    \\      |     /     |      \n"
            "  \\     15---14---13     /       \n"
            "   \\   /            \\   /       \n"
            "    \\ /              \\ /        \n"
            "    16---------------20           \n"
            "\n");
}

// displays instructions
void displayInstructions()
{
    printf( "Hunt the Wumpus:                                             \n"
            "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
            "room has 3 tunnels leading to other rooms.                   \n"
            "                                                             \n"
            "Hazards:                                                     \n"
            "1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
            "2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
            "   fly you to some random room, which could be troublesome.  Then those bats go \n"
            "   to a new room different from where they came from and from the other bats.   \n"
            "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
            "   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
            "    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
            "    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
            "    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
            "    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
            "    room, he snaps your neck and you die!                                       \n"
            "                                                                                \n"
            "Moves:                                                                          \n"
            "On each move you can do the following, where input can be upper or lower-case:  \n"
            "1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
            "   then a room number.                                                          \n"
            "2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
            "   you specify.  Your arrow ends up in the final room.                          \n"
            "   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
            "   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
            "   by spaces. If an arrow can't go a direction because there is no connecting   \n"
            "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
            "   continues doing this until it has traveled the designated number of rooms.   \n"
            "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
            "   automatically pick up the arrow if you go through a room with the arrow in   \n"
            "   it.                                                                          \n"
            "3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
            "4. Enter 'C' to cheat and display current board positions.                      \n"
            "5. Enter 'D' to display this set of instructions.                               \n"
            "6. Enter 'P' to print the maze room layout.                                     \n"
            "7. Enter 'X' to exit the game.                                                  \n"
            "                                                                                \n"
            "Good luck!                                                                      \n"
            " \n\n");
}//end displayInstructions()


// Return true if randomValue is already in array
int alreadyFound(int randomValue,      // New number we're checking
                 int *randomNumbers,  // Set of numbers previously found
                 int limit)            // How many numbers previously found
{
    int returnValue = 0;

    // compare random value against all previously found values
    for( int i = 0; i<limit; i++) {
        if( randomValue == randomNumbers[i]) {
            returnValue = 1;   // It is already there
            break;
        }
    }

    return returnValue;
}

// Fill this array with unique random integers 1..20
void setUniqueValues(int *randomNumbers,   // pointer to array of random numbers
                     int size)              // Size of random numbers array
{
    int randomValue = -1;

    for( int i = 0; i<size; i++) {
        do {
            randomValue = rand() % NUMBER_OF_ROOMS + 1;   // random number 1..20
        } while (alreadyFound(randomValue, randomNumbers, i));
        *(randomNumbers + i) = randomValue; // sets correct array value after displacement
    }
}

// Set the Wumpus, player, bats and pits in distinct random rooms
void initializeGame(struct GameInfo *gameInfo)   // All game settings variables
{
    // Array pointer to 7 unique values 1..20, to be used in initializing  hazards locations
    int* randNums = malloc(7*sizeof(int));

    // Select some unique random values 1..20 to be used for game info
    setUniqueValues(randNums, 7);

    // Use the unique random numbers to set initial locations of hazards with pointer displacement, which
    //    should be non-overlapping.
    gameInfo->personRoom = *(randNums+0);
    gameInfo->wumpusRoom = *(randNums+1);
    gameInfo->pitRoom1 = *(randNums+2);
    gameInfo->pitRoom2 = *(randNums+3);
    gameInfo->batsRoom1 = *(randNums+4);
    gameInfo->batsRoom2 = *(randNums+5);
    gameInfo->arrowRoom = *(randNums+6);

    gameInfo->moveNumber = 1;
    free(randNums); // frees the dynamic array of randomNumbers
}// end initializeBoard(...)

// Returns 1 if nextRoom is adjacent to current room, else returns 0.
int roomIsAdjacent( const int *tunnels,     // Array of adjacent tunnels
                    int nextRoom)        // Desired room to move to
{
    return( *(tunnels) == nextRoom || *(tunnels + 1) == nextRoom || *(tunnels + 2) == nextRoom);
}

// Display where everything is on the board.
void displayCheatInfo(struct GameInfo gameInfo)
{
    printf( "Cheating! Game elements are in the following rooms: \n"
            "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
            "%4d %5d %6d %5d %5d %5d %5d \n\n",
            gameInfo.personRoom,
            gameInfo.wumpusRoom,
            gameInfo.pitRoom1,
            gameInfo.pitRoom2,
            gameInfo.batsRoom1,
            gameInfo.batsRoom2,
            gameInfo.arrowRoom
    );
}// end displayCheatInfo(...)

// Display room number and hazards detected
void displayRoomInfo( struct GameInfo gameInfo, int *adjRooms)
{
    // Retrieve player's current room number and display it
    int currentRoom = gameInfo.personRoom;
    printf("You are in room %d. ", currentRoom);

    // Retrieve values of all 3 adjacent rooms
    int room1 = *(adjRooms);
    int room2 = *(adjRooms+1);
    int room3 = *(adjRooms+2);

    // Display hazard detection message if Wumpus is in an adjacent room
    int wumpusRoom = gameInfo.wumpusRoom;
    if( room1 == wumpusRoom || room2 == wumpusRoom || room3 == wumpusRoom) {
        printf("You smell a stench. ");
    }

    // Display hazard detection message if a pit is in an adjacent room
    int pit1Room = gameInfo.pitRoom1;
    int pit2Room = gameInfo.pitRoom2;
    if( room1 == pit1Room || room1 == pit2Room ||
        room2 == pit1Room || room2 == pit2Room ||
        room3 == pit1Room || room3 == pit2Room
            ) {
        printf("You feel a draft. ");
    }

    //display hazard detection if bats are in an adjacent room
    int bats1Room = gameInfo.batsRoom1;
    int bats2Room = gameInfo.batsRoom2;
    if( room1 == bats1Room || room1 == bats2Room ||
        room2 == bats1Room || room2 == bats2Room ||
        room3 == bats1Room || room3 == bats2Room
            ) {
        printf("You hear rustling of bat wings. ");
    }
    printf("\n\n");
}//end displayRoomInfo(...)

// If the player just moved into a room with a pit, the person dies.
// If the person just moved into the Wumpus room, then if the room number is odd
// the Wumpus moves to a random adjacent room.
// If the player moves into a room with bats, the player gets transported to a random room, and the bats transfer to
// a random room different from where they came from, the other bats room, and the current user room
void checkForHazards(
        struct GameInfo *gameInfo, // Hazards location and game info
        int *personIsAlive,  // Person is alive, but could die depending on the hazards
        int *adjRooms)       // pointer to the user adjacent rooms
{
    // retrieve the room the person is in
    int personRoom = gameInfo->personRoom;

    // Check for the Wumpus
    if( personRoom == gameInfo->wumpusRoom) {
        if( gameInfo->wumpusRoom %2 == 1) {
            // You got lucky and the Wumpus moves away
            printf( "You hear a slithering sound, as the Wumpus slips away. \n"
                    "Whew, that was close! \n");
            gameInfo->wumpusRoom = *(adjRooms);  // Choose the lowest-numbered adjacent room
        }
        else {
            // Wumpus kills you
            printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n"
                       "It is over.\n");
            *personIsAlive = 0;
            return;
        }
    }
    // Check whether there is a pit
    if( personRoom == gameInfo->pitRoom1 || personRoom == gameInfo->pitRoom2) {
        // Person falls into pit
        printf("Aaaaaaaaahhhhhh....   \n");
        printf("    You fall into a pit and die. \n");
        *personIsAlive = 0;
        return;
    }

    // check if the room has an arrow in it
    if(gameInfo->arrowRoom == personRoom){
        printf("Congratulations, you found the arrow and can once again shoot.\n");
        gameInfo->arrowRoom = -1;
    }

    // check if the room has any bats in it
    if( personRoom == gameInfo->batsRoom1 || personRoom == gameInfo->batsRoom2) {
        printf("Woah... you're flying! \n");

        // determines which bat room
        int bat;
        if(personRoom == gameInfo->batsRoom1)
            bat = 1;
        else
            bat = 2;

        // sends user to a random room
        int randUserRoom = rand() % NUMBER_OF_ROOMS + 1;
        gameInfo->personRoom = randUserRoom;

        // sends bat to a random room other than the user room, the old bat room, and the other bat room
        int randBatRoom;
        int validRoom = 0;
        while(!validRoom){
            randBatRoom = rand() % NUMBER_OF_ROOMS + 1;
            if(randBatRoom != gameInfo->personRoom && randBatRoom != gameInfo->batsRoom1 && randBatRoom != gameInfo->batsRoom2){
                validRoom = 1;
            }
        }

        // sets the correct bat to the new location
        if(bat == 1)
            gameInfo->batsRoom1 = randBatRoom;
        else
            gameInfo->batsRoom2 = randBatRoom;

        printf("You've just been transported by bats to room %d.\n", randUserRoom);
        checkForHazards(gameInfo, personIsAlive, adjRooms);
    }
}//end checkForHazards(...)

// Prompt for and reset the positions of the game hazards and the person's location,
// useful for testing.  No error checking is done on these values.
void resetPositions(struct GameInfo *theGameInfo)
{
    printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n");
    scanf(" %d %d %d %d %d %d %d", &theGameInfo->personRoom, &theGameInfo->wumpusRoom,
          &theGameInfo->pitRoom1, &theGameInfo->pitRoom2, &theGameInfo->batsRoom1, &theGameInfo->batsRoom2,
          &theGameInfo->arrowRoom);
    printf("\n");
}

// Shoots the arrow along the user path
void shootArrow(struct GameInfo *gameInfo, // access game information
                int *adjRooms, // access various nearby rooms
                int *personIsAlive, // set if person dies
                int *wumpusIsAlive, // set if wumpus dies
                int *arrowPath, // pointer to the dynamic array of arrow path
                int numofRooms) { // num of rooms arrow travels

    for (int i = 0; i < numofRooms; i++) { // for 1-3 rooms
        if (i == 0) { // if first room, set arrow location to user room
            gameInfo->arrowRoom = gameInfo->personRoom;
        }

        // gets the room the arrow is trying to go, and checks if the room is adjacent or not
        int destArrowRoom = *(arrowPath + i);

        // if room is adjacent, sets arrow to next room and checks if wumpus or player is in the room
        if (destArrowRoom == *(adjRooms + (3 * gameInfo->arrowRoom)) ||
            destArrowRoom == *(adjRooms + (3 * gameInfo->arrowRoom) + 1)
            || destArrowRoom == *(adjRooms + (3 * gameInfo->arrowRoom) + 2) ) {
            gameInfo->arrowRoom = destArrowRoom;
            if (gameInfo->arrowRoom == gameInfo->wumpusRoom) { // arrow kills wumpus
                *wumpusIsAlive = 0;
                printf("Wumpus has just been pierced by your deadly arrow! \n"
                       "Congratulations on your victory, you awesome hunter you.\n");
                return;
            }
            if (gameInfo->arrowRoom == gameInfo->personRoom) { // arrow kills person
                *personIsAlive = 0;
                printf("You just shot yourself.  \n"
                       "Maybe Darwin was right.  You're dead.\n");
                return;
            }
        }
        else { // if room is not adjacent
            printf("Room %d is not adjacent.  Arrow ricochets...\n", destArrowRoom);
            gameInfo->arrowRoom = *(adjRooms + (3 * gameInfo->arrowRoom));
            if (gameInfo->arrowRoom == gameInfo->wumpusRoom) { // arrow kills wumpus by accident
                *wumpusIsAlive = 0;
                printf("Your arrow ricochet killed the Wumpus, you lucky dog!\n"
                       "Accidental victory, but still you win!\n");
                return;
            }
            if (gameInfo->arrowRoom == gameInfo->personRoom) { // arrow kills user by accident
                *personIsAlive = 0;
                printf("You just shot yourself, and are dying.\n"
                       "It didn't take long, you're dead.\n");
                return;
            }
        }
    }
}


int main(void) {
    struct GameInfo gameInfo;   // Used to more easily pass game info variables around
    int personIsAlive = 1;  // Used in checking for end of game
    int wumpusIsAlive = 1;  // Used in checking for end of game
    char typeOfMove;            // Used to handle user input letter
    int nextRoom;               // User input of destination room number, used on a 'M' type move

    // Seed the random number generator.  Change seed to time(0) to change output each time.
    // srand(time(0));
    srand(1);

    // dynamically create and set the adjacent rooms, free at end of program
    int* rooms = initializeRooms();

    // Set random initial values for person, Wumpus, bats and pits
    initializeGame( &gameInfo);

    // Main playing loop.  Break when player dies, or player kills Wumpus
    while (personIsAlive && wumpusIsAlive) {

        // Display current room information: Room number, hazards detected
        displayRoomInfo( gameInfo, (rooms + 3*gameInfo.personRoom));

        // Prompt for and handle move
        printf("%d. Enter your move (or 'D' for directions): ", gameInfo.moveNumber);
        scanf(" %c", &typeOfMove);
        typeOfMove = toupper(typeOfMove);  // Make uppercase to facilitate checking

        // Check all types of user input and handle them.
        if( typeOfMove == 'D') {
            displayCave();
            displayInstructions();
            continue;       // Loop back up to reprompt for the same move
        }
        else if( typeOfMove == 'P') {
            // To assist with play, display the cave layout
            displayCave();
            continue;       // Loop back up to reprompt for the same move
        }
        else if( typeOfMove == 'M') {
            // Move to an adjacent room,
            scanf(" %d", &nextRoom);

            // pointer displacement to pass nearby rooms to current person position
            if( roomIsAdjacent( (rooms + 3*gameInfo.personRoom), nextRoom)) {
                gameInfo.personRoom = nextRoom;        // move to a new room
                // Check if pit or wumpus is present in this new room
                checkForHazards(&gameInfo, &personIsAlive, (rooms + 3*gameInfo.personRoom));
            }
            else {
                printf("Invalid move.  Please retry. \n");
                continue;        // Doesn't count as a move, so retry same move.
            }
        }
        else if( typeOfMove == 'C') {
            // Display Cheat information
            displayCheatInfo(gameInfo);
            continue;        // Doesn't count as a move, so retry same move.
        }
        else if( typeOfMove == 'R') {
            // Specify resetting the hazards and person positions, useful for testing
            resetPositions( &gameInfo);
            continue;        // Doesn't count as a move, so retry same move.
        }
        else if( typeOfMove == 'G') {
            // Prompt for room number guess and see if user has found the Wumpus
            int wumpusRoomGuess = 0;
            printf("Enter room (1..20) you think Wumpus is in: ");
            scanf(" %d", &wumpusRoomGuess);
            // See if userguess was correct, for a win or loss.
            if( gameInfo.wumpusRoom == wumpusRoomGuess) {
                printf("You won!\n");
            }
            else{
                printf("You lost.\n");
            }
            break;
        }
        else if(typeOfMove == 'S'){
            // checks if the user has an arrow in the inventory
            if(gameInfo.arrowRoom != -1){
                printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
                gameInfo.moveNumber++;
                continue;
            }

            // gets the size and dynamically allocates arrow path array
            printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
            int numofRooms;
            int roomNum;
            scanf(" %d", &numofRooms);
            if(numofRooms > 3){
                numofRooms = 3;
                printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
            }
            int* arrowPath = malloc(numofRooms*sizeof(int));

            // stores the user requested arrow path into an array
            for(int i = 0; i < numofRooms; i++){
                scanf(" %d", &(*(arrowPath+i)));
            }

            // shoots the arrow along the user requested path and checks for collisions with player or wumpus
            shootArrow(&gameInfo, rooms, &personIsAlive, &wumpusIsAlive, arrowPath, numofRooms);
            gameInfo.wumpusRoom = *(rooms + (3*gameInfo.wumpusRoom)); // moves wumpus to lowest adjacent room after finished
            free(arrowPath); // frees dynamic array for next arrow shot
        }
        else if( typeOfMove == 'X') {
            // Exit program
            personIsAlive = 0;   // Indicate person is dead as a way to exit playing loop
            break;
        }
        else{
            break;
        }

        // Increment the move number
        gameInfo.moveNumber = gameInfo.moveNumber + 1;

    }//end while(personIsAlive && wumpusIsAlive)

    printf("\nExiting Program ...\n");
    free(rooms); // frees the adjacent rooms array lol
    return 0;
}