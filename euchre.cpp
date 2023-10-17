#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  // Read command line args and check for errors
  Game game(/* game details */);
  game.play();

  for (size_t i = 0; i < players.size(); ++i) {
  delete players[i];
}
}

class Game {
 public:
  Game(POINTS_TO_WIN, NAME1, TYPE1, NAME2, TYPE2, NAME3, TYPE3, NAME4, TYPE4);
  void play();

 private:
  std::vector<Player*> players;
  Pack pack;
  // ...

  void shuffle();
  void deal(/* ... */);
  void make_trump(/* ... */);
  void play_hand(/* ... */);
  // ...
};


//---------------------------------------------

#include <iostream>
#include <fstream>
#include "Matrix.hpp"
#include "Image.hpp"
#include "processing.hpp"
using namespace std;

int main(int argc, char *argv[]) {
  //open file streams
  ifstream fin;

  string inputFile = argv[1]; // //
  fin.open(inputFile);
  //string outputFile = argv[2]; 

  //ofstream fout(outputFile);
  //initialze image
  Image* img = new Image;
  Image_init(img, fin);
  int originalWidth = Image_width(img);
  int originalHeight = Image_height(img);

  int desiredWidth = atoi(argv[3]);
  int desiredHeight = originalHeight;
  if (argc == 5){
    desiredHeight = atoi(argv[4]);
  }

//  fin.open(originalPPM); //fin.open(argv[1]);

  if (!fin.is_open()) {
  cout << "Error opening file: " << inputFile << endl;;
  return 1;
  }
  
  // argc is argument count. integer representing how many arguments were implemente din command line. ./resize.exe arg1 arg2 arg3. argc=4
  // argv is an array of pointers that point to c style strings. if you wanna access that fist argument do:argv[1] returns a c style string

  if (argc < 4 || argc > 5 ){ //The desired width is greater than 0 and less than or equal to the original width of the input image.
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     delete img;
     return 1;
  }
  if (desiredWidth < 0 && desiredWidth > originalWidth){
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     delete img;
     return 1;
  }
  if(desiredHeight < 0 && desiredHeight > originalWidth){
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     delete img;
     return 1;
  }

  ofstream fout(argv[2]);

  if (!fout.is_open()) {
  cout << "Error opening file: " << inputFile << endl;
  delete img;
  return 1;
  }

  seam_carve(img, desiredWidth, desiredHeight);
  Image_print(img, fout);
  delete img;
  return 0;


  }