#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "cJSON.h"
#include "player.h"

#define NUM_HAND        2
#define NUM_COMMUNITY   5
#define NUM_DECK        53 //cards are 1-indexed
#define MAX_OPPONENTS   10

typedef enum phase
{
    PHASE_DEAL,
    PHASE_FLOP,
    PHASE_TURN,
    PHASE_RIVER,
    PHASE_ERROR
} Phase;

typedef struct gamestate
{
    int round_id;
    int initial_stack;
    int stack;
    int current_bet;
    int call_amount;
    int current_pot;
    Phase phase;
    int hand[NUM_HAND];
    int handsize;
    bool your_turn;
    Player opponents[MAX_OPPONENTS];
    int num_opponents;
    int num_playing;
    int community[NUM_COMMUNITY];
    int communitysize;
    bool deck[NUM_DECK];
} GameState;

/*
 * Set the game state according to the given JSON
 * game: the game state to set
 * json: a JSON representation of the game state
 */
void SetGameState(GameState *game, cJSON *json);

/*
 * Update the game's deck based on
 * the game's hand and community cards
 * game: the game to update
 */
void UpdateGameDeck(GameState *game);

/*
 * Create an int representing the given card
 * card: the string representation of the card
 * return: the representation of this card as an int
 */
int StringToCard(char *card);

/*
 * Set the card array to the given JSON array
 * cards: the int array of where to place the results
 * json: a JSON array of card strings
 * return: the number of cards in the array
 */
int GetCardArray(int *cards, cJSON *json);

/*
 * Print the current table information
 * game: the game state containing the table information
 * logfile: the file for logging output
 */
void PrintTableInfo(GameState *game, FILE *logfile);

/*
 * Print the AI's cards to the given file
 * game: the game state containing the cards
 * logfile: the file for logging output
 */
void PrintCards(GameState *game, FILE *logfile);

/*
 * Print the current players at the table and their information
 * game: the game state containing the players
 * logfile: the file for logging output
 */
void PrintPlayers(GameState *game, FILE *logfile);

#endif
