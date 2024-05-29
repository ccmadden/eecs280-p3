#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}

// ADD MORE TESTS HERE
TEST(test_human_get_name) {
    //create a human player
    Player *human = Player_factory("NotBot", "Human");
    ASSERT_EQUAL("NotBot", human->get_name());
    delete human;
}

TEST(test_simple_no_name) { 
    Player * no_name = Player_factory("", "Simple");
    ASSERT_EQUAL("", no_name->get_name());
    delete no_name;
}

TEST(test_human_no_name) {
    //create a human player
    Player *human = Player_factory("", "Human");
    ASSERT_EQUAL("",human -> get_name());
    delete human;
}

TEST(simple_player_make_trump_1_card_r1) { 
  Player * carl = Player_factory("Carl", "Simple");
  carl->add_card(Card(KING,CLUBS));
  Card king_clubs(KING, CLUBS);
  Suit trump;
  bool orderup = carl->make_trump(
    king_clubs, 
    false, 
    1,
    trump
  );
  ASSERT_FALSE(orderup);

  delete carl;
}

TEST(simple_player_make_trump_2_cards_r1) { 
  Player * carl = Player_factory("Carl", "Simple");
  carl->add_card(Card(KING,CLUBS));
  carl->add_card(Card(QUEEN,CLUBS));
  Card queen_clubs(QUEEN, CLUBS);
  Suit trump;
  bool orderup = carl->make_trump(
    queen_clubs, 
    false, 
    1,
    trump
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,CLUBS);

  delete carl;
}

TEST(test_simple_player_make_trump_orderup_1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump = SPADES;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump_pass_1) { 
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, CLUBS));
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, SPADES));

  // Bob makes trump
  Card nine_clubs(NINE, CLUBS);
  Suit trump = CLUBS;
  bool orderup = bob->make_trump(
    nine_clubs,    // Upcard
    false,         
    1,             // First round
    trump          // Suit ordered up (if any)
  );

  // Verify Bob's order up decision
  ASSERT_FALSE(orderup); 

  delete bob;
}

TEST(test_simple_player_make_trump_dealer_2) { 
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));

  // Bob makes trump
  Card ten_spades(TEN, SPADES);
  Suit trump = SPADES;
  bool orderup = bob->make_trump(
    ten_spades,    // Upcard
    true,          // Bob is also the dealer
    2,             // Second round
    trump          // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}


TEST(test_simple_player_make_trump_orderup_2) { 
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(ACE, HEARTS));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(JACK, HEARTS));
  bob->add_card(Card(JACK, DIAMONDS));

  // Bob makes trump
  Card jack_diamonds(JACK, DIAMONDS);
  Suit trump = HEARTS;
  bool orderup = bob->make_trump(
    jack_diamonds,    // Upcard
    false,           // Bob is not the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

TEST(test_simple_player_make_trump_pass_2) { 
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(ACE, DIAMONDS));
  bob->add_card(Card(KING, HEARTS));

  // Bob makes trump
  Card jack_clubs(JACK, CLUBS);
  Suit trump = CLUBS;
  bool orderup = bob->make_trump(
    jack_clubs,    // Upcard
    false,         // Bob is not the dealer
    2,             // Second round
    trump          // Suit ordered up (if any)
  );

  // Verify Bob's order up decision
  ASSERT_FALSE(orderup);

  delete bob;
}

//add or discard when the lowest card is the up card-- NEED TO FIX
TEST(test_add_discard_upcard_least) { 

  vector<Card> evan_hand;
  //Evan's hand 
  Player * evan = Player_factory("Evan", "Simple");
  evan->add_card(Card(TEN, SPADES));
  evan_hand.push_back(Card(TEN, SPADES));
  evan->add_card(Card(QUEEN, HEARTS));
  evan_hand.push_back(Card(QUEEN, HEARTS));
  evan->add_card(Card(QUEEN, CLUBS));
  evan_hand.push_back(Card(QUEEN, CLUBS));

  //Evan adds and then discards the upcard
  evan->add_and_discard( 
    Card(NINE, DIAMONDS) //upcard and least card
  );
  delete evan;
}


