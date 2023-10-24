#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Pack.hpp"
#include "Card.hpp"
#include "Player.hpp"
using namespace std;

class Game {
 public:
  Game(int points_to_win, string shuffle, vector<Player*> playersPlay, Pack packPlay){
    players = playersPlay;
    pack = packPlay;
    POINTS_TO_WIN = points_to_win;
    SHUFFLE = shuffle;
  }

  //this is mainly copied so change this a lot
  void play(int POINTS_TO_WIN, vector<Player*> players, string SHUFFLE){
    int team_points_A = 0; 
    int team_points_B = 0;
    int hand_round = 0;
    int dealerIndex = 0;
    int leadIndex = dealerIndex + 1;
    int ordered_up = 0;
    int team_tricks_A = 0;
    int team_tricks_B = 0;
    const string* player1 = &(*players[0]).get_name();
    const string* player2 = &(*players[1]).get_name();
    const string* player3 = &(*players[2]).get_name();
    const string* player4 = &(*players[3]).get_name();
    while (team_points_A < POINTS_TO_WIN && team_points_B < POINTS_TO_WIN){
      cout << "Hand " << hand_round << endl;
      cout << players[dealerIndex]->get_name() << " deals"<< endl; //(*players[dealerIndex]).get_name()
      shuffle(SHUFFLE);
      deal(pack, players, dealerIndex);
      Suit trump;
      // Card upcard = pack.deal_one();
      cout << upcard << " turned up" << endl;
      trump = upcard.get_suit();
      int x_playersTurn=0;
      make_trump(upcard, dealerIndex, players, x_playersTurn);
      // playHand(team_tricks_A, team_tricks_B, dealerIndex, trump);
      // if (leadIndex > 3){
      //   leadIndex = leadIndex - 4;
      // }
      indexOfPrevWinner = 10;
      for (int i = 0; i < 5; i++){
        play_trick(dealerIndex, trump, team_points_A, team_points_B, indexOfPrevWinner);
        if (leadIndex % 2 == 0) {
          team_tricks_A = team_tricks_A + 1;
        }
        else {
          team_tricks_B = team_tricks_B + 1;
        }
      }
      if (team_tricks_A > team_tricks_B){
        // print0Winners(team_tricks_A, ordered_up, team_points_A);
        team_points_A = team_points_A + 1;
        cout << player1 << " and " << player3 << " win the hand" << endl;
        if (ordered_up % 2 != 0){
          team_points_A = team_points_A + 1;
          cout << "euchred!" << endl;
        } 
        else if (team_tricks_A == 5){
          team_points_A = team_points_A + 1;
          cout << "march!" << endl;
        }
      }
      else if (team_tricks_B > team_tricks_A){
        // print1Winners(team_tricks_B, ordered_up, team_points_B);
        team_points_B = team_points_B + 1;
        cout << player2 << " and " << player4 << " win the hand" << endl;
        if (ordered_up % 2 != 0){
          team_points_B = team_points_B + 1;
          cout << "euchred!" << endl;
        } 
        else if (team_tricks_B == 5){
          team_points_B = team_points_B + 1;
          cout << "march!" << endl;
        }
      } 
    } 
      hand_round = hand_round + 1;
      dealerIndex = dealerIndex + 1;
      if (dealerIndex > 3) {//what does this thing mean --> {
        dealerIndex = dealerIndex - 4;
        // printScore(team_points_A,team_points_B);
        cout << player1 << " and " << player3   
        << " have " << team_points_A << " points" << endl;
        cout << player2 << " and "<< player4 
        << " have " << team_points_B << " points" << endl;
      }    
      // printGameResults(team_points_A, team_points_B);
      if (team_points_A > team_points_B){
        cout << player1 << " and " << player3 << " win the hand" << endl;
      } 
      else {
        cout << player2 << " and " << player4 << " win the hand" << endl;
      }
    }

 private:
  std::vector<Player*> players;
  int indexOfPrevWinner;
  Pack pack;
  string SHUFFLE;
  int POINTS_TO_WIN;
  Card upcard;

