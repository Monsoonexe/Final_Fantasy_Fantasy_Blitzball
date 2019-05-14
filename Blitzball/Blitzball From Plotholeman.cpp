#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <vector>
using namespace std;

ofstream recap;
ifstream teamdata;
ifstream playerdata;

//========================GAME VARIABLES==============================

bool team1ball = true; string ball_name = "INVALID";
int ball_xpos = 0; int ball_ypos = 0;
int radius = 10000; int ballspot_distance = 6000; int engage_distance = 1000;
int timeleft = 300; bool team1starts2nd = false; int shtbonus = 0;
bool try_again = true; int bench = 0;

//============================TEAM 1==================================

//Team 1 Variables
string t1name = "INVALID"; string t1 = "INVALID";
string t1formation = "NORMAL"; int t1score = 0;

//Team 1 Center
string t1c_name = "INVALID"; string t1c_bonus = "SHT";
int t1c_xpos = 0; int t1c_ypos = 0; 
string t1c_risk = "NORMAL"; string t1c_type = "NORMAL";
int t1c_sht = 0; int t1c_pas = 0; int t1c_end = 0; 
int t1c_atk = 0; int t1c_blk = 0; int t1c_ca = 0; 

//Team 1 Right Forward
string t1rf_name = "INVALID"; string t1rf_bonus = "SHT";
int t1rf_xpos = 0; int t1rf_ypos = 0; 
string t1rf_risk = "NORMAL"; string t1rf_type = "NORMAL";
int t1rf_sht = 0; int t1rf_pas = 0; int t1rf_end = 0; 
int t1rf_atk = 0; int t1rf_blk = 0; int t1rf_ca = 0; 

//Team 1 Left Forward
string t1lf_name = "INVALID"; string t1lf_bonus = "SHT";
int t1lf_xpos = 0; int t1lf_ypos = 0; 
string t1lf_risk = "NORMAL"; string t1lf_type = "NORMAL";
int t1lf_sht = 0; int t1lf_pas = 0; int t1lf_end = 0; 
int t1lf_atk = 0; int t1lf_blk = 0; int t1lf_ca = 0; 

//Team 1 Right Defender
string t1rd_name = "INVALID"; string t1rd_bonus = "SHT";
int t1rd_xpos = 0; int t1rd_ypos = 0; 
string t1rd_risk = "NORMAL"; string t1rd_type = "NORMAL";
int t1rd_sht = 0; int t1rd_pas = 0; int t1rd_end = 0; 
int t1rd_atk = 0; int t1rd_blk = 0; int t1rd_ca = 0; 

//Team 1 Left Defender
string t1ld_name = "INVALID"; string t1ld_bonus = "SHT";
int t1ld_xpos = 0; int t1ld_ypos = 0; 
string t1ld_risk = "NORMAL"; string t1ld_type = "NORMAL";
int t1ld_sht = 0; int t1ld_pas = 0; int t1ld_end = 0; 
int t1ld_atk = 0; int t1ld_blk = 0; int t1ld_ca = 0; 

//Team 1 Goalie
string t1g_name = "INVALID"; int t1g_boost = 0;
int t1g_xpos = -10000; int t1g_ypos = 0; 
string t1g_risk = "NORMAL"; string t1g_type = "NORMAL";
int t1g_sht = 0; int t1g_pas = 0; int t1g_end = 0; 
int t1g_atk = 0; int t1g_blk = 0; int t1g_ca = 0; 

//============================TEAM 2==================================

//Team 2 Variables
string t2name = "INVALID"; string t2 = "INVALID";
string t2formation = "NORMAL"; int t2score = 0;


//Team 2 Center
string t2c_name = "INVALID"; string t2c_bonus = "SHT";
int t2c_xpos = 0; int t2c_ypos = 0; 
string t2c_risk = "NORMAL"; string t2c_type = "NORMAL";
int t2c_sht = 0; int t2c_pas = 0; int t2c_end = 0; 
int t2c_atk = 0; int t2c_blk = 0; int t2c_ca = 0; 

//Team 2 Right Forward
string t2rf_name = "INVALID"; string t2rf_bonus = "SHT";
int t2rf_xpos = 0; int t2rf_ypos = 0; 
string t2rf_risk = "NORMAL"; string t2rf_type = "NORMAL";
int t2rf_sht = 0; int t2rf_pas = 0; int t2rf_end = 0; 
int t2rf_atk = 0; int t2rf_blk = 0; int t2rf_ca = 0; 

//Team 2 Left Forward
string t2lf_name = "INVALID"; string t2lf_bonus = "SHT";
int t2lf_xpos = 0; int t2lf_ypos = 0; 
string t2lf_risk = "NORMAL"; string t2lf_type = "NORMAL";
int t2lf_sht = 0; int t2lf_pas = 0; int t2lf_end = 0; 
int t2lf_atk = 0; int t2lf_blk = 0; int t2lf_ca = 0; 

//Team 2 Right Defender
string t2rd_name = "INVALID"; string t2rd_bonus = "SHT";
int t2rd_xpos = 0; int t2rd_ypos = 0; 
string t2rd_risk = "NORMAL"; string t2rd_type = "NORMAL";
int t2rd_sht = 0; int t2rd_pas = 0; int t2rd_end = 0; 
int t2rd_atk = 0; int t2rd_blk = 0; int t2rd_ca = 0; 

//Team 2 Left Defender
string t2ld_name = "INVALID"; string t2ld_bonus = "SHT";
int t2ld_xpos = 0; int t2ld_ypos = 0; 
string t2ld_risk = "NORMAL"; string t2ld_type = "NORMAL";
int t2ld_sht = 0; int t2ld_pas = 0; int t2ld_end = 0; 
int t2ld_atk = 0; int t2ld_blk = 0; int t2ld_ca = 0; 

//Team 2 Goalie
string t2g_name = "INVALID"; int t2g_boost = 0;
int t2g_xpos = 10000; int t2g_ypos = 0; 
string t2g_risk = "NORMAL"; string t2g_type = "NORMAL";
int t2g_sht = 0; int t2g_pas = 0; int t2g_end = 0; 
int t2g_atk = 0; int t2g_blk = 0; int t2g_ca = 0; 

//===========================================================================
//=============================Package Functions=============================
//===========================================================================

void tackle_slip (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ pas += 2*lvl; end += 3*lvl; ca += lvl; }

void grip_gloves (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ pas += 2*lvl; blk += 3*lvl; ca += lvl; }

void elite_defense (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ pas += lvl; atk += 2*lvl; blk += 2*lvl; ca += lvl; }

void brawler (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ end += lvl; atk += 3*lvl; blk += lvl; ca += lvl; }

void golden_arm (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ pas += 3*lvl; sht += 2*lvl; blk += lvl; }

void jecht_shot (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ sht += 2*lvl; end += 2*lvl; atk += 2*lvl; }

void volley_shot (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ sht += 3*lvl; end += 2*lvl; blk += lvl; }

void all_rounder (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ sht += lvl; pas += lvl; end += lvl; atk += lvl; blk += lvl; ca += lvl; }

void super_goalie (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ ca += (int)1.5*lvl; pas += lvl; }

void keepa (int lvl, int & sht, int & pas, int & end, int & atk, int & blk, int & ca)
{ sht += 2*lvl; ca += lvl; }

//===========================================================================
//=============================Helper Functions==============================
//===========================================================================

//Get Distance Function
double get_dist (int from_xpos, int from_ypos, int to_xpos, int to_ypos){
 double distance = sqrt(pow(from_xpos-to_xpos,2)+pow(from_ypos-to_ypos,2));
 return distance;
}

//Get Shot Function
int get_sht (string player){
 if (player == t1c_name) { return t1c_sht; }
 else if (player == t1rf_name) { return t1rf_sht; }
 else if (player == t1lf_name) { return t1lf_sht; }
 else if (player == t1rd_name) { return t1rd_sht; }
 else if (player == t1ld_name) { return t1ld_sht; }
 else if (player == t1g_name) { return t1g_sht; } 
 else if (player == t2c_name) { return t2c_sht; }
 else if (player == t2rf_name) { return t2rf_sht; }
 else if (player == t2lf_name) { return t2lf_sht; }
 else if (player == t2rd_name) { return t2rd_sht; }
 else if (player == t2ld_name) { return t2ld_sht; }
 else if (player == t2g_name) { return t2g_sht; } 
 else { recap << endl << "GET_SHT IS A LIE!"; exit(0); }
}

//Get Pass Function
int get_pas (string player){
 if (player == t1c_name) { return t1c_pas; }
 else if (player == t1rf_name) { return t1rf_pas; }
 else if (player == t1lf_name) { return t1lf_pas; }
 else if (player == t1rd_name) { return t1rd_pas; }
 else if (player == t1ld_name) { return t1ld_pas; }
 else if (player == t1g_name) { return t1g_pas; } 
 else if (player == t2c_name) { return t2c_pas; }
 else if (player == t2rf_name) { return t2rf_pas; }
 else if (player == t2lf_name) { return t2lf_pas; }
 else if (player == t2rd_name) { return t2rd_pas; }
 else if (player == t2ld_name) { return t2ld_pas; }
 else if (player == t2g_name) { return t2g_pas; } 
 else { recap << endl << "GET_PAS IS A LIE!"; exit(0); }
}

//Get Endurance Function
int get_end (string player){
 if (player == t1c_name) { return t1c_end; }
 else if (player == t1rf_name) { return t1rf_end; }
 else if (player == t1lf_name) { return t1lf_end; }
 else if (player == t1rd_name) { return t1rd_end; }
 else if (player == t1ld_name) { return t1ld_end; }
 else if (player == t1g_name) { return t1g_end; } 
 else if (player == t2c_name) { return t2c_end; }
 else if (player == t2rf_name) { return t2rf_end; }
 else if (player == t2lf_name) { return t2lf_end; }
 else if (player == t2rd_name) { return t2rd_end; }
 else if (player == t2ld_name) { return t2ld_end; }
 else if (player == t2g_name) { return t2g_end; } 
 else { recap << endl << "GET_END IS A LIE!"; exit(0); }
}

//Get Tackle Function
int get_atk (string player){
 if (player == t1c_name) { return t1c_atk; }
 else if (player == t1rf_name) { return t1rf_atk; }
 else if (player == t1lf_name) { return t1lf_atk; }
 else if (player == t1rd_name) { return t1rd_atk; }
 else if (player == t1ld_name) { return t1ld_atk; }
 else if (player == t1g_name) { return t1g_atk; } 
 else if (player == t2c_name) { return t2c_atk; }
 else if (player == t2rf_name) { return t2rf_atk; }
 else if (player == t2lf_name) { return t2lf_atk; }
 else if (player == t2rd_name) { return t2rd_atk; }
 else if (player == t2ld_name) { return t2ld_atk; }
 else if (player == t2g_name) { return t2g_atk; } 
 else { recap << endl << "GET_ATK IS A LIE!"; exit(0); }
}

//Get Block Function
int get_blk (string player){
 if (player == t1c_name) { return t1c_blk; }
 else if (player == t1rf_name) { return t1rf_blk; }
 else if (player == t1lf_name) { return t1lf_blk; }
 else if (player == t1rd_name) { return t1rd_blk; }
 else if (player == t1ld_name) { return t1ld_blk; }
 else if (player == t1g_name) { return t1g_blk; } 
 else if (player == t2c_name) { return t2c_blk; }
 else if (player == t2rf_name) { return t2rf_blk; }
 else if (player == t2lf_name) { return t2lf_blk; }
 else if (player == t2rd_name) { return t2rd_blk; }
 else if (player == t2ld_name) { return t2ld_blk; }
 else if (player == t2g_name) { return t2g_blk; } 
 else { recap << endl << "GET_BLK IS A LIE!"; exit(0); }
}