TEST(test_simple_player_lead_card_non_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_player_leads_highest_non_trump_mixed_hand) {
  // Alice's hand
  Player * alice = Player_factory("Alice", "Simple");
  alice->add_card(Card(NINE, CLUBS));
  alice->add_card(Card(TEN, DIAMONDS)); 
  alice->add_card(Card(JACK, HEARTS)); // Trump card
  alice->add_card(Card(QUEEN, HEARTS));  // Trump card
  alice->add_card(Card(KING, CLUBS)); // Highest non-trump

  // Alice leads
  Card card_led = alice->lead_card(HEARTS); // Trump is Hearts

  // Verify Alice selects the highest non-trump card to lead
  Card king_clubs(KING, CLUBS);
  ASSERT_EQUAL(card_led, king_clubs);

  delete alice;
}


TEST(test_player_leads_highest_trump_all_trump_hand) {
  // Charlie's hand
  Player * charlie = Player_factory("Charlie", "Simple");
  charlie->add_card(Card(NINE, HEARTS));
  charlie->add_card(Card(TEN, HEARTS));
  charlie->add_card(Card(JACK, HEARTS)); 
  charlie->add_card(Card(QUEEN, HEARTS)); 
  charlie->add_card(Card(KING, HEARTS));

  // Charlie leads
  Card card_led = charlie->lead_card(HEARTS); // Trump is Hearts
  // Verify Charlie selects the highest trump card to lead
  Card jack_hearts(JACK, HEARTS);
  ASSERT_EQUAL(card_led, jack_hearts); //having problems 

  delete charlie;
}


TEST(test_player_leads_highest_card_no_trumps) {
  // Dana's hand
  Player * dana = Player_factory("Dana", "Simple");
  dana->add_card(Card(NINE, CLUBS));
  dana->add_card(Card(TEN, CLUBS));
  dana->add_card(Card(JACK, SPADES)); // Highest card
  dana->add_card(Card(QUEEN, DIAMONDS));
  dana->add_card(Card(KING, CLUBS));

  // Dana leads
  Card card_led = dana->lead_card(HEARTS); // Trump is Hearts

  // Verify Dana selects the highest card to lead
  Card king_clubs(KING, CLUBS);
  ASSERT_EQUAL(card_led, king_clubs);

  delete dana;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;
}

TEST(test_player_follows_suit_with_highest_card) {
  // Emily's hand
  Player * emily = Player_factory("Emily", "Simple");
  emily->add_card(Card(NINE, CLUBS));
  emily->add_card(Card(TEN, CLUBS));
  emily->add_card(Card(JACK, CLUBS)); // Highest in clubs
  emily->add_card(Card(QUEEN, SPADES));
  emily->add_card(Card(KING, SPADES));

  // Emily plays a card, following suit with the highest card
  Card ten_clubs(TEN, CLUBS); // Ten of Clubs is led
  Card card_played = emily->play_card(ten_clubs, DIAMONDS); // Trump suit is Diamonds

  // Verify Emily plays the Jack of Clubs, the highest in the led suit
  ASSERT_EQUAL(card_played, Card(JACK, CLUBS));

  delete emily;
}

TEST(test_player_cannot_follow_suit_plays_lowest_card) {
  // Frank's hand
  Player * frank = Player_factory("Frank", "Simple");
  frank->add_card(Card(NINE, DIAMONDS)); // Lowest card
  frank->add_card(Card(TEN, HEARTS)); 
  frank->add_card(Card(JACK, HEARTS));
  frank->add_card(Card(QUEEN, SPADES));
  frank->add_card(Card(KING, SPADES));

  // Frank plays a card, unable to follow suit
  Card jack_clubs(JACK, CLUBS); // Jack of Clubs is led
  Card card_played = frank->play_card(jack_clubs, HEARTS); // Trump suit is Hearts

  // Verify Frank plays the Ten of Hearts, the lowest card in his hand
  ASSERT_EQUAL(card_played, Card(NINE, DIAMONDS));

  delete frank;
}

