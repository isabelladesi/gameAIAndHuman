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



// void sortHand_byRank_ascending(vector<Card> hand){
//     vector<Card> hand_Sorted;
//     int n = hand.size();
//     bool swapped;
//     for (int i = 0; i < n - 1; i++) {
//         swapped = false;
//         for (int j = 0; j < n - i - 1; j++) {
//             if (hand.at(j).get_rank() > hand.at(j+1).get_rank()) {
//               	// Card temp = hand.at(j);
//               	// hand.at(j) = hand.at(j+1);
//                 // hand.at(j+1) = temp;
//                 swap(hand.at(j), hand.at(j+1));
//                 swapped = true;
//             }
//         }
//         if (swapped == false)
//             break;
//     }
//    //return hand_Sorted;

// }

vector<Card> sortReal(vector<Card> hand, Suit trump){
    sort(hand.begin(), hand.end());
    int indexLB=-1;
    int indexRB=-1;
    for(int i=0; i<hand.size(); i++){
        if(hand[i].is_left_bower(trump)){
            indexLB =i;
            // hand.push_back(hand[i]);
            // hand.erase(hand.begin() + i);
        }
        if (hand[i].is_right_bower(trump)){
            indexRB=i;
            // hand.push_back(hand[i]);
            // hand.erase(hand.begin() + i);
        }
    }
    if(indexLB!=-1){ //there is a LB
        hand.push_back(hand[indexLB]);
        hand.erase(hand.begin() + indexLB);
    }

    if(indexRB != -1){ //there is a RB
        hand.push_back(hand[indexRB]);
        hand.erase(hand.begin() + indexRB);
    }

    return hand;

}

class SimplePlayer : public Player{
    public:
    
    //SimplePlayer(const string& player_name): Player() {}    //pass hand size to be 5??
    //does player_name name matter? cause it works if player_name is just name. 
    //which do i return player_name or name? r they the same?

    SimplePlayer(string name) : player_name(name) {
   // hand.resize(5);
    }

    const string & get_name() const override{
        return player_name;

    }
    
    void add_card(const Card &c) override{
        hand.push_back(c);
        sort(hand.begin(), hand.end());
    }

    bool make_trump (const Card &upcard, bool is_dealer,
        int round, Suit &order_up_suit) const override{
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
                else if(currentCard.is_left_bower(upcardSuit)){
                    valuableCards++;
                }
            }


