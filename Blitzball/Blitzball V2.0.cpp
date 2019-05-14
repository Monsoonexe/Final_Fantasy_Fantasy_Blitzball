#include <iostream> //lines 900ish
#include <fstream>  // Formation Sweepl and SWEPR 
#include <stdio.h>  //LF and RF respectively have a Y pos of "0000"
#include <stdlib.h> //mistake or really meant to be 4 zeros?
#include <time.h>
#include <math.h>
#include <conio.h> //version 1.5 and beyond should compile. 
#include <vector>//not free of logic errors, probably
using namespace std;
ofstream recap;
ifstream teamdata;
ifstream playerdata;

//========================KNOWN ISSUES=======================================
/*
known issues....
Weird ypos for LF and RF in SWeep L and Sweep R 0000
NO GLOBAL VARIABLES!!!!!so carrier or goalie or form should
be only destination

double check to make sure "Time" is being counted correctly
noticed a "buzzer beater" at 4:03
*/
//============================PROTOTYPES================================
struct Player;
void pass(const vector <Player*> blockers);


//========================GAME VARIABLES===============================
const int radius = 10000; const int ballspot_distance = 6000; 
const int engage_distance = 1000;
int shtbonus = 0;
int timeleft = 300; bool team1starts2nd = false;
bool try_again = true; int bench = 0;

//==========================DATA TYPES=================================
enum Action {SHOT, PASS, ENDURANCE, ATTACK, BLOCK, CATCH};
enum Formation {NORMAL, JECHT, CENTER, WIDE, SWEEPL, RELAY, SWEEPR,
  CRASHL, CRESCENT, CRASHR};
enum Position {CN, RF, LF, RD, LD, GL, BN};
enum PlayerType {BH, TP, AW, PB, BF, C, NO};
enum RiskType {LOW = 1, CASUAL = 2, HIGH = 3};
enum TeamNo {HOME=0, AWAY=1};
enum TeamRole {DFS, OFS};

//============================PLAYERS==================================
struct Player{
  string name;//I'm slim shady
  Position position; //players should also know what they are
  int sht, pas, end, atk, blk, ca;//stats and position in pool
  Action bonusStat;
  RiskType risk;
  PlayerType type;
  TeamNo teamNo;//which team am I on?
  int xpos, ypos;
  bool hasBall;
  Player(){;}//THIS IS INTEGRAL FOR THE PROGRAM TO RUN, APPARENTLY!
  Player(const TeamNo newTeamNo){
    name = "INVALID";
    position = BN; //players should also know what they are
    sht=0; pas=0; end=0; atk=0; blk=0; ca=0;
    bonusStat = SHOT;//randomized before game starts
    risk = CASUAL;
    type = NO;
    teamNo=newTeamNo;//no team 
    xpos = 0;   ypos = 0;//position in pool
    hasBall = false;
    //team1.roster[CN].pas;//call to stat of player in position on team
  }//end default constructor

  // Player(const string name, const Position position, const int sht, 
  //   const int pas, const int end, const int atk, const int blk, const int ca, 
  //   const RiskType risk, const TeamNo teamNo, const PlayerType type,
  //   const int xpos, const int ypos){
  //   this->name = name; this->position = position;
  //   this->xpos = xpos; this->ypos = ypos; this->sht = sht; this->pas = pas;
  //   this->end = end; this->atk = atk; this->blk = blk; this->ca = ca;
  //   hasBall = false; //nobody should have ball at this point
  //   this->risk = risk; this->teamNo = teamNo; this->type = type;
  // }//end constructor if avoiding reading from file
  //combined protected movement member
  void swim(const int xpos, const int ypos){
    this->xpos = xpos, this->ypos = ypos;}
  //gives location of private member variables
  void getLoc(int &xpos, int &ypos){
    xpos=this->xpos; ypos=this->ypos;}
};//end Player 

//============================BALL=====================================
struct Ball{
  int xpos, ypos;
  Ball(){xpos = 0; ypos = 0;}//default constructor
  Ball(int x, int y){xpos = x; xpos = y;}//goal constructor
}ball;

//=====================TEAM BUILDER====================================

class Team{
private:
  string initials, name;
  Formation formation;
  int score;
  TeamNo teamNo;//home team?  team 0?
public:
  Player roster[6];
  Ball goal;//coordinates of team's goal
  Team(const TeamNo newTeamNo){
    initials = "INVALID";
    name = "INVALID";
    formation = NORMAL;
    score = 0;
    teamNo = newTeamNo;    //set goal position
    if(teamNo == HOME){setGoal(-10000, 0);}//team HOME is left
    else{setGoal(10000, 0);}//AWAY team on right
    // can use the Position enum type to search through list as well
    roster[6];
    for(int teammate = 0; teammate<6; ++teammate){//fill each roster with default player
       roster[teammate]= Player(teamNo);
    }//end for
    setGoaliePosition();//bleh, redundant, but whatever
  }//end default team constructor

  bool hasBall(){
    for(int teammate = 0; teammate<6; ++teammate){
      if(roster[teammate].hasBall){return true;}//we have the ball
    }//end for each teammate
    return false;//we don't have the ball
  }//end hasBall()

  void setGoal(const int x, const int y){goal.xpos = x; goal.ypos = y;}
  Ball getGoal(){return goal;}

  //add a point to this team's score
  void addScore(){++score;}//applies point
  int getScore(){return score;}//returns current score

  //getters
  string getInitials(){return initials;}
  string getName(){return name;}
  Formation getFormation(){return formation;}
  TeamNo getTeamNo(){return teamNo;}
  //setters
  void setInitials(const string newInit){initials = newInit;}
  void setName(const string newName){name = newName;}
  void setFormation(const Formation newForm){formation = newForm;}
  void setColors(const string color, const string font){
    for(int player = 0; player<6; ++player){
      roster[player].name = color + roster[player].name + font;
    }//end teammates
    name = color + name + font; //team name!
  }//end setColors
  void setGoaliePosition(){
    if(teamNo == HOME){roster[GL].xpos = -10000; roster[GL].ypos=0;}//HOME team goal
    else{roster[GL].xpos = 10000; roster[GL].ypos = 0;}//AWAY team goal
  }//end setGoaliePosition() 

}team1(HOME), team2(AWAY);

void teamNameCheck(const string);//prototype

//===========================================================================
//=============================Helper Functions==============================
//===========================================================================

void flushBuffer(){
  cin.clear();
  cin.ignore(1000, '\n');
}//flushes 1000 characters out of the cin input buffer

//returns Player who hasBall = true
Player *getCarrier(){
  Player *carrier = nullptr;
  int noOfCarriers=0;//results in an error if this is ever more than 1
  Team *teams[2]={&team1, &team2};
  for(int tm = 0; tm<2; ++tm){//each team
    for(int player = 0; player<6; ++player){//each player
      if(teams[tm]->roster[player].hasBall){//has ball?
        carrier = &teams[tm]->roster[player];//this is the carrier
        ++noOfCarriers;//should NEVER be != 1
      }
    }
  }
  if(noOfCarriers>1){cout<<"ERROR: Multiple carriers!!"<<endl; teamNameCheck("...multi carrier..."); getch();}
  else if(noOfCarriers<1){cout<<"ERROR: No carrier!"<<endl; teamNameCheck("...no carrier...");getch();}
  else{return carrier;}
}//end getCarrier()

