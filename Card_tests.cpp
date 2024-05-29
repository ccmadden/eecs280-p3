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
TEST(test_initialize_ctor) { 
    Card c; 
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES,c.get_suit());
}

TEST(test_get_suit_trump) { 
    Card of_trump(JACK, DIAMONDS);
    Suit trump = HEARTS;
    ASSERT_EQUAL(HEARTS, of_trump.get_suit(trump));
}

TEST(test_get_suit_not_trump) { 
    Card not_of_trump(NINE, DIAMONDS);
    Suit trump = SPADES;
    ASSERT_EQUAL(DIAMONDS,not_of_trump.get_suit(trump));
}

TEST(test_is_ace) { 
    Card ace(ACE, CLUBS);
    ASSERT_TRUE(ace.is_face_or_ace());
}

TEST(test_is_face) { 
    Card face(QUEEN, CLUBS);
    ASSERT_TRUE(face.is_face_or_ace());
}

TEST(test_card_f_o_a) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(true, c.is_face_or_ace());

    Card c1(NINE, DIAMONDS);
    ASSERT_EQUAL(false, c1.is_face_or_ace())

}

TEST(test_right_bower_basic){
    Suit trump = DIAMONDS;
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(true, c.is_right_bower(trump));

    Card c1(JACK, HEARTS);
    ASSERT_EQUAL(false, c1.is_right_bower(trump));
}

TEST(test_left_bower_basic){
    Suit trump = DIAMONDS;
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(false, c.is_left_bower(trump));

    Card c1(JACK, HEARTS);
    ASSERT_EQUAL(true, c1.is_left_bower(trump));

}

TEST(test_is_trump){
    Suit trump = DIAMONDS;
    Card c(NINE, DIAMONDS);
    ASSERT_EQUAL(true, c.is_trump(trump));

    Card c1(NINE, HEARTS);
    ASSERT_EQUAL(false, c1.is_trump(trump));

    Card c2(JACK, HEARTS);
    ASSERT_EQUAL(true, c2.is_trump(trump));
}

TEST(test_suit_next) { 
    Suit suit1 = HEARTS; 
    ASSERT_EQUAL(DIAMONDS, Suit_next(suit1));
    Suit suit2 = SPADES;
    ASSERT_EQUAL(CLUBS, Suit_next(suit2));
}

TEST(test_cardless) { 
    Card a(NINE, DIAMONDS);
    Card b(TEN,CLUBS);
    Suit trump1 = CLUBS;
    ASSERT_EQUAL(true, Card_less(a,b,trump1));

    Card c(SIX,DIAMONDS);
    Card d(SEVEN,CLUBS);
    Suit trump2 = DIAMONDS;
    ASSERT_EQUAL(false, Card_less(c,d,trump2));

    Card e(QUEEN,HEARTS);
    Card f(KING, HEARTS);
    Suit trump3 = SPADES;
    ASSERT_EQUAL(true, Card_less(e,f,trump3));

    Suit trump = SPADES;
    Card c1(NINE, SPADES);
    Card c2(TEN, SPADES);
    ASSERT_EQUAL(true, Card_less(c1, c2, trump));

    Card c3(JACK, SPADES);
    ASSERT_EQUAL(false, Card_less(c3, c2, trump));

    Card c4(QUEEN, HEARTS);
    ASSERT_EQUAL(true, Card_less(c4, c3, trump));

    Card c5(JACK, CLUBS);
    Card c6 (ACE, SPADES);
    ASSERT_EQUAL(true, Card_less(c6, c5, trump));

    ASSERT_EQUAL( true, Card_less(c5, c3, trump));

}

TEST (test_card_led){
    Suit trump = HEARTS;
    Card c1 (JACK, DIAMONDS);
    Card c2 (ACE, CLUBS);
    ASSERT_FALSE(Card_less(c1, c2, trump));
    Card c3 (JACK, HEARTS);
    ASSERT_TRUE(Card_less(c1, c3, trump));
    Card led_card(KING, SPADES);
    Card c4(TEN, SPADES);
    Card c5 (NINE, SPADES);
    Card c6 (ACE, DIAMONDS);
    Card c7 (NINE, CLUBS);
    Card c9 (ACE, SPADES);

    ASSERT_TRUE(Card_less(c5, c4,led_card,trump));
    ASSERT_TRUE(Card_less(c2, c4, led_card, trump));
    ASSERT_FALSE(Card_less(c3,c5, led_card,trump));
    ASSERT_FALSE(Card_less (c6, c7, led_card, trump));
    ASSERT_TRUE(Card_less(c9,c3, led_card, trump));
    ASSERT_TRUE(Card_less(c7, c2, led_card, trump));
}

TEST (test_operators){
    Card c1(TEN, SPADES);
    Card c2(ACE, DIAMONDS);
    Card c3(ACE, SPADES);

    ASSERT_TRUE(operator<(c1, c2));
    ASSERT_FALSE(operator>(c1, c2));
    ASSERT_TRUE(operator==(c1, c1));
    
    ASSERT_TRUE(operator>(c2,c3));
    ASSERT_TRUE(operator<(c3,c2));

}

TEST_MAIN()
