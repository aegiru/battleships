#include <iostream>
#include "definitions.h"

using namespace std;

//
// SIMPLE UTILITY FUNCTIONS USED THROUGHOUT THE PROGRAM
//

int minimum(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}



int maximum(int a, int b) {
    if (a < b) {
        return b;
    } else {
        return a;
    }
}



bool isNegative(int a) {
    if (a < 0) {
        return true;
    } else {
        return false;
    }
}



int positiveModulo(int a, int b) {
    return ((a % b) + b) % b;
}



int composePart(int length) {
    int toReturn = DEFAULT_COMPOSED_PART;
    for (int i = DEFAULT_COMPOSE_START; i < length; i++) {
        toReturn+=(int)(NOT_DESTROYED_PART * pow(PART_MULTIPLIER, i));
    }
    return toReturn;
}



int playerNumber(char playerChar) {
    if (playerChar == FIRST_PLAYER_LETTER) {
        return FIRST_PLAYER_NUMBER;
    } else if (playerChar == SECOND_PLAYER_LETTER) {
        return SECOND_PLAYER_NUMBER;
    } else {
        return UNSUCCESSFUL_OPERATION;
    }
}



char playerChar(int playerID) {
    if (playerID == FIRST_PLAYER_NUMBER) {
        return FIRST_PLAYER_LETTER;
    } else if (playerID == SECOND_PLAYER_NUMBER) {
        return SECOND_PLAYER_LETTER;
    } else {
        return (char)UNSUCCESSFUL_OPERATION;
    }
}



int defaultSum() {
    return DEFAULT_NUMBER_OF_DESTROYERS + DEFAULT_NUMBER_OF_CRUISERS + DEFAULT_NUMBER_OF_BATTLESHIPS + DEFAULT_NUMBER_OF_CARRIERS;
}



int integerBasedOnType(const char *inputType) {
    if (strcmp(inputType, DEFAULT_DESTROYER_TYPE) == SUCCESSFUL_STRCMP) {
        return DEFAULT_DESTROYER_POINT;
    } else if (strcmp(inputType, DEFAULT_CRUISER_TYPE) == SUCCESSFUL_STRCMP) {
        return DEFAULT_CRUISER_POINT;
    } else if (strcmp(inputType, DEFAULT_BATTLESHIP_TYPE) == SUCCESSFUL_STRCMP) {
        return DEFAULT_BATTLESHIP_POINT;
    } else if (strcmp(inputType, DEFAULT_CARRIER_TYPE) == SUCCESSFUL_STRCMP) {
        return DEFAULT_CARRIER_POINT;
    }
    return -1;
}



int lengthBasedOnType(const char *inputType) {
    if (strcmp(inputType, DEFAULT_DESTROYER_TYPE) == SUCCESSFUL_STRCMP) {
        return DEFAULT_DESTROYER_LENGTH;
    } else if (strcmp(inputType, DEFAULT_CRUISER_TYPE) == SUCCESSFUL_STRCMP) {
        return DEFAULT_CRUISER_LENGTH;
    } else if (strcmp(inputType, DEFAULT_BATTLESHIP_TYPE) == SUCCESSFUL_STRCMP) {
        return DEFAULT_BATTLESHIP_LENGTH;
    } else if (strcmp(inputType, DEFAULT_CARRIER_TYPE) == SUCCESSFUL_STRCMP) {
        return DEFAULT_CARRIER_LENGTH;
    }
    return -1;
}



char* typeBasedOnInteger(int input) {
    char* defaultReturn = (char*)DEFAULT_STRING;
    if (input == DEFAULT_DESTROYER_POINT) {
        return (char*)DEFAULT_DESTROYER_TYPE;
    } else if (input == DEFAULT_CARRIER_POINT) {
        return (char*)DEFAULT_CARRIER_TYPE;
    } else if (input == DEFAULT_CRUISER_POINT) {
        return (char*)DEFAULT_CRUISER_TYPE;
    } else if (input == DEFAULT_BATTLESHIP_POINT) {
        return (char*)DEFAULT_BATTLESHIP_TYPE;
    }
    return defaultReturn;
}



int secondMovementPartMultiplier(char rotationDirection) {
    if (rotationDirection == FORWARD_MOVE) {
        return SECOND_MOVE_FORWARD_MOVE_MULTIPLIER;
    } else {
        return SECOND_MOVE_NOT_FORWARD_MOVE_MULTIPLIER;
    }
}



char translateMovement(char currentDirection, char rotationDirection) {
    char directionsData[NUMBER_OF_DIRECTIONS] = {DEFAULT_GROW_DOWNWARDS_DIRECTION, DEFAULT_GROW_LEFTWARDS_DIRECTION, DEFAULT_GROW_UPWARDS_DIRECTION, DEFAULT_GROW_RIGHTWARDS_DIRECTION};
    int index = DEFAULT_TRANSLATE_INDEX;
    for (int i = DEFAULT_TRANSLATE_DIRECTION_ITERATE_START; i < NUMBER_OF_DIRECTIONS; i++) {
        if (currentDirection == directionsData[i]) {
            index = i;
        }
    }

    int translation = DEFAULT_TRANSLATE_TRANSLATION;
    if (rotationDirection == FORWARD_MOVE) {
        translation = FORWARD_MOVE_TRANSLATION;
    } else if (rotationDirection == LEFT_MOVE) {
        translation = LEFT_MOVE_TRANSLATION;
    } else if (rotationDirection == RIGHT_MOVE) {
        translation = RIGHT_MOVE_TRANSLATION;
    }

    return directionsData[positiveModulo((index + translation), NUMBER_OF_DIRECTIONS)];
}



int movesBasedOnType(char inputType[INPUT_TYPE_LENGTH]) {
    int moves[SHIP_TYPE_NUMBER] = {DEFAULT_CARRIER_MOVES, DEFAULT_BATTLESHIP_MOVES, DEFAULT_CRUISER_MOVES, DEFAULT_DESTROYER_MOVES};
    return moves[integerBasedOnType(inputType)];
}



bool rangeCalculateBasedOnType(char* inputType) {
    bool ranges[SHIP_TYPE_NUMBER] = {DEFAULT_CARRIER_CALCULATE_RANGE, DEFAULT_BATTLESHIP_CALCULATE_RANGE, DEFAULT_CRUISER_CALCULATE_RANGE, DEFAULT_DESTROYER_CALCULATE_RANGE};
    return ranges[integerBasedOnType(inputType)];
}



int getnThDigit(int number, int n) {
    return ((int)(number / pow(10, n)) % 10);
}



char getnTHDigitAsChar(int number, int n) {
    return (char)(ASCII_ZERO_POINT + getnThDigit(number, n));
}



int compensateForZeroInEndingValues(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n;
    }
}



int compensateForNegativeStartingValues(int n) {
    if (isNegative(n)) {
        return n + 1;
    } else {
        return n;
    }
}

//
// End of utility functions, beginning of class declarations.
//



//
// Coordinate class that stores the data of a 2D point in two separate variables.
//

class coordinate {
public:
    int x = DEFAULT_STARTING_POINT_X, y = DEFAULT_STARTING_POINT_Y;
    coordinate();
    coordinate(int inputY, int inputX);
};



coordinate::coordinate() = default;



coordinate::coordinate(int inputY, int inputX) {
    this->y = inputY;
    this->x = inputX;
}



// The "directions" function is used to turn a direction into data saying how this
// particular direction grows in both the Y and X axis.
coordinate directions(char inputDirection) {
    coordinate output;
    if (inputDirection == DEFAULT_GROW_UPWARDS_DIRECTION) {
        output.x = DEFAULT_GROW_UPWARDS_X;
        output.y = DEFAULT_GROW_UPWARDS_Y;
    } else if (inputDirection == DEFAULT_GROW_DOWNWARDS_DIRECTION) {
        output.x = DEFAULT_GROW_DOWNWARDS_X;
        output.y = DEFAULT_GROW_DOWNWARDS_Y;
    } else if (inputDirection == DEFAULT_GROW_RIGHTWARDS_DIRECTION) {
        output.x = DEFAULT_GROW_RIGHTWARDS_X;
        output.y = DEFAULT_GROW_RIGHTWARDS_Y;
    } else if (inputDirection == DEFAULT_GROW_LEFTWARDS_DIRECTION) {
        output.x = DEFAULT_GROW_LEFTWARDS_X;
        output.y = DEFAULT_GROW_LEFTWARDS_Y;
    }
    return output;
}