const Player &getGoalie(const Player &player){
  const Team *teams[2] = {&team1, &team2};//put teams in a searchable list
  return teams[player.teamNo]->roster[GL];//return ptr to this team's goalie
}

Player &getBadGoalie(){
  const Player *carrier = getCarrier();
  Team *teams[2]={&team1, &team2};
  if(carrier->teamNo==HOME){return teams[AWAY]->roster[GL];}
  else if(carrier->teamNo==AWAY){return teams[HOME]->roster[GL];}
  else cout<<"ERROR: getBadGoalie(): no goalie";exit(0);
}//end getBadGoalie()

//================================Distance Formulae================================
//distance formula for raw coordinates
double get_dist (const int from_xpos, const int from_ypos, const int to_xpos, const int to_ypos){
 double distance = sqrt(pow(from_xpos-to_xpos,2)+pow(from_ypos-to_ypos,2));
 return distance;
}
//overloaded distance formula for use with Players
double get_dist(const Player &player, const Player &target){
  double distance = sqrt(pow(player.xpos - target.xpos,2)+
    pow(player.ypos - target.ypos,2));
  return distance;
}
//overloaded distance formula for use with Player to Ball
double get_dist(const Player &player, const Ball &target){
  double distance = sqrt(pow(player.xpos - target.xpos,2)+
    pow(player.ypos - target.ypos,2));
  return distance;
}

//======================Randomizers=======================
//Return random ca (for goalie) 
int random_ca(const Player roster[]){
  return roster[rand()%5].ca;
}

//Randomize Bonus Modifiers
void randomize_bonuses(Team teams[]){
  for(int iTeam = 0; iTeam<2; ++iTeam){
    for(int iPlayer = 0; iPlayer<5; ++iPlayer){
      teams[iTeam].roster[iPlayer].bonusStat = static_cast<Action>(rand()%6);
    }
  }
}

//==============================================================================
//==============================Fill Blockers===================================
//==============================================================================
//Ball is Loose
vector <Player*> fill_blockers(){
  //Variables
  const Player *carrier = getCarrier();//who has the ball?   
  const int carX = carrier->xpos; 
  const int carY = carrier->ypos;
  vector <Player*> defender_list;
  Team *teams[2]={&team1, &team2};
  for(int teammate = 0; teammate<5; ++teammate){//go through defending team
    Player *defender = &teams[getBadGoalie().teamNo]->roster[teammate];
    if(get_dist(carX,carY, defender->xpos, defender->ypos) <= engage_distance 
      && defender->name!=carrier->name){//except self
      defender_list.push_back(defender);
      //recap<<defender->name<<" added to defender_list."<<endl;//print test
    }//end if defender is within engage distance of carrier
  }//end for each defender
 
  //Special exception: uncontested vectors
  if(defender_list.size() <= 1) {return defender_list; }//quick, easy exit

  //bubble sort defender_list on ATK
  Player *temp = nullptr;//place holder
  bool swapMade = false; //flag
  do{//bubble sort
    swapMade = false;
    for(int teammate = 0; teammate < defender_list.size()-1; ++teammate){
      if(defender_list[teammate]->atk>defender_list[teammate+1]->atk){
        temp = defender_list[teammate];//temp holder
        defender_list[teammate] = defender_list[teammate+1];//swap
        defender_list[teammate+1] = temp;//swap
        swapMade = true;//flagged
      }//end if
    }//end for
  }while(swapMade);//swap was made
  return defender_list;//returns sorted pointer list of defenders based on atk
}//end fill_blockers()

//==============================================================================
//===============================Random Stat====================================
//==============================================================================

int rstat(const Player &player, const Action action){
  //Basic variables
  int stat = 0;
  //Modify boundaries based on risk
  RiskType riskmod = player.risk;

  //Modify high and low boundaries based on risk
  //originally both 1.0?  why??  expresssly stated as 120% and 80%
  double s_high = 1.2 + 0.1*riskmod; 
  double s_low = .8 - 0.1*riskmod;
   
  //Grab stat of player
  PlayerType carTB = player.type;//carrier's Type Bonus

  //switch variables
  bool type_bonus = false;//if type is activated
  switch(action){
    case SHOT:{
      stat = player.sht+shtbonus;
      if(carTB == AW or carTB == C) {type_bonus = true;} break;
    }//end case SHOT
    case PASS:{
      stat = player.pas;
      if(carTB == TP or carTB == BH) {type_bonus = true;} break;
    }//end case PASS
    case ENDURANCE:{
      stat = player.pas;
      if(carTB == AW or carTB == BH) {type_bonus = true;} break;
    }//end case END
    case ATTACK:{
      stat = player.atk;
      if(carTB == PB or carTB == TP) {type_bonus = true;} break;
    }//end case ATK
    case BLOCK:{
      stat = player.blk;
      if(carTB == PB or carTB == BF) {type_bonus = true;} break;
    }//end case END
    case CATCH:{
      stat = player.ca;
      if(carTB == BF or carTB == C) {type_bonus = true;} break;
    }//end case CAT
  }//end switch
  if(type_bonus){s_high+=0.05*riskmod; s_low-= 0.05*riskmod;}

  //Establish stat boundaries as integers
  int stat_high = (int)(stat*s_high+0.5);
  int stat_low = (int)(stat*s_low+0.5);
 
  // recap << carrier.name << ":" << endl
  //     << "High Percent: " << s_high*100 << endl
  //     << "Low Percent: " << s_low*100 << endl << endl;
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
  team1.roster[CN].xpos = -3000; team1.roster[CN].ypos = 0;
  team1.roster[RF].xpos = -2000; team1.roster[RF].ypos = -6000;
  team1.roster[LF].xpos = -2000; team1.roster[LF].ypos = 6000;
  team1.roster[RD].xpos = -7000; team1.roster[RD].ypos = -3000;
  team1.roster[LD].xpos = -7000; team1.roster[LD].ypos = 3000;
 //Team 2 Starting Positions
  team2.roster[CN].xpos = 3000; team2.roster[CN].ypos = 0;
  team2.roster[RF].xpos = 2000; team2.roster[RF].ypos = 6000;
  team2.roster[LF].xpos = 2000; team2.roster[LF].ypos = -6000;
  team2.roster[RD].xpos = 7000; team2.roster[RD].ypos = 3000;
  team2.roster[LD].xpos = 7000; team2.roster[LD].ypos = -3000;
}//end assign_positions()