TEST(test_player_has_only_trump_cards_plays_lowest_trump) {
  // Grace's hand
  Player * grace = Player_factory("Grace", "Simple");
  grace->add_card(Card(TEN, HEARTS)); // Lowest trump
  grace->add_card(Card(JACK, HEARTS));
  grace->add_card(Card(QUEEN, HEARTS));
  grace->add_card(Card(KING, HEARTS));
  grace->add_card(Card(ACE, HEARTS));

  // Grace plays a card, with only trump cards in hand
  Card nine_clubs(NINE, CLUBS); // Nine of Clubs is led
  Card card_played = grace->play_card(nine_clubs, HEARTS); // Trump suit is Hearts

  // Verify Grace plays the Ten of Hearts, the lowest trump in her hand
  ASSERT_EQUAL(card_played, Card(TEN, HEARTS));

  delete grace;
}

TEST(test_player_1card) {
  // Grace's hand
  Player * steve = Player_factory("Steve", "Simple");
  steve->add_card(Card(TEN, HEARTS)); 

  // Grace plays a card
  Card ten_hearts(TEN, HEARTS); 
  Card card_played = steve->play_card(ten_hearts, HEARTS); // Trump suit is Hearts

  ASSERT_EQUAL(card_played, Card(TEN, HEARTS));

  delete steve;
}

TEST(test_simple_player_does_not_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_make_trump_screw_the_dealer) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}
TEST(test_make_trump_r2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(TEN, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}
TEST(test_make_trump_r1_no) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(TEN, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    1,              // Second round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}

TEST(test_make_trump_r1_no2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}

TEST(test_make_trump_r2_no) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}
TEST(test_make_trump_r1_no_r2_yes) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );
  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, CLUBS);
  delete bob;
}

TEST(test_make_trump__r2_yes) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );
  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);
  delete bob;
}

TEST(make_trump_lb_r1){
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(JACK, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );
  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);
  delete bob;
}
TEST(make_trump_lb_r2){
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(JACK, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,          
    2,              // First round
    trump           // Suit ordered up (if any)
  );
  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);
  delete bob;
}

TEST(test_add_discard1) { 

  vector<Card> evan_hand;
  //Evan's hand 
  Player * evan = Player_factory("Evan", "Simple");
  evan->add_card(Card(NINE, DIAMONDS));
  evan_hand.push_back(Card(NINE, DIAMONDS));
  evan->add_card(Card(NINE, CLUBS));
  evan_hand.push_back(Card(NINE, CLUBS));
  evan->add_card(Card(QUEEN, DIAMONDS));
  evan_hand.push_back(Card(QUEEN, DIAMONDS));
  evan->add_card(Card(TEN,CLUBS));
  evan_hand.push_back(Card(TEN,CLUBS));
   evan->add_card(Card(JACK,CLUBS));
  evan_hand.push_back(Card(JACK,CLUBS));


  //Evan adds and then discards the upcard
 evan->add_and_discard( 
    Card(NINE, SPADES));
     //upcard and least card
     ASSERT_TRUE(evan_hand.size() == 5);

     vector <Card> new_hand;
     new_hand.push_back(Card(NINE, DIAMONDS));
     new_hand.push_back(Card(NINE, CLUBS));
     new_hand.push_back(Card(QUEEN, DIAMONDS));
     new_hand.push_back(Card(TEN,CLUBS));
     new_hand.push_back(Card(JACK,CLUBS));

    ASSERT_EQUAL(evan_hand, new_hand);
    delete evan;

}


TEST(make_trump_dl_r1_no){
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(JACK, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );
  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, CLUBS);
  delete bob;
}

TEST(make_trump_dl_r2_yes){
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(JACK, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );
  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);
  delete bob;
}
TEST(make_trump_dl_r1_yes){
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(JACK, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );
  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);
  delete bob;
}

