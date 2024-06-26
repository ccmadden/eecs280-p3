#include "Card.hpp"
#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <array>

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on. 
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack() { 
    next = 0;
    int i = 0;
    
    for (int suit = SPADES; suit <= DIAMONDS; ++suit) { 
        for (int rank = NINE; rank <= ACE; ++rank) { 
            cards[i] = Card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            i++;
        }
    }
    //D > C > H > S
    //A > K > Q > J > 10 > 9
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
// NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream& pack_input) {
    next = 0;
    for (int i = 0; i < PACK_SIZE; ++i) { 
        pack_input >> cards[i];
    }
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() { 
    Card next_card = cards[next]; 
    next++;
    return next_card;
}

  // EFFECTS: Resets next index to first card in the Pack
void Pack::reset() { 
   next = 0;
}

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() { 
    std::array<Card, PACK_SIZE> copy_array;
    // make sure it shuffles through 7 times
    for (int j = 0; j < 7;j++){
        int y = 0;
        for( int i = 0; i < PACK_SIZE; i++){
            copy_array[i] = cards[i];
        }
        for ( int i = 0; i < PACK_SIZE; i++){
            if (i < PACK_SIZE/2) {
                cards[(i * 2) + 1] = copy_array[i];
        // either divided or multiplied not sure
            } else {
                cards[y] = copy_array[i];
                 y = y + 2;
            }
        }
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const { 
    if (next == 24) {
        return true;
    } else {
        return false;
    }
}