//
// End of coordinate declarations.
//



//
// Beginning of the declaration of a list based on the coordinate class
// as well as its utility functions.
//

class coordinateList {
public:
    coordinate point;
    coordinateList* next;
    coordinateList();
};



coordinateList::coordinateList() = default;



void initCoordinateList(coordinateList* head) {
    head->next = UNINITIALIZED_LIST_ELEMENT;
}



void addAfterInCoordinateList(coordinateList *list, coordinate coord) {
    coordinateList *newElement = new coordinateList;
    newElement->point = coord;
    newElement->next = list->next;
    list->next = newElement;
}



void removeAfterInCoordinateList(coordinateList *list) {
    if (list->next != UNINITIALIZED_LIST_ELEMENT) {
        coordinateList *element = list->next;
        list->next = list->next->next;
        delete element;
    }
}



void removeElementsInCoordinateList(coordinateList *list) {
    coordinateList *helpList = list;
    do {
        removeAfterInCoordinateList(helpList);
    } while ( (helpList = helpList->next) != UNINITIALIZED_LIST_ELEMENT);
}

//
// End of coordinateList declarations.
//

//
// Beginning of a reefs class, used to store reefs on the board.
// Reefs are handled this way because they were implemented before the lecture
// mentioned lists, and I couldn't find time to swap reefs into a coordinateList.
// The reefs class is essentially a coordinate-based vector limited in its
// uses to what was specified in the instruction.
//

class reefs {
public:
    int size = 0;
    coordinate* list;
    reefs();
    void push(int y, int x);
    const bool exists(int y, int x);
};



reefs::reefs() {
    this->list = new coordinate[this->size];
}



const bool reefs::exists(int y, int x) {
    for (int i = 0; i < this->size; i++) {
        if (this->list[i].y == y && this->list[i].x == x) {
            return true;
        }
    }

    return false;
}



void reefs::push(int y, int x) {
    if (this->exists(y, x)) {
        return;
    }

    this->size++;
    coordinate* newList = new coordinate[this->size];

    for (int i = 0; i < this->size - 1; i++) {
        newList[i] = this->list[i];
    }

    coordinate toInsert = coordinate(y, x);
    newList[this->size - 1] = toInsert;
    this->list = newList;
}

//
// End of reefs declarations.
//



//
// Beginning of the ship class, used for, quite obviously, storing ship data.
// It also contains utility functions to help with printing the game board and such.
//

class ship {
public:
    coordinate startingPoint;
    bool initialized  = DEFAULT_UNINITIALIZED;
    int length, remainingMoves = 0;
    char direction = DEFAULT_DIRECTION;
    int* destroyedParts;
    bool infiniteRange = DEFAULT_CALCULATE_RANGE;
    int remainingShots;
    int spyPlanes;
    ship(char inputDirection, int inputY, int inputX,  int inputLength, int inputDestroyedParts);
    ship();
    const bool isInitialized();
    const bool isEqual(ship ignoredShip);
    coordinate cannonPoint();
    static int cannonIndex();
    coordinate enginePoint();
    const int engineIndex();
    const coordinate radarPoint();
    static int radarIndex();
    bool isCannonDestroyed();
    bool isEngineDestroyed();
    bool isRadarDestroyed();
    bool isVisible(int y, int x);
    const bool hasRemainingShots();
    const bool hasRemainingSpyPlanes();
    bool isInRange(int y, int x);
    void resetShots();
};



ship::ship(char inputDirection, int inputY, int inputX, int inputLength, int inputDestroyedParts) {
    this->direction = inputDirection;
    this->startingPoint.y = inputY;
    this->startingPoint.x = inputX;
    this->initialized = DEFAULT_INITIALIZED;
    this->length = inputLength;
    this->remainingShots = this->length;
    this->spyPlanes = this->length;
    this->destroyedParts = new int[this->length];

    for (int i = 0; i < this->length; i++) {
        this->destroyedParts[i] = getnThDigit(inputDestroyedParts, this->length + PART_READ_OFFSET - i);
    }
}



ship::ship() {
    this->startingPoint.y = DEFAULT_STARTING_POINT_Y;
    this->startingPoint.x = DEFAULT_STARTING_POINT_X;
}



const bool ship::isInitialized() {
    if (this->initialized == DEFAULT_UNINITIALIZED) {
        return DEFAULT_UNINITIALIZED_RETURN;
    } else if (this->initialized == DEFAULT_INITIALIZED) {
        return DEFAULT_INITIALIZED_RETURN;
    } else {
        return DEFAULT_UNKNOWN_RETURN;
    }
}



const bool ship::isEqual(ship ignoredShip) {
    bool isYEqual = (ignoredShip.startingPoint.y == this->startingPoint.y);
    bool isXEqual = (ignoredShip.startingPoint.x == this->startingPoint.x);
    bool isDirectionEqual = (ignoredShip.direction == this->direction);
    bool isLengthEqual = (ignoredShip.length == this->length);

    return (isYEqual && isXEqual && isDirectionEqual && isLengthEqual);
}



coordinate ship::cannonPoint() {
    coordinate direction = directions(this->direction);
    int pointY = this->startingPoint.y + ((DEFAULT_CANNON_OFFSET) * direction.y);
    int pointX = this->startingPoint.x + ((DEFAULT_CANNON_OFFSET) * direction.x);
    coordinate toReturn = coordinate(pointY, pointX);

    return toReturn;
}



int ship::cannonIndex() {
    return DEFAULT_CANNON_OFFSET;
}



coordinate ship::enginePoint() {
    coordinate direction = directions(this->direction);
    int pointY = this->startingPoint.y + ((this->length + DEFAULT_ENGINE_OFFSET) * direction.y);
    int pointX = this->startingPoint.x + ((this->length + DEFAULT_ENGINE_OFFSET) * direction.x);
    coordinate toReturn = coordinate(pointY, pointX);

    return toReturn;
}



const int ship::engineIndex()  {
    return (this->length + DEFAULT_ENGINE_OFFSET);
}



const coordinate ship::radarPoint() {
    return this->startingPoint;
}



int ship::radarIndex() {
    return DEFAULT_RADAR_INDEX;
}



bool ship::isCannonDestroyed() {
    if (this->destroyedParts[this->cannonIndex()] == DESTROYED_PART) {
        return true;
    } else if (this->destroyedParts[this->cannonIndex()] == NOT_DESTROYED_PART) {
        return false;
    }

    return false;
}



bool ship::isEngineDestroyed() {
    if (this->destroyedParts[this->engineIndex()] == DESTROYED_PART) {
        return true;
    } else if (this->destroyedParts[this->engineIndex()] == NOT_DESTROYED_PART) {
        return false;
    }

    return false;
}



bool ship::isRadarDestroyed() {
    if (this->destroyedParts[this->radarIndex()] == DESTROYED_PART) {
        return true;
    } else if (this->destroyedParts[this->radarIndex()] == NOT_DESTROYED_PART) {
        return false;
    }

    return false;
}



const bool ship::hasRemainingShots() {
    if (this->remainingShots > UNABLE_TO_SHOOT_NUMBER) {
        return true;
    } else {
        return false;
    }
}



const bool ship::hasRemainingSpyPlanes() {
    if (this->spyPlanes > UNABLE_TO_SPY_PLANE_NUMBER) {
        return true;
    } else {
        return false;
    }
}