//===========================================================================
//===========================Give Stats Function=============================
//===========================================================================
void give_stats(Player &player){
  //Stat Variables
  int sht = 1, pas = 1, end = 1,
      atk = 1, blk = 1, ca = 1;
  RiskType risk = CASUAL;
  PlayerType type = NO;
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
    if(temp2 == player.name){ break;}
  }
  int lvl = 0;//package multiplier
  //Tackle Slip
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  pas += 2*lvl; end += 3*lvl; ca += lvl; //set stats for package
  
  //Grip Gloves
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  pas += 2*lvl; blk += 3*lvl; ca += lvl; //set stats for package
 
  //Elite Defense
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  pas += lvl; atk += 2*lvl; blk += 2*lvl; ca += lvl; //set stats for package
 
  //Brawler
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  end += lvl; atk += 3*lvl; blk += lvl; ca += lvl; //set stats for package
 
  //Golden Arm
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  pas += 3*lvl; sht += 2*lvl; blk += lvl; //set stats for package
 
  //Jecht Shot
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  sht += 2*lvl; end += 2*lvl; atk += 2*lvl;
 
  //Volley Shot
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  sht += 3*lvl; end += 2*lvl; blk += lvl;
 
  //All-Rounder
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  sht += lvl; pas += lvl; end += lvl; atk += lvl; blk += lvl; ca += lvl;
 
  //Super Goalie
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  ca += (int)1.5*lvl; pas += lvl;
 
  //Keepa
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  lvl = atoi(temp.substr(0,pos).c_str());
  sht += 2*lvl; ca += lvl;
   
  //Risk
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  if(temp.substr(0,pos) == "LOW")player.risk = LOW;
  else if(temp.substr(0,pos) == "NORMAL")player.risk = CASUAL;
  else if(temp.substr(0,pos) == "HIGH")player.risk = HIGH;
  //Type
  ++pos;
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  if(temp.substr(0,pos)=="BH")player.type = BH;
  else if(temp.substr(0,pos)=="TP")player.type = TP;
  else if(temp.substr(0,pos)=="AW")player.type = AW;
  else if(temp.substr(0,pos)=="PB")player.type = PB;
  else if(temp.substr(0,pos)=="BF")player.type = BF;
  else if(temp.substr(0,pos)=="CA")player.type = C;
  else if(temp.substr(0,pos)=="NO")player.type = NO;
  else {cout<<"ERROR setting player.type in player creation."<<endl; getch();}//print test

  //actually set the player's stats here
  player.sht = sht; player.pas = pas; player.end = end;
  player.atk = atk; player.blk = blk; player.ca = ca;

  //output test
  // cout << player.name << ":" << endl
  //    << "SHT: " << player.sht << "   PAS: " << player.pas 
  //    << "   END: " << player.end << endl
  //    << "ATK: " << player.atk << "   BLK: " << player.blk 
  //    << "   CA: " << player.ca << endl << endl
  //    << "RISK: " << player.risk << "TYPE: " << player.type << endl;
  //    getch();//print test
// temp = getch();
 
// pos = getch();
  system("cls");
  playerdata.close();
}//end give_stats()
                  
//===========================================================================
//==========================Initialize players Function===========================
//===========================================================================
void initPlayer(const string newPlayer, Team &team){                       
 char userChoice = ' ';//user's choice of player position         
 cout << newPlayer << " will be my" << endl
  << "4 = Left Forward" << endl
  << "5 = Center" << endl
  << "6 = Right Forward" << endl
  << "1 = Left Defender" << endl
  << "2 = Goalie" << endl
  << "3 = Right Defender" << endl
  << "0 = BENCH" << endl << endl;
  bool invalidInput;//console input invalid
  Position position = BN;
  do{//input validation
    invalidInput = false;//assumed correct
    userChoice=getch();//get a single character from user
    switch(userChoice){//menu
      case '0':{cout<<"Player Benched."<<endl; //confirmation
        position = BN; //flag to skip player
        break;}//player is on bench
      case '1':{position = LD; break;}
      case '2':{position = GL; break;}
      case '3':{position = RD; break;}
      case '4':{position = LF; break;}
      case '5':{position = CN; break;}
      case '6':{position = RF; break;}
      default:{cout<<"ERROR: enter a number 0-6 as shown."<<endl;
        invalidInput = true; break;}
    }//end switch
    if(position != BN){
      if(team.roster[position].name != "INVALID"){
        invalidInput = true;
        cout<<"ERROR: Position taken. Try again."<<endl;
      }//end if position already taken
    }//end if player not benched
  }while(invalidInput);//input is invalid
  if(position==BN){return;}//move on to next player
  team.roster[position].position = position;//tell player what position
  team.roster[position].name = newPlayer;//give player name
  give_stats(team.roster[position]);//set stats of player
}//end position_pick()
//===========================================================================
//============================Team Pick Function=============================
//===========================================================================

void team_pick(Team &team){
  string temp = "INVALID";
             
  cout << "Input Team Initials: ";//console prompt
  cin>>temp;//team initials
  team.setInitials(temp);

  //Open the file
  teamdata.seekg(0);
  teamdata.clear();
  teamdata.open("teamdata.txt");   
   
  cout << "Formation: " << endl
      << "7. CrashL" << "     " << "8. Crescent" << "   " << "9. CrashR" << endl
      << "4. SweepL" << "     " << "5. Relay" << "     " << " 6. SweepR" << endl      
      << "1. Jecht" << "      " << "2. Center" << "     " << "3. Wide" << endl
      << "              0. Normal" << endl << endl;
  bool invalidInput = false;//flag for incorrect input
  char form_input = ' ';//holds new formation
  Formation newFormation;
  do{//input validation
    invalidInput = false;
    form_input = getch();
    switch(form_input){
      case '0':{newFormation = NORMAL; break;}
      case '1':{newFormation = JECHT; break;}
      case '2':{newFormation = CENTER; break;}
      case '3':{newFormation = WIDE; break;}
      case '4':{newFormation = SWEEPL; break;}
      case '5':{newFormation = RELAY; break;}
      case '6':{newFormation = SWEEPR; break;}
      case '7':{newFormation = CRASHL; break;}
      case '8':{newFormation = CRESCENT; break;}
      case '9':{newFormation = CRASHR; break;}
      default:{cout<<"ERROR:  re-input formation."<<endl;
        invalidInput = true; break;}//end invalid input
    }//end switch
  }while(invalidInput);
  team.setFormation(newFormation);//set new formation 
  int pos=0; string temp2 = "INVALID";
 
 //Cycle through the names
 while (!teamdata.eof()){
  getline(teamdata, temp);
  pos = temp.find('=');
  temp2 = temp.substr(0,pos);
  if (temp2 == team.getInitials()){break;}
 }

 //Close the file
  teamdata.close();
  
 //If bad team, try again
 if (temp2 == "#EOF#" or temp2 == "#EOF#|" or temp2 == "#EOF"){ 
  cout<<"ERROR:  BAD TEAM! #EOF#"<<endl; getch();
  try_again = true; //BAD GLOBAL BOOLEAN!
  system("cls");
  return; 
 }
 
 //Team Name
 ++pos;
 temp = temp.substr(pos,256);
 pos = temp.find(':');
 team.setName(temp.substr(0,pos));//set team name
 
 bool invalidTeam = true;//repeat until full roster causes break
 //Individual Players
 while(invalidTeam){
  system("cls");
  ++pos;
  //bool rosterFull = false;//flag for all positions filled
  if (team.roster[CN].name != "INVALID" && team.roster[RF].name != "INVALID" 
    && team.roster[LF].name != "INVALID" && team.roster[RD].name != "INVALID"
    && team.roster[LD].name != "INVALID" && team.roster[GL].name != "INVALID")
    {break;}//once these are all full, stop seeking file
  temp = temp.substr(pos,256);
  pos = temp.find('|');
  temp2 = temp.substr(0,pos);
  initPlayer(temp2, team);//temp2 is player's name
 }
 try_again = false;
}

//===========================================================================
//===========================================================================
//==============================Ball Functions===============================
//===========================================================================
//===========================================================================

void ball_refresh(){
  Player *carrier = getCarrier();
  ball.xpos = carrier->xpos; ball.ypos = carrier->ypos;
}