//Get Catch Function
int get_ca (string player){
 if (player == t1c_name) { return t1c_ca; }
 else if (player == t1rf_name) { return t1rf_ca; }
 else if (player == t1lf_name) { return t1lf_ca; }
 else if (player == t1rd_name) { return t1rd_ca; }
 else if (player == t1ld_name) { return t1ld_ca; }
 else if (player == t1g_name) { return t1g_ca; } 
 else if (player == t2c_name) { return t2c_ca; }
 else if (player == t2rf_name) { return t2rf_ca; }
 else if (player == t2lf_name) { return t2lf_ca; }
 else if (player == t2rd_name) { return t2rd_ca; }
 else if (player == t2ld_name) { return t2ld_ca; }
 else if (player == t2g_name) { return t2g_ca; } 
 else { recap << endl << "GET_CA IS A LIE!"; exit(0); }
}

//Get Position Function
string get_position (string player){
 if (player == t1c_name) { return "T1C"; }
 else if (player == t1rf_name) { return "T1RF"; }
 else if (player == t1lf_name) { return "T1LF"; }
 else if (player == t1rd_name) { return "T1RD"; }
 else if (player == t1ld_name) { return "T1LD"; }
 else if (player == t1g_name) { return "T1G"; } 
 else if (player == t2c_name) { return "T2C"; }
 else if (player == t2rf_name) { return "T2RF"; }
 else if (player == t2lf_name) { return "T2LF"; }
 else if (player == t2rd_name) { return "T2RD"; }
 else if (player == t2ld_name) { return "T2LD"; }
 else if (player == t2g_name) { return "T2G"; } 
 else { recap << endl << "GET_CA IS A LIE!"; exit(0); }
}

//Get X-Position Function
int get_xpos (string player){
 if (player == t1c_name) { return t1c_xpos; }
 else if (player == t1rf_name) { return t1rf_xpos; }
 else if (player == t1lf_name) { return t1lf_xpos; }
 else if (player == t1rd_name) { return t1rd_xpos; }
 else if (player == t1ld_name) { return t1ld_xpos; }
 else if (player == t1g_name) { return t1g_xpos; } 
 else if (player == t2c_name) { return t2c_xpos; }
 else if (player == t2rf_name) { return t2rf_xpos; }
 else if (player == t2lf_name) { return t2lf_xpos; }
 else if (player == t2rd_name) { return t2rd_xpos; }
 else if (player == t2ld_name) { return t2ld_xpos; }
 else if (player == t2g_name) { return t2g_xpos; } 
 else { recap << endl << "GET_XPOS IS A LIE!"; exit(0); }
}

//Get Y-Position Function
int get_ypos (string player){
 if (player == t1c_name) { return t1c_ypos; }
 else if (player == t1rf_name) { return t1rf_ypos; }
 else if (player == t1lf_name) { return t1lf_ypos; }
 else if (player == t1rd_name) { return t1rd_ypos; }
 else if (player == t1ld_name) { return t1ld_ypos; }
 else if (player == t1g_name) { return t1g_ypos; } 
 else if (player == t2c_name) { return t2c_ypos; }
 else if (player == t2rf_name) { return t2rf_ypos; }
 else if (player == t2lf_name) { return t2lf_ypos; }
 else if (player == t2rd_name) { return t2rd_ypos; }
 else if (player == t2ld_name) { return t2ld_ypos; }
 else if (player == t2g_name) { return t2g_ypos; } 
 else { recap << endl << "GET_YPOS IS A LIE!"; exit(0); }
}

//Get Formation Function
string get_formation (string player){
 if (player == t1c_name) { return t1formation; }
 else if (player == t1rf_name) { return t1formation; }
 else if (player == t1lf_name) { return t1formation; }
 else if (player == t1rd_name) { return t1formation; }
 else if (player == t1ld_name) { return t1formation; }
 else if (player == t1g_name) { return t1formation; } 
 else if (player == t2c_name) { return t2formation; }
 else if (player == t2rf_name) { return t2formation; }
 else if (player == t2lf_name) { return t2formation; }
 else if (player == t2rd_name) { return t2formation; }
 else if (player == t2ld_name) { return t2formation; }
 else if (player == t2g_name) { return t2formation; } 
 else { recap << endl << "Get_Formation IS A LIE!"; exit(0); }
}

//Return random ca (for goalie) 
string get_risk(string player){
 if (player == t1c_name) { return t1c_risk; }
 else if (player == t1rf_name) { return t1rf_risk; }
 else if (player == t1lf_name) { return t1lf_risk; }
 else if (player == t1rd_name) { return t1rd_risk; }
 else if (player == t1ld_name) { return t1ld_risk; }
 else if (player == t1g_name) { return t1g_risk; } 
 else if (player == t2c_name) { return t2c_risk; }
 else if (player == t2rf_name) { return t2rf_risk; }
 else if (player == t2lf_name) { return t2lf_risk; }
 else if (player == t2rd_name) { return t2rd_risk; }
 else if (player == t2ld_name) { return t2ld_risk; }
 else if (player == t2g_name) { return t2g_risk; } 
 else { recap << endl << "GET_RISK IS A LIE!"; exit(0); }
}

//Return random bonus (from goalie)
string random_bonus(){
 int random = rand()%5;
 if (random == 0){ return "SHT"; }
 else if (random == 1){ return "PAS"; }
 else if (random == 2){ return "END"; }
 else if (random == 3){ return "ATK"; }
 else { return "BLK"; }
}

//Return random ca (for goalie) 
int random_ca(string goalie){
 int random = rand()%5;
 if (goalie == t1g_name){
  if (random == 0){ return t1c_ca; }
  else if (random == 1){ return t1rf_ca; }
  else if (random == 2){ return t1lf_ca; }
  else if (random == 3){ return t1rd_ca; }
  else { return t1ld_ca; }
 }
 else {
  if (random == 0){ return t2c_ca; }
  else if (random == 1){ return t2rf_ca; }
  else if (random == 2){ return t2lf_ca; }
  else if (random == 3){ return t2rd_ca; }
  else { return t2ld_ca; }      
 }
}

//Randomize Bonus Modifiers
void randomize_bonuses(){
 t1c_bonus = random_bonus();
 t1rf_bonus = random_bonus();
 t1lf_bonus = random_bonus();
 t1rd_bonus = random_bonus();
 t1ld_bonus = random_bonus();
 
 t2c_bonus = random_bonus();
 t2rf_bonus = random_bonus();
 t2lf_bonus = random_bonus();
 t2rd_bonus = random_bonus();
 t2ld_bonus = random_bonus();
}

//Get X-Position Function
int give_xpos (string player, int pos){
 if (player == t1c_name) { t1c_xpos = pos; }
 else if (player == t1rf_name) { t1rf_xpos = pos; }
 else if (player == t1lf_name) { t1lf_xpos = pos; }
 else if (player == t1rd_name) { t1rd_xpos = pos; }
 else if (player == t1ld_name) { t1ld_xpos = pos; }
 else if (player == t1g_name) { t1g_xpos = pos; } 
 else if (player == t2c_name) { t2c_xpos = pos; }
 else if (player == t2rf_name) { t2rf_xpos = pos; }
 else if (player == t2lf_name) { t2lf_xpos = pos; }
 else if (player == t2rd_name) { t2rd_xpos = pos; }
 else if (player == t2ld_name) { t2ld_xpos = pos; }
 else if (player == t2g_name) { t2g_xpos = pos; } 
 else { recap << endl << "GET_XPOS IS A LIE!"; exit(0); }
}

//Get Y-Position Function
int give_ypos (string player, int pos){
 if (player == t1c_name) { t1c_ypos = pos; }
 else if (player == t1rf_name) { t1rf_ypos = pos; }
 else if (player == t1lf_name) { t1lf_ypos = pos; }
 else if (player == t1rd_name) { t1rd_ypos = pos; }
 else if (player == t1ld_name) { t1ld_ypos = pos; }
 else if (player == t1g_name) { t1g_ypos = pos; } 
 else if (player == t2c_name) { t2c_ypos = pos; }
 else if (player == t2rf_name) { t2rf_ypos = pos; }
 else if (player == t2lf_name) { t2lf_ypos = pos; }
 else if (player == t2rd_name) { t2rd_ypos = pos; }
 else if (player == t2ld_name) { t2ld_ypos = pos; }
 else if (player == t2g_name) { t2g_ypos = pos; }
 else { recap << endl << "GET_YPOS IS A LIE!"; exit(0); }
}

//Get Y-Position Function
string bad_goalie (string player){
 if (player == t1c_name) { return t2g_name; }
 else if (player == t1rf_name) { return t2g_name; }
 else if (player == t1lf_name) { return t2g_name; }
 else if (player == t1rd_name) { return t2g_name; }
 else if (player == t1ld_name) { return t2g_name; }
 else if (player == t1g_name) { return t2g_name; } 
 else if (player == t2c_name) { return t1g_name; }
 else if (player == t2rf_name) { return t1g_name; }
 else if (player == t2lf_name) { return t1g_name; }
 else if (player == t2rd_name) { return t1g_name; }
 else if (player == t2ld_name) { return t1g_name; }
 else if (player == t2g_name) { return t1g_name; }
 else { recap << endl << "BAD GOALIE!"; exit(0); }
}

//==============================================================================
//=================================Bonuses======================================
//==============================================================================

//Get Goalie Function
string get_goalie (string player){
 if (player == t1c_name) { return t1g_name; }
 else if (player == t1rf_name) { return t1g_name; }
 else if (player == t1lf_name) { return t1g_name; }
 else if (player == t1rd_name) { return t1g_name; }
 else if (player == t1ld_name) { return t1g_name; }
 else if (player == t1g_name) { return t1g_name; }
 else if (player == t2c_name) { return t2g_name; }
 else if (player == t2rf_name) { return t2g_name; }
 else if (player == t2lf_name) { return t2g_name; }
 else if (player == t2rd_name) { return t2g_name; }
 else if (player == t2ld_name) { return t2g_name; }
 else if (player == t2g_name) { return t2g_name; }
 else { recap << endl << "GET_GOALIE IS A LIE!"; exit(0); }
}

//Get Type Bonus Function
string get_type_bonus (string player){
 if (player == t1c_name) { return t1c_type; }
 else if (player == t1rf_name) { return t1rf_type; }
 else if (player == t1lf_name) { return t1lf_type; }
 else if (player == t1rd_name) { return t1rd_type; }
 else if (player == t1ld_name) { return t1ld_type; }
 else if (player == t1g_name) { return t1g_type; }
 else if (player == t2c_name) { return t2c_type; }
 else if (player == t2rf_name) { return t2rf_type; }
 else if (player == t2lf_name) { return t2lf_type; }
 else if (player == t2rd_name) { return t2rd_type; }
 else if (player == t2ld_name) { return t2ld_type; }
 else if (player == t2g_name) { return t2g_type; }
 else { recap << endl << "GET_GOALIE IS A LIE!"; exit(0); }
}

//Get Bonus Shot Function
int get_bonus_sht (string player){
 if (player == t1c_name && t1c_bonus == "SHT") { return t1g_sht; }
 if (player == t1rf_name && t1rf_bonus == "SHT") { return t1g_sht; }
 if (player == t1lf_name && t1lf_bonus == "SHT") { return t1g_sht; }
 if (player == t1rd_name && t1rd_bonus == "SHT") { return t1g_sht; }
 if (player == t1ld_name && t1ld_bonus == "SHT") { return t1g_sht; }
 if (player == t2c_name && t2c_bonus == "SHT") { return t2g_sht; }
 if (player == t2rf_name && t2rf_bonus == "SHT") { return t2g_sht; }
 if (player == t2lf_name && t2lf_bonus == "SHT") { return t2g_sht; }
 if (player == t2rd_name && t2rd_bonus == "SHT") { return t2g_sht; }
 if (player == t2ld_name && t2ld_bonus == "SHT") { return t2g_sht; }
 return 0;
}