// Unlike the function's syntax may suggest, this function checks if
// the point is in range of the ship, not if the ship is in range of the point.
bool ship::isInRange(int y, int x) {
    coordinate cannonPosition = this->cannonPoint();

    if (sqrt(pow(cannonPosition.y - y, 2) + pow(cannonPosition.x - x, 2)) <= this->length) {
        return true;
    } else {
        return false;
    }
}



bool ship::isVisible(int y, int x) {
    coordinate radarPosition = this->radarPoint();

    if (sqrt(pow(radarPosition.y - y, 2) + pow(radarPosition.x - x, 2)) <= this->length) {
        return true;
    } else {
        return false;
    }
}



void ship::resetShots() {
    this->remainingShots = this->length;
}

//
// End of ship related code.
//



//
// ListOfShips class is a vector, but even more limited than "reefs".
// It also uses ships instead of coordinates.
//

class listOfShips {
public:
    ship* completeList;
    listOfShips();
    int size;
    explicit listOfShips(int count);
    void changeCount(int count);
};



listOfShips::listOfShips() {
    this->size = defaultSum();
    this->completeList = new ship[this->size];
}



listOfShips::listOfShips(int count) {
    this->size = count;
    this->completeList = new ship[count];
}



void listOfShips::changeCount(int count) {
    ship* temporaryList = new ship[count];

    for (int i = 0; i < minimum(count, this->size); i++) {
        temporaryList[i] = this->completeList[i];
    }

    this->completeList = temporaryList;
    this->size = count;
}

//
// End of listOfShips code.
//



//
// The maxShips class declaration,
// used to store the players' ship amounts.
//

class maxShips {
public:
    maxShips();

    const int sum();

    int size;

    void change(int index, int toChange);

    int* list;
};



maxShips::maxShips() {
    this->size = SHIP_TYPE_NUMBER;
    this->list = new int[this->size];

    for (int i = 0; i < this->size; i++) {
        if (i == DEFAULT_DESTROYER_POINT) {
            this->list[i] = DEFAULT_NUMBER_OF_DESTROYERS;
        } else if (i == DEFAULT_CRUISER_POINT) {
            this->list[i] = DEFAULT_NUMBER_OF_CRUISERS;
        } else if (i == DEFAULT_BATTLESHIP_POINT) {
            this->list[i] = DEFAULT_NUMBER_OF_BATTLESHIPS;
        } else if (i == DEFAULT_CARRIER_POINT) {
            this->list[i] = DEFAULT_NUMBER_OF_CARRIERS;
        }
    }
}



const int maxShips::sum() {
    int toSum = 0;

    for (int i = 0; i < this->size; i++) {
        toSum += this->list[i];
    }

    return toSum;
}



void maxShips::change(int index, int toChange) {
    this->list[index] = toChange;
}

//
// End of maxShips code.
//



//
// As usual, the name suggests what the class' use is.
// The player class stores the data of a player, with some utility functions.
//

class player {
public:
    explicit player(char inputName);
    player();
    void assignName(char inputName);
    void allowPositions(int y1, int x1, int y2, int x2);
    coordinateList spyPlanes;
    maxShips playerMaxShips = maxShips();
    listOfShips* playerListOfShips;
    char name;
    int allowedY1, allowedX1, allowedY2, allowedX2, numberOfLists;
    int numberOfListsIterationStart;
    bool isPlayerListFilled(char *inputType);
    bool usedAllShips();
    void setFleet(int index, int toChange);
    const int remainingShipParts();
    void resetShipMovements();
    void resetShipShots();
    void resetSpyPlanes();
    void resetTurn(bool resetMovement, bool resetShipShots, bool resetSpyPlanes);
};



player::player(char inputName) {
    this->name = inputName;
    this->numberOfLists = SHIP_TYPE_NUMBER;
    this->playerListOfShips = new listOfShips[this->numberOfLists];

    for (int i = 0; i < this->numberOfLists; i++) {
        playerListOfShips[i] = listOfShips(this->playerMaxShips.list[i]);
    }

    initCoordinateList(&spyPlanes);
}



player::player() {
    this->numberOfLists = SHIP_TYPE_NUMBER;
    this->playerListOfShips = new listOfShips[this->numberOfLists];

    for (int i = 0; i < this->numberOfLists; i++) {
        playerListOfShips[i] = listOfShips(this->playerMaxShips.list[i]);
    }

    initCoordinateList(&spyPlanes);
}



void player::assignName(char inputName) {
    this->name = inputName;
}



void player::allowPositions(int y1, int x1, int y2, int x2) {
    this->allowedY1 = y1;
    this->allowedX1 = x1;
    this->allowedY2 = y2;
    this->allowedX2 = x2;
}



bool player::isPlayerListFilled(char *inputType) {
    int listID = integerBasedOnType(inputType);

    for (int i = 0; i < this->playerListOfShips[listID].size; i++) {
        if (!this->playerListOfShips[listID].completeList[i].isInitialized()) {
            return false;
        }
    }

    return true;
}



bool player::usedAllShips() {
    for (int i = 0; i < this->numberOfLists; i++) {
        for (int j = 0; j < this->playerListOfShips[i].size; j++) {
            if (!this->playerListOfShips[i].completeList[j].isInitialized()) {
                return false;
            }
        }
    }

    return true;
}



void player::setFleet(int index, int toChange) {
    this->playerMaxShips.change(index, toChange);
    this->playerListOfShips[index].changeCount(toChange);
}



const int player::remainingShipParts() {
    int count = 0;

    for (int i = 0; i < this->numberOfLists; i++) {
        for (int j = 0; j < this->playerListOfShips[i].size; j++) {
            for (int k = 0; k < this->playerListOfShips[i].completeList[j].length; k++) {
                if (this->playerListOfShips[i].completeList[j].destroyedParts[k] == NOT_DESTROYED_PART) {
                    count++;
                }
            }
        }
    }

    return count;
}



void player::resetShipMovements() {
    for (int i = 0; i < this->numberOfLists; i++) {
        for (int j = 0; j < this->playerListOfShips[i].size; j++) {
            this->playerListOfShips[i].completeList[j].remainingMoves = movesBasedOnType(typeBasedOnInteger(i));
        }
    }
}



void player::resetShipShots() {
    for (int i = 0; i < this->numberOfLists; i++) {
        for (int j = 0; j < this->playerListOfShips[i].size; j++) {
            this->playerListOfShips[i].completeList[j].remainingShots = this->playerListOfShips[i].completeList[j].length;
        }
    }
}



void player::resetSpyPlanes() {
    for (int i = 0; i < this->numberOfLists; i++) {
        for (int j = 0; j < this->playerListOfShips[i].size; j++) {
            this->playerListOfShips[i].completeList[j].spyPlanes = this->playerListOfShips[i].completeList[j].length;
            removeElementsInCoordinateList(&(this->spyPlanes));
        }
    }
}



void player::resetTurn(bool resetMovement, bool resetShipShots, bool resetSpyPlanes) {
    if (resetMovement) {
        this->resetShipMovements();
    }

    if (resetShipShots) {
        this->resetShipShots();
    }

    if (resetSpyPlanes) {
        this->resetSpyPlanes();
    }
}

//
// End of player code.
//



class board {
public:
    player* players;
    int sizeY, sizeX, playersCount;
    int startingY, startingX;
    reefs boardReefs;
    board(int y, int x, int inputPlayerCount);
    board();
    void assignPlayer(int id, char inputName);
    void print(int x, char state);
    bool didPlayerWin(int index);
    void prepareRenderAndVisibility(char **toPrint, bool **visibility, int printStartY, int printSizeY, int printStartX, int printSizeX);
    void renderShipsAndVisibility(char **toPrint, bool **visibility, int yOffset, int xOffset, char state, bool extendedPrinting);
    void renderReefs(char **toPrint);
    void renderBoardPositions(char **toPrint, bool **visibility, int printStartY, int printSizeY, int printStartX, int printSizeX);
    void removeRenderAndVisibility(char **toPrint, bool **visibility, int printStartY, int printSizeY);
    void printOnScreen(char **toPrint, bool **visibility, char state, int printStartY, int printSizeY, int printStartX, int printSizeX);
    void renderSpyPlaneVisibility(bool **visibility, char state);
    bool isInBounds(int y, int x);
};