double ball_distance(const Player &player){
  double ball_distance = sqrt(pow(player.xpos - ball.xpos,2) + 
  pow(player.ypos - ball.ypos,2));
 return ball_distance;
}
//takes ball away from everyone but and gives ball to rebounder
void turnover(Player &rebounder){
  teamNameCheck("entering turnover()");
  Team *teams[2]={&team1, &team2};
  for(int tm = 0; tm<2; ++tm){//each team
    for(int player = 0; player<6; ++player){//each player
      teams[tm]->roster[player].hasBall = false;//every player drops ball
    }
  }
  rebounder.hasBall = true;//only rebounder grabs ball
  ball_refresh();//refresh ball coordinates to carrier's
  teamNameCheck("leaving turnover()");
}//end turnover()

//==============================================================================
//===============================Loose Ball=====================================
//==============================================================================

//Ball is Loose
void loose_ball(const Player &fumbler){//butterfingers!!
  //!!!!might need to use ball.xy instead of carrier xy!!!!!!!!
  double shortest = 3*radius; //shortest dist. why set to this number?
  double distance = 0.0;//distance teammate is from ball
  vector <Player*> closestPlayers;
  //who is the closest player to the ball?
  Team *teams[2]={&team1, &team2};
  for(int tm = 0; tm<2; ++tm){//for each team
    for(int teammate=0; teammate<6; ++teammate){//iterate through BOTH 
      distance = get_dist(teams[tm]->roster[teammate], fumbler);//check team 1
      if(distance<=shortest){shortest=distance;}//end compare and/or set shortest distance to ball
    }//get distance for each teammate to fumbler position
  }//end for each team
  //make a vector of players who are like distance from ball
  for(int tm=0;tm<2;++tm){//for each team
    for(int teammate=0; teammate<6; ++teammate){//look through players of team1 AND team2 to find like distance
      distance = get_dist(teams[tm]->roster[teammate], fumbler);
      if(distance>=shortest and distance<=shortest+(engage_distance/2)){//if w/n half of encounter distance of ball
        closestPlayers.push_back(&team1.roster[teammate]);}//end if w/n fumble recover range
    }//end for each player
  }//end for eac hteam
  Player &rebounder = *closestPlayers[rand()%closestPlayers.size()];//random among list
  turnover(rebounder);//this person has the ball
  //if goalie gets it, goaliekick
  if(rebounder.position==GL){vector <Player*> emptyvec; pass(emptyvec);}  
}//end loose_ball()

//===========================================================================
//===========================================================================
//============================Movement Functions=============================
//===========================================================================
//===========================================================================

//===========================================================================
//===========================Sphere Edge Function============================
//===========================================================================

//Sphere Edge Function: Keeps dudes in the pool (can't leave pool boundaries)
void sphere_edge (int &xpos, int &ypos){
 double dxpos = (double)xpos;
 double dypos = (double)ypos;
 double pythago = sqrt((xpos*xpos)+(ypos*ypos));
 double cangle = 0.0;
 if (pythago > radius){//is player headed out of bounds?
  cangle = asin(dypos/pythago);
  dypos = radius*sin(cangle);
  dxpos = radius*cos(cangle);
  xpos = (int)dxpos;
  ypos = (int)dypos;
 }//end keep player inbounds 
}

//===========================================================================
//=========================Random Movement Function==========================
//===========================================================================

//Completely random movement
void random_movement(Player &player){
 int xmove = rand()%engage_distance;
 int ymove = (int)sqrt(pow(engage_distance,2) - pow(xmove,2));
 //50% chance to move forward or back
 if (rand()%2 == 1){ xmove = -1*xmove; }
 if (rand()%2 == 1){ ymove = -1*ymove; }
 xmove += player.xpos; ymove += player.ypos;
 sphere_edge(xmove, ymove); player.swim(xmove,ymove);
}//end random movement

//===========================================================================
//========================Optimal Movement Function==========================
//===========================================================================

//Optimal movement to a given target
void optimal_movement(Player &player, 
  const int target_xpos, const int target_ypos){
  int move_distance = engage_distance;
  double cangle = 0;
 
 //Already there
 if (player.xpos == target_xpos && player.ypos == target_ypos){
  random_movement(player);        
 }
 
 //Carrier moves 10% slower
 if (player.name==getCarrier()->name){ 
  const float slowSpeed = .9;
  move_distance = slowSpeed*engage_distance;          
 }
 
 //Triangle
 int height = target_ypos - player.ypos;
 int width = target_xpos - player.xpos;
 if (width == 0 && height >= 0){ cangle = 1.57; }
 else if (width == 0 && height < 0){ cangle = 4.71; }
 else { cangle = atan2(height,width); }
 
 //Close enough? Let 'em have it
 if (sqrt(height*height+width*width) <= move_distance){
  player.swim(target_xpos, target_ypos);
  return;
 }
 
 //Take x-component of movement triangle and add to current x-position
 double dxpos = move_distance*cos(cangle);
 dxpos += player.xpos;
 int newxpos = (int)dxpos;
 
 //Take y-component of movement triangle and add to current y-position
 double dypos = move_distance*sin(cangle);
 dypos += player.ypos;
 int newypos = (int)dypos;
 
 //Apply new coordinates, restrict movement outside sphere
 sphere_edge (newxpos, newypos); player.swim(newxpos,newypos);
}//end optimal movement()

//===========================================================================
//===========================Carry Ball Function=============================
//===========================================================================
//Person with the ball carries it straight to the goal
void carry_ball(){//towards that bad, bad goalie ;)
  optimal_movement(*getCarrier(), getBadGoalie().xpos, getBadGoalie().ypos);
  ball_refresh();
  recap << getCarrier()->name << "'s ball at (" << ball.xpos/1000 << ","
          << ball.ypos/1000 << "). Shot Bonus: " << shtbonus << endl;
}//end carry_ball()

//===========================================================================
//===========================Ball Pursuit Function===========================
//===========================================================================
//Seek out the ball carrier if in range
void ball_pursuit(Player &player){         
  //So close, just move 'em
  if(get_dist(player, ball) <= engage_distance){//if player w/n reach
    player.swim(ball.xpos, ball.ypos);//player is right on top of it!
    return;//just right up on in there
  }//end if within reach
  else{optimal_movement(player, ball.xpos, ball.ypos);}
  //If in view of ball carrier, move directly toward ball
}//end ball_pursuit()

//===========================================================================
//=========================Tackle Movement Function==========================
//===========================================================================

//Optimal movement to a given target
void tackle_movement(Player &player, const Player &target){
 double cangle = 0;
 
 //Triangle
 int height = target.ypos - player.ypos;
 int width = target.xpos - player.xpos;
 if (width == 0 && height >= 0){ cangle = 1.57; }
 else if (width == 0 && height < 0){ cangle = 4.71; }
 else { cangle = atan2(height,width); }
 
 //Take x-component of movement triangle and add to current x-position
 double dxpos = 5*engage_distance*cos(cangle)/4;
 dxpos += target.xpos;
 int newxpos = (int)dxpos;
 
 //Take y-component of movement triangle and add to current y-position
 double dypos = 5*engage_distance*sin(cangle)/4;
 dypos += target.ypos;
 int newypos = (int)dypos;
 
 //Apply new coordinates, restrict movement outside sphere
 sphere_edge(newxpos, newypos); player.swim(newxpos,newypos);
}

//===========================================================================
//=========================Assume Formation Function=========================
//===========================================================================

