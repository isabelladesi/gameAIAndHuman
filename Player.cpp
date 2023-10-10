#include "Player.hpp"
#include "Card.hpp"
#include <cassert>
#include <string>
#include <vector>

using namespace std;

// Player * Player_factory(const string &name, const string &strategy) {
//   assert(false);
// }

ostream & operator<<(ostream &os, const Player &p) {
  assert(false);
}

class SimplePlayer : public Player{
    public:
    
    SimplePlayer(const string player_name): Player() {}    //pass hand size to be 5??
    //does player_name name matter? cause it works if player_name is just name. which do i return player_name or name? r they the same?

    const string & get_name() const override{
        return player_name;

    }
    
    void add_card(const Card &c) override{
        // add requires asset?
        hand.push_back(&c);
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
                currentCard = *hand.at(i);
                currentCardSuit = currentCard.get_suit();
                if(currentCardSuit == upcardSuit && currentCard.is_face_or_ace() == true){
                    valuableCards++;
                }
            }


            if (valuableCards >=2){
                order_up_suit = upcardSuit;
                return true;
            }
            // else{
            //     return false;
            // }
        } //get suit takes in trump suit as an input

        else if(round == 2){
            for (int i=0; i < hand.size(); i++){
                currentCard = *hand.at(i);
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
            // else{
            //     return false;
            // }


        }
        return false;
    }

    void add_and_discard(const Card &upcard) override{
        assert(hand.size() >=1);
        hand.pop_back();
        hand.push_back(&upcard);

    }

    Card lead_card(Suit trump) override{
        assert(hand.size() >=1);
        Card leadCard;
        Card trumpLeadCard;
        Card currentCard;
        Suit currentCardSuit;
        int rank;
        int highestRank = 0;
        int trumpHighestRank = 0;
        int numTrumpCardsInHand = 0;
        int indexLeadCard;
        int indexTrumpLeadCard;

        //traversing the hand
        for (int i=0; i < hand.size(); i++){
                currentCard = *hand.at(i);
                currentCardSuit = currentCard.get_suit();
                rank = currentCard.get_rank();

                if(currentCardSuit != trump){
                    if (rank > highestRank){
                        highestRank = rank;
                        leadCard = currentCard;
                        indexLeadCard = i;
                    }
                }
                else{
                    numTrumpCardsInHand++;
                    if(rank > trumpHighestRank){
                        trumpHighestRank = rank;
                        trumpLeadCard = currentCard;
                        indexTrumpLeadCard = i;
                    }
                }
            }

            if(numTrumpCardsInHand == hand.size()){ //all cards in hand are trump cards
                hand.erase(hand.begin() + indexTrumpLeadCard);
                return trumpLeadCard;
            }
            else {
                hand.erase(hand.begin() + indexLeadCard);
                return leadCard;
            }

            //test: highest rank being at edges. diff orders of trump and nontrump cards
    }

    Card play_card(const Card &led_card, Suit trump) override{
        assert(hand.size() >=1);
        Card playCard;
        Card playCardDiffSuit;
        Card leadCard = lead_card(trump);
        Suit leadCardSuit = leadCard.get_suit();
        Card currentCard;
        Suit currentCardSuit;
        int rank;
        int highestRankSameSuit = 0;
        int indexSameSuit;
        int numOfDiffSuitCards;
        int lowestRankDiffSuit = 15;
        int indexLowestDiffSuitCard;
        
        for (int i=0; i < hand.size(); i++){
            currentCard = *hand.at(i);
            currentCardSuit = currentCard.get_suit();
            rank = currentCard.get_rank();
            if(currentCardSuit == leadCardSuit){
                if(rank > highestRankSameSuit){
                    highestRankSameSuit = rank;
                    playCard = currentCard;
                    indexSameSuit = i;
                }
            }
            else{
                numOfDiffSuitCards++;
                if(rank < lowestRankDiffSuit){
                        lowestRankDiffSuit = rank;
                        playCardDiffSuit = currentCard;
                        indexLowestDiffSuitCard = i;
                    }
            }

        }
        //player does not have same suit as lead card in their hand, so plays lowest card
        if(numOfDiffSuitCards == hand.size()){ 
            hand.erase(hand.begin() + indexLowestDiffSuitCard);
            return playCardDiffSuit;
        }
        else {
            hand.erase(hand.begin() + indexSameSuit);
            return playCard;
        }

    }

    private:
    const string player_name; 
    vector<const Card *> hand;

};

//  void SimplePlayer::SimplePlayer(const std::string& player_name, vector<Card> v, int playersHand ){
//  }

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
//   if (strategy == "Human") {
//     return new HumanPlayer(name);
//   }  
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}