TEST(make_trump_dl_r2_yes_screw){
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(NINE, CLUBS));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );
  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);
  delete bob;
}

TEST(test_add_discard_lb) { 

  vector<Card> evan_hand;
  //Evan's hand 
  Player * evan = Player_factory("Evan", "Simple");
  evan->add_card(Card(NINE, SPADES));
  evan_hand.push_back(Card(NINE, SPADES));
  evan->add_card(Card(ACE, DIAMONDS));
  evan_hand.push_back(Card(TEN, DIAMONDS));
  evan->add_card(Card(TEN, DIAMONDS));
  evan_hand.push_back(Card(TEN, DIAMONDS));
  evan->add_card(Card(TEN,CLUBS));
  evan_hand.push_back(Card(TEN,CLUBS));
   evan->add_card(Card(JACK,HEARTS));
  evan_hand.push_back(Card(JACK,HEARTS));


  //Evan adds and then discards the upcard
 evan->add_and_discard( 
    Card(KING, DIAMONDS));
     //upcard and least card
     ASSERT_TRUE(evan_hand.size() == 5);

vector <Card> new_hand;
     new_hand.push_back(Card(ACE, DIAMONDS));
     new_hand.push_back(Card(QUEEN, DIAMONDS));
     new_hand.push_back(Card(TEN,CLUBS));
     new_hand.push_back(Card(JACK,HEARTS));
     new_hand.push_back(Card(KING, DIAMONDS));

    Card shoul_be_gone(NINE, SPADES);

bool is_correct = false;

  for(int i = 0; i < new_hand.size(); i++){
    if(new_hand[i] == shoul_be_gone){
      is_correct = false;
    }
    else if (new_hand[i] ==  Card(KING, DIAMONDS)){
      is_correct = true;
    }
    else{
      is_correct = false;
    }
  }
  
  ASSERT_TRUE(is_correct);
  delete evan;

}

TEST(test_add_discard_rb) { 

  vector<Card> evan_hand;
  //Evan's hand 
  Player * evan = Player_factory("Evan", "Simple");
  evan->add_card(Card(NINE, SPADES));
  evan_hand.push_back(Card(NINE, SPADES));
  evan->add_card(Card(ACE, DIAMONDS));
  evan_hand.push_back(Card(TEN, DIAMONDS));
  evan->add_card(Card(TEN, DIAMONDS));
  evan_hand.push_back(Card(TEN, DIAMONDS));
  evan->add_card(Card(TEN,CLUBS));
  evan_hand.push_back(Card(TEN,CLUBS));
   evan->add_card(Card(JACK,DIAMONDS));
  evan_hand.push_back(Card(JACK,DIAMONDS));


  //Evan adds and then discards the upcard
 evan->add_and_discard( 
    Card(KING, DIAMONDS));
     //upcard and least card
     ASSERT_TRUE(evan_hand.size() == 5);

vector <Card> new_hand;
     new_hand.push_back(Card(ACE, DIAMONDS));
     new_hand.push_back(Card(QUEEN, DIAMONDS));
     new_hand.push_back(Card(TEN,CLUBS));
     new_hand.push_back(Card(JACK,DIAMONDS));
     new_hand.push_back(Card(KING, DIAMONDS));

    Card shoul_be_gone(NINE, SPADES);

bool is_correct = false;

  for(int i = 0; i < new_hand.size(); i++){
    if(new_hand[i] == shoul_be_gone){
      is_correct = false;
    }
    else if (new_hand[i] ==  Card(KING, DIAMONDS)){
      is_correct = true;
    }
    else{
      is_correct = false;
    }
  }
  
  ASSERT_TRUE(is_correct);
  delete evan;

}