//Go to designated location based on specified formation
void assume_formation(Player &player, const Formation &formation, 
    const bool on_offense){
  Position position = player.position;//haha confusing???? nope!
 //Normal Formation
  int xdest, ydest = 0; //player's destination
  
 switch(formation){//which formation?
  case NORMAL:{
    if(position == CN){ 
      if(on_offense){xdest = 5000; ydest = 0;}
      else{xdest = -1000; ydest = 0;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 7000; ydest= 5000;}
      else{xdest= -2000; ydest= 6000;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 7000; ydest= -5000;}
      else{xdest= -2000; ydest= -6000;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= 0; ydest= 4000;}
      else{xdest= -7000; ydest= 3000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= 0; ydest= -4000;}
      else{xdest= -7000; ydest= -3000;}
    }//end RIGHT DEFENDER
    break;
  }//end case NORMAL
  case CENTER:{
    if(position == CN){ 
      if(on_offense){xdest = 4000; ydest = 0;}
      else{xdest = -3000; ydest = 0;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 6000; ydest= 3000;}
      else{xdest= -4000; ydest= 4000;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 6000; ydest= -3000;}
      else{xdest= -8000; ydest= 2000;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= 0; ydest= 4000;}
      else{xdest= -7000; ydest= 3000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= 0; ydest= -4000;}
      else{xdest= -7000; ydest= -3000;}
    }//end RIGHT DEFENDER
    break;//break CENTER
  }//end CENTER
  case WIDE:{
    if(position == CN){ 
      if(on_offense){xdest = 3000; ydest = 0;}
      else{xdest = -5000; ydest = 0;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 7000; ydest= 2000;}
      else{xdest= -1000; ydest= 9000;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 7000; ydest= -2000;}
      else{xdest= -1000; ydest= -9000;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= -1000; ydest= 5000;}
      else{xdest= -6000; ydest= 4000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= -1000; ydest= -5000;}
      else{xdest= -6000; ydest= -4000;}
    }//end RIGHT DEFENDER
    break;
  }//end case WIDE
  case SWEEPR:{
    if(position == CN){ 
      if(on_offense){xdest = 5000; ydest = 3000;}
      else{xdest = -2000; ydest = 6000;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 6000; ydest= 0;}
      else{xdest= -1000; ydest= 0;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 7000; ydest= -2000;}
      else{xdest= -1000; ydest= -4000;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= -1000; ydest= 2000;}
      else{xdest= -7000; ydest= 4000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= 1000; ydest= -6000;}
      else{xdest= -7000; ydest= -3000;}
    }//end RIGHT DEFENDER
    break;
  }//end SWEEPR
  case SWEEPL:{
    if(position == CN){ 
      if(on_offense){xdest = 5000; ydest = -3000;}
      else{xdest = -2000; ydest = -6000;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 7000; ydest= 2000;}
      else{xdest= -1000; ydest= 4000;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 6000; ydest= 0;}
      else{xdest= -1000; ydest= 0;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= 1000; ydest= 6000;}
      else{xdest= -7000; ydest= 3000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= -1000; ydest= -2000;}
      else{xdest= -7000; ydest= -4000;}
    }//end RIGHT DEFENDER
    break;
  }//end SWEEPR
  case JECHT:{
    if(position == CN){ 
      if(on_offense){xdest = 4000; ydest = 4000;}
      else{xdest = -3000; ydest = -5000;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 4000; ydest= 4000;}
      else{xdest= -3000; ydest= 5000;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 8200; ydest= 0;}
      else{xdest= 0; ydest= 0;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= -1000; ydest= 3500;}
      else{xdest= -6000; ydest= 4000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= -1000; ydest= -3500;}
      else{xdest= -6000; ydest= -4000;}
    }//end RIGHT DEFENDER
    break;
  }//end JECHT
  case CRESCENT:{
    if(position == CN){ 
      if(on_offense){xdest = 4000; ydest = 0;}
      else{xdest = -8000; ydest = 0;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 7000; ydest= 6000;}
      else{xdest= -1000; ydest= 6000;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 7000; ydest= -6000;}
      else{xdest= -1000; ydest= -6000;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= -1000; ydest= 4000;}
      else{xdest= -6000; ydest= 4000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= -1000; ydest= -4000;}
      else{xdest= -6000; ydest= -4000;}
    }//end RIGHT DEFENDER
    break;
  }//end CRESCENT
  case RELAY:{
    if(position == CN){ 
      if(on_offense){xdest = -1000; ydest = 0;}
      else{xdest = -4000; ydest = 0;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 7000; ydest= 3000;}
      else{xdest= -1000; ydest= 7000;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 7000; ydest= -3000;}
      else{xdest= -1000; ydest= -7000;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= -3000; ydest= 5000;}
      else{xdest= -7000; ydest= 2000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= -3000; ydest= -5000;}
      else{xdest= -7000; ydest= -2000;}
    }//end RIGHT DEFENDER
    break;
  }//end RELAY
  case CRASHR:{
    if(position == CN){ 
      if(on_offense){xdest = 3000; ydest = -5000;}
      else{xdest = -2000; ydest = -2000;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 6000; ydest= 0;}
      else{xdest= -2000; ydest= 5000;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 8000; ydest= -3000;}
      else{xdest= -1000; ydest= -8000;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= -4000; ydest= 2000;}
      else{xdest= -6000; ydest= 1000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= -3000; ydest= -6000;}
      else{xdest= -6000; ydest= -4000;}
    }//end RIGHT DEFENDER
    break;
  }//end RELAY
  case CRASHL:{
    if(position == CN){ 
      if(on_offense){xdest = 3000; ydest = 5000;}
      else{xdest = -2000; ydest = 2000;}
    }//end CENTER
    if(position == LF){ 
      if(on_offense){xdest= 8000; ydest= 3000;}
      else{xdest= -1000; ydest= 0;}
    }//end LEFT FORWARD
    if(position == RF){ 
      if(on_offense){xdest= 6000; ydest= 0;}
      else{xdest= -2000; ydest= -5000;}
    }//end RIFGHT FORWARD
    if(position == LD){ 
      if(on_offense){xdest= -3000; ydest= 6000;}
      else{xdest= -6000; ydest= 4000;}
    }//end LEFT DEFENDER
    if(position == RD){ 
      if(on_offense){xdest= -4000; ydest= -2000;}
      else{xdest= -6000; ydest= -1000;}
    }//end RIGHT DEFENDER
    break;
  }//end CRASHL
  default:{recap << "Assume_Formation IS A LIE!" << endl; exit(0); break;}
 }//end FORMATION switch
 //AWAY team uses mirrored coordinates
  if(player.teamNo == AWAY){xdest *= -1; ydest *= -1;} 
  optimal_movement(player, xdest, ydest);//calculate and move player
}//end assume_formation()

//===========================================================================
//==========================Defense Function=================================
//===========================================================================

//Defensive Movements
void defense(Team &team){
  for(int teammate = 0; teammate < 5; ++teammate){//exclude goalie
    if(ball_distance(team.roster[teammate])<=ballspot_distance){//pursuit check
      ball_pursuit(team.roster[teammate]);}//go get it!! end if can pursue ball
    else{assume_formation(team.roster[teammate], 
      team.getFormation(), team.hasBall());}//end else return to position
  }//end for
}//end defense()

//===========================================================================
//==============================Offense Function=============================
//===========================================================================

void offense(Team &team){
  for(int teammate = 0; teammate <5; ++teammate){//exclude goalie
    if(team.roster[teammate].name != getCarrier()->name){//if this player does NOT have the ball..
      assume_formation(team.roster[teammate],//fall back in formation
        team.getFormation(), team.hasBall());
    }//end if
  }//for
}//end offense()  

