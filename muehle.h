#ifndef MUEHLE_H_INCLUDED
#define MUEHLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define VALID 1
#define INVALID_MOVEMENT -1
#define INVALID_INPUT -2
#define RED1 "\x1b[1;31mX\x1b[0m"
#define BLUE2 "\x1b[1;33mX\x1b[0m"

int user_input(void);
int flush_buff(void);
int coordinate(int zahl, int xOderY);
int normal_movement(int feld[3][8], int firstInput, int secondInput);
void init_feld(int feld[3][8]);
int steineSetzen(int feld[3][8], int zahl, int spieler);
void print_feld(int feld[3][8]);
int obInMuele(int feld[3][8], int input);
void felder_tauschen(int alteFeld[3][8], int neueFeld[3][8]);
int anzahlVonMuelen(int feld[3][8]);
int steineLoeschen(int feld[3][8], int input, int welcheSpieler);
int spring_movement(int feld[3][8], int input1, int input2);
void start_2_spieler(int feld[3][8]);
int obInMuele2(int feld[3][8], int x, int y);
int obAlleInMuele(int feld[3][8], int welcherSpieler);
int muele(int alteFeld[3][8], int neueFeld[3][8], int stein);
int moving_2_spieler(int feld[3][8]);
int steine_zaehlen(int feld[3][8], int welcheSpieler);
void start_ai_spieler(int feld[3][8]);
int normal_movement_check(int feld[3][8], int firstInput, int secondInput);
int moving_ai_spieler(int feld[3][8]);
const char *ntoc(int n);
int start_game(int feld[3][8]);
void Muehle(int feld[3][8]);
void print_feld2(int i,int feld[3][8],int modus);
int moving_2_spieler_variant(int feld[3][8]);
void print_feld3( int feld[3][8], int spieler1,int spieler2);

#endif