board::board() {
    this->playersCount = NUMBER_OF_PLAYERS;
    this->players = new player[this->playersCount];
    this->sizeY = BOARD_SIZE_Y;
    this->sizeX = BOARD_SIZE_X;
    this->startingY = MINIMUM_BOARD_Y;
    this->startingX = MINIMUM_BOARD_X;

    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
        if (i == 0) {
            this->players[i].assignName(FIRST_PLAYER_LETTER);
            this->players[i].allowPositions(DEFAULT_FIRST_PLAYER_Y1, DEFAULT_FIRST_PLAYER_X1, DEFAULT_FIRST_PLAYER_Y2, DEFAULT_FIRST_PLAYER_X2);
        } else if (i == 1) {
            this->players[i].assignName(SECOND_PLAYER_LETTER);
            this->players[i].allowPositions(DEFAULT_SECOND_PLAYER_Y1, DEFAULT_SECOND_PLAYER_X1, DEFAULT_SECOND_PLAYER_Y2, DEFAULT_SECOND_PLAYER_X2);
        }
    }
}



board::board(int y, int x, int inputPlayerCount) {
    this->playersCount = inputPlayerCount;
    this->players = new player[this->playersCount];
    this->sizeY = y;
    this->sizeX = x;
}



bool board::isInBounds(int y, int x) {
    if (this->startingY <= y && y < this->sizeY && startingX <= x && x < sizeX) {
        return true;
    } else {
        return false;
    }
}



void board::assignPlayer(int id, char inputName) {
    this->players[id].assignName(inputName);
}



void board::prepareRenderAndVisibility(char **toPrint, bool **visibility, int printStartY, int printSizeY, int printStartX, int printSizeX) {
    for (int i = printStartY; i < printSizeY; i++) {
        toPrint[i] = new char[printSizeX];
        visibility[i] = new bool[printSizeX];

        for (int j = printStartX; j < printSizeX; j++) {
            toPrint[i][j] = DEFAULT_EMPTY_CHARACTER;
            visibility[i][j] = false;
        }
    }
}



void board::renderShipsAndVisibility(char **toPrint, bool **visibility, int yOffset, int xOffset, char state, bool extendedPrinting) {
    for (int i = 0; i < this->playersCount; i++) {
        for (int j = 0; j < this->players[i].numberOfLists; j++) {
            for (int k = 0; k < this->players[i].playerListOfShips[j].size; k++) {
                if (this->players[i].playerListOfShips[j].completeList[k].isInitialized()) {
                    if (i == playerNumber(state)) {
                        for (int m = this->startingY; m < this->sizeY; m++) {
                            for (int n = this->startingX; n < this->sizeX; n++) {
                                if (this->players[i].playerListOfShips[j].completeList[k].isVisible(m, n)) {
                                    visibility[m + yOffset][n + xOffset] = true;
                                }
                            }
                        }
                    }
                    coordinate direction = directions(this->players[i].playerListOfShips[j].completeList[k].direction);

                    for (int l = 0; l < this->players[i].playerListOfShips[j].completeList[k].length; l++) {
                        char outputChar;

                        if (this->players[i].playerListOfShips[j].completeList[k].destroyedParts[l] == NOT_DESTROYED_PART) {
                            outputChar = DEFAULT_SHIP_CHARACTER;

                            if (extendedPrinting) {
                                if (l == this->players[i].playerListOfShips[j].completeList[k].radarIndex()) {
                                    outputChar = DEFAULT_RADAR_CHARACTER;
                                } else if (l == this->players[i].playerListOfShips[j].completeList[k].engineIndex()) {
                                    outputChar = DEFAULT_ENGINE_CHARACTER;
                                } else if (l == this->players[i].playerListOfShips[j].completeList[k].cannonIndex()) {
                                    outputChar = DEFAULT_CANNON_CHARACTER;
                                }
                            }
                        } else {
                            outputChar = DEFAULT_DESTROYED_SHIP_CHARACTER;
                        }

                        toPrint[this->players[i].playerListOfShips[j].completeList[k].startingPoint.y + (l * direction.y) + yOffset][this->players[i].playerListOfShips[j].completeList[k].startingPoint.x + (l * direction.x) + xOffset] = outputChar;
                    }
                }
            }
        }
    }
}



void board::renderReefs(char **toPrint) {
    for (int i = 0; i < this->boardReefs.size; i++) {
        toPrint[this->boardReefs.list[i].y][this->boardReefs.list[i].x] = DEFAULT_REEF_CHARACTER;
    }
}



void board::renderBoardPositions(char **toPrint, bool **visibility, int printStartY, int printSizeY, int printStartX, int printSizeX) {
    int currentPrintY = EXTENDED_PRINT_NUMBER_Y_START;
    for (int i = printStartY + EXTENDED_PRINT_Y_OFFSET; i < printSizeY; i++) {
        for (int j = EXTENDED_PRINT_POSITION_X_START; j < EXTENDED_PRINT_POSITION_X_END; j++) {
            int boardPositionY = i;
            int boardPositionX = EXTENDED_PRINT_POSITION_X_END + BOARD_POSITION_PRINT_OFFSET - j;
            visibility[boardPositionY][boardPositionX] = true;
            toPrint[boardPositionY][boardPositionX] = getnTHDigitAsChar(currentPrintY, j);
        }

        currentPrintY += EXTENDED_PRINT_NUMBER_INCREMENT;
    }

    int currentPrintX = EXTENDED_PRINT_NUMBER_X_START;
    for (int i = printStartX + EXTENDED_PRINT_X_OFFSET; i < printSizeX; i++) {
        for (int j = EXTENDED_PRINT_POSITION_Y_START; j < EXTENDED_PRINT_POSITION_Y_END; j++) {
            int boardPositionY = EXTENDED_PRINT_POSITION_Y_END + BOARD_POSITION_PRINT_OFFSET - j;
            int boardPositionX = i;
            visibility[boardPositionY][boardPositionX] = true;
            toPrint[boardPositionY][boardPositionX] = getnTHDigitAsChar(currentPrintX, j);
        }

        currentPrintX += EXTENDED_PRINT_NUMBER_INCREMENT;
    }

    for (int i = EXTENDED_PRINT_POSITION_Y_START; i < EXTENDED_PRINT_POSITION_Y_END; i++) {
        for (int j = EXTENDED_PRINT_POSITION_X_START; j < EXTENDED_PRINT_POSITION_X_END; j++) {
            visibility[i][j] = true;
        }
    }
}



void board::removeRenderAndVisibility(char **toPrint, bool **visibility, int printStartY, int printSizeY) {
    for (int i = printStartY; i < printSizeY; i++) {
        delete[] visibility[i];
        delete[] toPrint[i];
    }
    delete[] visibility;
    delete[] toPrint;
}



void board::renderSpyPlaneVisibility(bool **visibility, char state) {
    if (state == STATE_STATE) {
        return;
    }

    coordinateList helpList = this->players[playerNumber(state)].spyPlanes;
    while (helpList.next != UNINITIALIZED_LIST_ELEMENT) {
        int startY = maximum(this->startingY, helpList.next->point.y - SPY_RANGE);
        int endY = minimum(this->sizeY, helpList.next->point.y + SPY_RANGE + SPY_RANGE_FOR_COMPENSATION);
        int startX = maximum(this->startingX, helpList.next->point.x - SPY_RANGE);
        int endX = minimum(this->sizeX, helpList.next->point.x + SPY_RANGE + SPY_RANGE_FOR_COMPENSATION);

        for (int i = startY; i < endY; i++) {
            for (int j = startX; j < endX; j++) {
                visibility[i][j] = true;
            }
        }

        helpList.next = helpList.next->next;
    }
}