//===============================Auto OFS or DFS==============================
void skirmish(){
  Team *teams[2];//create empty holder for ofs and dfs
  if(team1.hasBall()){teams[OFS] = &team1; teams[DFS] = &team2;}
  else if(team2.hasBall()){teams[OFS] = &team2; teams[DFS] = &team1;}
  else cout<<"WTF am I doing with my life????"<<endl;
  offense(*teams[OFS]); defense(*teams[DFS]);
  ball_refresh();//update ball position
}//end skirmish()

//===========================================================================
//===========================================================================
//======================Shoot, Pass, Engage Functions========================
//===========================================================================
//===========================================================================
bool testPass(const Player &target, const Action action){
  Player *carrier = getCarrier();
  int actionStat = rstat(*carrier, action);//initialize stat with player val
  //a test shouldn't account for possible bonus.  1:6 chance of really screwing up
  if(carrier->bonusStat == action){actionStat+=rstat(getGoalie(*carrier), action);}
  int traveling = get_dist(*carrier, target) / engage_distance;
  while(traveling>0){actionStat*=.9; --traveling;}//degrade by 10% per "time"
  if(actionStat>=0){return true;}//action was sucessful
  else{return false;}//test action failed
}//end testPass

//===========================================================================
//========================Player Upfield Function============================
//===========================================================================

//Checks if a teammate is in passing range and closer to the goal
vector <Player*> gatherUpfielders(const Player &carrier){
  double pdist = 2.0*radius; 
  vector <Player*> upfielders;
  //if possible, have functions accept parameter for pointer instead of reference
  Team *teams[2];//decide who is on OFS-offense or DFS-defense
  if(team1.hasBall()){teams[OFS]=&team1; teams[DFS]=&team2;}
  else if(team2.hasBall()){teams[DFS]=&team1; teams[OFS]=&team2;}
  else{cout<<"ERROR: No team hasBall()"<<endl; getch();}
  for(int teammate = 0; teammate<5; ++teammate){//5 bc goalie never upfield
    if(carrier.name != teams[OFS]->roster[teammate].name){//if not self
      if(get_dist(carrier, teams[DFS]->goal) > //if carrier distance farther than
        get_dist(teams[OFS]->roster[teammate], teams[DFS]->goal)){//team distance
        if(testPass(teams[OFS]->roster[teammate], PASS)){//if w/n pass range
        upfielders.push_back(&teams[OFS]->roster[teammate]);}
        //recap<<teams[OFS]->roster[teammate].name<<" added to upfielders."<<endl;}//add to list
      }//if teammate is closer
    }//end if teammate is not me
  }//end for each person on my team
  //if(upfielders.size()==0){upfielders[0]=nullptr;}//can test against to see if false
  return upfielders;//return a list of pointers to all players on your team
                //who are closer to the enemy's goal than you and also 
                //who passed a successful testPass()
}//end gather_upfield()

//===========================================================================
//=========================Pass Target Function==============================
//===========================================================================
//who am i going to pass to?
//Checks if a teammate is in pass range and closer to the goal
Player & pass_target(const Player &carrier){
  //recap<<"In pass_target..."<<endl;//print test
  vector <Player*> upfielders = gatherUpfielders(carrier);
  Player* target = nullptr;//target of pass
  int random = 0; //Choose random fielder
  if(upfielders.size() > 1){//if many eligible bachelors...
    target = upfielders[rand()%upfielders.size()];//rando!
    //recap<<"target: "<<target->name<<endl;//print test
    //future AI will check for "openness"
  }//end if poole of players
  else if(upfielders.size() == 1){target = upfielders[0];}//if only 1
  else{//if none and must pass
    int closest = 20000;//looking for clostest player
    Team *teams[2]={&team1, &team2};
    for(int teammate = 0; teammate < 5; ++teammate){
      if(get_dist(carrier, teams[carrier.teamNo]->roster[teammate])<closest){
        if(carrier.name != teams[carrier.teamNo]->roster[teammate].name){//if not self
          if(carrier.teamNo == teams[carrier.teamNo]->roster[teammate].teamNo)//if on same team
          {closest = teammate;}//find closest player
        }
      }//end if this teammate closer to me
      target = &teams[carrier.teamNo]->roster[closest];//target is closest teammate
    }//end for each teammate
  }//end if no one w/n range
  //recap<<"Now leaving pass_target."<<endl;
  //recap<<"return name: "<<target->name<<endl;
  return *target;
}//end pass_target()

//===========================================================================
//=============================Pass Function=================================
//===========================================================================

void pass(const vector <Player*> blockers){
  Player *carrier = getCarrier();
  recap<<carrier->name;
  if(carrier->bonusStat==PASS){recap << "*";}
  recap<<" throws a pass!"<<endl;
  int pass = rstat(*carrier, PASS);//initialize stat with player val
  if(carrier->bonusStat == PASS){pass+=rstat(getGoalie(*carrier), PASS);}
  for(int blocker = 0; blocker<blockers.size(); ++blocker){//for each blocker
    pass-=rstat(*blockers[blocker], BLOCK);//blocks
    if(blockers[blocker]->bonusStat ==BLOCK){
      pass-= rstat(getGoalie(*blockers[blocker]), BLOCK);}//end if bonus
    if(pass>0){//gets a hand on it
      recap<<blockers[blocker]->name;
      if(blockers[blocker]->bonusStat == BLOCK){recap<<"*";}//add * for bonus
      recap<<" gets a hand on it!"<<endl;
      ++shtbonus;
    }//end if blocker gets a hand on it
    else if(pass<=0){//blocker gets it
      recap <<blockers[blocker]->name;
      if(blockers[blocker]->bonusStat == BLOCK){recap<<"*";}
      recap <<" grabs the ball!"<< endl<<endl; 
      turnover(*blockers[blocker]);
      shtbonus = 0; return;
    }//end blocker gets it
  }//end each blocker has made an attempt
  //ball now travelling through water
  Player &target = pass_target(*carrier); //to whom am i passing?
  //recap <<"pass target: "<<target.name<<endl;//print test
  int traveling = get_dist(*carrier, target) / engage_distance;
  //recap<<"TRAVELING: "<<traveling<<endl;//print test
  while(traveling>0){pass*=.9; --traveling; --timeleft;}//degrade by 10% per "time"
  if(pass>0){//pass successfull!!
    turnover(target); //give ball even if
    recap<<target.name<<" catches the pass!"<<endl<<endl;
    shtbonus+=3; return;}//increase sht bonus action was sucessful
  else{//pass failed
    recap<<target.name<<" fumbles the pass!"<<endl; 
    loose_ball(target); return;}//pass failed.  ball is loose
}//end pass()

//===========================================================================
//===========================Test Shot Function==============================
//===========================================================================

//Checks if the shooter has a feasible chance at making a goal
bool test_shot (const Player &carrier, vector <Player*> blockers){
  //quick exit.  no shots from own side of court
  if(carrier.teamNo == HOME && carrier.xpos <= 0){return false;}
  if(carrier.teamNo == AWAY && carrier.xpos >= 0){return false;}
  //get carrier shot stat
  int shot = rstat(carrier, SHOT);
  if(carrier.bonusStat == SHOT){shot += rstat(getGoalie(carrier), SHOT);}
  for(int blocker = 0; blocker<blockers.size(); ++blocker){//for each blocker
    shot-=rstat(*blockers[blocker], BLOCK);//blocks
  }//end for
  if(shot<=0){return false;}// cannot make a shot
  Player* goalie;
  if(carrier.teamNo == HOME){goalie = &team2.roster[GL];}
  else if(carrier.teamNo == AWAY){goalie = &team1.roster[GL];}
  int traveling = get_dist(carrier, *goalie)/engage_distance;
  while(traveling>0){shot*=.9; --traveling;}
  if(shot<=0){return false;}//cannot shoot
  shot-=rstat(*goalie, CATCH);
  if(shot<=0){return false;}
  else return true;
}//end test_shot()
//===========================================================================
//===============================Shoot Function==============================
//===========================================================================