TEST(test_add_discard3) { 

  vector<Card> evan_hand;
  //Evan's hand 
  Player * evan = Player_factory("Evan", "Simple");
  evan->add_card(Card(NINE, SPADES));
  evan_hand.push_back(Card(NINE, SPADES));
  evan->add_card(Card(ACE, DIAMONDS));
  evan_hand.push_back(Card(ACE, DIAMONDS));
  evan->add_card(Card(QUEEN, DIAMONDS));
  evan_hand.push_back(Card(QUEEN, DIAMONDS));
  evan->add_card(Card(TEN,CLUBS));
  evan_hand.push_back(Card(TEN,CLUBS));
   evan->add_card(Card(JACK,CLUBS));
  evan_hand.push_back(Card(JACK,CLUBS));


  //Evan adds and then discards the upcard
 evan->add_and_discard( 
    Card(KING, DIAMONDS));
     //upcard and least card
     ASSERT_TRUE(evan_hand.size() == 5);

vector <Card> new_hand;
     new_hand.push_back(Card(ACE, DIAMONDS));
     new_hand.push_back(Card(QUEEN, DIAMONDS));
     new_hand.push_back(Card(TEN,CLUBS));
     new_hand.push_back(Card(JACK,CLUBS));
     new_hand.push_back(Card(KING, DIAMONDS));

    Card shoul_be_gone(NINE, SPADES);

bool is_correct = false;

  for(int i = 0; i < new_hand.size(); i++){
    if(new_hand[i] == shoul_be_gone){
      is_correct = false;
    }
    else if (new_hand[i] ==  Card(KING, DIAMONDS)){
      is_correct = true;
    }
    else{
      is_correct = false;
    }
  }
  
  ASSERT_TRUE(is_correct);

  delete evan;

}