void board::printOnScreen(char **toPrint, bool **visibility, char state, int printStartY, int printSizeY, int printStartX, int printSizeX) {
    for (int i = printStartY; i < printSizeY; i++) {
        for (int j = printStartX; j < printSizeX; j++) {
            if (visibility[i][j] || state == STATE_STATE) {
                cout << toPrint[i][j];
            } else {
                cout << OUT_OF_RANGE_CHARACTER;
            }
        }

        cout << endl;
    }
}



void board::print(int x, char state) {
    bool extendedPrinting = false;
    int yExtension = NORMAL_PRINT_Y_EXTENSION;
    int xExtension = NORMAL_PRINT_X_EXTENSION;
    int yOffset = NORMAL_PRINT_Y_OFFSET;
    int xOffset = NORMAL_PRINT_X_OFFSET;

    if (x == EXTENDED_PRINT_INT) {
        extendedPrinting = true;
        yExtension = EXTENDED_PRINT_Y_EXTENSION;
        xExtension = EXTENDED_PRINT_X_EXTENSION;
        yOffset = EXTENDED_PRINT_Y_OFFSET;
        xOffset = EXTENDED_PRINT_X_OFFSET;
    }

    int printStartY = this->startingY;
    int printStartX = this->startingX;
    int printSizeY = this->sizeY + yExtension;
    int printSizeX = this->sizeX + xExtension;
    char **toPrint = new char*[printSizeY];
    bool **visibility = new bool*[printSizeY];

    this->prepareRenderAndVisibility(toPrint, visibility, printStartY, printSizeY, printStartX, printSizeX);

    this->renderReefs(toPrint);

    this->renderShipsAndVisibility(toPrint, visibility, yOffset, xOffset, state, extendedPrinting);

    if (extendedPrinting) {
        this->renderBoardPositions(toPrint, visibility, printStartY, printSizeY, printStartX, printSizeX);
    }

    this->renderSpyPlaneVisibility(visibility, state);

    this->printOnScreen(toPrint, visibility, state, printStartY, printSizeY, printStartX, printSizeX);

    removeRenderAndVisibility(toPrint, visibility, printStartY, printSizeY);
}



bool board::didPlayerWin(int index) {
    for (int i = 0; i < this->playersCount; i++) {
        if (!this->players[i].usedAllShips()) {
            return false;
        }

        if (i != index) {
            if (this->players[i].remainingShipParts() != ALL_PARTS_DESTROYED) {
                return false;
            }
        }
    }

    return true;
}



//
// The gameState class contains all the data regarding the state of the game.
// It also has first-line handlers for the players' commands.
//

class gameState {
public:
    char state;
    int remainingMoves = DEFAULT_MOVE_COUNT;
    char nextPlayer;
    bool utilizeNextPlayer = DEFAULT_NEXT_PLAYER_UTILIZATION;
    bool extendedShips;
    gameState();
    board gameBoard;
    void toggleExtendedShips();
    bool placeShip(char playerChar, char inputType[INPUT_TYPE_LENGTH], char inputDirection, int inputY, int inputX, int shipIndex, int partDescription, char inputBuffer[INPUT_BUFFER_SIZE]);
    bool commandHandler(char inputBuffer[INPUT_BUFFER_SIZE]);
    bool changeState(char goalState, char inputBuffer[INPUT_BUFFER_SIZE]);
    bool isOnReefs(ship inputShip);
    bool isTooClose(ship inputShip, ship ignoredShip, bool ignore);
    bool placeShipHandler(char inputBuffer[INPUT_BUFFER_SIZE]);
    bool shoot(char inputBuffer[INPUT_BUFFER_SIZE]);
    void setPlayerFleet();
    void printHandler();
    bool checkWins(char playerChar);
    void changeBoardSize();
    void initializePositions();
    bool reefHandler(char inputBuffer[INPUT_BUFFER_SIZE]);
    bool moveShipHandler(char inputBuffer[INPUT_BUFFER_SIZE]);
    static bool isInBounds(ship inputShip);
    bool spyHandler(char inputBuffer[INPUT_BUFFER_SIZE]);
    bool attemptShot(int y, int x, int i = -1, char *inputType = (char*)"UNDEF");
    void placeShipGenericError(char inputBuffer[INPUT_BUFFER_SIZE], char playerChar, int inputY, int inputX, char inputDirection, int shipIndex, char inputType[INPUT_TYPE_LENGTH], int partDescription);
    void shootGenericError(char inputBuffer[INPUT_BUFFER_SIZE], int shipIndex, char inputType[INPUT_TYPE_LENGTH], int inputY, int inputX);
    void reefGenericError(char inputBuffer[INPUT_BUFFER_SIZE], int inputY, int inputX);
    void changeStateGenericError(char inputBuffer[INPUT_BUFFER_SIZE]);
    void spyGenericError(char inputBuffer[INPUT_BUFFER_SIZE], int index, int y, int x);
    void moveGenericError(char inputBuffer[INPUT_BUFFER_SIZE], int index, char inputType[INPUT_TYPE_LENGTH], char inputDirection);
    bool allShipsPlaced();
    bool nextPlayerHandler();
    void saveGenericError(char inputBuffer[INPUT_BUFFER_SIZE]);
    bool saveState(char inputBuffer[INPUT_BUFFER_SIZE]);
};



gameState::gameState() {
    this->state = FREE_STATE;
    this->remainingMoves = DEFAULT_MOVE_COUNT;
    this->extendedShips = false;
}



void gameState::toggleExtendedShips() {
    this->extendedShips = !this->extendedShips;
}



bool gameState::isOnReefs(ship inputShip) {
    coordinate direction = directions(inputShip.direction);
    for (int i = 0; i < inputShip.length; i++) {
        if (this->gameBoard.boardReefs.exists(inputShip.startingPoint.y + (direction.y * i), inputShip.startingPoint.x + (direction.x * i))) {
            return true;
        }
    }
    return false;
}



bool gameState::allShipsPlaced() {
    for (int i = 0; i < this->gameBoard.playersCount; i++) {
        if (!this->gameBoard.players[i].usedAllShips()) {
            return false;
        }
    }
    return true;
}



bool gameState::isInBounds(ship inputShip) {
    coordinate direction = directions(inputShip.direction);
    for (int i = 0; i < inputShip.length; i++) {
        int y = inputShip.startingPoint.y + (i * direction.y);
        int x = inputShip.startingPoint.x + (i * direction.x);
        if (MINIMUM_BOARD_Y > y || y >= BOARD_SIZE_Y || MINIMUM_BOARD_X > x || x >= BOARD_SIZE_X) {
            return false;
        }
    }
    return true;
}