//Get Bonus Pass Function
int get_bonus_pas (string player){
 if (player == t1c_name && t1c_bonus == "PAS") { return t1g_pas; }
 if (player == t1rf_name && t1rf_bonus == "PAS") { return t1g_pas; }
 if (player == t1lf_name && t1lf_bonus == "PAS") { return t1g_pas; }
 if (player == t1rd_name && t1rd_bonus == "PAS") { return t1g_pas; }
 if (player == t1ld_name && t1ld_bonus == "PAS") { return t1g_pas; }
 if (player == t2c_name && t2c_bonus == "PAS") { return t2g_pas; }
 if (player == t2rf_name && t2rf_bonus == "PAS") { return t2g_pas; }
 if (player == t2lf_name && t2lf_bonus == "PAS") { return t2g_pas; }
 if (player == t2rd_name && t2rd_bonus == "PAS") { return t2g_pas; }
 if (player == t2ld_name && t2ld_bonus == "PAS") { return t2g_pas; }
 return 0;
}

//Get Bonus Endurance Function
int get_bonus_end (string player){
 if (player == t1c_name && t1c_bonus == "END") { return t1g_end; }
 if (player == t1rf_name && t1rf_bonus == "END") { return t1g_end; }
 if (player == t1lf_name && t1lf_bonus == "END") { return t1g_end; }
 if (player == t1rd_name && t1rd_bonus == "END") { return t1g_end; }
 if (player == t1ld_name && t1ld_bonus == "END") { return t1g_end; }
 if (player == t2c_name && t2c_bonus == "END") { return t2g_end; }
 if (player == t2rf_name && t2rf_bonus == "END") { return t2g_end; }
 if (player == t2lf_name && t2lf_bonus == "END") { return t2g_end; }
 if (player == t2rd_name && t2rd_bonus == "END") { return t2g_end; }
 if (player == t2ld_name && t2ld_bonus == "END") { return t2g_end; }
 return 0;
}

//Get Bonus Attack Function
int get_bonus_atk (string player){
 if (player == t1c_name && t1c_bonus == "ATK") { return t1g_atk; }
 if (player == t1rf_name && t1rf_bonus == "ATK") { return t1g_atk; }
 if (player == t1lf_name && t1lf_bonus == "ATK") { return t1g_atk; }
 if (player == t1rd_name && t1rd_bonus == "ATK") { return t1g_atk; }
 if (player == t1ld_name && t1ld_bonus == "ATK") { return t1g_atk; }
 if (player == t2c_name && t2c_bonus == "ATK") { return t2g_atk; }
 if (player == t2rf_name && t2rf_bonus == "ATK") { return t2g_atk; }
 if (player == t2lf_name && t2lf_bonus == "ATK") { return t2g_atk; }
 if (player == t2rd_name && t2rd_bonus == "ATK") { return t2g_atk; }
 if (player == t2ld_name && t2ld_bonus == "ATK") { return t2g_atk; }
 return 0;
}

//Get Bonus Block Function
int get_bonus_blk (string player){
 if (player == t1c_name && t1c_bonus == "BLK") { return t1g_blk; }
 if (player == t1rf_name && t1rf_bonus == "BLK") { return t1g_blk; }
 if (player == t1lf_name && t1lf_bonus == "BLK") { return t1g_blk; }
 if (player == t1rd_name && t1rd_bonus == "BLK") { return t1g_blk; }
 if (player == t1ld_name && t1ld_bonus == "BLK") { return t1g_blk; }
 if (player == t2c_name && t2c_bonus == "BLK") { return t2g_blk; }
 if (player == t2rf_name && t2rf_bonus == "BLK") { return t2g_blk; }
 if (player == t2lf_name && t2lf_bonus == "BLK") { return t2g_blk; }
 if (player == t2rd_name && t2rd_bonus == "BLK") { return t2g_blk; }
 if (player == t2ld_name && t2ld_bonus == "BLK") { return t2g_blk; }
 return 0;
}

//==============================================================================
//===============================Loose Ball=====================================
//==============================================================================

//Ball is Loose
string loose_ball (string target){
       
 //Variables
 int x = get_xpos(target); int y = get_ypos(target);
 double shortest = 3*radius;
 vector <string> closest;
 int random = 0;
 string recovery = "";
 
 //Find the closest people to target
 if (target != t1c_name && get_dist(x,y,t1c_xpos,t1c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t1c_xpos,t1c_ypos); 
 }
 if (target != t1rf_name && get_dist(x,y,t1c_xpos,t1c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t1c_xpos,t1c_ypos); 
 }
 if (target != t1lf_name && get_dist(x,y,t1c_xpos,t1c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t1c_xpos,t1c_ypos); 
 }
 if (target != t1rd_name && get_dist(x,y,t1c_xpos,t1c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t1c_xpos,t1c_ypos); 
 }
 if (target != t1ld_name && get_dist(x,y,t1c_xpos,t1c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t1c_xpos,t1c_ypos); 
 }
 if (target != t2c_name && get_dist(x,y,t2c_xpos,t2c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t2c_xpos,t2c_ypos); 
 }
 if (target != t2rf_name && get_dist(x,y,t2c_xpos,t2c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t2c_xpos,t2c_ypos); 
 }
 if (target != t2lf_name && get_dist(x,y,t2c_xpos,t2c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t2c_xpos,t2c_ypos); 
 }
 if (target != t2rd_name && get_dist(x,y,t2c_xpos,t2c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t2c_xpos,t2c_ypos); 
 }
 if (target != t2ld_name && get_dist(x,y,t2c_xpos,t2c_ypos) <= shortest){ 
  shortest = get_dist(x,y,t2c_xpos,t2c_ypos); 
 }
 
 //All names into list if equally close to target
 if (target != t1c_name && get_dist(x,y,t1c_xpos,t1c_ypos) == shortest){ 
  closest.push_back(t1c_name);
 }
 if (target != t1rf_name && get_dist(x,y,t1c_xpos,t1c_ypos) == shortest){  
  closest.push_back(t1rf_name);
 }
 if (target != t1lf_name && get_dist(x,y,t1c_xpos,t1c_ypos) == shortest){  
  closest.push_back(t1lf_name);
 }
 if (target != t1rd_name && get_dist(x,y,t1c_xpos,t1c_ypos) == shortest){ 
  closest.push_back(t1rd_name);
 }
 if (target != t1ld_name && get_dist(x,y,t1c_xpos,t1c_ypos) == shortest){ 
  closest.push_back(t1ld_name);
 }
 if (target != t2c_name && get_dist(x,y,t2c_xpos,t2c_ypos) == shortest){ 
  closest.push_back(t2c_name);
 }
 if (target != t2rf_name && get_dist(x,y,t2c_xpos,t2c_ypos) == shortest){  
  closest.push_back(t2rf_name);
 }
 if (target != t2lf_name && get_dist(x,y,t2c_xpos,t2c_ypos) == shortest){ 
  closest.push_back(t2lf_name);
 }
 if (target != t2rd_name && get_dist(x,y,t2c_xpos,t2c_ypos) == shortest){ 
  closest.push_back(t2rd_name);
 }
 if (target != t2ld_name && get_dist(x,y,t2c_xpos,t2c_ypos) == shortest){ 
  closest.push_back(t2ld_name);
 }
 
 if (closest.size() == 1) { recovery = closest[0]; }
 else { random = rand()%closest.size(); recovery = closest[random]; }
 recap << recovery << " claims the ball." << endl << endl;
 return recovery;
}

//==============================================================================
//==============================Fill Blockers===================================
//==============================================================================

//Ball is Loose
vector <string> fill_blockers (string player){
       
 //Variables
 int x = get_xpos(player); int y = get_ypos(player);
 vector <string> blockers;
 vector <string> sorted_blockers;
 int i = 0; int j = 0; int topattack = 0;
 
 //Team 1
 if (team1ball){
  if (get_dist(x,y,t2c_xpos,t2c_ypos) <= engage_distance){
   blockers.push_back(t2c_name);                                    
  }
  if (get_dist(x,y,t2rf_xpos,t2rf_ypos) <= engage_distance){
   blockers.push_back(t2rf_name);                                    
  }
  if (get_dist(x,y,t2lf_xpos,t2lf_ypos) <= engage_distance){
   blockers.push_back(t2lf_name);                                    
  }
  if (get_dist(x,y,t2rd_xpos,t2rd_ypos) <= engage_distance){
   blockers.push_back(t2rd_name);                                    
  }
  if (get_dist(x,y,t2ld_xpos,t2ld_ypos) <= engage_distance){
   blockers.push_back(t2ld_name);                                    
  }
 }
  
  //Team 2
 else {
  if (get_dist(x,y,t1c_xpos,t1c_ypos) <= engage_distance){
   blockers.push_back(t1c_name);                                    
  }
  if (get_dist(x,y,t1rf_xpos,t1rf_ypos) <= engage_distance){
   blockers.push_back(t1rf_name);                                    
  }
  if (get_dist(x,y,t1lf_xpos,t1lf_ypos) <= engage_distance){
   blockers.push_back(t1lf_name);                                    
  }
  if (get_dist(x,y,t1rd_xpos,t1rd_ypos) <= engage_distance){
   blockers.push_back(t1rd_name);                                    
  }
  if (get_dist(x,y,t1ld_xpos,t1ld_ypos) <= engage_distance){
   blockers.push_back(t1ld_name);                                    
  }
 }
 
 //Special exception: uncontested vectors
 if (blockers.size() <= 1) { return blockers; }
 
 //Sort vector by ATK
 while (blockers.size() > 0){
  //Find highest ATK among blockers
  while (i < blockers.size()){
   if (get_atk(blockers[i]) > topattack){ 
    topattack = get_atk(blockers[i]); 
    j = i; 
   }
   i ++;
  }
  
  //Add top blocker to sorted_blockers
  sorted_blockers.push_back(blockers[j]);
  blockers.erase(blockers.begin()+j);
  i = 0; j = 0; topattack = 0;
 }
 return sorted_blockers;
}

//==============================================================================
//===============================Random Stat====================================
//==============================================================================

int rstat(string player, string action){
    
 //Basic variables
 int stat = 0;
 int riskmod = 1;
  
 //Stat boundaries: 120% and 80%
 double s_high = 1.0;
 double s_low = 1.0;
 
 //Modify boundaries based on risk
 string risk = get_risk(player);
 if (risk == "HIGH"){ riskmod = 3; }
 if (risk == "NORMAL"){ riskmod = 2; }
 if (risk == "LOW"){ riskmod = 1; }
 
 //Modify high and low boundaries based on risk
 s_high += 0.1*riskmod;
 s_low -= 0.1*riskmod;
 
 //Grab stat of player
 string bonus = get_type_bonus(player);
 if (action == "shot"){ 
  stat = get_sht(player)+shtbonus; 
  if (bonus == "AW"){ s_high += 0.05*riskmod; s_low += 0.05*riskmod; }
  if (bonus == "C"){ s_high -= 0.05*riskmod; s_low -= 0.05*riskmod; }
 }
 if (action == "pass"){ 
  stat = get_pas(player); 
  if (bonus == "TP"){ s_high += 0.05*riskmod; s_low += 0.05*riskmod; }
  if (bonus == "BH"){ s_high -= 0.05*riskmod; s_low -= 0.05*riskmod; }
 }
 if (action == "passnogoal"){ 
  stat = get_pas(player); 
  if (get_goalie(player) == "NOPE!"){ stat = 0; }
  if (bonus == "TP"){ s_high += 0.05*riskmod; s_low += 0.05*riskmod; }
  if (bonus == "BH"){ s_high -= 0.05*riskmod; s_low -= 0.05*riskmod; }
 }
 if (action == "endurance"){ 
  stat = get_end(player); 
  if (bonus == "BH"){ s_high += 0.05*riskmod; s_low += 0.05*riskmod; }
  if (bonus == "AW"){ s_high -= 0.05*riskmod; s_low -= 0.05*riskmod; }
 }
 if (action == "attack"){ 
  stat = get_atk(player); 
  if (bonus == "PB"){ s_high += 0.05*riskmod; s_low += 0.05*riskmod; }
  if (bonus == "TP"){ s_high -= 0.05*riskmod; s_low -= 0.05*riskmod; }
 }
 if (action == "block"){ 
  stat = get_blk(player); 
  if (bonus == "BF"){ s_high += 0.05*riskmod; s_low += 0.05*riskmod; }
  if (bonus == "PB"){ s_high -= 0.05*riskmod; s_low -= 0.05*riskmod; }
 }
 if (action == "catch"){ 
  stat = get_ca(player); 
  if (bonus == "C"){ s_high += 0.05*riskmod; s_low += 0.05*riskmod; }
  if (bonus == "BF"){ s_high -= 0.05*riskmod; s_low -= 0.05*riskmod; }
 }

 //Establish stat boundaries as integers
 int stat_high = (int)(stat*s_high+0.5);
 int stat_low = (int)(stat*s_low+0.5);
 
// recap << player << ":" << endl
//       << "High Percent: " << s_high*100 << endl
//       << "Low Percent: " << s_low*100 << endl << endl;

 //Special cases
 if (stat_high < 2){ return 1; }
 if (stat_high == stat_low){ return stat_low; }

 //Mod by HIGH% of number and go until a number greather than LOW% is found
 int random = rand()%stat_high;
 while (random < stat_low){
  random = rand()%stat_high; 
 }

 return random;
}