  void shuffle(string SHUFFLE) {
    if (SHUFFLE == "shuffle") {
      pack.shuffle();
    } 
    else {
      pack.reset();
    } 
    return;
  }
  //   pack.shuffle();
  void deal(Pack pack1, vector<Player*> players, int indexOfDealer){ //cant i delete pack1 and just use pack private variable?
    int currentPlayer;
    bool hasBeenDealt = false;
    for (int i=0; i<players.size(); i++){ //deal round 1 
    currentPlayer =(i+1+indexOfDealer)%4;
      if ((hasBeenDealt)==false){
        players[currentPlayer]->add_card(pack1.deal_one());
        players[currentPlayer]->add_card(pack1.deal_one());
        players[currentPlayer]->add_card(pack1.deal_one());
        hasBeenDealt = true;
      }
      else{
        players[currentPlayer]->add_card(pack1.deal_one());
        players[currentPlayer]->add_card(pack1.deal_one());
        hasBeenDealt = false;
      }
    }
    hasBeenDealt=false;
    currentPlayer=0;
    for (int i=0; i<players.size(); i++){ //deal round 2
    currentPlayer =(i+1+indexOfDealer)%4;
      if ((hasBeenDealt)==false){
        players[currentPlayer]->add_card(pack1.deal_one());
        players[currentPlayer]->add_card(pack1.deal_one());
        hasBeenDealt = true;
      }
      else{
        players[currentPlayer]->add_card(pack1.deal_one());
        players[currentPlayer]->add_card(pack1.deal_one());
        players[currentPlayer]->add_card(pack1.deal_one());
        hasBeenDealt = false;
      }
    }
    upcard = pack1.deal_one();

  }
  void make_trump(Card &upcard, int dealerIndex, vector<Player*> players, int x_playersTurn){
    Suit order_up_suit;
    bool is_dealer;
   // new Player currentPlayer; //= dealerIndex; //is dealer alwyas player 0? does it change with rounds?
    int currentPlayer;
    for(int round = 1; round <3; round++){
      for(int i=0; i< players.size(); i++){ //changing indexes (1+i)%4

        currentPlayer =(i+1+dealerIndex)%4; // ELDEST HAND FORMULA (LEFT OF DEALER)
        if (players[currentPlayer] == players[dealerIndex]){
          is_dealer = true;
        }
        else{
          is_dealer = false;
        }

        if(players[currentPlayer]->make_trump(upcard, is_dealer, round, order_up_suit)==false){ //should i access players w a * here too?
          cout << players[currentPlayer]->get_name() << " passes" << endl; // (*players[i]).get_name() 
        }
        else if(players[currentPlayer]->make_trump(upcard, is_dealer, round, order_up_suit)==true && round==1){
          cout << players[currentPlayer]->get_name() << " orders up " << order_up_suit << endl;
          x_playersTurn = currentPlayer;
          
          //PRINT DEALERS HAND
          players[dealerIndex]->add_and_discard(upcard);

          return;
        }
        else if(players[currentPlayer]->make_trump(upcard, is_dealer, round, order_up_suit)==true && round==2){
          cout << (*players[currentPlayer]).get_name() << " orders up " << order_up_suit << endl; //does my make trump account for dealer stuff? add tests abt it?
          x_playersTurn = currentPlayer;
          cout << "\n";
          gitreturn;
        }
      }
    }
  }
    void play_trick(int dealerIndex, Suit trump, int team1points, int team2points, int winnerLastRound){
      //eldest hand index
      //vector<Card> AllCardsPlayed;

      Card ledCard;
      Card playedCard;
      int leadPlayerIndex;
      //int indexOfWinningPlayer;//?****
      int currentPlayer;
      if (winnerLastRound==10){//(team1points ==0 && team2points==0){ //no one won previous round aka first round
        leadPlayerIndex = (dealerIndex+1)%4; //lead player only next to dealer in first round. future rounds it will be the player that wins the previous trick
        ledCard = players[leadPlayerIndex]->lead_card(trump); //same thing as playing the card //max card
      }
      else {
        leadPlayerIndex = winnerLastRound; //make a function that returns index of player who won last round and put it in the if(card_less_) statement
      }

      Card highest = ledCard;
      string playerWithHighestCard;
      //int indexOfWinningPlayer;

      cout << ledCard << " led by " << endl;
      for (int i=0; i<players.size()-1; i++){
        currentPlayer = leadPlayerIndex+1+i; //maybe???
        playedCard = (players[currentPlayer])->play_card(ledCard, trump);//(*players[currentPlayer]).play_card(ledCard,trump);
        //AllCardsPlayed.push_back(playedCard);
        cout << playedCard << " played by " << players[currentPlayer]->get_name()<<endl; //(*players[currentPlayer]).get_name() << endl;

        //track the max card in this for loop along with the name . led crad < current card ...
        if(Card_less(highest, playedCard, ledCard, trump)){
          highest = playedCard;
          playerWithHighestCard = players[currentPlayer]->get_name();
          //leadPlayerIndex = currentPlayer;
          //indexOfWinningPlayer = currentPlayer; // >***
          indexOfPrevWinner = currentPlayer;

        }
      }
      //  Card highest = AllCardsPlayed[0];
      //  int cardHighestIndex;

      // for (int i = 1; i < 4; i++){
      //   if(Card_less(highest, AllCardsPlayed[i], ledCard, trump)) {
      //     highest = AllCardsPlayed[i];
      //     cardHighestIndex = i;
      //   }
      // }
      // int trickWinner;
      // trickWinner = (leadPlayerIndex + cardHighestIndex)%4;
      cout << playerWithHighestCard << " takes the trick" << "\n" << endl;


    }
  };

  int main(int argc, char **argv) {
  //open file streams
  ifstream fin;

  string inputFile = argv[1]; // //
  fin.open(inputFile);
  //string outputFile = argv[2]; 

  string SHUFFLE = argv[2];
  int POINTS_TO_WIN = atoi(argv[3]);
  Pack deck(fin);
  string NAME1 = argv[4];
  string TYPE1 = argv[5];
  string NAME2 = argv[6];
  string TYPE2 = argv[7];
  string NAME3 = argv[8];
  string TYPE3 = argv[9];
  string NAME4 = argv[10];
  string TYPE4 = argv[11];
  //-------------------------------
  if (!fin.is_open()) { //ADD COUT STATEMENTS TO ALL OF THEM AND SEE WHICH ONES ARENT WORKING!!!!!!
    cout << "Error opening " << inputFile << endl;;
    return 1;
  }
  if (!(argc == 12)){ //There are exactly 12 arguments, including the executable name.
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    return 1;
  }
  if (POINTS_TO_WIN < 1 || POINTS_TO_WIN > 100){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    return 1;
  }
  if (!((SHUFFLE == "shuffle") || (SHUFFLE == "noshuffle"))){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    return 1;
  }
  if (!((TYPE1 == "Simple") || (TYPE1 == "Human"))){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     
    return 1;
  }
  if (!((TYPE2 == "Simple") || (TYPE2 == "Human"))){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    return 1;
  }
  if (!((TYPE3 == "Simple") || (TYPE3 == "Human"))){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    return 1;
  }

  for (int i = 0; i < 12; i++){
    cout << argv[i] << " ";
  }
  cout << endl;

  //vector<Player*> players = {&NAME1, &NAME2, &NAME3, &NAME4};
  // vector<Player*> players;
  // players.push_back(&NAME1);
  // players.push_back(&NAME2);
  // players.push_back(&NAME3);
  // players.push_back(&NAME4); //NAME's are not players

  vector<Player*> players;
  for(int i = 4; i <= 10; i += 2){
    Player * playerTemp = Player_factory(argv[i],argv[i+1]);
    players.push_back(playerTemp);
  }

  Game game(POINTS_TO_WIN, SHUFFLE, players, deck);
  game.play(POINTS_TO_WIN, players, SHUFFLE);

  for (size_t i = 0; i < players.size(); ++i) {
    delete players[i];
  }
} 
  //this is the right file

//---------------------------------------------

  // argc is argument count. integer representing how many arguments were 
  //implemente din command line. ./resize.exe arg1 arg2 arg3. argc=4
  // argv is an array of pointers that point to c style strings. if you wanna 
  //access that fist argument do:argv[1] returns a c style string