//Checks if the shooter has a feasible chance at making a goal
void shoot(vector <Player*> blockers){
  Player *carrier = getCarrier();
  recap<<carrier->name;
  if(carrier->bonusStat==SHOT){recap << "*";}
  recap << " shoots!" << endl;

 //get carrier shot stat
 int shot = rstat(*carrier, SHOT);
 if(carrier->bonusStat == SHOT){shot += rstat(getGoalie(*carrier), SHOT);}
 for(int blocker = 0; blocker<blockers.size(); ++blocker){//for each blocker
    shot-=rstat(*blockers[blocker], BLOCK);//blocks
    if(blockers[blocker]->bonusStat ==BLOCK){
      shot-= rstat(getGoalie(*blockers[blocker]), BLOCK);}//end if bonus
    if(shot>0){//gets a hand on it
      recap<<blockers[blocker]->name;
      if(blockers[blocker]->bonusStat == BLOCK){recap<<"*";}//add * for bonus<<" gets a hand on it!"<<endl;
      recap<<" gets a hand on it!"<<endl<<endl;
    }//end if blocker gets a hand on it
    else if(shot<=0){//blocker gets it
      recap <<blockers[blocker]->name;
      if(blockers[blocker]->bonusStat == BLOCK){recap<<"*";}
      recap <<" grabs the ball!"<< endl<<endl; 
      turnover(*blockers[blocker]);
      shtbonus = 0; return;
    }//end blocker gets it
  }//end each blocker has made an attempt
 //Calculate distance ball must travel to reach the goalie
  //find opposing goalie
  Player* goalie;
  if(carrier->teamNo == HOME){goalie = &team2.roster[GL];}
  else if(carrier->teamNo == AWAY){goalie = &team1.roster[GL];}
  int traveling = get_dist(*carrier, *goalie) / engage_distance;
  recap << "Shot Power: "<<shot;
  while(traveling>0){
    shot*=.9; // degrade through water
    recap<<"..."<<shot;//output
    --traveling; --timeleft;}//degrade by 10% per "time"
  recap<<endl;
  int goalieCA = rstat(*goalie, CATCH);
  recap<<goalie->name<<"'s CA: "<<goalieCA<<endl;
  shot -=goalieCA;
  if(shot>0){//GGGGGGOOOOOOOAAALAAALALLALALALLALALALAL
    Team *teams[2] = {&team1, &team2};
    teams[carrier->teamNo]->addScore();//add point
    assign_positions();//reset to center
    int minutes = (300-timeleft)/60;
    int seconds = timeleft%60;
    recap << goalie->name << " can't catch it! Goal!" << endl << endl
          << "Score:" << endl
          << team1.getName() << ": " << team1.getScore() << endl
          << team2.getName() << ": " << team2.getScore() << endl 
          << "Time: " << minutes << ":";
    if (seconds < 10){ recap << "0"; }
    if (seconds < 0){ seconds = 0; }
    recap << seconds << endl << endl;
    //No release at final shot
    if (timeleft <= 0) { return;}
    turnover(teams[goalie->teamNo]->roster[CN]);//give ball to team center
    recap << "The ball is released!" << endl
    << getCarrier()->name <<" catches the ball!"<<endl<<endl;
    shtbonus = 0;
 }//end if goalllllllllll
 else if (shot <= 0 && shot >= -2){//Loose ball!
  recap << goalie->name << " gets a hand on it!" << endl;
  loose_ball(*goalie);//scramble for ball
  shtbonus = 0;//reset shit bonus
 }//end if goale bounces it
 //Goalie snags it
 else{//goalie kick!!
  turnover(*goalie);
  recap << goalie->name << " catches the ball." << endl;
  vector <Player*> emptyvec; pass(emptyvec);//throw it to anybody you can!
  shtbonus = 0;//reset shot bounus
 }//end goalie gets it
}//end shot()

//===========================================================================
//=============================Battle Function===============================
//===========================================================================

bool battle (Player &carrier, vector <Player*> blockers){
 int dodge = 20; int random = rand()%dodge; bool disoriented = false;
 //if(carrier.bonusStat==ENDURANCE){recap << "*";}//got bonus
 //No Defenders
 if (blockers.size() == 0){return true;}

 //Give actual endurance (random) + goalie bonus (maybe)
 int endurance = rstat(carrier, ENDURANCE);//carrier endurance holder
 if(carrier.bonusStat ==ENDURANCE){endurance += rstat(getGoalie(carrier),ENDURANCE); }
 for(int blocker = 0; blocker < blockers.size(); ++blocker){
  tackle_movement(*blockers[blocker],carrier);//hit it!!
  if(random == 0 && !disoriented){//dodge check
   recap << carrier.name << " dodges " << blockers[blocker]->name 
   << "'s attack." << endl; 
  }//end dodge check
  else if(random == 1 && !disoriented){ 
   recap << carrier.name << " dodges " << blockers[blocker]->name
         << "'s attack, but is disoriented." << endl; 
   disoriented = true;
  }
  else{//tackle hits hard
    endurance -= rstat(*blockers[blocker], ATTACK);
    if(blockers[blocker]->bonusStat == ATTACK){ 
      endurance -= rstat(getGoalie(*blockers[blocker]), ATTACK);}
    if(disoriented){endurance = 0;}//Next tackle will strip ball
    if(endurance <= 0){//ball is stripped by this tackler
      recap << blockers[blocker]->name << " hits hard and grabs the ball from " 
          << carrier.name << "!" << endl;
      turnover(*blockers[blocker]);
      shtbonus = 0;
      return false;
    }//end if ball stripped
    else{recap << blockers[blocker]->name << " tackles hard!" 
      << endl; ++shtbonus;}
  }//end tackling
  random = rand()%dodge; --timeleft;
 }//end for each defender in blockers list
 return true;
}//end battle()

//===========================================================================
//=============================Engage Function===============================
//===========================================================================

