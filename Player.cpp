#include "Player.hpp"
#include "Card.hpp"
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Player * Player_factory(const string &name, const string &strategy) {
//   assert(false);
// }



void sortHand_byRank_ascending(vector<Card> hand){
    vector<Card> hand_Sorted;
    int n = hand.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (hand.at(j).get_rank() > hand.at(j+1).get_rank()) {
              	// Card temp = hand.at(j);
              	// hand.at(j) = hand.at(j+1);
                // hand.at(j+1) = temp;
                swap(hand.at(j), hand.at(j+1));
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
  //  return hand_Sorted;

}

class SimplePlayer : public Player{
    public:
    
    //SimplePlayer(const string& player_name): Player() {}    //pass hand size to be 5??
    //does player_name name matter? cause it works if player_name is just name. which do i return player_name or name? r they the same?

    SimplePlayer(string name) : player_name(name) {
   // hand.resize(5);
    }

    const string & get_name() const override{
        return player_name;

    }
    
    void add_card(const Card &c) override{
        // add requires asset?
        hand.push_back(c);
        sort(hand.begin(), hand.end());
    }

    bool make_trump (const Card &upcard, bool is_dealer,int round, Suit &order_up_suit) const override{
        assert(round == 1 || round ==2);

        Suit upcardSuit = upcard.get_suit();
        int valuableCards = 0;
        Card currentCard;
        Suit currentCardSuit;

        if (round == 1){
            //traversing the hand
            for (int i=0; i < hand.size(); i++){
                currentCard = hand.at(i);
                currentCardSuit = currentCard.get_suit();
                if(currentCardSuit == upcardSuit && currentCard.is_face_or_ace() == true){
                    valuableCards++;
                }
            }


            if (valuableCards >=2){
                order_up_suit = upcardSuit;
                return true;
            }
       
        } //get suit takes in trump suit as an input

        else if(round == 2){
            for (int i=0; i < hand.size(); i++){
                currentCard = hand.at(i);
                currentCardSuit = currentCard.get_suit();

                if(currentCardSuit == Suit_next(upcardSuit) && currentCard.is_face_or_ace() == true){
                    valuableCards++;
                }
            }

            if (valuableCards >=1){
                order_up_suit = Suit_next(upcardSuit);
                return true;
            }
            else if(is_dealer==true){ //screw the dealer
                order_up_suit = Suit_next(upcardSuit); //order up any suit
                return true;
            }
          


        }
        return false;
    }

    void add_and_discard(const Card &upcard) override{
        assert(hand.size() >=1);
        hand.erase(hand.begin());
        hand.push_back(upcard); //any card?
        sort(hand.begin(), hand.end());

    }

    Card lead_card(Suit trump) override{
        assert(hand.size() >=1);
        Card leadCard;

        Card currentCard;
        Suit currentCardSuit;
    
        int indexLeadCard;
  

        //traversing the hand
        for (int i=hand.size()-1; i>-1; i--){
                currentCard = hand.at(i);
                currentCardSuit = currentCard.get_suit();

                if(currentCardSuit != trump){
                    indexLeadCard = i;
                    leadCard = currentCard;

                    hand.erase(hand.begin() + indexLeadCard);
                    return leadCard;
      
                }
     
            }


            leadCard = hand.at(hand.size()-1);
            hand.erase(hand.begin() + hand.size()-1);
            return leadCard;
            
            //test: highest rank being at edges. diff orders of trump and nontrump cards
    }

    Card play_card(const Card &led_card, Suit trump) override{
        assert(hand.size() >=1);
        Card playCard;

        Suit leadCardSuit = led_card.get_suit();
        Card currentCard;
        Suit currentCardSuit;


        int indexPlayCard;

      //  sortHand_byRank_ascending(hand);
        
        for (int i=hand.size()-1; i>-1; i--){
            currentCard = hand.at(i);
            currentCardSuit = currentCard.get_suit();
          //  rank = currentCard.get_rank();
            if(currentCardSuit == leadCardSuit){
                indexPlayCard = i;
                playCard = currentCard;

                hand.erase(hand.begin() + indexPlayCard);
                return playCard;
            }
    

        }
        playCard = hand.at(0);
        hand.erase(hand.begin() + hand.size()-1);
        
        return playCard;

    }

    private:
    const string player_name; 
    vector<Card> hand;
    //vector<const Card *> hand;

};

ostream & operator<<(ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}

class HumanPlayer : public Player{
    public:



    HumanPlayer(const string& name) : player_name(name) {
  //  hand.resize(5);
    }
    const string & get_name() const override{
        return player_name;

    }
    void add_card(const Card &c) override{
        // add requires asset?
        hand.push_back(c);
        sort(hand.begin(), hand.end());
    }
    bool make_trump (const Card &upcard, bool is_dealer,int round, Suit &order_up_suit) const override{
        assert(false);
    }

    void add_and_discard(const Card &upcard) override{
        assert(hand.size() >=1);
        hand.erase(hand.begin());
        hand.push_back(upcard); //any card?
        sort(hand.begin(), hand.end());

    }
    Card lead_card(Suit trump) override{
        assert(false);
    }
    Card play_card(const Card &led_card, Suit trump) override{
        assert(false);
    }

    private:
    const string player_name; 
    vector<Card> hand;
    //vector<const Card *> hand;

};

//  void SimplePlayer(const std::string& player_name, vector<Card> v, int playersHand ){
//     playerName(player_name);
//  }
// SimplePlayer::SimplePlayer(const std::string& name) : player_name(name) {
//     hand.resize(5);
//     // The constructor initializes playerName with the provided name.
//     // hand is initialized as an empty vector of const Card objects.
// }



Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  if (strategy == "Human") {
    return new HumanPlayer(name);
  }  
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}