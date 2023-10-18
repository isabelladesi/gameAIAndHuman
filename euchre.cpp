#include <iostream>
#include <fstream>
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
    if (argc == 12){ //There are exactly 12 arguments, including the executable name.
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

  Game game(POINTS_TO_WIN, SHUFFLE, NAME1, TYPE1, NAME2, TYPE2, NAME3, TYPE3, NAME4, TYPE4);
  game.play();

  for (size_t i = 0; i < players.size(); ++i) {
  delete players[i];
  }
}

class Game {
 public:
  Game(int POINTS_TO_WIN, string SHUFFLE, string NAME1, string TYPE1, string NAME2, 
    string TYPE2, string NAME3, string TYPE3, string NAME4, string TYPE4);
  void play();

 private:
  std::vector<Player*> players;
  Pack pack;
  // ...

  void shuffle();
  void deal(/* ... */);
  void make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit);
  void play_hand(/* ... */);
  // ...
};


//---------------------------------------------

  // argc is argument count. integer representing how many arguments were implemente din command line. ./resize.exe arg1 arg2 arg3. argc=4
  // argv is an array of pointers that point to c style strings. if you wanna access that fist argument do:argv[1] returns a c style string