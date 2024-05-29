#include "Player.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include "Card.hpp"

using namespace std;

class SimplePlayer : public Player {
   private:
    string name;
    vector<Card> hand;

   public:
    // EFFECTS returns player's name
    SimplePlayer() {
    }
    SimplePlayer(string player_name) {
        name = player_name;
    }

    const string &get_name() const override {
        return name;
    }

    // REQUIRES player has less than MAX_HAND_SIZE cards
    // EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        hand.push_back(c);
    }

    // REQUIRES round is 1 or 2
    // MODIFIES order_up_suit
    // EFFECTS If Player wishes to order up a trump suit then return true and
    //   change order_up_suit to desired suit.  If Player wishes to pass, then do
    //   not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer, int round,
                    Suit &order_up_suit) const override {
        if (round == 1) {
            int counter = 0;
            for (int i = 0; i < hand.size(); ++i) {
                if (hand[i].is_face_or_ace() &&
                    (hand[i].get_suit() == upcard.get_suit() ||
                     hand[i].is_left_bower(upcard.get_suit()) ||
                     hand[i].is_right_bower(upcard.get_suit()))) {
                    counter++;
                }
            }
            if (counter >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            } else {
                return false;
            }
        } else if (round == 2) {
            int counter = 0;
            for (int i = 0; i < hand.size(); ++i) {
                if (hand[i].is_face_or_ace() &&
                    (hand[i].get_suit() == Suit_next(upcard.get_suit()) ||
                    // do we use suit next
                     hand[i].is_left_bower(Suit_next(upcard.get_suit())))) {
                    counter++;
                }
            }
            if (counter >= 1 || is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        Suit ordered_up_suit = upcard.get_suit();
        int offset = 0;
        hand.push_back(upcard);
        Card least_card = hand[0];
        for (int i = 0; i < hand.size(); i++) {
            if (Card_less(hand[i], least_card, ordered_up_suit)) {
                least_card = hand[i];
                offset = i;
            }
        }

        hand.erase(hand.begin() + offset);
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Leads one Card from Player's hand according to their strategy
    //   "Lead" means to play the first Card in a trick.  The card
    //   is removed the player's hand.
    Card lead_card(Suit trump) override {
        int trump_count = 0;
        Card highest_non_trump_card;
        Card highest_trump_card;
        Card highest_card;
        int highest_trump_index = 0;
        int highest_non_trump_index = 0;

        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].is_trump(trump)) {
                trump_count++;
                if (highest_trump_card < hand[i]) {
                    highest_trump_card = hand[i];
                    highest_trump_index = i;
                }
            } else {
                if (highest_non_trump_card < hand[i]) {
                    highest_non_trump_card = hand[i];
                    highest_non_trump_index = i;
                }
            }
        }

        if (trump_count == hand.size()) {
            for (int i = 0; i < hand.size(); ++i) {
   if (hand[i].is_right_bower(trump) || hand[i].is_left_bower(trump)) {
                    if (hand[i].is_right_bower(trump)) {
                        highest_trump_card = hand[i];
                        hand.erase(hand.begin() + i);
                        return highest_trump_card;
                    } else if (hand[i].is_left_bower(trump)) {
                        highest_trump_card = hand[i];
                        hand.erase(hand.begin() + i);
                        return highest_trump_card;
                    }
                }
            }
            hand.erase(hand.begin() + highest_trump_index);
            return highest_trump_card;
        } else {
            hand.erase(hand.begin() + highest_non_trump_index);
            return highest_non_trump_card;
        }
        return highest_card;
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Plays one Card from Player's hand according to their strategy.
    //   The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {
        // if can follow suit, play highest card in that suit
        // if not, you're gonna play lowest card in that suit
        vector<Card> led_cards;
        // vector<Card> non_led_cards;
        Card highest_card;
        Card lowest_card;
        int highest_led_index = 0;
        int lowest_index = 0;

        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].get_suit() == led_card.get_suit()) {
                led_cards.push_back(hand[i]);
            }
        }

        if (led_cards.size() > 0) {
            // highest_card = led_cards[0];
            for (int i = 0; i < led_cards.size(); ++i) {
                if (Card_less(highest_card, led_cards[i], led_card, trump)) {
                    highest_card = led_cards[i];
                    highest_led_index = i;
                }
            }
        } else {
            lowest_card = hand[0];
            for (int i = 0; i < hand.size(); ++i) {
                if (Card_less(hand[i], lowest_card, led_card, trump)) {
                    lowest_card = hand[i];
                    lowest_index = i;
                }
            }
        }

        if (led_cards.size() > 0) {
            Card return_highest = highest_card;
            for (int i = 0; i < hand.size(); ++i) {
                if (hand[i] == highest_card) {
                    highest_led_index = i;
                    hand.erase(hand.begin() + highest_led_index);
                    return return_highest;
                }
            }
        
        } else {
            Card return_lowest = lowest_card;
            for (int i = 0; i < hand.size(); ++i) {
                if (hand[i] == lowest_card) {
                    lowest_index = i;
                    hand.erase(hand.begin() + lowest_index);
                    return return_lowest;
                }
            }
        }
        return lowest_card;
    }

    // Needed to avoid some compiler errors
    // NOTE: Do NOT write a destructor in the Player subclasses.
    // The compiler-generated
    // ones will work fine.
    ~SimplePlayer() {
    }
};

