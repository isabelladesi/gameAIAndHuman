#include "Pack.hpp"
#include "Card.hpp"
#include <array>


  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack(){
    int x = 0;
    next = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s) {
      Suit suit = static_cast<Suit>(s);

      for (int r = NINE; r <= ACE; ++r) {
        Rank rank = static_cast<Rank>(r);
        Card rankSuit = Card(rank, suit);
        cards[x] = rankSuit;
        x = x+1;
      }
    }
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input){
    Card i;
    int x = 0;
    next = 0;
    while (pack_input >> i){
        cards[x] = i;
        x = x + 1;
      }
    }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    Card dealOne = cards[next];
    next = next + 1;
    return dealOne;
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
    Card pack1[PACK_SIZE/2];
    Card pack2[PACK_SIZE/2];
    int j;

    for(int i=0; i<cards.size()/2; i++){
      pack1[i] = cards[i];
      pack2[i] = cards[i+cards.size()/2];
    }

    for(int nShuffle=0; nShuffle<7; nShuffle++){
      j=0;
      while (j<cards.size()/2){
        for(int i=0; i<cards.size(); i=i+2){
          cards[i] = pack2[j];
          cards[i+1]= pack1[j];
          j++;
        }
      }
      for(int i=0; i<cards.size()/2; i++){
        pack1[i] = cards[i];
        pack2[i] = cards[i+cards.size()/2];
      }
    }
    next = 0;   
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    if (next == 24){
      return true;
    }
    else{
      return false;
    }
  }