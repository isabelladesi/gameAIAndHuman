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

TEST(test_stream) {
    Card c(KING, SPADES);

    ostringstream os;
    os << c;
    ASSERT_EQUAL(os.str(), "King of Spades");

    istringstream is("Jack of Diamonds");
    Card b;
    is >> b;
    ASSERT_EQUAL(b, Card(JACK, DIAMONDS));
}

TEST(test_card_lower_value) {
    Card b(NINE, CLUBS);
    Card c(NINE, HEARTS);
    ASSERT_EQUAL(false, b < c);
    Card a(NINE, DIAMONDS);
    Card d(TEN, DIAMONDS);
    ASSERT_EQUAL(true, a < d);
}

TEST(test_card_higher_value) {
    Card b(NINE, CLUBS);
    Card c(NINE, HEARTS);
    ASSERT_EQUAL(true, b > c);
    Card a(NINE, DIAMONDS);
    Card d(TEN, DIAMONDS);
    ASSERT_EQUAL(false, a > d);
}

TEST(test_card_higher_same_value) {
    Card b(NINE, CLUBS);
    Card c(NINE, HEARTS);
    Card d(NINE, HEARTS);
    ASSERT_EQUAL(true, c >= d);
    ASSERT_EQUAL(false, d >= b);
}

TEST(test_card_same_value) {
    Card c(ACE, HEARTS);
    Card d(ACE, HEARTS);
    ASSERT_EQUAL(true, c == d);
}

TEST(test_card_not_same_value) {
    Card c(ACE, SPADES);
    Card d(ACE, SPADES);
    Card a(ACE, DIAMONDS);
    ASSERT_EQUAL(false, c != d);
    ASSERT_EQUAL(true, d != a);
}

TEST(test_card_suit_next) {
    Suit suitA = Suit::SPADES;
    Suit suitB = Suit::CLUBS;
    Suit suitC = Suit::HEARTS;
    Suit suitD = Suit::DIAMONDS;
    ASSERT_EQUAL(CLUBS, Suit_next(suitA));
    ASSERT_EQUAL(SPADES, Suit_next(suitB));
    ASSERT_EQUAL(DIAMONDS, Suit_next(suitC));
    ASSERT_EQUAL(HEARTS, Suit_next(suitD));
}

TEST(test_card_lessA) {
    Card a(ACE, SPADES);
    Card b(KING, SPADES);
    Card c(JACK, SPADES);
    Card d(JACK, CLUBS);
    Card e(ACE, HEARTS);
    Card f(ACE, DIAMONDS);
    Card g(ACE, CLUBS);
    Suit trump = Suit::SPADES;

    ASSERT_EQUAL(true, Card_less(b, a, trump));
    ASSERT_EQUAL(true, Card_less(a, c, trump));
    ASSERT_EQUAL(true, Card_less(a, d, trump));
    ASSERT_EQUAL(true, Card_less(a, d, trump));
    ASSERT_EQUAL(true, Card_less(g, f, trump));
}

// TEST(test_card_lessB) {
//     Card a(ACE, SPADES);
//     Card b(KING, SPADES);
//     Card c(JACK, SPADES);
//     Card d(JACK, CLUBS);
//     Card e(ACE, HEARTS);
//     Card f(ACE, DIAMONDS);
//     Card g(ACE, CLUBS);
//     Suit trump = Suit::SPADES;
//     Suit ledA = Suit::SPADES;
//     Suit ledB = Suit::DIAMONDS;

//     ASSERT_EQUAL(true, Card_less(b, a, trump));
//     ASSERT_EQUAL(true, Card_less(a, c, trump));
//     ASSERT_EQUAL(true, Card_less(a, d, trump));
//     ASSERT_EQUAL(true, Card_less(a, d, trump));
//     ASSERT_EQUAL(true, Card_less(g, f, trump));
// }

TEST_MAIN()