TEST(test_simple_player_lead_card1_all_trump_but_one) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  vector <Card> bob_hand;
  bob_hand.push_back(Card(NINE, HEARTS));
  bob_hand.push_back(Card(TEN, HEARTS));
  bob_hand.push_back(Card(QUEEN, CLUBS));
  bob_hand.push_back(Card(KING, HEARTS));
  bob_hand.push_back(Card(ACE, HEARTS));


  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, DIAMONDS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card c (QUEEN, CLUBS);
  ASSERT_EQUAL(card_led, c); //check led card

  vector <Card> new_hand;
  new_hand.push_back(Card(NINE, HEARTS));
  new_hand.push_back(Card(TEN, HEARTS));
  new_hand.push_back(Card(KING, HEARTS));
  new_hand.push_back(Card(ACE, HEARTS));


  bool is_correct = false;

  for(int i = 0; i < new_hand.size(); i++){
    if(new_hand[i] == c){
      is_correct = false;
    }
    else{
      is_correct = true;
    }
  }
  
  ASSERT_TRUE(is_correct);

  delete bob;
  }

  TEST(test_add_and_discard_rb_and_lb){
  Player *evan = Player_factory("evan", "Simple");
  // all trump cards, with the rb and lb
  evan->add_card(Card(JACK, HEARTS)); 
  evan->add_card(Card(QUEEN, HEARTS)); 
  evan->add_card(Card(KING, HEARTS)); 
  evan->add_card(Card(ACE, HEARTS)); 
  evan->add_card(Card(JACK,DIAMONDS)); 

  Card lc(ACE,SPADES);
  Card uc(NINE, HEARTS);

  bool is_dealer = true;
  int round = 1;
  Suit trump;
  evan->make_trump(uc, is_dealer, round, trump);
  evan->add_and_discard(uc);
  ASSERT_EQUAL(evan->play_card(lc, trump), Card(QUEEN,HEARTS));
  ASSERT_EQUAL(evan->lead_card(trump),Card(JACK, HEARTS)); //highest rb
  ASSERT_EQUAL(evan->lead_card(trump),Card(JACK, DIAMONDS)); //  lb
  ASSERT_EQUAL(evan->lead_card(trump),Card(ACE, HEARTS)); // highest non b
  ASSERT_EQUAL(evan->lead_card(trump),Card(KING, HEARTS)); // second highets non b
 

  delete evan; 
}

  TEST(test_add_and_discard_lb){
  Player *evan = Player_factory("evan", "Simple");
  // all trump cards, all follow suit of the upcard, upcard is the least
  evan->add_card(Card(NINE, CLUBS)); 
  evan->add_card(Card(QUEEN, HEARTS)); 
  evan->add_card(Card(KING, HEARTS)); 
  evan->add_card(Card(ACE, HEARTS)); 
  evan->add_card(Card(JACK,DIAMONDS)); 

  Card lc(ACE,SPADES);
  Card uc(NINE, HEARTS);

  bool is_dealer = true;
  int round = 1;
  Suit trump;
  evan->make_trump(uc, is_dealer, round, trump);
  evan->add_and_discard(uc); // discards of nine of clubs
  ASSERT_EQUAL(evan->play_card(lc, trump), Card(NINE,HEARTS));
  ASSERT_EQUAL(evan->lead_card(trump),Card(JACK, DIAMONDS)); //highest lb//  lb
  ASSERT_EQUAL(evan->lead_card(trump),Card(ACE, HEARTS)); // highest non b
  ASSERT_EQUAL(evan->lead_card(trump),Card(KING, HEARTS));
  ASSERT_EQUAL(evan->lead_card(trump),Card(QUEEN, HEARTS));
  
  delete evan; 
}

 TEST(test_add_and_discard_rb){
  Player *evan = Player_factory("evan", "Simple");
  // all trump cards, all follow suit of the upcard, upcard is the least
  evan->add_card(Card(NINE, CLUBS)); 
  evan->add_card(Card(QUEEN, HEARTS)); 
  evan->add_card(Card(KING, HEARTS)); 
  evan->add_card(Card(ACE, HEARTS)); 
  evan->add_card(Card(JACK,HEARTS)); 

  Card lc(ACE,SPADES);
  Card uc(NINE, HEARTS);

  bool is_dealer = true;
  int round = 1;
  Suit trump;
  evan->make_trump(uc, is_dealer, round, trump);
  evan->add_and_discard(uc); // discards of nine of clubs
  ASSERT_EQUAL(evan->play_card(lc, trump), Card(NINE,HEARTS));
  ASSERT_EQUAL(evan->lead_card(trump),Card(JACK, HEARTS)); //highest lb//  lb
  ASSERT_EQUAL(evan->lead_card(trump),Card(ACE, HEARTS)); // highest non b
  ASSERT_EQUAL(evan->lead_card(trump),Card(KING, HEARTS));
  ASSERT_EQUAL(evan->lead_card(trump),Card(QUEEN, HEARTS));
  
  delete evan; 
}

 TEST(test_add_and_discard_no_bpwers){
  Player *evan = Player_factory("evan", "Simple");
  // all trump cards, all follow suit of the upcard, upcard is the least
  evan->add_card(Card(NINE, CLUBS)); 
  evan->add_card(Card(QUEEN, HEARTS)); 
  evan->add_card(Card(KING, HEARTS)); 
  evan->add_card(Card(ACE, HEARTS)); 
  evan->add_card(Card(TEN,CLUBS)); 

  Card lc(ACE,SPADES);
  Card uc(NINE, HEARTS);

  bool is_dealer = true;
  int round = 1;
  Suit trump;
  evan->make_trump(uc, is_dealer, round, trump);
  evan->add_and_discard(uc); // discards of nine of clubs
  ASSERT_EQUAL(evan->play_card(lc, trump), Card(TEN,CLUBS));//highest lb//  lb
  ASSERT_EQUAL(evan->lead_card(trump),Card(ACE, HEARTS)); // highest non b
  ASSERT_EQUAL(evan->lead_card(trump),Card(KING, HEARTS));
  ASSERT_EQUAL(evan->lead_card(trump),Card(QUEEN, HEARTS));
  ASSERT_EQUAL(evan->lead_card(trump),Card(NINE, HEARTS));

  
  delete evan; 
}

TEST_MAIN()
