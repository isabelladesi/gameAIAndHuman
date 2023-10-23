#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Pack.hpp"
#include "Card.hpp"
#include "Player.hpp"
using namespace std;

int main(int argc, char **argv) {
    //open file streams
    ifstream fin;

    string inputFile = argv[1]; // //
    fin.open(inputFile);
  //string outputFile = argv[2]; 

    string SHUFFLE = argv[2];
    int POINTS_TO_WIN = atoi(argv[3]);
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
    if (!(argc == 12)){ //There are exactly 12 arguments, including the executable name.
        cout << "Usage: euchre.exe" << inputFile << SHUFFLE
        << POINTS_TO_WIN << NAME1 << TYPE1 << NAME2 << TYPE2 << NAME3 << TYPE3
        << NAME4 << TYPE4 << endl;
        return 1;
    }
    if (POINTS_TO_WIN < 1 || POINTS_TO_WIN > 100){
        cout << "Usage: euchre.exe" << inputFile << SHUFFLE
        << POINTS_TO_WIN << NAME1 << TYPE1 << NAME2 << TYPE2 << NAME3 << TYPE3
        << NAME4 << TYPE4 << endl;
        return 1;
    }
    if (!(SHUFFLE == "shuffle") || !(SHUFFLE == "no shuffle")){
        cout << "Usage: euchre.exe" << inputFile << SHUFFLE
        << POINTS_TO_WIN << NAME1 << TYPE1 << NAME2 << TYPE2 << NAME3 << TYPE3
        << NAME4 << TYPE4 << endl;
        return 1;
    }
    if (!(TYPE1 == "Simple") || !(TYPE1 == "Human")){
        cout << "Usage: euchre.exe" << inputFile << SHUFFLE
        << POINTS_TO_WIN << NAME1 << TYPE1 << NAME2 << TYPE2 << NAME3 << TYPE3
        << NAME4 << TYPE4 << endl;
        return 1;
    }
    if (!(TYPE2 == "Simple") || !(TYPE2 == "Human")){
        cout << "Usage: euchre.exe" << inputFile << SHUFFLE
        << POINTS_TO_WIN << NAME1 << TYPE1 << NAME2 << TYPE2 << NAME3 << TYPE3
        << NAME4 << TYPE4 << endl;
        return 1;
    }
        if (!(TYPE3 == "Simple") || !(TYPE3 == "Human")){
        cout << "Usage: euchre.exe" << inputFile << SHUFFLE
        << POINTS_TO_WIN << NAME1 << TYPE1 << NAME2 << TYPE2 << NAME3 << TYPE3
        << NAME4 << TYPE4 << endl;
        return 1;
    }

  // Game game(POINTS_TO_WIN, SHUFFLE, NAME1, TYPE1, NAME2, 
  //TYPE2, NAME3, TYPE3, NAME4, TYPE4);
  // game.play();

  // for (size_t i = 0; i < players.size(); ++i) {
  // delete players[i];
  // }
}

class Game {
 public:
  Game(int POINTS_TO_WIN, string SHUFFLE, string NAME1, string TYPE1, string NAME2, 
    string TYPE2, string NAME3, string TYPE3, string NAME4, string TYPE4);

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
      cout << (*players[dealerIndex]).get_name() << " deals"<< endl;
      shuffle(SHUFFLE);
      deal(pack, players);
      Suit trump;
      Card upcard = pack.deal_one();
      cout << upcard << " turned up" << endl;
      int x_playersTurn;
      make_trump(upcard, dealerIndex, players, x_playersTurn);
      playHand(team_tricks_A, team_tricks_B, dealerIndex, trump);
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
      if (dealerIndex > 3) {//what does this thing mean --> {dealer -=4;}
        // printScore(team_points_A,team_points_B);
        cout << player1 << " and " << player3   
        << " have " << team_points_A << " points" << endl;
        cout << player2 << " and "<< player4 
        << " have " << team_points_B << " points" << endl;
      }    
      // printGameResults(team_points_A, team_points_B);
      if (team_points_A > team_points_B){
        cout << player1 << " and " << player3 << " win!" << endl;
      } 
      else {
        cout << player2 << " and " << player4 << " win!" << endl;
      }
    }

 private:
  std::vector<Player*> players;
  Pack pack;
  // ...

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
  void deal(Pack pack, vector<Player*> players){
    for (int i=0; i<players.size(); i++){ //deal round 1 
      if (i%2==0){
        players[i]->add_card(pack.deal_one());
        players[i]->add_card(pack.deal_one());
        players[i]->add_card(pack.deal_one());
      }
      else{
        players[i]->add_card(pack.deal_one());
        players[i]->add_card(pack.deal_one());
      }
    }
    for (int i=0; i<players.size(); i++){ //deal round 2
      if (i%2==0){
        players[i]->add_card(pack.deal_one());
        players[i]->add_card(pack.deal_one());
      }
      else{
        players[i]->add_card(pack.deal_one());
        players[i]->add_card(pack.deal_one());
        players[i]->add_card(pack.deal_one());
      }
    }
  }
  void make_trump(Card &upcard, int dealerIndex, vector<Player*> players, int x_playersTurn){
    Suit upcardSuit = upcard.get_suit(); //suggested trump suit
    Suit order_up_suit;
    bool is_dealer=false;
    int currentPlayer = dealerIndex; //is dealer alwyas player 0? does it change with rounds?
    for(int round = 1; round <3; round++){
      for(int i=0; i< players.size(); i++){ //changing indexes
        currentPlayer+=1;
        if(currentPlayer>3){
          currentPlayer-=4;
        }
        if (dealerIndex == currentPlayer){
          is_dealer = true;
        }

        if(players[currentPlayer]->make_trump(upcard, is_dealer, round, order_up_suit)==false){ //should i access players w a * here too?
          cout << (*players[i]).get_name() << " passes" << endl;
        }
        else if(players[currentPlayer]->make_trump(upcard, is_dealer, round, order_up_suit)==true && round==1){
          cout << (*players[currentPlayer]).get_name() << " orders up " << order_up_suit << endl;
          x_playersTurn = currentPlayer;
          (*players[dealerIndex]).add_and_discard(upcard);
          //return;
        }
        else if(players[currentPlayer]->make_trump(upcard, is_dealer, round, order_up_suit)==true && round==2){
          cout << (*players[currentPlayer]).get_name() << " orders up " << order_up_suit << endl; //does my make trump account for dealer stuff? add tests abt it?
          x_playersTurn = currentPlayer;
          cout << "\n";
          //return;
        }
      }
    }
  }
  }; 
//   void play_hand(/* ... */);
//   // ...
// };


//---------------------------------------------

  // argc is argument count. integer representing how many arguments were 
  //implemente din command line. ./resize.exe arg1 arg2 arg3. argc=4
  // argv is an array of pointers that point to c style strings. if you wanna 
  //access that fist argument do:argv[1] returns a c style string