void engage(){
  Player *carrier = getCarrier();//refresh carrier
  vector <Player*> blockers = fill_blockers();
  vector <Player*> estimateTackle; vector <Player*> estimateBlock;
  int endurance = rstat(*carrier,ENDURANCE);
  if(carrier->bonusStat==ENDURANCE){endurance += rstat(getGoalie(*carrier), ENDURANCE);}

 //How many on defense + Bonus output
  if(blockers.size() > 0){
    for(int blocker = 0; blocker<blockers.size(); ++blocker){
      recap << blockers[blocker]->name <<" ";}
    recap<< "on defense.";
  if(carrier->bonusStat==ENDURANCE){recap << "*";}//got bonus
  recap << endl;
  }////end if there are blockers to fight
 
 //Estimate who to break and who to throw past
 for(int blocker = 0; blocker < blockers.size(); ++blocker){
  endurance -= blockers[blocker]->atk;//blocker "tackles" carrier
  if(endurance > 0){estimateTackle.push_back(blockers[blocker]);}//add to tackler list
  else{estimateBlock.push_back(blockers[blocker]);}//add to blocker list
 }//end for encounter evaluation
  //Physical Vector: END vs ATK
  if(!battle(*carrier, estimateTackle)){recap << endl;return;}
  //you are here if still carrying the ball
  
  //Buzzer Beater
  if(timeleft <= 1){
   recap << "Time is almost up!" << endl;
   shoot(estimateBlock); return;
  }//end buzzer beater
 
  //Still defenders Left
  //Ball Vector: SHT/PAS vs BLK
  if(estimateBlock.size() > 0){//Shoot
    if(test_shot(*carrier, estimateBlock)){shoot(estimateBlock);}//if you had... one shot....one opportunity....
    else{pass(estimateBlock);return;}//end else
}//end if
 
  else{//No Defenders Left: Pass, Shoot, or Dribble
    vector <Player*> upfielders = gatherUpfielders(*carrier);
    if(test_shot(*carrier, estimateBlock)){shoot(estimateBlock);}//end else shoot choice
    else if(upfielders.size()>0){pass(estimateBlock);}//end else if pass choice
    else if(estimateBlock.size() == 0){recap << endl;}
    return;    
  }//end else dribble
}//end engage()

//========================Output Team Lineup================================
void outputTeamLineup(Team &team){
  const string forms[] = {"NORMAL", "JECHT", "CENTER", "WIDE", "SWEEPL",
  "RELAY", "SWEEPR", "CRASHL", "CRESCENT", "CRASHR"};
 	recap<< "Team "<<1+static_cast<int>(team.getTeamNo())<<endl
    <<"Name: "<< team.getName()<<endl
 		<<"Formation: "<<forms[team.getFormation()]<<endl
    <<"Center: " <<team.roster[CN].name<<endl
    <<"Right Forward: "<<team.roster[RF].name<<endl
    <<"Left Forward: "<<team.roster[LF].name<<endl
    <<"Right Defender: "<<team.roster[RD].name<<endl
    <<"Left Defender: "<<team.roster[LD].name<<endl
    <<"Goalie: "<<team.roster[GL].name<<endl<<endl<<endl;
 }//end outputTeamLineup

//===================================================================
//=========================INTERMISSION==============================
//===================================================================
void intermission(){
  Team *teams[2]={&team1, &team2};
  recap << endl << "And that's it for the first half! " << endl;
  Team *leading; Team *trailing;
  if(teams[HOME]->getScore() == teams[AWAY]->getScore()){ 
   recap << "With the score tied at " << teams[HOME]->getScore() 
      << " to " << teams[AWAY]->getScore() << ", this is still anyone's game!"
      << endl << endl; return;//end tie
  }//end if score is tied
  else if(teams[HOME]->getScore() > teams[AWAY]->getScore()){  
    leading = teams[HOME]; trailing = teams[AWAY];
  }//end if team1 score higher
  else {leading = teams[AWAY]; trailing = teams[HOME];}//end vise versa
  //recap score
   recap << "The " << leading->getName() << " lead the " 
         << trailing->getName() << " with a "
         << leading->getScore() << " to " << trailing->getScore() 
         << " lead." << endl
         << "Will the " << trailing->getName() << " be able to catch up?"
         << endl << endl; 
}//end intermissison

//===========================PLAY BALL!==============================
void playBall(Team *teams[]){
  recap << "The ball is released!" << endl
       << getCarrier()->name << " catches the ball." << endl << endl;
  while(timeleft > 0){
    teamNameCheck(" beginning new 'time' instance. ");
    carry_ball(); skirmish(); engage(); ball_refresh();
    randomize_bonuses(*teams);  timeleft -= 2;
  }//wash, rince, goooooaaaaallllllll
}//end playBall()

//===========================TEAM NAME CHECK===========================
//I used this guy to debug.  makes sure no one changes teams
//can be used to verify other things as well, such as only one player having possession

void teamNameCheck(const string prompt){
  vector <string> playerNames;
  Team *teams[2]={&team1, &team2};
  for(int tm=0; tm<2; ++tm){
    for(int teammate = 0; teammate<6; ++teammate){
      if(teams[tm]->getTeamNo() != teams[tm]->roster[teammate].teamNo){
        cout<<"ERROR:  player handling. "  << prompt <<
        "player is on wrong team"<<endl;
        outputTeamLineup(*teams[HOME]);//print test
        outputTeamLineup(*teams[AWAY]);//print test
        getch();
      }
    }
  }
}

//===========================================================================
//==============================Main Function================================
//===========================================================================

int main(){
  Team *teams[]={&team1, &team2};
  srand(time(0));
  int i = 0;
    
 //Declare Team 1   
 while (try_again){
  cout<<"Team 1 "<<endl;
    team_pick(*teams[HOME]);
  }
 //Declare Team 2
 try_again = true;
 while(try_again){
  cout << "Team 2 " << endl;
  team_pick(*teams[AWAY]);
 }

 //Personal name for the file
 string filename = "";
 filename = teams[HOME]->getInitials() + " vs " + teams[AWAY]->getInitials() + ".html";
 recap.open(filename.c_str()); 

 const string homeColor = "<font color=\"#FF0000\">";
 const string awayColor = "<font color=\"#0000FF\">";
 const string font = "</font>";
 team1.setColors(homeColor, font); team2.setColors(awayColor, font);
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
 
 outputTeamLineup(*teams[HOME]);
 outputTeamLineup(*teams[AWAY]);

 //Start the game
 recap << "Welcome to today's game between the " << teams[HOME]->getName() 
       << " and the " << teams[AWAY]->getName() << "!" << endl << endl;
//==========================FIRST HALF=============================== 
 assign_positions(); randomize_bonuses(*teams);
 recap << "*************************************************" << endl
       << "*******************First Half********************" << endl
       << "*************************************************" << endl << endl;
 //Coin Toss. Decide who starts with possession. and goes second 
  turnover(teams[rand()%2]->roster[CN]);//give to that team's center
  teams[HOME]->hasBall()==true? team1starts2nd = false : team1starts2nd = true;
  playBall(teams); //playBALLLLLLLL
  intermission();//HALF TIME SHOW!!!!!!!!
//==========================SECOND HALF==============================
 assign_positions(); timeleft = 300;
 recap << "*****************************************" << endl
       << "***************Second Half***************" << endl
       << "*****************************************" << endl << endl;
       //who start second?
 team1starts2nd? turnover(teams[HOME]->roster[CN]) : turnover(teams[AWAY]->roster[CN]);
 playBall(teams);//let's Blitz!!!

//===================================================================
//==========================FINAL OUTPUT=============================
//===================================================================

  int t1score = teams[HOME]->getScore();//bad code!! bad form1!!
  int t2score = teams[AWAY]->getScore();//no! BAD Loss of privacy!

 recap << "And that buzzer means the game is over!" << endl
        << "And with a final score of " 
        << t1score << " to " << t2score << "," << endl;
       
 if (t1score > t2score){
  recap << "the " << teams[HOME]->getName() << " win!";
 }
 else if (t2score > t1score){
  recap << "the " << teams[AWAY]->getName() << " win!";    
 }
 else {recap << "it's a tie game!";}   

 outputTeamLineup(*teams[HOME]);
 outputTeamLineup(*teams[AWAY]);

 recap << "</pre>" << endl
       << "</body>" << endl
       << "</html>";

 recap.close();
 return 0;
}//fin