            if (valuableCards >=2){
                order_up_suit = upcardSuit;
                return true;
            }
       
        } //get suit takes in trump suit as an input

        else if(round == 2){
            valuableCards=0;
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
            else if(is_dealer==true){ //screw the dealer        SHOULDNT THIS BE FIRST
                order_up_suit = Suit_next(upcardSuit); //order up any suit
                return true;
            }
          


        }
        return false;
    }

    void add_and_discard(const Card &upcard) override{
        assert(hand.size() >=1);
        hand.erase(hand.begin());
        add_card(upcard);
        //hand.push_back(upcard); //any card?
        //sort(hand.begin(), hand.end());

    }

    Card lead_card(Suit trump) override{
        assert(hand.size() >=1);
        // Card leadCard;

        // Card currentCard;
        // Suit currentCardSuit;
    
        // int indexLeadCard;
        bool hasnontrump = false;

        // find if it has non trump suit
        for (int i = 0; i < hand.size(); i++){
            if (hand[i].get_suit(trump) != trump){
                hasnontrump = true;
            }
        }

        // if has non trump suit, play highest card in hand
        if (hasnontrump) {
            Card highestnontrump(TWO, Suit_next(trump));
            int highestcardindex = -1;
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i].get_suit(trump) != trump && Card_less(highestnontrump, hand[i], trump)) {
                    highestnontrump = hand[i];
                    highestcardindex = i;
                }
            }
            hand.erase(hand.begin() + highestcardindex);
            return highestnontrump;
        }

        // if there are only trump, play highest trump card
        else {
            Card highesttrump(TWO, trump);
            int highesttrumpindex = -1;
            for (int i = 0; i < hand.size(); i++) {
                if (Card_less(highesttrump, hand[i], trump)) {
                    highesttrump = hand[i];
                    highesttrumpindex = i;
                }
            }
            hand.erase(hand.begin() + highesttrumpindex);
            return highesttrump;
        }

        // //traversing the hand
        // for (int i=hand.size()-1; i>-1; i--){
        //         currentCard = hand.at(i);
        //         currentCardSuit = currentCard.get_suit();

        //         if(currentCardSuit != trump){
        //             indexLeadCard = i;
        //             leadCard = currentCard;

        //             hand.erase(hand.begin() + indexLeadCard);
        //             return leadCard;
      
        //         }
     
        //     }


        //     leadCard = hand.at(hand.size()-1);
        //     hand.erase(hand.begin() + hand.size()-1);
        //     return leadCard;
            
        //     //test: highest rank being at edges. diff orders of trump 
        //     //and nontrump cards
    }

    Card play_card(const Card &led_card, Suit trump) override{
        hand = sortReal(hand,trump);
        Card playCard;
        Suit leadCardSuit = led_card.get_suit(trump);
        // Card RBower(JACK, leadCardSuit);
        // Card LBower(JACK,);
        Card currentCard;
        Suit currentCardSuit;

        //make two for loops, one keeping track of highest following suit and one 
        //keeping track of lowest card of not the same suit

        //could make a sort that takes rank into account but "thats more complicated"


        int indexPlayCard;

        //sortHand_byRank_ascending(hand);
        
        for (int i=hand.size()-1; i>-1; i--){
            currentCard = hand.at(i);
            currentCardSuit = currentCard.get_suit();
          //  rank = currentCard.get_rank();
            if(currentCardSuit == leadCardSuit){
                // if(currentCard.is_right_bower(trump)){

                // }
                indexPlayCard = i;
                playCard = currentCard;

                hand.erase(hand.begin() + indexPlayCard);
                return playCard;
            }
            // else{

            // }
    

        }
        playCard = hand.at(0);
        hand.erase(hand.begin());
        
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

    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i)
        cout << "Human player " << player_name << "'s hand: "
        << "[" << i << "] " << hand[i] << "\n";
}

    bool make_trump (const Card &upcard, bool is_dealer, 
    int round, Suit &order_up_suit) const override{
        print_hand();
        cout << "Human player " << player_name << ", please enter a suit, or \"pass\":\n";
        string decision;
        cin >> decision;
        Suit ordered_up;
        if (decision != "pass") {
            ordered_up = string_to_suit(decision);
            order_up_suit = ordered_up;
            return true;
        }
        else {
            return false;
        }
    }

    void add_and_discard(const Card &upcard) override{
        assert(hand.size() >=1);
        sort(hand.begin(), hand.end());
        print_hand();
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << player_name << ", please select a card to discard:\n";
        Card discardCard;
        cin >> discardCard;
        int indexDiscardCard;
        for (int i=0; i<hand.size(); i++){
            if (hand[i] == discardCard){
                indexDiscardCard = i;
            }
        }
        hand.erase(hand.begin() + indexDiscardCard);
        hand.push_back(upcard); 
        sort(hand.begin(), hand.end());

    }
    Card lead_card(Suit trump) override{
        print_hand();
        cout << "Human player " << player_name << ", please select a card:\n";
        Card ledCard;
        cin >> ledCard;
        int indexLedCard;
        for (int i=0; i<hand.size(); i++){
            if (hand[i] == ledCard){
                indexLedCard = i;
            }
        }
        hand.erase(hand.begin() + indexLedCard);
        return ledCard;

    }
    Card play_card(const Card &led_card, Suit trump) override{
        print_hand();
        cout << "Human player " << player_name << ", please select a card:\n";
        Card playedCard;
        cin >> playedCard;
        int indexPlayedCard;
        for (int i=0; i<hand.size(); i++){
            if (hand[i] == playedCard){
                indexPlayedCard = i;
            }
        }
        hand.erase(hand.begin() + indexPlayedCard);
        return playedCard;
    }

    private:
    const string player_name; 
    vector<Card> hand;
    //vector<const Card *> hand;

};

//  void SimplePlayer(const std::string& player_name, vector<Card> v, 
//int playersHand ){
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