#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_get_rank) {
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(JACK, c.get_rank());
}

TEST(test_card_get_suit) {
    Card c(JACK, SPADES);
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_card_face_or_ace) {
    Card c(JACK, SPADES);
    ASSERT_EQUAL(true, c.is_face_or_ace());
    Card b(NINE, SPADES);
    ASSERT_EQUAL(false, b.is_face_or_ace());
}

TEST(test_card_is_right_bower) {
    Suit trump = Suit::SPADES;
    Card c(JACK, SPADES);
    ASSERT_EQUAL(true, c.is_right_bower(trump));
    Card b(NINE, SPADES);
    ASSERT_EQUAL(false, b.is_right_bower(trump));
    Card a(JACK, CLUBS);
    ASSERT_EQUAL(false, a.is_right_bower(trump));
}

TEST(test_card_is_left_bower) {
    Suit trump = Suit::HEARTS;
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(true, c.is_left_bower(trump));
    Card b(NINE, DIAMONDS);
    ASSERT_EQUAL(false, b.is_left_bower(trump));
    Card a(JACK, HEARTS);
    ASSERT_EQUAL(false, a.is_left_bower(trump));
}

TEST(test_card_is_trump) {
    Suit trump = Suit::HEARTS;
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(false, c.is_trump(trump));
    Card b(NINE, HEARTS);
    ASSERT_EQUAL(true, b.is_trump(trump));
}

//not sure how to do this one
// TEST(test_card_operator<<) {
//     Card c(KING, SPADES);
//     ASSERT_EQUAL("King of Spades", pack_input >> c);
// }

TEST(test_card_lower_value) {
    Card b(NINE, CLUBS);
    Card c(NINE, HEARTS);
    ASSERT_EQUAL(false, b < c);
    Card a(NINE, DIAMONDS);
    Card d(TEN, DIAMONDS);
    ASSERT_EQUAL(true, a < d);
}

TEST_MAIN()