//===========================================================================
//========================Assign Positions Function==========================
//===========================================================================

void assign_positions (){

 //Team 1 Starting Positions     
 t1c_xpos = -3000; t1c_ypos = 0;
 t1rf_xpos = -2000; t1rf_ypos = -6000;
 t1lf_xpos = -2000; t1lf_ypos = 6000;
 t1rd_xpos = -7000; t1rd_ypos = -3000;
 t1ld_xpos = -7000; t1ld_ypos = 3000;

 
 //Team 2 Starting Positions
 t2c_xpos = 3000; t2c_ypos = 0;
 t2rf_xpos = 2000; t2rf_ypos = 6000;
 t2lf_xpos = 2000; t2lf_ypos = -6000;
 t2rd_xpos = 7000; t2rd_ypos = 3000;
 t2ld_xpos = 7000; t2ld_ypos = -3000;
}

//===========================================================================
//===========================Give Stats Function=============================
//===========================================================================

void give_stats (string player){
 
 //Stat Variables
 int sht = 1;
 int pas = 1;
 int end = 1;
 int atk = 1;
 int blk = 1;
 int ca = 1;
 string risk = "NORMAL";
 string type = "NO";

 //Function Variables
 int pos = 0;
 string temp = "INVALID";
 string temp2 = "INVALID";

//Open the file
 playerdata.seekg(0);
 playerdata.clear();
 playerdata.open("playerdata.txt");  
 
 //Cycle through the names
 while (!playerdata.eof()){
  getline(playerdata, temp);
  pos = temp.find('=');
  temp2 = temp.substr(0,pos);
  if (temp2 == player){ break; }
 }
 
 //Not Found
 if (temp2 != player){ 
  cout << "WARNING: " << player << " not found! Make sure " << player 
       << " is spelled the same in teamdata and playerdata and resim match."
       << endl << "Press enter to exit." << endl;
  temp2 = getch(); 
  playerdata.close();
  exit(0);
  }
 
 //Tackle Slip
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 tackle_slip(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //Grip Gloves
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 grip_gloves(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //Elite Defense
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 elite_defense(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //Brawler
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 brawler(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //Golden Arm
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 golden_arm(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //Jecht Shot
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 jecht_shot(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //Volley Shot
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 volley_shot(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //All-Rounder
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 all_rounder(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //Super Goalie
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 super_goalie(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //Keepa
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 temp2 = temp.substr(0,pos);
 keepa(atoi(temp.substr(0,pos).c_str()),sht,pas,end,atk,blk,ca);
 
 //Risk
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 risk = temp.substr(0,pos);
 
 //Type
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find('|');
 type = temp.substr(0,pos);
 
 if (player == t1c_name){ t1c_sht = sht; t1c_pas = pas; t1c_end = end; t1c_type = type;
                          t1c_atk = atk; t1c_blk = blk; t1c_ca = ca; t1c_risk = risk; }
 if (player == t1rf_name){ t1rf_sht = sht; t1rf_pas = pas; t1rf_end = end; t1rf_type = type;
                           t1rf_atk = atk; t1rf_blk = blk; t1rf_ca = ca; t1rf_risk = risk; }
 if (player == t1lf_name){ t1lf_sht = sht; t1lf_pas = pas; t1lf_end = end; t1lf_type = type;
                           t1lf_atk = atk; t1lf_blk = blk; t1lf_ca = ca; t1lf_risk = risk; }
 if (player == t1rd_name){ t1rd_sht = sht; t1rd_pas = pas; t1rd_end = end; t1rd_type = type;
                           t1rd_atk = atk; t1rd_blk = blk; t1rd_ca = ca; t1rd_risk = risk; }
 if (player == t1ld_name){ t1ld_sht = sht; t1ld_pas = pas; t1ld_end = end; t1ld_type = type;
                           t1ld_atk = atk; t1ld_blk = blk; t1ld_ca = ca; t1ld_risk = risk; }
 if (player == t1g_name){ t1g_sht = sht; t1g_pas = pas; t1g_end = end; t1g_type = type;
                          t1g_atk = atk; t1g_blk = blk; t1g_ca = ca; t1g_risk = risk; }
 if (player == t2c_name){ t2c_sht = sht; t2c_pas = pas; t2c_end = end; t2c_type = type;
                          t2c_atk = atk; t2c_blk = blk; t2c_ca = ca; t2c_risk = risk; }
 if (player == t2rf_name){ t2rf_sht = sht; t2rf_pas = pas; t2rf_end = end; t2rf_type = type;
                           t2rf_atk = atk; t2rf_blk = blk; t2rf_ca = ca; t2rf_risk = risk; }
 if (player == t2lf_name){ t2lf_sht = sht; t2lf_pas = pas; t2lf_end = end; t2lf_type = type;
                           t2lf_atk = atk; t2lf_blk = blk; t2lf_ca = ca; t2lf_risk = risk; }
 if (player == t2rd_name){ t2rd_sht = sht; t2rd_pas = pas; t2rd_end = end; t2rd_type = type;
                           t2rd_atk = atk; t2rd_blk = blk; t2rd_ca = ca; t2rd_risk = risk; }
 if (player == t2ld_name){ t2ld_sht = sht; t2ld_pas = pas; t2ld_end = end; t2ld_type = type;
                           t2ld_atk = atk; t2ld_blk = blk; t2ld_ca = ca; t2ld_risk = risk; }
 if (player == t2g_name){ t2g_sht = sht; t2g_pas = pas; t2g_end = end; t2g_type = type;
                          t2g_atk = atk; t2g_blk = blk; t2g_ca = ca; t2g_risk = risk; }
 
// cout << player << ":" << endl
//      << "SHT: " << sht << "   PAS: " << pas << "   END: " << end << endl
//      << "ATK: " << atk << "   BLK: " << blk << "   CA: " << ca << endl << endl
//      << "RISK: " << risk << "TYPE: " << type << endl;
// temp = getch();
 
// pos = getch();
 system("cls");
 playerdata.close();
}
                  
//===========================================================================
//==========================Position Pick Function===========================
//===========================================================================

void position_pick (string player, string & center, string & forward1, string & forward2,
                    string & defender1, string & defender2, string & goalie){   
                       
 int num = 0; 
                       
 cout << player << " will be my" << endl << "4 = Left Forward" << endl
                                         << "5 = Center" << endl
                                         << "6 = Right Forward" << endl
                                         << "1 = Left Defender" << endl
                                         << "2 = Goalie" << endl
                                         << "3 = Right Defender" << endl
                                         << "0 = BENCH" << endl << endl;
 while (true){ 
  num = getch();
  if (num == 53 && center == "INVALID"){ center = player; break; }       
  else if (num == 54 && forward1 == "INVALID"){ forward1 = player; break; }       
  else if (num == 52 && forward2 == "INVALID"){ forward2 = player; break; }       
  else if (num == 49 && defender2 == "INVALID"){ defender2 = player; break; }       
  else if (num == 51 && defender1 == "INVALID"){ defender1 = player; break; }       
  else if (num == 50 && goalie == "INVALID"){ goalie = player; break; } 
  else if (num == 48 && bench < 2){ bench ++; break; }
 }

 return;
    
}

//===========================================================================
//============================Team Pick Function=============================
//===========================================================================

void team_pick (string & team_initials, string & team_name, string & formation, 
                string & center, string & forward1, string & forward2,
                string & defender1, string & defender2, string & goalie){     
     
int pos = 0; 
string temp = "INVALID";
string temp2 = "INVALID";
int i = 0;
int form_input = 0;
           
 cout << "Input Team Initials: ";
 cin >> team_initials;

 //Open the file
 teamdata.seekg(0);
 teamdata.clear();
 teamdata.open("teamdata.txt");   
 
 cout << "Formation: " << endl
      << "7. CrashL" << "     " << "8. Crescent" << "   " << "9. CrashR" << endl
      << "4. SweepL" << "     " << "5. Relay" << "     " << " 6. SweepR" << endl      
      << "1. Normal" << "     " << "2. Center" << "     " << "3. Wide" << endl
      << "              0. Jecht" << endl << endl;
      
 while (true){
  form_input = getch();
  if (form_input == 49){ formation = "NORMAL"; break; }
  if (form_input == 50){ formation = "CENTER"; break; }
  if (form_input == 51){ formation = "WIDE"; break; }
  if (form_input == 52){ formation = "SWEEPL"; break; }
  if (form_input == 53){ formation = "RELAY"; break; }
  if (form_input == 54){ formation = "SWEEPR"; break; }
  if (form_input == 55){ formation = "CRASHL"; break; }
  if (form_input == 56){ formation = "CRESCENT"; break; }
  if (form_input == 57){ formation = "CRASHR"; break; }
  if (form_input == 48){ formation = "JECHT"; break; }
 }
 
 
 //Cycle through the names
 while (!teamdata.eof()){
  getline(teamdata, temp);
  pos = temp.find('=');
  temp2 = temp.substr(0,pos);
  if (temp2 == team_initials){ break; }
 }

 //Close the file
  teamdata.close();
  
 //If bad team, try again
 if (temp2 == "#EOF#" or temp2 == "#EOF#|" or temp2 == "#EOF"){ 
  try_again = true; 
  system("cls");
  return; 
 }
 
 //Team Name
 pos ++;
 temp = temp.substr(pos,256);
 pos = temp.find(':');
 team_name = temp.substr(0,pos);
 
 //Individual Players
 while (true){
  system("cls");
  pos ++;
  if (center != "INVALID" && forward1 != "INVALID" && forward2 != "INVALID" && 
      defender1 != "INVALID" && defender2 != "INVALID" && goalie != "INVALID"){ break; }
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  position_pick (temp2, center, forward1, forward2, defender1, defender2, goalie);
  give_stats(temp2);
 }
 try_again = false;
}

//===========================================================================
//===========================================================================
//==============================Ball Functions===============================
//===========================================================================
//===========================================================================

void ball_refresh (string carrier){

 //Change Ball X-Position, Y-Position, and Team Possession
 ball_name = carrier;
 if (carrier == t1c_name) { ball_xpos = t1c_xpos; ball_ypos = t1c_ypos; team1ball = true; }
 else if (carrier == t1rf_name) { ball_xpos = t1rf_xpos; ball_ypos = t1rf_ypos; team1ball = true; }
 else if (carrier == t1lf_name) { ball_xpos = t1lf_xpos; ball_ypos = t1lf_ypos; team1ball = true; }
 else if (carrier == t1rd_name) { ball_xpos = t1rd_xpos; ball_ypos = t1rd_ypos; team1ball = true; }
 else if (carrier == t1ld_name) { ball_xpos = t1ld_xpos; ball_ypos = t1ld_ypos; team1ball = true; }
 else if (carrier == t1g_name) { ball_xpos = t1g_xpos; ball_ypos = t1g_ypos; team1ball = true; } 
 else if (carrier == t2c_name) { ball_xpos = t2c_xpos; ball_ypos = t2c_ypos; team1ball = false; }
 else if (carrier == t2rf_name) { ball_xpos = t2rf_xpos; ball_ypos = t2rf_ypos; team1ball = false; }
 else if (carrier == t2lf_name) { ball_xpos = t2lf_xpos; ball_ypos = t2lf_ypos; team1ball = false; }
 else if (carrier == t2rd_name) { ball_xpos = t2rd_xpos; ball_ypos = t2rd_ypos; team1ball = false; }
 else if (carrier == t2ld_name) { ball_xpos = t2ld_xpos; ball_ypos = t2ld_ypos; team1ball = false; }
 else if (carrier == t2g_name) { ball_xpos = t2g_xpos; ball_ypos = t2g_ypos; team1ball = false; } 
 else { recap << endl << "BALL_REFRESH IS A LIE!"; exit(0); }
}

double ball_distance (string player){
 int xpos = get_xpos(player); int ypos = get_ypos(player);
 double ball_distance = sqrt(pow(xpos - ball_xpos,2) + pow(ypos - ball_ypos,2));
 return ball_distance;
}

//===========================================================================
//===========================================================================
//============================Movement Functions=============================
//===========================================================================
//===========================================================================


//===========================================================================
//===========================Sphere Edge Function============================
//===========================================================================

//Sphere Edge Function: Keeps dudes in the pool (can't leave pool boundaries)
void sphere_edge (int & xpos, int & ypos){
 double dxpos = (double)xpos;
 double dypos = (double)ypos;
 double pythago = sqrt((xpos*xpos)+(ypos*ypos));
 double cangle = 0.0;
 if (pythago > radius){
  cangle = asin(dypos/pythago);
  dypos = radius*sin(cangle);
  dxpos = radius*cos(cangle);
  xpos = (int)dxpos;
  ypos = (int)dypos;
 }   
}

//===========================================================================
//=========================Random Movement Function==========================
//===========================================================================

//Completely random movement
void random_movement(string player){
 int xmove = rand()%engage_distance;
 int ymove = (int)sqrt(pow(engage_distance,2) - pow(xmove,2));
 if (rand()%2 == 1){ xmove = -1*xmove; }
 if (rand()%2 == 1){ ymove = -1*ymove; }
 xmove += get_xpos(player);
 ymove += get_ypos(player);
 sphere_edge(xmove, ymove);
 give_xpos(player, xmove);
 give_ypos(player, ymove);
}

//===========================================================================
//========================Optimal Movement Function==========================
//===========================================================================

//Optimal movement to a given target
void optimal_movement(string player, int target_xpos, int target_ypos){
 int xpos = get_xpos(player);
 int ypos = get_ypos(player);
 int move_distance = engage_distance;
 double cangle = 0;
 
 //Already there
 if (xpos == target_xpos && ypos == target_ypos){
  random_movement(player);        
 }
 
 //Carrier moves slower
 if (player == ball_name){ 
  move_distance = 9*engage_distance/10;          
 }
 
 //Triangle
 int height = target_ypos - ypos;
 int width = target_xpos - xpos;
 if (width == 0 && height >= 0){ cangle = 1.57; }
 else if (width == 0 && height < 0){ cangle = 4.71; }
 else { cangle = atan2(height,width); }
 
 //Close enough? Let 'em have it
 if (sqrt(height*height+width*width) <= move_distance){
  give_xpos(player,target_xpos); give_ypos(player,target_ypos);
  return;
 }
 
 //Take x-component of movement triangle and add to current x-position
 double dxpos = move_distance*cos(cangle);
 dxpos += xpos;
 int newxpos = (int)dxpos;
 
 //Take y-component of movement triangle and add to current y-position
 double dypos = move_distance*sin(cangle);
 dypos += ypos;
 int newypos = (int)dypos;
 
 //Apply new coordinates, restrict movement outside sphere
 sphere_edge (newxpos, newypos);
 give_xpos(player,newxpos);
 give_ypos(player,newypos);
}

//===========================================================================
//===========================Carry Ball Function=============================
//===========================================================================

//Person with the ball carries it straight to the goal
void carry_ball(string player){
 int target_xpos = 0;
 
 if (team1ball){ target_xpos = t2g_xpos; }
 else { target_xpos = t1g_xpos; }
 
 optimal_movement(player,target_xpos,0);
}

//===========================================================================
//===========================Ball Pursuit Function===========================
//===========================================================================

//Seek out the ball carrier if in range
void ball_pursuit(string player){    
      
 //So close, just move 'em
 if (ball_distance(player) <= engage_distance){
  give_xpos(player,ball_xpos); 
  give_ypos(player,ball_ypos); 
  return;
 }
 
 //If in view of ball carrier, move directly toward ball
 optimal_movement(player, ball_xpos, ball_ypos);
}

//===========================================================================
//=========================Tackle Movement Function==========================
//===========================================================================

//Optimal movement to a given target
void tackle_movement(string player, int target_xpos, int target_ypos){
 int xpos = get_xpos(player);
 int ypos = get_ypos(player);
 double cangle = 0;
 
 //Triangle
 int height = target_ypos - ypos;
 int width = target_xpos - xpos;
 if (width == 0 && height >= 0){ cangle = 1.57; }
 else if (width == 0 && height < 0){ cangle = 4.71; }
 else { cangle = atan2(height,width); }
 
 //Take x-component of movement triangle and add to current x-position
 double dxpos = 5*engage_distance*cos(cangle)/4;
 dxpos += target_xpos;
 int newxpos = (int)dxpos;
 
 //Take y-component of movement triangle and add to current y-position
 double dypos = 5*engage_distance*sin(cangle)/4;
 dypos += target_ypos;
 int newypos = (int)dypos;
 
 //Apply new coordinates, restrict movement outside sphere
 sphere_edge (newxpos, newypos);
 give_xpos(player,newxpos);
 give_ypos(player,newypos);
}

//===========================================================================
//=========================Assume Formation Function=========================
//===========================================================================

//Go to designated location based on specified formation
void assume_formation(string player){    
 string position = get_position(player);
 string formation = get_formation(player);

 //Normal Formation
 if (formation == "NORMAL"){
  if (position == "T1C"){ 
   if (team1ball) { optimal_movement(player, 5000, 0); }
   else { optimal_movement(player, -1000, 0); }
  }
  if (position == "T1LF"){ 
   if (team1ball) { optimal_movement(player, 7000, 5000); }
   else { optimal_movement(player, -2000, 6000); }
  }
  if (position == "T1RF"){ 
   if (team1ball) { optimal_movement(player, 7000, -5000); }
   else { optimal_movement(player, -2000, -6000); }
  }
  if (position == "T1LD"){ 
   if (team1ball) { optimal_movement(player, 0, 4000); }
   else { optimal_movement(player, -7000, 3000); }
  }
  if (position == "T1RD"){ 
   if (team1ball) { optimal_movement(player, 0, -4000); }
   else { optimal_movement(player, -7000, -3000); }
  }
  if (position == "T2C"){ 
   if (!team1ball) { optimal_movement(player, -5000, 0); }
   else { optimal_movement(player, 1000, 0); }
  }
  if (position == "T2LF"){ 
   if (!team1ball) { optimal_movement(player, -7000, -5000); }
   else { optimal_movement(player, 2000, -6000); }
  }
  if (position == "T2RF"){ 
   if (!team1ball) { optimal_movement(player, -7000, 5000); }
   else { optimal_movement(player, 2000, 6000); }
  }
  if (position == "T2LD"){ 
   if (!team1ball) { optimal_movement(player, 0, -4000); }
   else { optimal_movement(player, 7000, -3000); }
  }
  if (position == "T2RD"){ 
   if (!team1ball) { optimal_movement(player, 0, 4000); }
   else { optimal_movement(player, 7000, 3000); }
  }
 }

 //Center Formation
 else if (formation == "CENTER"){
  if (position == "T1C"){
   if (team1ball) { optimal_movement(player, 4000, 0); }
   else { optimal_movement(player, -3000, 0); }
  }
  if (position == "T1LF"){
   if (team1ball) { optimal_movement(player, 6000, 3000); }
   else { optimal_movement(player, -4000, 4000); }
  }
  if (position == "T1RF"){
   if (team1ball) { optimal_movement(player, 6000, -3000); }
   else { optimal_movement(player, -4000, -4000); }
  }
  if (position == "T1LD"){
   if (team1ball) { optimal_movement(player, -1000, 3000); }
   else { optimal_movement(player, -8000, 2000); }
  }
  if (position == "T1RD"){
   if (team1ball) { optimal_movement(player, -1000, -3000); }
   else { optimal_movement(player, -8000, -2000); }
  }
  if (position == "T2C"){ 
   if (!team1ball) { optimal_movement(player, -4000, 0); }
   else { optimal_movement(player, 3000, 0); }
  }
  if (position == "T2LF"){ 
   if (!team1ball) { optimal_movement(player, -6000, -3000); }
   else { optimal_movement(player, 4000, -4000); }
  }
  if (position == "T2RF"){ 
   if (!team1ball) { optimal_movement(player, -6000, 3000); }
   else { optimal_movement(player, 4000, 4000); }
  }
  if (position == "T2LD"){ 
   if (!team1ball) { optimal_movement(player, 1000, -3000); }
   else { optimal_movement(player, 8000, -2000); }
  }
  if (position == "T2RD"){ 
   if (!team1ball) { optimal_movement(player, 1000, 3000); }
   else { optimal_movement(player, 8000, 2000); }
  }
 }
 
 //Wide Formation
 else if (formation == "WIDE"){
  if (position == "T1C"){ 
   if (team1ball) { optimal_movement(player, 3000, 0); }
   else { optimal_movement(player, -5000, 0); }
  }
  if (position == "T1LF"){ 
   if (team1ball) { optimal_movement(player, 7000, 2000); }
   else { optimal_movement(player, -1000, 9000); }
  }
  if (position == "T1RF"){ 
   if (team1ball) { optimal_movement(player, 7000, -2000); }
   else { optimal_movement(player, -1000, -9000); }
  }
  if (position == "T1LD"){ 
   if (team1ball) { optimal_movement(player, -1000, 5000); }
   else { optimal_movement(player, -6000, 4000); }
  }
  if (position == "T1RD"){ 
   if (team1ball) { optimal_movement(player, -1000, -5000); }
   else { optimal_movement(player, -6000, -4000); }
  }
  if (position == "T2C"){ 
   if (!team1ball) { optimal_movement(player, -3000, 0); }
   else { optimal_movement(player, 5000, 0); }
  }
  if (position == "T2LF"){ 
   if (!team1ball) { optimal_movement(player, -7000, -2000); }
   else { optimal_movement(player, 1000, -9000); }
  }
  if (position == "T2RF"){ 
   if (!team1ball) { optimal_movement(player, -7000, 2000); }
   else { optimal_movement(player, 1000, 9000); }
  }
  if (position == "T2LD"){ 
   if (!team1ball) { optimal_movement(player, 1000, -5000); }
   else { optimal_movement(player, 6000, -4000); }
  }
  if (position == "T2RD"){ 
   if (!team1ball) { optimal_movement(player, 1000, 5000); }
   else { optimal_movement(player, 6000, 4000); }
  }
 }
 
 //SWEEPR Formation
 else if (formation == "SWEEPR"){
  if (position == "T1C"){ 
   if (team1ball) { optimal_movement(player, 5000, 3000); }
   else { optimal_movement(player, -2000, 6000); }
  }
  if (position == "T1LF"){ 
   if (team1ball) { optimal_movement(player, 6000, 0000); }
   else { optimal_movement(player, -1000, 0000); }
  }
  if (position == "T1RF"){ 
   if (team1ball) { optimal_movement(player, 7000, -2000); }
   else { optimal_movement(player, -1000, -4000); }
  }
  if (position == "T1LD"){ 
   if (team1ball) { optimal_movement(player, -1000, 2000); }
   else { optimal_movement(player, -7000, 4000); }
  }
  if (position == "T1RD"){ 
   if (team1ball) { optimal_movement(player, 1000, -6000); }
   else { optimal_movement(player, -7000, -3000); }
  }
 if (position == "T2C"){ 
   if (team1ball) { optimal_movement(player, -5000, -3000); }
   else { optimal_movement(player, 2000, -6000); }
  }
  if (position == "T2LF"){ 
   if (team1ball) { optimal_movement(player, -6000, 0000); }
   else { optimal_movement(player, 1000, 0000); }
  }
  if (position == "T2RF"){ 
   if (team1ball) { optimal_movement(player, -7000, 2000); }
   else { optimal_movement(player, 1000, 4000); }
  }
  if (position == "T2LD"){ 
   if (team1ball) { optimal_movement(player, 1000, -2000); }
   else { optimal_movement(player, 7000, -4000); }
  }
  if (position == "T2RD"){ 
   if (team1ball) { optimal_movement(player, -1000, 6000); }
   else { optimal_movement(player, 7000, 3000); }
  }
 }
 
 //SWEEPL Formation
 else if (formation == "SWEEPL"){
  if (position == "T1C"){ 
   if (team1ball) { optimal_movement(player, 5000, -3000); }
   else { optimal_movement(player, -2000, -6000); }
  }
  if (position == "T1LF"){ 
   if (team1ball) { optimal_movement(player, 7000, 2000); }
   else { optimal_movement(player, -1000, 4000); }
  }
  if (position == "T1RF"){ 
   if (team1ball) { optimal_movement(player, 6000, 0000); }
   else { optimal_movement(player, -1000, 0000); }
  }
  if (position == "T1LD"){ 
   if (team1ball) { optimal_movement(player, 1000, 6000); }
   else { optimal_movement(player, -7000, 3000); }
  }
  if (position == "T1RD"){ 
   if (team1ball) { optimal_movement(player, -1000, -2000); }
   else { optimal_movement(player, -7000, -4000); }
  }
 if (position == "T2C"){ 
   if (team1ball) { optimal_movement(player, -5000, 3000); }
   else { optimal_movement(player, 2000, 6000); }
  }
  if (position == "T2LF"){ 
   if (team1ball) { optimal_movement(player, -7000, -2000); }
   else { optimal_movement(player, 1000, -4000); }
  }
  if (position == "T2RF"){ 
   if (team1ball) { optimal_movement(player, -6000, 0000); }
   else { optimal_movement(player, 1000, 0000); }
  }
  if (position == "T2LD"){ 
   if (team1ball) { optimal_movement(player, -1000, -6000); }
   else { optimal_movement(player, 7000, -3000); }
  }
  if (position == "T2RD"){ 
   if (team1ball) { optimal_movement(player, 1000, 2000); }
   else { optimal_movement(player, 7000, 4000); }
  }
 }

 //Jecht Formation
 else if (formation == "JECHT"){
  if (position == "T1C"){ 
   if (team1ball) { optimal_movement(player, 4000, -4000); }
   else { optimal_movement(player, -3000, -5000); }
  }
  if (position == "T1LF"){ 
   if (team1ball) { optimal_movement(player, 4000, 4000); }
   else { optimal_movement(player, -3000, 5000); }
  }
  if (position == "T1RF"){ 
   if (team1ball) { optimal_movement(player, 8200, 0); }
   else { optimal_movement(player, 0, 0); }
  }
  if (position == "T1LD"){ 
   if (team1ball) { optimal_movement(player, -1000, 3500); }
   else { optimal_movement(player, -6000, 4000); }
  }
  if (position == "T1RD"){ 
   if (team1ball) { optimal_movement(player, -1000, -3500); }
   else { optimal_movement(player, -6000, -4000); }
  }
  if (position == "T2C"){ 
   if (!team1ball) { optimal_movement(player, -4000, 4000); }
   else { optimal_movement(player, 3000, 5000); }
  }
  if (position == "T2LF"){ 
   if (!team1ball) { optimal_movement(player, -4000, -4000); }
   else { optimal_movement(player, 3000, -5000); }
  }
  if (position == "T2RF"){ 
   if (!team1ball) { optimal_movement(player, -8200, 0); }
   else { optimal_movement(player, 0, 0); }
  }
  if (position == "T2LD"){ 
   if (!team1ball) { optimal_movement(player, 1000, -3500); }
   else { optimal_movement(player, 6000, -4000); }
  }
  if (position == "T2RD"){ 
   if (!team1ball) { optimal_movement(player, 1000, 3500); }
   else { optimal_movement(player, 6000, 4000); }
  }
 }

 //Crescent Formation
 else if (formation == "CRESCENT"){
  if (position == "T1C"){ 
   if (team1ball) { optimal_movement(player, 4000, 0); }
   else { optimal_movement(player, -8000, 0); }
  }
  if (position == "T1LF"){ 
   if (team1ball) { optimal_movement(player, 7000, 6000); }
   else { optimal_movement(player, -1000, 6000); }
  }
  if (position == "T1RF"){ 
   if (team1ball) { optimal_movement(player, 7000, -6000); }
   else { optimal_movement(player, -1000, -6000); }
  }
  if (position == "T1LD"){ 
   if (team1ball) { optimal_movement(player, -1000, 4000); }
   else { optimal_movement(player, -6000, 4000); }
  }
  if (position == "T1RD"){ 
   if (team1ball) { optimal_movement(player, -1000, -4000); }
   else { optimal_movement(player, -6000, -4000); }
  }
  if (position == "T2C"){ 
   if (!team1ball) { optimal_movement(player, -4000, 0); }
   else { optimal_movement(player, 8000, 0); }
  }
  if (position == "T2LF"){ 
   if (!team1ball) { optimal_movement(player, -7000, -6000); }
   else { optimal_movement(player, 1000, -6000); }
  }
  if (position == "T2RF"){ 
   if (!team1ball) { optimal_movement(player, -7000, 6000); }
   else { optimal_movement(player, 1000, 6000); }
  }
  if (position == "T2LD"){ 
   if (!team1ball) { optimal_movement(player, 1000, -4000); }
   else { optimal_movement(player, 6000, -4000); }
  }
  if (position == "T2RD"){ 
   if (!team1ball) { optimal_movement(player, 1000, 4000); }
   else { optimal_movement(player, 6000, 4000); }
  }
 }

 //Relay Formation
 else if (formation == "RELAY"){
  if (position == "T1C"){ 
   if (team1ball) { optimal_movement(player, -1000, 0); }
   else { optimal_movement(player, -4000, 0); }
  }
  if (position == "T1LF"){ 
   if (team1ball) { optimal_movement(player, 7000, 3000); }
   else { optimal_movement(player, -1000, 7000); }
  }
  if (position == "T1RF"){ 
   if (team1ball) { optimal_movement(player, 7000, -3000); }
   else { optimal_movement(player, -1000, -7000); }
  }
  if (position == "T1LD"){ 
   if (team1ball) { optimal_movement(player, -3000, 5000); }
   else { optimal_movement(player, -7000, 2000); }
  }
  if (position == "T1RD"){ 
   if (team1ball) { optimal_movement(player, -3000, -5000); }
   else { optimal_movement(player, -7000, -2000); }
  }
  if (position == "T2C"){ 
   if (!team1ball) { optimal_movement(player, 1000, 0); }
   else { optimal_movement(player, 4000, 0); }
  }
  if (position == "T2LF"){ 
   if (!team1ball) { optimal_movement(player, -7000, -3000); }
   else { optimal_movement(player, 1000, -7000); }
  }
  if (position == "T2RF"){ 
   if (!team1ball) { optimal_movement(player, -7000, 3000); }
   else { optimal_movement(player, 1000, 7000); }
  }
  if (position == "T2LD"){ 
   if (!team1ball) { optimal_movement(player, 3000, -5000); }
   else { optimal_movement(player, 7000, -2000); }
  }
  if (position == "T2RD"){ 
   if (!team1ball) { optimal_movement(player, 3000, 5000); }
   else { optimal_movement(player, 7000, 2000); }
  }
 }
 
 //CrashR Formation
 else if (formation == "CRASHR"){
  if (position == "T1C"){ 
   if (team1ball) { optimal_movement(player, 3000, -5000); }
   else { optimal_movement(player, -2000, -2000); }
  }
  if (position == "T1LF"){ 
   if (team1ball) { optimal_movement(player, 6000, 0); }
   else { optimal_movement(player, -2000, 5000); }
  }
  if (position == "T1RF"){ 
   if (team1ball) { optimal_movement(player, 8000, -3000); }
   else { optimal_movement(player, -1000, -8000); }
  }
  if (position == "T1LD"){ 
   if (team1ball) { optimal_movement(player, -4000, 2000); }
   else { optimal_movement(player, -6000, 1000); }
  }
  if (position == "T1RD"){ 
   if (team1ball) { optimal_movement(player, -3000, -6000); }
   else { optimal_movement(player, -6000, -4000); }
  }
  if (position == "T2C"){ 
   if (!team1ball) { optimal_movement(player, -3000, 5000); }
   else { optimal_movement(player, 2000, 2000); }
  }
  if (position == "T2LF"){ 
   if (!team1ball) { optimal_movement(player, -6000, 0); }
   else { optimal_movement(player, 2000, -5000); }
  }
  if (position == "T2RF"){ 
   if (!team1ball) { optimal_movement(player, -8000, 3000); }
   else { optimal_movement(player, 1000, 8000); }
  }
  if (position == "T2LD"){ 
   if (!team1ball) { optimal_movement(player, 4000, -2000); }
   else { optimal_movement(player, 6000, -1000); }
  }
  if (position == "T2RD"){ 
   if (!team1ball) { optimal_movement(player, 3000, 6000); }
   else { optimal_movement(player, 6000, 4000); }
  }
 }
 
 //CrashL Formation
 else if (formation == "CRASHL"){
  if (position == "T1C"){ 
   if (team1ball) { optimal_movement(player, 3000, 5000); }
   else { optimal_movement(player, -2000, 2000); }
  }
  if (position == "T1LF"){ 
   if (team1ball) { optimal_movement(player, 8000, 3000); }
   else { optimal_movement(player, -1000, 8000); }
  }
  if (position == "T1RF"){ 
   if (team1ball) { optimal_movement(player, 6000, 0); }
   else { optimal_movement(player, -2000, -5000); }
  }
  if (position == "T1LD"){ 
   if (team1ball) { optimal_movement(player, -3000, 6000); }
   else { optimal_movement(player, -6000, 4000); }
  }
  if (position == "T1RD"){ 
   if (team1ball) { optimal_movement(player, -4000, -2000); }
   else { optimal_movement(player, -6000, -1000); }
  }
  if (position == "T2C"){ 
   if (!team1ball) { optimal_movement(player, -3000, -5000); }
   else { optimal_movement(player, 2000, -2000); }
  }
  if (position == "T2LF"){ 
   if (!team1ball) { optimal_movement(player, -8000, -3000); }
   else { optimal_movement(player, 1000, -8000); }
  }
  if (position == "T2RF"){ 
   if (!team1ball) { optimal_movement(player, -6000, 0); }
   else { optimal_movement(player, 2000, 5000); }
  }
  if (position == "T2LD"){ 
   if (!team1ball) { optimal_movement(player, 3000, -6000); }
   else { optimal_movement(player, 6000, -4000); }
  }
  if (position == "T2RD"){ 
   if (!team1ball) { optimal_movement(player, 4000, 2000); }
   else { optimal_movement(player, 6000, 1000); }
  }
 }
 
 //Else I'm Confused...
 else { recap << "Assume_Formation IS A LIE!" << endl; exit(0); }
}
//===========================================================================
//=========================Team 1 Defense Function===========================
//===========================================================================

//Defensive Movements
void t1_defense (){
     
 //Center
 if (ball_distance(t1c_name) <= ballspot_distance){ ball_pursuit(t1c_name); }
 else { assume_formation(t1c_name); }
 
  //Left Forward
 if (ball_distance(t1lf_name) <= ballspot_distance){ ball_pursuit(t1lf_name); }
 else { assume_formation(t1lf_name); }
 
  //Right Forward
 if (ball_distance(t1rf_name) <= ballspot_distance){ ball_pursuit(t1rf_name); }
 else { assume_formation(t1rf_name); }
 
  //Left Defense
 if (ball_distance(t1ld_name) <= ballspot_distance){ ball_pursuit(t1ld_name); }
 else { assume_formation(t1ld_name); }
 
  //Right Defense
 if (ball_distance(t1rd_name) <= ballspot_distance){ ball_pursuit(t1rd_name); }
 else { assume_formation(t1rd_name); }
 
}

//===========================================================================
//=========================Team 2 Defense Function===========================
//===========================================================================

//Defensive Movements
void t2_defense (){
     
 //Center
 if (ball_distance(t2c_name) <= ballspot_distance){ ball_pursuit(t2c_name); }
 else { assume_formation(t2c_name); }
 
  //Left Forward
 if (ball_distance(t2lf_name) <= ballspot_distance){ ball_pursuit(t2lf_name); }
 else { assume_formation(t2lf_name); }
 
  //Right Forward
 if (ball_distance(t2rf_name) <= ballspot_distance){ ball_pursuit(t2rf_name); }
 else { assume_formation(t2rf_name); }
 
  //Left Defense
 if (ball_distance(t2ld_name) <= ballspot_distance){ ball_pursuit(t2ld_name); }
 else { assume_formation(t2ld_name); }
 
  //Right Defense
 if (ball_distance(t2rd_name) <= ballspot_distance){ ball_pursuit(t2rd_name); }
 else { assume_formation(t2rd_name); }
 
}

//===========================================================================
//=========================Team 1 Offense Function===========================
//===========================================================================

//Offensive Movements
void t1_offense (){
     
 if (t1c_name != ball_name) { assume_formation(t1c_name); }
 if (t1lf_name != ball_name) { assume_formation(t1lf_name); }
 if (t1rf_name != ball_name) { assume_formation(t1rf_name); }
 if (t1ld_name != ball_name) { assume_formation(t1ld_name); }
 if (t1rd_name != ball_name) { assume_formation(t1rd_name); }
 
}

//===========================================================================
//=========================Team 2 Defense Function===========================
//===========================================================================

//Offensive Movements
void t2_offense (){
     
 if (t2c_name != ball_name) { assume_formation(t2c_name); }
 if (t2lf_name != ball_name) { assume_formation(t2lf_name); }
 if (t2rf_name != ball_name) { assume_formation(t2rf_name); }
 if (t2ld_name != ball_name) { assume_formation(t2ld_name); }
 if (t2rd_name != ball_name) { assume_formation(t2rd_name); }
 
}

//===========================================================================
//===========================================================================
//======================Shoot, Pass, Engage Functions========================
//===========================================================================
//===========================================================================

//===========================================================================
//========================Player Upfield Function============================
//===========================================================================

//Checks if a teammate is in pass range and closer to the goal
bool player_upfield (string player){
 int i = 0; int j = 0; int goalie_xpos = 0; 
 double pdist = 2.0*radius; int pass = 0;
 vector <string> buddies;
 vector <string> upfield;
 if (team1ball){ 
  if (player != t1c_name){ buddies.push_back(t1c_name); }
  if (player != t1rf_name){ buddies.push_back(t1rf_name); }
  if (player != t1lf_name){ buddies.push_back(t1lf_name); }
  if (player != t1rd_name){ buddies.push_back(t1rd_name); }
  if (player != t1ld_name){ buddies.push_back(t1ld_name); }
  goalie_xpos = radius;
  pdist = get_dist(get_xpos(player),get_ypos(player),goalie_xpos,0);
 }
 else { 
  if (player != t2c_name){ buddies.push_back(t2c_name); }
  if (player != t2rf_name){ buddies.push_back(t2rf_name); }
  if (player != t2lf_name){ buddies.push_back(t2lf_name); }
  if (player != t2rd_name){ buddies.push_back(t2rd_name); }
  if (player != t2ld_name){ buddies.push_back(t2ld_name); }
  goalie_xpos = -1*radius;
  pdist = get_dist(get_xpos(player),get_ypos(player),goalie_xpos,0);
 }

 //Are any players closer to the goal?
 while (i < buddies.size()){
  if (get_dist(get_xpos(buddies[i]),get_ypos(buddies[i]),goalie_xpos,0) < pdist){
   upfield.push_back(buddies[i]);
  }
  i++;
 }
 
 //Can I throw the ball to any of those guys upfield?
 i = 0;
 while (i < upfield.size()){
  pass = rstat(player,"pass");
  if (get_bonus_pas(player) > 0){ pass += rstat(get_goalie(player),"passnogoal"); }
  pdist = get_dist(get_xpos(player),get_ypos(player),
                   get_xpos(upfield[i]),get_ypos(upfield[i]));
  j = (int) pdist/engage_distance;
  while (j > 0){ pass = (int) 0.9*pass; j--; }
  if (pass >= 0){ return true; }
  i ++;
 }

 return false;
}

//===========================================================================
//=========================Pass Target Function==============================
//===========================================================================

//Checks if a teammate is in pass range and closer to the goal
string pass_target (string player){
 int i = 0; int j = 0; int goalie_xpos = 0; 
 double pdist = 2.0*radius; int pass = 0;
 vector <string> buddies;
 vector <string> upfield;
 vector <string> targets;
 if (team1ball){ 
  if (player != t1c_name){ buddies.push_back(t1c_name); }
  if (player != t1rf_name){ buddies.push_back(t1rf_name); }
  if (player != t1lf_name){ buddies.push_back(t1lf_name); }
  if (player != t1rd_name){ buddies.push_back(t1rd_name); }
  if (player != t1ld_name){ buddies.push_back(t1ld_name); }
  goalie_xpos = radius;
  pdist = get_dist(get_xpos(player),get_ypos(player),goalie_xpos,0);
 }
 else { 
  if (player != t2c_name){ buddies.push_back(t2c_name); }
  if (player != t2rf_name){ buddies.push_back(t2rf_name); }
  if (player != t2lf_name){ buddies.push_back(t2lf_name); }
  if (player != t2rd_name){ buddies.push_back(t2rd_name); }
  if (player != t2ld_name){ buddies.push_back(t2ld_name); }
  goalie_xpos = -1*radius;
  pdist = get_dist(get_xpos(player),get_ypos(player),goalie_xpos,0);
 }

 //Are any players closer to the goal?
 while (i < buddies.size()){
  if (get_dist(get_xpos(buddies[i]),get_ypos(buddies[i]),goalie_xpos,0) < pdist){
   upfield.push_back(buddies[i]);
  }
  i++;
 }
 
 //Can I throw the ball to any of those guys upfield?
 i = 0;
 while (i < upfield.size()){
  pass = rstat(player,"pass");
  if (get_bonus_pas(player) > 0){ pass += rstat(get_goalie(player),"passnogoal"); }
  pdist = get_dist(get_xpos(player),get_ypos(player),
                   get_xpos(upfield[i]),get_ypos(upfield[i]));
  j = (int) pdist/engage_distance;
  while (j > 0){ /*pass = (int) 0.9*pass;*/ pass --; j--; }
  if (pass >= 0){ targets.push_back(upfield[i]); }
  i++;
 }
 
 //Choose random fielder
 int random = 0;
 if (targets.size() > 1){
  random = rand()%targets.size();
  return targets[random];
 }
 //If only one target...
 else if (targets.size() == 1){
  return targets[0];     
 }
 else {
  random = rand()%buddies.size();
  return buddies[random];    
 }
}

//===========================================================================
//=============================Pass Function=================================
//===========================================================================

void pass (string player, vector <string> blockers){

 int pass = rstat(player,"pass");
  if (get_bonus_pas(player) > 0){ pass += rstat(get_goalie(player),"passnogoal"); }
 string target = pass_target(player);
 
 //Penetrate the blockers?
 int i = 0;
 while (i < blockers.size()){
  pass -= rstat(blockers[i],"block");
  if (get_bonus_blk(player) > 0){ pass -= rstat(get_goalie(blockers[i]),"block"); }
  if (pass <= 0){
   //Blocker gets it
   ball_refresh(blockers[i]);
   recap << blockers[i];
   if (get_bonus_blk(blockers[i]) > 0){ recap << "*"; }
   recap << " grabs the ball!" << endl << endl;
   shtbonus = 0;
   return;
  }
  else {
   //Hit but keeps ball
   recap << blockers[i];
   if (get_bonus_blk(blockers[i]) > 0){ recap << "*"; }
   recap << " gets a hand on it!" << endl;     
   shtbonus ++;
  }
  i++;
 }
 
 //Calculate distance ball must travel to reach the target
 double dist_to_target = get_dist(get_xpos(player),get_ypos(player),
                                  get_xpos(target),get_ypos(player));
 i = (int)dist_to_target/engage_distance;
 
 //Ball traveling through the water, 90% lost for each movement
 while (i > 0){
  //pass = (int)0.9*pass;
  pass --;
  i --; timeleft --;
 } 
 
 //Pass Complete
 if (pass > 0){
  recap << target << " catches the pass!" << endl << endl;
  ball_refresh(target);
  shtbonus += 3;
 }
 //Pass Incomplete
 else {
  recap << target << " fumbles the pass!" << endl;
  ball_name = loose_ball(target);
  ball_refresh(ball_name);
  shtbonus = 0;
 }     
}

//===========================================================================
//===========================Test Shot Function==============================
//===========================================================================

//Checks if the shooter has a feasible chance at making a goal
bool test_shot (string player, vector <string> blockers){
     
 if (team1ball && get_xpos(player) < 0){ return false; }
 if (!team1ball && get_xpos(player) > 0){ return false; }
     
 //Find enemy goalie
 string goalie = bad_goalie(player);
 ball_refresh(player);
 
 int shot = rstat(player,"shot");
 if (get_bonus_sht(player) > 0){ shot += rstat(get_goalie(player),"shot"); }
 int i = 0; int dist = 0;
 double dtg = get_dist(get_xpos(player),get_ypos(player),
                    get_xpos(goalie),get_ypos(goalie));
 dist = (int)dtg/engage_distance;
 
 //Through defenders
 while (i < blockers.size()){
  shot -= rstat(blockers[i],"block");
  if (get_bonus_blk(player) > 0){ shot -= rstat(get_goalie(blockers[i]),"block"); }    
  i++;      
 }
 
 //Through water
 while (dist > 0) {
  shot = 9*shot/10;
  dist --;      
 }
 
 //Through goalie
 shot -= rstat(goalie,"catch");
 
 //If it makes it through all that...
 //recap << "Test Shot: " << shot << endl;
 if (shot > 0){ return true; }
 else { return false; }
}

//===========================================================================
//=============================Shoot Function================================
//===========================================================================

void shoot (string player, vector <string> blockers) {

 int shot = rstat(player,"shot");
 if (get_bonus_sht(player) > 0){ shot += rstat(get_goalie(player),"shot"); }
 int ca = 0;
 string goalie = bad_goalie(player);
 
 //Penetrate the blockers?
 int i = 0;
 while (i < blockers.size()){
  shot -= rstat(blockers[i],"block");
  if (get_bonus_blk(player) > 0){ shot -= rstat(get_goalie(blockers[i]),"block"); }
  if (shot <= 0){
   //Blocker gets it
   ball_refresh(blockers[i]);
   recap << blockers[i];
   if (get_bonus_blk(blockers[i]) > 0){ recap << "*"; }
   recap << " grabs the ball!" << endl << endl;
   shtbonus = 0;
   return;
  }
  else {
   //Hit but keeps ball
   recap << blockers[i];
   if (get_bonus_blk(blockers[i]) > 0){ recap << "*"; }
   recap << " gets a hand on it!" << endl;     
   shtbonus ++;
  }
  i++;
 }
 
 //Calculate distance ball must travel to reach the goalie
 double dist_to_goal = 0;
 dist_to_goal = sqrt(pow(get_xpos(player)-get_xpos(goalie),2)+pow(get_ypos(player),2));
 i = (int)dist_to_goal/engage_distance;
 
 //Ball traveling through the water, 90% lost for each movement
 recap << "Shot Power: " << shot;
 while (i > 0){
  shot = 9*shot/10;
  recap << "..." << shot;
  i --; timeleft --;
 }
 
 recap << endl;
 int goalieca = rstat(goalie,"catch");
 recap << goalie << "'s CA: " << goalieca << endl;
 shot -= goalieca;
 
 //Shot goes in!
 if (shot > 0){
  if (team1ball){ t1score ++; ball_name = t2c_name; }
  else { t2score ++; ball_name = t1c_name; }
  assign_positions();
  ball_refresh(ball_name);
  int minutes = (300-timeleft)/60;
  int seconds = timeleft%60;
  recap << goalie << " can't catch it! Goal!" << endl << endl
        << "Score:" << endl
        << t1name << ": " << t1score << endl
        << t2name << ": " << t2score << endl 
        << "Time: " << minutes << ":";
  if (seconds < 10){ recap << "0"; }
  if (seconds < 0){ seconds = 0; }
  recap << seconds << endl << endl;
  
  //No release at final shot
  if (timeleft <= 0) { return; }
  
  recap << "The ball is released!" << endl
        << ball_name << " catches the ball." << endl << endl;  
  shtbonus = 0;  
 }
 //Loose ball!
 else if (shot <= 0 && shot >= -2){
  recap << goalie << " gets a hand on it!" << endl;
  string newballer = loose_ball(goalie);
  ball_refresh(newballer);
  shtbonus = 0;
 }
 //Goalie snags it
 else {
  if (team1ball){ team1ball = false; }
  else { team1ball = true; }
  recap << goalie << " catches the ball." << endl
        << goalie << " throws a pass." << endl;
  vector <string> emptyvec;
  pass(goalie,emptyvec);
  shtbonus = 0;
 } 
}

//===========================================================================
//=============================Battle Function===============================
//===========================================================================

bool battle (string player, vector <string> blockers){
 int i = 0; 
 int dodge = 20; int random = rand()%dodge; bool disoriented = false;
 
 //No Defenders
 if (blockers.size() == 0){ return true; }

 //Give actual endurance (random) + goalie bonus (maybe)
 int endurance = rstat(player,"endurance");
 if (get_bonus_end(player) > 0){ endurance += rstat(get_goalie(player),"endurance"); }
 while (i < blockers.size()){
  tackle_movement(blockers[i],get_xpos(player),get_ypos(player));
  if (random == 0 && !disoriented){ 
   recap << player << " dodges " << blockers[i] << "'s attack." << endl; 
  }
  else if (random == 1 && !disoriented){ 
   recap << player << " dodges " << blockers[i] 
         << "'s attack, but is disoriented." << endl; 
   disoriented = true;
  }
  else {
   endurance -= rstat(blockers[i],"attack");
   if (get_bonus_atk(player) > 0){ endurance -= rstat(get_goalie(blockers[i]),"attack"); }
   if (disoriented) { endurance = 0; }
   if (endurance <= 0){
    recap << blockers[i] << " hits hard and grabs the ball from " 
          << player << "!" << endl << endl;
    ball_refresh(blockers[i]);
    shtbonus = 0;
    return false;
   }
   else {
    recap << blockers[i] << " tackles hard!" << endl;     
    shtbonus ++;
   }
  }
  i++; random = rand()%dodge; timeleft --;
 }
 return true;
} 

//===========================================================================
//=============================Engage Function===============================
//===========================================================================

void engage (string player){
 vector <string> blockers; blockers = fill_blockers(player);
 vector <string> blockers1; vector <string> blockers2;
 int i = 0; 
 int endurance = rstat(player,"endurance");
 if (get_bonus_end(player) > 0){ endurance += rstat(get_goalie(player),"endurance"); }
 
 //How many on defense + Bonus output
 if (blockers.size() > 0){
  recap << blockers.size() << " on defense.";
  if (get_bonus_end(player) > 0){ recap << "*"; }
  recap << endl;
 }
 
 //Estimate how many able to break
 while (i < blockers.size()){
  endurance -= get_atk(blockers[i]);
  if (endurance > 0) { blockers1.push_back(blockers[i]); }
  else { blockers2.push_back(blockers[i]); }
  i++;
 }
  
  //Physical Vector: END vs ATK
  if(!battle(player, blockers1)){ 
   recap << endl;
   return; 
  }
  
  //Buzzer Beater
  if (timeleft <= 1){
   recap << player;
   if (get_bonus_sht(player) > 0){ recap << "*"; }
   recap << " shoots at the buzzer!" << endl;
   shoot(player,blockers2); 
   return;
  }
 
 //Ball Vector: SHT/PAS vs BLK
 if (blockers2.size() > 0){
  //Shoot
  if (test_shot(player,blockers2)){ 
   recap << player;
   if (get_bonus_sht(player) > 0){ recap << "*"; }
   recap << " shoots!" << endl;
   shoot(player,blockers2); 
  }
  //Pass
  else {
   recap << player;
   if (get_bonus_pas(player) > 0){ recap << "*"; }
   recap << " throws a pass!" << endl;
   pass(player,blockers2); 
  }
  return;
 }
 
 //No Defenders Left: Pass, Shoot, or Dribble
 else {
  //Shoot
  if (test_shot(player,blockers2)){ 
   recap << player;
   if (get_bonus_sht(player) > 0){ recap << "*"; }
   recap << " shoots!" << endl;
   shoot(player,blockers2); 
  }
  //Pass
  else if (player_upfield(player)) {
   recap << player;
   if (get_bonus_pas(player) > 0){ recap << "*"; }
   recap << " throws a pass!" << endl;
   pass(player,blockers2); 
  }
  else {
   if (blockers2.size() == 0){ recap << endl; }
   return;    
  }
 }
}

//===========================================================================
//==============================Main Function================================
//===========================================================================

int main(){

 srand(time(0));
 int i = 0;
    
 //Declare Team 1   
 while (try_again){
  cout << "Team 1 " << endl;
  team_pick(t1, t1name, t1formation, t1c_name, t1rf_name, t1lf_name, t1rd_name, t1ld_name, t1g_name);
 }
       
 //Declare Team 2
 try_again = true; bench = 0;
 while (try_again){
  cout << "Team 2 " << endl;
  team_pick(t2, t2name, t2formation, t2c_name, t2rf_name, t2lf_name, t2rd_name, t2ld_name, t2g_name);
 }

 //Personal name for the file
 string filename = "";
 filename = t1 + " vs " + t2 + ".html";
 recap.open(filename.c_str()); 
 
//Give colors
t1c_name = "<font color=\"#FF0000\">" + t1c_name + "</font>"; 
t2c_name = "<font color=\"#0000FF\">" + t2c_name + "</font>";
t1lf_name = "<font color=\"#FF0000\">" + t1lf_name + "</font>"; 
t2lf_name = "<font color=\"#0000FF\">" + t2lf_name + "</font>";
t1rf_name = "<font color=\"#FF0000\">" + t1rf_name + "</font>"; 
t2rf_name = "<font color=\"#0000FF\">" + t2rf_name + "</font>";
t1ld_name = "<font color=\"#FF0000\">" + t1ld_name + "</font>"; 
t2ld_name = "<font color=\"#0000FF\">" + t2ld_name + "</font>";
t1rd_name = "<font color=\"#FF0000\">" + t1rd_name + "</font>"; 
t2rd_name = "<font color=\"#0000FF\">" + t2rd_name + "</font>";
t1g_name = "<font color=\"#FF0000\">" + t1g_name + "</font>"; 
t2g_name = "<font color=\"#0000FF\">" + t2g_name + "</font>";
       
//===================================================================
//============================PREGAME================================
//===================================================================   

 //HTML Code Prep
 recap << "<html>" << endl
       << "<head>" << endl
       << "  <title>TGP Blitzball</title>" << endl
       << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">" << endl
       << "</head>" << endl << endl
       << "<body text=\"#000000\" bgcolor=\"#FFFFFF\">"
       << endl << "<pre>"
       << endl << endl; 
 
 //Output Team Line-up
 recap << "Team 1: " << t1name << endl
       << "Formation: " << t1formation << endl
       << "Center: " << t1c_name << endl
       << "Right Forward: " << t1rf_name << endl
       << "Left Forward: " << t1lf_name << endl
       << "Right Defender: " << t1rd_name << endl
       << "Left Defender: " << t1ld_name << endl
       << "Goalie: " << t1g_name << endl << endl
       << "Team 2: " << t2name << endl
       << "Formation: " << t2formation << endl
       << "Center: " << t2c_name << endl
       << "Right Forward: " << t2rf_name << endl
       << "Left Forward: " << t2lf_name << endl
       << "Right Defender: " << t2rd_name << endl
       << "Left Defender: " << t2ld_name << endl
       << "Goalie: " << t2g_name << endl << endl << endl;

 //Start the game
 recap << "Welcome to today's game between the " << t1name 
       << " and the " << t2name << "!" << endl << endl;
 
//===================================================================
//==========================FIRST HALF===============================
//===================================================================     
 
 //First Half
 assign_positions(); randomize_bonuses();
 recap << "*************************************************" << endl
       << "*******************First Half********************" << endl
       << "*************************************************" << endl << endl;
       
 //Coin Toss. Decide who starts with possession.
 if (rand()%2 == 1){ team1ball = false; ball_refresh(t2c_name); team1starts2nd = true; }
 else { team1ball = true; ball_refresh(t1c_name); team1starts2nd = false; }
  
 recap << "The ball is released!" << endl
       << ball_name << " catches the ball." << endl << endl;    
 
 while (timeleft > 0){
  
  carry_ball(ball_name);
  ball_refresh(ball_name);
  recap << ball_name << "'s ball at (" << get_xpos(ball_name)/1000 << ","
        << get_ypos(ball_name)/1000 << "). Shot Bonus: " << shtbonus << endl;
  if (team1ball){ t1_offense(); t2_defense(); }
  else { t2_offense(); t1_defense(); }
  ball_refresh(ball_name);
  engage(ball_name);
  ball_refresh(ball_name);
  randomize_bonuses();
  timeleft -= 2;
  }
 
//===================================================================
//=========================INTERMISSION==============================
//===================================================================

recap << endl << "And that's it for the first half! " << endl;
if (t1score > t2score){  
 recap << "The " << t1name << " lead the " << t2name << " with a "
       << t1score << " to " << t2score << " lead." << endl
       << "Will the " << t2name << " be able to catch up?" << endl << endl;   
}
else if (t1score < t2score){ 
 recap << "The " << t2name << " lead the " << t1name << " with a "
       << t2score << " to " << t1score << " lead." << endl
       << "Will the " << t1name << " be able to catch up?" << endl << endl;
}
else { 
 recap << "With the score tied at " << t1score << " to " << t2score
       << ", this is still anyone's game!" << endl << endl;
}
 
//===================================================================
//==========================SECOND HALF==============================
//===================================================================

 //Start the second half!
 assign_positions(); timeleft = 300;
 recap << "*****************************************" << endl
       << "***************Second Half***************" << endl
       << "*****************************************" << endl << endl;
 recap << "The ball is released!" << endl;

 //Who gets the ball first?
 if (team1starts2nd){ ball_refresh(t1c_name); team1ball = true; }
 else { ball_refresh(t2c_name); team1ball = false; }
 recap << ball_name << " catches the ball." << endl << endl;    
      
 //Second Half
 while (timeleft > 0){  
  carry_ball(ball_name);
  ball_refresh(ball_name);
  recap << ball_name << "'s ball at (" << get_xpos(ball_name)/1000 << ","
        << get_ypos(ball_name)/1000 << "). Shot Bonus: " << shtbonus << endl;
  if (team1ball){ t1_offense(); t2_defense(); }
  else { t2_offense(); t1_defense(); }
  ball_refresh(ball_name);
  engage(ball_name);
  ball_refresh(ball_name);
  randomize_bonuses();
  timeleft -= 2;
 }

//===================================================================
//==========================FINAL OUTPUT=============================
//===================================================================

 recap << "And that buzzer means the game is over!" << endl
        << "And with a final score of " << t1score << " to "
        << t2score << "," << endl;
       
 if (t1score > t2score){
  recap << "the " << t1name << " win!";
 }
 else if (t2score > t1score){
  recap << "the " << t2name << " win!";    
 }
 else {
  recap << "it's a tie game!";    
 }   

 recap << "</pre>" << endl
       << "</body>" << endl
       << "</html>";

 recap.close();
 return 0;
}