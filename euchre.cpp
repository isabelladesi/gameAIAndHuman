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

  void print_winners(int team_tricks_A, int team_tricks_B, 
   int &team_points_A, int &team_points_B, int ordered_up){
    if (team_tricks_A > team_tricks_B){
    // print0Winners(team_tricks_A, ordered_up, team_points_A);
      team_points_A = team_points_A + 1;
      cout << players[0]->get_name() << " and " 
       << players[2]->get_name() << " win the hand" << endl;
      if (ordered_up % 2 != 0){
        team_points_A = team_points_A + 2;
        cout << "euchred!" << endl;
      } 
      else if (team_tricks_A == 5){
        team_points_A = team_points_A + 2;
        cout << "march!" << endl;
      }
    }
    else if (team_tricks_B > team_tricks_A){
      // print1Winners(team_tricks_B, ordered_up, team_points_B);
      team_points_B = team_points_B + 1;
      cout << players[1]->get_name() << " and " 
       << players[3]->get_name() << " win the hand" << endl;
      if (ordered_up % 2 != 0){
        team_points_B = team_points_B + 2;
        cout << "euchred!" << endl;
      } 
      else if (team_tricks_B == 5){
        team_points_B = team_points_B + 2;
        cout << "march!" << endl;
      }
    }
  }

  //this is mainly copied so change this a lot
  void play(int POINTS_TO_WIN, vector<Player*> players, string SHUFFLE){
    int team_points_A = 0; 
    int team_points_B = 0;
    int hand_round = 0;
    int dealerIndex = 0;
    int ordered_up = 0;
    int team_tricks_A = 0;
    int team_tricks_B = 0;
    const string* player1 = &(*players[0]).get_name();
    const string* player2 = &(*players[1]).get_name();
    const string* player3 = &(*players[2]).get_name();
    const string* player4 = &(*players[3]).get_name();
    while (team_points_A < POINTS_TO_WIN && team_points_B < POINTS_TO_WIN){
      cout << "Hand " << hand_round << endl;
      cout << players[dealerIndex]->get_name() << " deals"<< endl; 
      shuffle(SHUFFLE);
      deal(pack, players, dealerIndex);
      // Suit trump;
      // Card upcard = pack.deal_one();
      cout << upcard << " turned up" << endl;
      trump = upcard.get_suit();
      Suit ordered_up_suit;
      make_trump(upcard, dealerIndex, players, ordered_up_suit);
      indexOfPrevWinner = 10;
      for (int i = 0; i < 5; i++){
        play_trick(dealerIndex, team_tricks_A, team_tricks_B, 
         indexOfPrevWinner);
      }
      //5 tricks have finished, this round is finished, update team points here
      print_winners(team_tricks_A, team_tricks_B, team_points_A, 
       team_points_B, ordered_up); 
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
    }
  }


 private:
  std::vector<Player*> players;
  int indexOfPrevWinner;
  Pack pack;
  string SHUFFLE;
  int POINTS_TO_WIN;
  Card upcard;
  Suit trump;

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
  void deal(Pack pack1, vector<Player*> players, int indexOfDealer){
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
  void make_trump(Card &upcard, int dealerIndex, 
   vector<Player*> players, Suit &ordered_up_suit){
    //Suit order_up_suit;
    bool is_dealer;
    int currentPlayer;
    for(int round = 1; round <3; round++){
      for(int i=0; i< players.size(); i++){ 

        currentPlayer =(i+1+dealerIndex)%4; 
        if (players[currentPlayer] == players[dealerIndex]){
          is_dealer = true;
        }
        else{
          is_dealer = false;
        }
        bool decision = players[currentPlayer]->
         make_trump(upcard, is_dealer, round, ordered_up_suit);
        
        if(decision==false){ //should i access players w a * here too?
          cout << players[currentPlayer]->get_name() 
           << " passes" << endl; // (*players[i]).get_name() 
        }
        else if(round==1){
          cout << players[currentPlayer]->get_name() 
           << " orders up " << ordered_up_suit << endl;
          // x_playersTurn = currentPlayer;
          trump = ordered_up_suit;
          //PRINT DEALERS HAND
          players[dealerIndex]->add_and_discard(upcard);

          return;
        }
        else {
          cout << players[currentPlayer]->get_name() 
           << " orders up " << ordered_up_suit << endl; 
          // x_playersTurn = currentPlayer;
          trump = ordered_up_suit;
          cout << "\n";
          return;
        }
      }
    }
  }
    void play_trick(int dealerIndex, int &team_tricks_A, 
     int &team_tricks_B, int winnerLastRound){
      //eldest hand index
      //vector<Card> AllCardsPlayed;

      Card ledCard;
      Card playedCard;
      int leadPlayerIndex;
      //int indexOfWinningPlayer;//?****
      int currentPlayer;
      if (winnerLastRound==10){
        leadPlayerIndex = (dealerIndex+1)%4; 
        ledCard = players[leadPlayerIndex]->lead_card(trump); 
      }
      else {
        leadPlayerIndex = winnerLastRound;
        ledCard = players[leadPlayerIndex]->lead_card(trump);
         
      }

      Card highest = ledCard;
      string playerWithHighestCard;
      //int indexOfWinningPlayer;

      cout << ledCard << " led by " << 
       players[leadPlayerIndex]->get_name() << endl;
      for (int i=leadPlayerIndex+1; i<leadPlayerIndex+4; i++){
        currentPlayer = i % 4; //maybe???
        playedCard = (players[currentPlayer])
         ->play_card(ledCard, trump);
        cout << playedCard << " played by " 
         << players[currentPlayer]->get_name()<<endl; 

        //track the max card in this for loop along with the name
        if(Card_less(highest, playedCard, ledCard, trump)){
          highest = playedCard;
          playerWithHighestCard = players[currentPlayer]
           ->get_name();
          indexOfPrevWinner = currentPlayer;

        }
      }
      //update team A or team B tricks here
      if (leadPlayerIndex % 2 == 0) {
        team_tricks_A = team_tricks_A + 1;
      }
      else {
        team_tricks_B = team_tricks_B + 1;
      }
      
      cout << playerWithHighestCard 
       << " takes the trick" << "\n" << endl;


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
  if (!fin.is_open()) { 
    cout << "Error opening " << inputFile << endl;;
    return 1;
  }
  if (!(argc == 12)){ //There are exactly 12 arguments
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