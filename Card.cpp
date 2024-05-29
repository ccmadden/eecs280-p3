#include "Card.hpp"

#include <array>
#include <cassert>
#include <iostream>

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
    "Two",    // TWO
    "Three",  // THREE
    "Four",   // FOUR
    "Five",   // FIVE
    "Six",    // SIX
    "Seven",  // SEVEN
    "Eight",  // EIGHT
    "Nine",   // NINE
    "Ten",    // TEN
    "Jack",   // JACK
    "Queen",  // QUEEN
    "King",   // KING
    "Ace"     // ACE
};

// REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
// EFFECTS returns the Rank correspoinding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
    for (int r = TWO; r <= ACE; ++r) {
        if (str == RANK_NAMES[r]) {
            return static_cast<Rank>(r);
        }
    }
    assert(false);  // Input string didn't match any rank
    return {};
}

// EFFECTS Prints Rank to stream, for example "Two"
std::ostream &operator<<(std::ostream &os, Rank rank) {
    os << RANK_NAMES[rank];
    return os;
}

// REQUIRES If any input is read, it must be a valid rank
// EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream &operator>>(std::istream &is, Rank &rank) {
    string str;
    if (is >> str) {
        rank = string_to_rank(str);
    }
    return is;
}

/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
    "Spades",    // SPADES
    "Hearts",    // HEARTS
    "Clubs",     // CLUBS
    "Diamonds",  // DIAMONDS
};

// REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
// EFFECTS returns the Suit correspoinding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        if (str == SUIT_NAMES[s]) {
            return static_cast<Suit>(s);
        }
    }
    assert(false);  // Input string didn't match any suit
    return {};
}

// EFFECTS Prints Suit to stream, for example "Spades"
std::ostream &operator<<(std::ostream &os, Suit suit) {
    os << SUIT_NAMES[suit];
    return os;
}

// REQUIRES If any input is read, it must be a valid suit
// EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream &operator>>(std::istream &is, Suit &suit) {
    string str;
    if (is >> str) {
        suit = string_to_suit(str);
    }
    return is;
}

/////////////// Write your implementation for Card below ///////////////

// EFFECTS Initializes Card to the Two of Spades
Card::Card() {
    rank = TWO;
    suit = SPADES;
}

// EFFECTS Initializes Card to specified rank and suit
Card::Card(Rank rank_in, Suit suit_in) {
    rank = rank_in;
    suit = suit_in;
}

// EFFECTS Returns the rank
Rank Card::get_rank() const {
    return rank;
}

// EFFECTS Returns the suit.  Does not consider trump.
Suit Card::get_suit() const {
    return suit;
}

// EFFECTS Returns the suit
// HINT: the left bower is the trump suit!
Suit Card::get_suit(Suit trump) const {
    if (is_left_bower(trump)) {
        return trump;
    }
    return suit;
}

// EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const {
    if (rank == JACK || rank == QUEEN || rank == KING || rank == ACE) {
        return true;
    } else {
        return false;
    }
}

// EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(Suit trump) const {
    if (rank == JACK && suit == trump) {
        return true;
    } else {
        return false;
    }
}

// EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(Suit trump) const {
    if (rank == JACK && suit == Suit_next(trump)) {
        return true;
    } else {
        return false;
    }
}

// EFFECTS Returns true if the card is a trump card.  All cards of the trump
//  suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(Suit trump) const {
    if (suit == trump || is_left_bower(trump)) {
        return true;
    } else {
        return false;
    }
}

// EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream &operator<<(std::ostream &os, const Card &card) {
    return os << card.get_rank() << " of " << card.get_suit();
}

// EFFECTS Reads a Card from a stream in the format "Two of Spades"
// NOTE The Card class declares this operator>> "friend" function,
//      which means it is allowed to access card.rank and card.suit.
std::istream &operator>>(std::istream &is, Card &card) {
    std::string junk;
    return is >> card.rank >> junk >> card.suit;
}

// EFFECTS Returns true if lhs is lower value than rhs.
//   Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() == rhs.get_rank()) {
        return lhs.get_suit() < rhs.get_suit();
    }
    return lhs.get_rank() < rhs.get_rank();
}

// EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//   Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    return lhs.get_rank() <= rhs.get_rank();
}

// EFFECTS Returns true if lhs is higher value than rhs.
//   Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() == rhs.get_rank()) {
        return rhs.get_suit() < lhs.get_suit();
    }
    return rhs.get_rank() < lhs.get_rank();
}

// EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//   Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    return rhs.get_rank() <= lhs.get_rank();
}

// EFFECTS Returns true if lhs is same card as rhs.
//   Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    return (lhs.get_rank() == rhs.get_rank() &&
    lhs.get_suit() == rhs.get_suit());
}

// EFFECTS Returns true if lhs is not the same card as rhs.
//   Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    return lhs.get_rank() != rhs.get_rank();
}

// EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit) {
    if (suit == HEARTS) {
        return DIAMONDS;
    } else if (suit == DIAMONDS) {
        return HEARTS;
    } else if (suit == SPADES) {
        return CLUBS;
    } else if (suit == CLUBS) {
        return SPADES;
    } else {
        return suit;
    }
}

// EFFECTS Returns true if a is lower value than b.  Uses trump to determine
//  order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump) {
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (b.is_right_bower(trump)) {
            return true;
        } else if (a.is_right_bower(trump)) {
            return false;
        } else if (b.is_left_bower(trump)) {
            return true;
        } else if (a.is_left_bower(trump)) {
            return false;
        } else {
            return a < b;
        }
    }
    if (a.is_trump(trump) && (!b.is_trump(trump))) {
        return false;
    }
    if ((!a.is_trump(trump)) && b.is_trump(trump)) {
        return true;
    }
    if (!(a.is_trump(trump)) && (!b.is_trump(trump))) {
        return a < b;
    }
    return a < b;
}

// EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//   and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump) {
    // a and/or b is trump
    if (a.is_trump(trump) || b.is_trump(trump)) {
        return Card_less(a, b, trump);
    } else {
        Suit led_suit = led_card.get_suit(trump);
        if (!(a.get_suit(trump) == led_suit) && b.get_suit(trump) == led_suit) {
            return true;
        }
        if (a.get_suit(trump) == led_suit && !(b.get_suit(trump) == led_suit)) {
            return false;
        }
        if (!(a.get_suit(trump) == led_suit) && !(b.get_suit(trump) == led_suit)){
            return Card_less(a, b, trump);
        }
    }
    return a < b;
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