bool gameState::isTooClose(ship inputShip, ship ignoredShip = ship(), bool ignore = false) {
    int** safeArea = new int*[this->gameBoard.sizeY];
    for (int i = 0; i < this->gameBoard.sizeY; i++) {
        safeArea[i] = new int[this->gameBoard.sizeX];
        for (int j = 0; j < this->gameBoard.sizeX; j++) {
            safeArea[i][j] = SAFE_SPOT;
        }
    }

    for (int i = 0; i < this->gameBoard.playersCount; i++) {
        for (int j = 0; j < this->gameBoard.players[i].numberOfLists; j++) {
            for (int l = 0; l < this->gameBoard.players[i].playerListOfShips[j].size; l++) {
                if (!(ignore && ignoredShip.isEqual(this->gameBoard.players[i].playerListOfShips[j].completeList[l]))) {
                    coordinate direction = directions(this->gameBoard.players[i].playerListOfShips[j].completeList[l].direction);

                    int startPointY = this->gameBoard.players[i].playerListOfShips[j].completeList[l].startingPoint.y - PROXIMITY_RANGE;
                    int startOffsetY = compensateForNegativeStartingValues(((int)isNegative(direction.y)) * this->gameBoard.players[i].playerListOfShips[j].completeList[l].length * direction.y);

                    int endPointY = this->gameBoard.players[i].playerListOfShips[j].completeList[l].startingPoint.y + PROXIMITY_RANGE;
                    int endOffsetY = compensateForZeroInEndingValues(((int) !isNegative(direction.y)) * this->gameBoard.players[i].playerListOfShips[j].completeList[l].length * direction.y);

                    int startPointX = this->gameBoard.players[i].playerListOfShips[j].completeList[l].startingPoint.x - PROXIMITY_RANGE;
                    int startOffsetX = compensateForNegativeStartingValues(((int)isNegative(direction.x)) * this->gameBoard.players[i].playerListOfShips[j].completeList[l].length * direction.x);

                    int endPointX = this->gameBoard.players[i].playerListOfShips[j].completeList[l].startingPoint.x + PROXIMITY_RANGE;
                    int endOffsetX = compensateForZeroInEndingValues(((int) !isNegative(direction.x)) * this->gameBoard.players[i].playerListOfShips[j].completeList[l].length * direction.x);

                    for (int k = maximum(startPointY + startOffsetY, this->gameBoard.startingY); k < minimum(endPointY + endOffsetY, this->gameBoard.sizeY); k++) {
                        for (int m = maximum(startPointX + startOffsetX, this->gameBoard.startingX); m < minimum(endPointX + endOffsetX, this->gameBoard.sizeX); m++) {
                            safeArea[k][m] = UNSAFE_SPOT;
                        }
                    }
                }
            }
        }
    }

    coordinate inputDirection = directions(inputShip.direction);
    for (int i = 0; i < inputShip.length; i++) {
        int y = inputShip.startingPoint.y + (i * inputDirection.y);
        int x = inputShip.startingPoint.x + (i * inputDirection.x);

        if (safeArea[y][x] == UNSAFE_SPOT) {
            for (int j = 0; j < this->gameBoard.sizeY; j++) {
                delete[] safeArea[j];
            }
            delete[] safeArea;
            return true;
        }
    }

    for (int i = 0; i < this->gameBoard.sizeY; i++) {
        delete[] safeArea[i];
    }
    delete[] safeArea;

    return false;
}



void genericErrorBeginning() {
    cout << INVALID_OPERATION_STRING << " \"";
}

void genericErrorEnding() {
    cout << "\": ";
}



void gameState::changeStateGenericError(char *inputBuffer) {
    genericErrorBeginning();
    cout << inputBuffer << " ";
    genericErrorEnding();
}



void gameState::placeShipGenericError(char *inputBuffer, char playerChar, int inputY, int inputX, char inputDirection, int shipIndex, char *inputType, int partDescription) {
    genericErrorBeginning();

    if (strcmp(inputBuffer, SHIP_COMMAND) == SUCCESSFUL_STRCMP) {
        cout << inputBuffer << " " << inputY << " " << inputX << " " << inputDirection << " " << shipIndex << " " << inputType;
    } else if (strcmp(inputBuffer, STATE_SHIP_COMMAND) == SUCCESSFUL_STRCMP) {
        cout << inputBuffer << " " << playerChar << " " << inputY << " " << inputX << " " << inputDirection << " " << shipIndex << " " << inputType << " " << partDescription;
    }

    genericErrorEnding();
}



void gameState::shootGenericError(char *inputBuffer, int shipIndex, char *inputType, int inputY, int inputX) {
    genericErrorBeginning();

    if (this->extendedShips) {
        cout << inputBuffer << " " << shipIndex << " " << inputType << " " << inputY << " " << inputX;
    } else {
        cout << inputBuffer << " " << inputY << " " << inputX;
    }

    genericErrorEnding();
}



void gameState::reefGenericError(char *inputBuffer, int inputY, int inputX) {
    genericErrorBeginning();

    cout << inputBuffer << " " << inputY << " " << inputX;

    genericErrorEnding();
}



void gameState::spyGenericError(char *inputBuffer, int index, int y, int x) {
    genericErrorBeginning();

    cout << inputBuffer << " " << index << " " << y << " " << x;

    genericErrorEnding();
}



void gameState::moveGenericError(char *inputBuffer, int index, char inputType[INPUT_TYPE_LENGTH], char inputDirection) {
    genericErrorBeginning();

    cout << inputBuffer << " " << index << " " << inputType << " " << inputDirection;

    genericErrorEnding();
}



void gameState::saveGenericError(char *inputBuffer) {
    genericErrorBeginning();

    cout << inputBuffer;

    genericErrorEnding();
}



bool gameState::placeShip (char playerChar, char inputType[INPUT_TYPE_LENGTH], char inputDirection, int inputY, int inputX, int shipIndex, int partDescription, char inputBuffer[INPUT_BUFFER_SIZE]) {
    int playerID = playerNumber(playerChar);
    bool isYAllowed = true;
    bool isXAllowed = true;

    ship newInstance = ship(inputDirection, inputY, inputX, lengthBasedOnType(inputType), partDescription);
    newInstance.remainingMoves = movesBasedOnType(inputType);
    newInstance.infiniteRange = rangeCalculateBasedOnType(inputType);
    coordinate direction = directions(newInstance.direction);

    for (int i = 0; i < newInstance.length; i++) {
        int y = newInstance.startingPoint.y + (i * direction.y);
        int x = newInstance.startingPoint.x + (i * direction.x);

        if (!(this->gameBoard.players[playerID].allowedY1 <= y && y <= this->gameBoard.players[playerID].allowedY2)) {
            isYAllowed = false;
            break;
        }

        if (!(this->gameBoard.players[playerID].allowedX1 <= x && x <= this->gameBoard.players[playerID].allowedX2)) {
            isXAllowed = false;
            break;
        }
    }

    if (isYAllowed && isXAllowed) {
        if (!gameBoard.isInBounds(inputY, inputX)) {
            cout << "OUT OF BOUNDS" << endl;
            return false;
        }

        if (!this->isOnReefs(newInstance)) {
            if (!this->isTooClose(newInstance)) {
                int listID = integerBasedOnType(inputType);

                if (!this->gameBoard.players[playerID].playerListOfShips[listID].completeList[shipIndex].isInitialized()) {
                    if (!this->gameBoard.players[playerID].isPlayerListFilled(inputType)) {
                        this->gameBoard.players[playerID].playerListOfShips[listID].completeList[shipIndex] = newInstance;
                    } else {
                        placeShipGenericError(inputBuffer, playerChar, inputY, inputX, inputDirection, shipIndex, inputType, partDescription);
                        cout << "ALL SHIPS OF THE CLASS ALREADY SET" << endl;
                        return false;
                    }
                } else {
                    placeShipGenericError(inputBuffer, playerChar, inputY, inputX, inputDirection, shipIndex, inputType, partDescription);
                    cout << "SHIP ALREADY PRESENT" << endl;
                    return false;
                }
            } else {
                placeShipGenericError(inputBuffer, playerChar, inputY, inputX, inputDirection, shipIndex, inputType, partDescription);
                cout << "PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
                return false;
            }
        } else {
            placeShipGenericError(inputBuffer, playerChar, inputY, inputX, inputDirection, shipIndex, inputType, partDescription);
            cout << "PLACING SHIP ON REEF" << endl;
            return false;
        }
    } else {
        placeShipGenericError(inputBuffer, playerChar, inputY, inputX, inputDirection, shipIndex, inputType, partDescription);
        cout << "NOT IN STARTING POSITION " << endl;
        return false;
    }

    return true;
}



bool gameState::placeShipHandler(char inputBuffer[INPUT_BUFFER_SIZE]) {
    char playerChar, inputType[INPUT_TYPE_LENGTH], inputDirection;
    int inputY, inputX, shipIndex, partDescription;

    if (this->state == FREE_STATE) {
        cout << "SELECT PLAYER FIRST" << endl;
        return false;
    } else if (this->state == STATE_STATE) {
        cin >> playerChar >> inputY >> inputX >> inputDirection >> shipIndex >> inputType >> partDescription;
    } else {
        playerChar = this->state;
        cin >> inputY >> inputX >> inputDirection >> shipIndex >> inputType;
        partDescription = composePart(lengthBasedOnType(inputType));
    }

    return this->placeShip(playerChar, inputType, inputDirection, inputY, inputX, shipIndex, partDescription, inputBuffer);
}