class HumanPlayer : public Player {
   private:
    string name;
    vector<Card> hand;

    void print_hand() const {
        for (size_t i = 0; i < hand.size(); ++i)
            cout << "Human player " << name << "'s hand: "
                 << "[" << i << "] " << hand[i] << "\n";
    }

   public:
    HumanPlayer() {
    }
    HumanPlayer(string player_name) {
        name = player_name;
    }

    // EFFECTS returns player's name
    const string &get_name() const override {
        return name;
    }

    // REQUIRES player has less than MAX_HAND_SIZE cards
    // EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        hand.push_back(c);
    }

    // REQUIRES round is 1 or 2
    // MODIFIES order_up_suit
    // EFFECTS If Player wishes to order up a trump suit then return true and
    //   change order_up_suit to desired suit.  If Player wishes to pass, then do
    //   not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer, int round,
                    Suit &order_up_suit) const override {
        // prompt user for their decision to pass or order up

        // print the player's hand
        print_hand();
cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
        string decision;
        cin >> decision;

        // pass or order up
        if (round == 1) {
            if (decision != "pass") {
                order_up_suit = string_to_suit(decision);
                return true;
            } else {
                return false;
            }
        }
        // print the player's hand
        else if (round == 2) {
            // pass or order up or screw the dealer
            if (is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            } else if (decision != "pass") {
                order_up_suit = string_to_suit(decision);
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        sort(hand.begin(), hand.end());
        print_hand();
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:\n";
        // card corresponds to index
        int discard_card;
        cin >> discard_card;
        // pick up the upcard + discard a card of their choice
        if (discard_card != -1) {
            hand.erase(hand.begin() + discard_card);
            hand.push_back(upcard);
            sort(hand.begin(), hand.end());
        }
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Leads one Card from Player's hand according to their strategy
    //   "Lead" means to play the first Card in a trick.  The card
    //   is removed the player's hand.
    Card lead_card(Suit trump) override {  // do we need trump??
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        // card corresponds to index
        int card_index;
        cin >> card_index;
        Card ledcard = hand[card_index];
        hand.erase(hand.begin() + card_index);
        return ledcard;
    }

    // REQUIRES Player has at least one card
    // EFFECTS  Plays one Card from Player's hand according to their strategy.
    //   The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        // card corresponds to index
        int card_index;
        cin >> card_index;
        Card playcard = hand[card_index];
        hand.erase(hand.begin() + card_index);
        return playcard;
    }

    // Needed to avoid some compiler errors
    // NOTE: Do NOT write a destructor in the Player subclasses.
    // The compiler-generated ones will work fine.
    ~HumanPlayer() {
    }
};

// EFFECTS: Returns a pointer to a player with the given name and strategy
// To create an object that won't go out of scope when the function returns,
// use "return new Simple(name)" or "return new Human(name)"
// Don't forget to call "delete" on each Player* after the game is over
Player *Player_factory(const string &name, const string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
    if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    return nullptr;
}

// EFFECTS: Prints player's name to os
ostream &operator<<(ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}
