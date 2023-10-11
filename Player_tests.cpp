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


// TEST(test_player_play_card_RBOWER) {
//   // Bob's hand
//   Player * bob = Player_factory("Bob", "Simple");
//   bob->add_card(Card(ACE, SPADES));
//   bob->add_card(Card(JACK, SPADES));
//   bob->add_card(Card(QUEEN, SPADES));
//   bob->add_card(Card(KING, SPADES));
//   bob->add_card(Card(ACE, SPADES));

//   // Bob plays a card
//   Card nine_spades(JACK, SPADES);
//   Card card_played = bob->play_card(
//     nine_spades,  // Nine of Spades is led
//     SPADES    // Trump suit
//   ); 

//   // Verify the card Bob played
//   ASSERT_EQUAL(card_played, Card(JACK, SPADES));
//   delete bob;
// }

TEST_MAIN()
