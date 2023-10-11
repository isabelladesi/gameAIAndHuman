#include "Pack.hpp"
#include "Card.hpp"


  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack(){
    for (card.get_suit() = SPADES; suit <= DIAMONDS; suit ++ ){
      sort(card.get_rank());
    }
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input){
    for (int i = 0; i < 52; i++){
      std::istream & operator>>(std::istream pack_input, Card &i);
    }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    return ;
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){

  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){

  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    return;
  }