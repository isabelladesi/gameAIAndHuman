#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST(test_player_lead_card_ALLTRUMP) {
    // isa's hand
  Player * isa = Player_factory("Bob", "Simple");
  isa->add_card(Card(NINE, SPADES));
  isa->add_card(Card(TEN, SPADES));
  isa->add_card(Card(QUEEN, SPADES));
  isa->add_card(Card(KING, SPADES));
  isa->add_card(Card(ACE, SPADES));

  // isa adds a card to his hand and discards one card
  isa->add_and_discard(
    Card(NINE, SPADES) // upcard
  );

  // isa leads
  Card card_led = isa->lead_card(SPADES);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete isa;

}

TEST(test_player_lead_card_MULTITRUMP) {
    // isa's hand
  Player * isa = Player_factory("Bob", "Simple");
  isa->add_card(Card(QUEEN, DIAMONDS));
  isa->add_card(Card(TEN, DIAMONDS));
  isa->add_card(Card(QUEEN, HEARTS));
  isa->add_card(Card(KING, SPADES));
  isa->add_card(Card(ACE, SPADES));

  // isa adds a card to his hand and discards one card
  isa->add_and_discard(
    Card(NINE, SPADES) // upcard
  );

  // isa leads
  Card card_led = isa->lead_card(SPADES);

  // Verify the card Bob selected to lead
  Card queen_diamonds(QUEEN, DIAMONDS);
  ASSERT_EQUAL(card_led, queen_diamonds); //check led card

  delete isa;

}

TEST(test_player_play_card_NORMAL) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(ACE, HEARTS));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_hearts(NINE, HEARTS);
  Card card_played = bob->play_card(
    nine_hearts,  // Nine of Spades is led
    SPADES    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(ACE, HEARTS));
  delete bob;
}

//**this test is failing**
TEST(test_player_play_card_RBOWER) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(ACE, SPADES));
  bob->add_card(Card(KING, SPADES)); //ALL TRUMP CARDS

  // Bob plays a card
  Card seven_spades(SEVEN, SPADES);
  Card card_played = bob->play_card(
    seven_spades,  // seven of Spades is led
    SPADES    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, SPADES));
  delete bob;
}

TEST(test_player_make_trump_NORMAL_round1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(ACE, HEARTS));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  bool is_dealer = true;
  Suit upCard_suit = Suit(DIAMONDS);
  
  Card jack_diamonds(JACK, DIAMONDS);
  bool did_bob_make_trump = bob->make_trump(jack_diamonds, is_dealer,1,upCard_suit);
  
  // Verify the card Bob played
  ASSERT_EQUAL(false, did_bob_make_trump);
  delete bob;
}
//**this test is failing**
TEST(test_player_make_trump_LB_round1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(ACE, CLUBS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(JACK, HEARTS));
  bob->add_card(Card(QUEEN, DIAMONDS));

  bool is_dealer = false;
  Suit upCard_suit = Suit(DIAMONDS); //trump suit is diamonds
  
  Card jack_diamonds(JACK, DIAMONDS); //upcard is jack of diamonds
  bool did_bob_make_trump = bob->make_trump(jack_diamonds, is_dealer,1,upCard_suit);
  
  // Verify the card Bob played
  ASSERT_EQUAL(true, did_bob_make_trump);
  delete bob;
}

TEST(test_player_make_trump_NORMAL_round2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, DIAMONDS));

  bool is_dealer = false;
  Suit upCard_suit = Suit(DIAMONDS); //trump suit is diamonds
  
  Card jack_diamonds(JACK, DIAMONDS); //upcard is king of diamonds
  bool did_bob_make_trump = bob->make_trump(jack_diamonds, is_dealer,2,upCard_suit);
  
  // Verify the card Bob played
  ASSERT_EQUAL(true, did_bob_make_trump);
  delete bob;
}

TEST(test_player_make_trump_dealer_round2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(EIGHT, HEARTS));
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, DIAMONDS));

  bool is_dealer = true;
  Suit upCard_suit = Suit(DIAMONDS); //trump suit is diamonds
  
  Card jack_diamonds(JACK, DIAMONDS); //upcard is king of diamonds
  bool did_bob_make_trump = bob->make_trump(jack_diamonds, is_dealer,2,upCard_suit);
  
  ASSERT_EQUAL(true, did_bob_make_trump);
  delete bob;
}

TEST(test_simple_player_not_make_trump) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    Card nine_diamonds(NINE, DIAMONDS); //upcard
    bool is_dealer = true;
    Suit DIAMONDS;
    bool did_bob_not_order_up = bob->make_trump(nine_diamonds, is_dealer, 1, DIAMONDS);
    ASSERT_FALSE(did_bob_not_order_up);

    delete bob;
}

TEST(test_simple_player_add_discard_all_trump) {
    // create hand for alice
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // add upcard to deck - will remove two spades
    bob->add_and_discard(Card(TWO, SPADES));

    // verify alice hand
    Card led = Card(THREE, SPADES);

    Card jackSpades = Card(JACK, SPADES);
    Card aceSpades = Card(ACE, SPADES);
    Card kingSpades = Card(KING, SPADES);
    Card queenSpades = Card(QUEEN, SPADES);
    Card twoSpades = Card(TWO, SPADES);
    ASSERT_EQUAL(jackSpades ,bob->play_card(led, SPADES));

    ASSERT_EQUAL(aceSpades ,bob->play_card(led, SPADES));

    ASSERT_EQUAL(kingSpades ,bob->play_card(led, SPADES));
    
    ASSERT_EQUAL(queenSpades ,bob->play_card(led, SPADES));

    ASSERT_EQUAL(twoSpades ,bob->play_card(led, SPADES));

    delete bob;
}

TEST(test_simple_player_add_discard_all_trump) { //CHANGE THIS
    // create hand for alice
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // add upcard to deck - will remove two spades
    bob->add_and_discard(Card(TWO, SPADES));

    // verify alice hand
    Card led = Card(THREE, SPADES);

    Card jackSpades = Card(JACK, SPADES);
    Card aceSpades = Card(ACE, SPADES);
    Card kingSpades = Card(KING, SPADES);
    Card queenSpades = Card(QUEEN, SPADES);
    Card twoSpades = Card(TWO, SPADES);
    ASSERT_EQUAL(jackSpades ,bob->play_card(led, SPADES));

    ASSERT_EQUAL(aceSpades ,bob->play_card(led, SPADES));

    ASSERT_EQUAL(kingSpades ,bob->play_card(led, SPADES));
    
    ASSERT_EQUAL(queenSpades ,bob->play_card(led, SPADES));

    ASSERT_EQUAL(twoSpades ,bob->play_card(led, SPADES));

    delete bob;
}

TEST_MAIN()