bool gameState::checkWins(char playerChar) {
    if (this->gameBoard.didPlayerWin(playerNumber(playerChar))) {
        return true;
    } else {
        return false;
    }
}



bool gameState::changeState(char goalState, char *inputBuffer) {
    if (this->state == FREE_STATE) {
        if (goalState != STATE_STATE && this->utilizeNextPlayer && goalState != this->nextPlayer) {
            changeStateGenericError(inputBuffer);
            cout << "THE OTHER PLAYER EXPECTED" << endl;
            return false;
        }

        this->state = goalState;
    } else if (this->state == goalState) {
        if (this->state != STATE_STATE) {
            this->gameBoard.players[playerNumber(this->state)].resetTurn(RESET_MOVEMENT_ON_TURN_END, RESET_SHOTS_ON_TURN_END, RESET_SPY_PLANES_ON_TURN_END);

            if (this->checkWins(this->state)) {
                cout << this->state << " won" << endl;
            }

            this->utilizeNextPlayer = true;
            this->nextPlayer = (playerChar(positiveModulo(playerNumber(this->state) + 1, this->gameBoard.playersCount)));
        }

        this->state = FREE_STATE;
        this->remainingMoves = DEFAULT_MOVE_COUNT;
    } else {
        cout << "OTHER PLAYER OR STATE EXPECTED." << endl;
        return false;
    }
    return true;
}



bool gameState::attemptShot(int y, int x, int index, char *inputType) {
    if (this->extendedShips && DOES_SHOOTING_DEPLETE_SHOTS) {
        this->gameBoard.players[playerNumber(this->state)].playerListOfShips[integerBasedOnType(inputType)].completeList[index].remainingShots--;
    }

    if (DOES_SHOOTING_DEPLETE_MOVES) {
        this->remainingMoves--;
    }

    for (int i = 0; i < this->gameBoard.playersCount; i++) {
        if (i == playerNumber(this->state)) {
            continue;
        }

        for (int j = 0; j < this->gameBoard.players[i].numberOfLists; j++) {
            for (int k = 0; k < this->gameBoard.players[i].playerListOfShips[j].size; k++) {
                coordinate direction = directions(this->gameBoard.players[i].playerListOfShips[j].completeList[k].direction);

                for (int l = 0; l < this->gameBoard.players[i].playerListOfShips[j].completeList[k].length; l++) {
                    if (y == this->gameBoard.players[i].playerListOfShips[j].completeList[k].startingPoint.y + (l * direction.y) && x == this->gameBoard.players[i].playerListOfShips[j].completeList[k].startingPoint.x + (l * direction.x)) {
                        this->gameBoard.players[i].playerListOfShips[j].completeList[k].destroyedParts[l] = DESTROYED_PART;
                        return true;
                    }
                }
            }
        }
    }

    return true;
}



bool gameState::shoot(char *inputBuffer) {
    int i, y, x;
    char *inputType = new char[INPUT_TYPE_LENGTH];

    if (this->extendedShips) {
        cin >> i >> inputType >> y >> x;
    } else {
        cin >> y >> x;
    }

    if (DOES_SHOOTING_CHECK_MOVES && this->remainingMoves == 0) {
        shootGenericError(inputBuffer, i, inputType, y, x);
        cout << "NO MOVES LEFT" << endl;
        delete[] inputType;
        return false;
    }

    char playerChar = this->state;
    if (playerChar != FREE_STATE && playerChar != STATE_STATE) {
        if (MINIMUM_BOARD_Y <= y && y < this->gameBoard.sizeY && MINIMUM_BOARD_X <= x && x < this->gameBoard.sizeX) {
            if (this->allShipsPlaced()) {
                if (this->extendedShips) {
                    if (this->gameBoard.players[playerNumber(this->state)].playerListOfShips[integerBasedOnType(inputType)].completeList[i].isCannonDestroyed()) {
                        shootGenericError(inputBuffer, i, inputType, y, x);
                        cout << "SHIP CANNOT SHOOT" << endl;
                        delete[] inputType;
                        return false;
                    } else {
                        if (!this->gameBoard.players[playerNumber(this->state)].playerListOfShips[integerBasedOnType(inputType)].completeList[i].hasRemainingShots()) {
                            shootGenericError(inputBuffer, i, inputType, y, x);
                            cout << "TOO MANY SHOOTS" << endl;
                            delete[] inputType;
                            return false;
                        } else {
                            if (!this->gameBoard.players[playerNumber(this->state)].playerListOfShips[integerBasedOnType(inputType)].completeList[i].isInRange(y, x)) {
                                shootGenericError(inputBuffer, i, inputType, y, x);
                                cout << "SHOOTING TOO FAR" << endl;
                                delete[] inputType;
                                return false;
                            }
                        }
                    }

                    bool temp = attemptShot(y, x, i, inputType);
                    delete[] inputType;
                    return temp;
                } else {
                    bool temp = attemptShot(y, x, i, inputType);
                    delete[] inputType;
                    return temp;
                }
            } else {
                shootGenericError(inputBuffer, i, inputType, y, x);
                cout << "NOT ALL SHIPS PLACED" << endl;
                delete[] inputType;
                return false;
            }
        } else {
            shootGenericError(inputBuffer, i, inputType, y, x);
            cout << "FIELD DOES NOT EXIST" << endl;
            delete[] inputType;
            return false;
        }
    }

    delete[] inputType;
    return false;
}



void gameState::printHandler() {
    int x;
    cin >> x;

    this->gameBoard.print(x, this->state);
    if (this->state == STATE_STATE) {
        cout << "PARTS REMAINING::";

        for (int i = 0; i < this->gameBoard.playersCount; i++) {
            cout << " " << this->gameBoard.players[i].name << " : " << this->gameBoard.players[i].remainingShipParts();
        }

        cout << endl;
    }
}



void gameState::setPlayerFleet() {
    char playerChar;
    cin >> playerChar;
    int* fleetArray = new int[SHIP_TYPE_NUMBER];

    for (int i = 0; i < SHIP_TYPE_NUMBER; i++) {
        if (i == DEFAULT_DESTROYER_POINT) {
            fleetArray[i] = DEFAULT_NUMBER_OF_DESTROYERS;
        } else if (i == DEFAULT_CRUISER_POINT) {
            fleetArray[i] = DEFAULT_NUMBER_OF_CRUISERS;
        } else if (i == DEFAULT_BATTLESHIP_POINT) {
            fleetArray[i] = DEFAULT_NUMBER_OF_BATTLESHIPS;
        } else if (i == DEFAULT_CARRIER_POINT) {
            fleetArray[i] = DEFAULT_NUMBER_OF_CARRIERS;
        }

        cin >> fleetArray[i];

        this->gameBoard.players[playerNumber(playerChar)].setFleet(i, fleetArray[i]);
    }
}



void gameState::changeBoardSize() {
    int y, x;
    cin >> y >> x;
    this->gameBoard.sizeY = y;
    this->gameBoard.sizeX = x;
}



void gameState::initializePositions() {
    char playerChar;
    int y1, x1, y2, x2;
    cin >> playerChar >> y1 >> x1 >> y2 >> x2;

    this->gameBoard.players[playerNumber(playerChar)].allowPositions(y1, x1, y2, x2);
}



bool gameState::reefHandler(char *inputBuffer) {
    int y, x;
    cin >> y >> x;

    if (this->gameBoard.isInBounds(y, x)) {
        this->gameBoard.boardReefs.push(y, x);
        return true;
    } else {
        reefGenericError(inputBuffer, y, x);
        return false;
    }
}



