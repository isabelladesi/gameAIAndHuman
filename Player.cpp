#include "Player.hpp"
#include <cassert>
#include <string>
#include <vector>

using namespace std;

Player * Player_factory(const string &name, const string &strategy) {
  assert(false);
}

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
        assert(false);
    }

    void add_and_discard(const Card &upcard) override{
        assert(hand.size() >=1);
        hand.pop_back();
        hand.push_back(&upcard);

    }

    Card lead_card(Suit trump) override{
        assert(false);
    }

    Card play_card(const Card &led_card, Suit trump) override{
        assert(false);
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
//  ...
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}