bool gameState::moveShipHandler(char inputBuffer[INPUT_BUFFER_SIZE]) {
    int id;
    char shipType[INPUT_TYPE_LENGTH];
    char inputDirection;
    cin >> id >> shipType >> inputDirection;
    ship newInstance;
    newInstance = this->gameBoard.players[playerNumber(this->state)].playerListOfShips[integerBasedOnType(shipType)].completeList[id];
    if (this->extendedShips && newInstance.isEngineDestroyed()) {
        moveGenericError(inputBuffer, id, shipType, inputDirection);
        cout << "SHIP CANNOT MOVE" << endl;
        return false;
    }
    if (newInstance.remainingMoves == 0) {
        moveGenericError(inputBuffer, id, shipType, inputDirection);
        cout << "SHIP MOVED ALREADY" << endl;
        return false;
    }
    coordinate direction = directions(newInstance.direction);
    newInstance.direction = translateMovement(newInstance.direction, inputDirection);
    coordinate secondDirection = directions(newInstance.direction);
    newInstance.startingPoint.x += ((DEFAULT_MOVEMENT_UNIT * direction.x) * DEFAULT_MOVE_MULTIPLIER) + (((newInstance.length + DEFAULT_SECOND_MOVE_OFFSET) * secondDirection.x) * DEFAULT_SECOND_MOVE_MULTIPLIER * secondMovementPartMultiplier(inputDirection));
    newInstance.startingPoint.y += ((DEFAULT_MOVEMENT_UNIT * direction.y) * DEFAULT_MOVE_MULTIPLIER) + (((newInstance.length + DEFAULT_SECOND_MOVE_OFFSET) * secondDirection.y) * DEFAULT_SECOND_MOVE_MULTIPLIER * secondMovementPartMultiplier(inputDirection));
    if (!this->isOnReefs(newInstance)) {
        if (this->isInBounds(newInstance)) {
            if (!this->isTooClose(newInstance, this->gameBoard.players[playerNumber(this->state)].playerListOfShips[integerBasedOnType(shipType)].completeList[id], IGNORE_ITSELF_WHEN_MOVING)) {
                newInstance.remainingMoves--;
                this->gameBoard.players[playerNumber(this->state)].playerListOfShips[integerBasedOnType(shipType)].completeList[id] = newInstance;
                return true;
            } else {
                moveGenericError(inputBuffer, id, shipType, inputDirection);
                cout << "PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            }
        } else {
            moveGenericError(inputBuffer, id, shipType, inputDirection);
            cout << "SHIP WENT FROM BOARD" << endl;
        }
    } else {
        moveGenericError(inputBuffer, id, shipType, inputDirection);
        cout << "PLACING SHIP ON REEF" << endl;
    }
    return false;
}



bool gameState::spyHandler(char *inputBuffer) {
    int i, y, x;
    cin >> i >> y >> x;
    if (!this->gameBoard.players[playerNumber(this->state)].playerListOfShips[integerBasedOnType(DEFAULT_CARRIER_TYPE)].completeList[i].isEngineDestroyed()) {
        if (this->gameBoard.players[playerNumber(this->state)].playerListOfShips[integerBasedOnType(DEFAULT_CARRIER_TYPE)].completeList[i].hasRemainingSpyPlanes()) {
            coordinate spyPoint = coordinate(y, x);
            addAfterInCoordinateList(&this->gameBoard.players[playerNumber(this->state)].spyPlanes, spyPoint);
            return true;
        } else {
            spyGenericError(inputBuffer, i, y, x);
            cout << "ALL PLANES SENT" << endl;
            return false;
        }
    } else {
        spyGenericError(inputBuffer, i, y, x);
        cout << "CANNOT SEND PLANE" << endl;
        return false;
    }
}



bool gameState::nextPlayerHandler() {
    char playerChar;
    cin >> playerChar;
    this->utilizeNextPlayer = true;
    this->nextPlayer = playerChar;
    return true;
}



bool gameState::saveState(char *inputBuffer) {
    if (this->state != STATE_STATE) {
        saveGenericError(inputBuffer);
        return false;
    }
    cout << STATE_COMMAND << endl;

    cout << BOARD_SIZE_COMMAND << " " << this->gameBoard.sizeY << " " << this->gameBoard.sizeX << endl;

    cout << NEXT_PLAYER_COMMAND << " " << this->nextPlayer << endl;

    for (int i = 0; i < this->gameBoard.playersCount; i++) {
        cout << INIT_POSITION_COMMAND << " " << this->gameBoard.players[i].name << " " << this->gameBoard.players[i].allowedY1 << " " << this->gameBoard.players[i].allowedX1 << " " << this->gameBoard.players[i].allowedY2 << " " << this->gameBoard.players[i].allowedX2 << endl;
        cout << SET_FLEET_COMMAND << " " << this->gameBoard.players[i].name;
        for (int j = 0; j < this->gameBoard.players[i].numberOfLists; j++) {
            cout << " " << this->gameBoard.players[i].playerListOfShips[j].size;
        }
        cout << endl;
        for (int j = 0; j < this->gameBoard.players[i].numberOfLists; j++) {
            for (int k = 0; k < this->gameBoard.players[i].playerListOfShips[j].size; k++) {
                int y = this->gameBoard.players[i].playerListOfShips[j].completeList[k].startingPoint.y;
                int x = this->gameBoard.players[i].playerListOfShips[j].completeList[k].startingPoint.x;
                char direction = this->gameBoard.players[i].playerListOfShips[j].completeList[k].direction;
                char *type = typeBasedOnInteger(j);
                cout << STATE_SHIP_COMMAND << " " << this->gameBoard.players[i].name << " " << y << " " << x << " " << direction << " " << k << " " << type << " ";
                for (int l = 0; l < this->gameBoard.players[i].playerListOfShips[j].completeList[k].length; l++) {
                    cout << this->gameBoard.players[i].playerListOfShips[j].completeList[k].destroyedParts[l];
                }
                cout << endl;
            }
        }
    }

    cout << STATE_COMMAND << endl;
    return true;
}



bool gameState::commandHandler(char inputBuffer[INPUT_BUFFER_SIZE]){
    bool inputValidity = true;
    if (strcmp(STATE_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        inputValidity = this->changeState(STATE_STATE, inputBuffer);
    } else if (strcmp(DEFAULT_FIRST_PLAYER_COMMAND, inputBuffer) ==SUCCESSFUL_STRCMP) {
        inputValidity = this->changeState(FIRST_PLAYER_LETTER, inputBuffer);
    } else if (strcmp(DEFAULT_SECOND_PLAYER_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        inputValidity = this->changeState(SECOND_PLAYER_LETTER, inputBuffer);
    } else if (strcmp(PRINT_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        this->printHandler();
    } else if (strcmp(SET_FLEET_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        this->setPlayerFleet();
    } else if (strcmp(NEXT_PLAYER_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        this->nextPlayerHandler();
    } else if (strcmp(BOARD_SIZE_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        this->changeBoardSize();
    } else if (strcmp(INIT_POSITION_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        this->initializePositions();
    } else if (strcmp(REEF_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        inputValidity = this->reefHandler(inputBuffer);
    } else if (strcmp(STATE_SHIP_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP || strcmp(SHIP_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        inputValidity = this->placeShipHandler(inputBuffer);
    } else if (strcmp(SHOOT_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        inputValidity = this->shoot(inputBuffer);
    } else if (strcmp(MOVE_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        inputValidity = this->moveShipHandler(inputBuffer);
    } else if (strcmp(EXTENDED_SHIPS_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        this->toggleExtendedShips();
    } else if (strcmp(SPY_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        inputValidity = this->spyHandler(inputBuffer);
    } else if (strcmp(SAVE_COMMAND, inputBuffer) == SUCCESSFUL_STRCMP) {
        inputValidity = this->saveState(inputBuffer);
    } else if (strcmp("quit", inputBuffer) == SUCCESSFUL_STRCMP) {
        return false;
    }

    if (STOP_GAME_ON_INVALID_INPUT && !inputValidity) {
        return false;
    }

    return true;
}



int main() {
    gameState state;
    char inputBuffer[INPUT_BUFFER_SIZE];
    bool toContinue = true;
    while (cin >> inputBuffer) {
        if (toContinue) {
            toContinue = state.commandHandler(inputBuffer);
        } else {
            break;
        }
    }

    return 0;
}
