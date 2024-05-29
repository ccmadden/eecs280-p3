#include <fstream>
#include <iostream>
using namespace std;
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"

class Game {
   public:
    Game();  // constructor

    Game(Pack pack_in, string shuffle_in, int pointsToWin_in,
         vector<Player *> players_in) {
        players = players_in;
        pack = pack_in;
        points_to_win = pointsToWin_in;
        shuffle_dec = shuffle_in;
    }

    void play() {
        bool neither_team_has_won = true;
        while (neither_team_has_won == true && !pack.empty()) 
        {team1_trick_wins_hand = 0;
            team2_trick_wins_hand = 0;dealer = players[hands % 4];
            left_to_dealer = players[(((hands % 4) + 1) % 4)];
            if (team1_points >= points_to_win) {
                cout << players[0]->get_name() << " and " << players[2]->get_name()
                     << " win!" << endl;
                neither_team_has_won = false;
                return;
            }
            if (team2_points >= points_to_win) {
                cout << players[1]->get_name() << " and " << players[3]->get_name()
                     << " win!" << endl;
                neither_team_has_won = false;
                return;
            }
            shuffle();
            deal();
            cout << "Hand " << hands << endl;
            cout << dealer->get_name() << " deals" << endl;
            cout << upcard;  // WOOH!
            cout << " turned up" << endl;
            make_trump();
            cout << endl;
            play_hand();
            score();
            hands++;
        }
    };

   private:
    vector<Player *> players;
    Pack pack;
    string shuffle_dec;
    vector<string> types;
    string pack_filename;
    int points_to_win;
    int team1_points = 0;
    int team2_points = 0;
    int team1_trick_wins_hand = 0;
    int team2_trick_wins_hand = 0;
    int team_called_trump = 0;
    int hands = 0;
    Player *dealer;
    Card upcard;
    Suit trump_suit;
    int winnerPlayerIndex = 1;
    Player *left_to_dealer;

    void shuffle() {
        if (shuffle_dec == "shuffle"){
           pack.shuffle();
        }
    }

    void deal() {
      pack.reset();
        dealer = players[hands % 4];
        // 3232 pattern
        for (int i = 0; i < players.size(); ++i) {
            if (i % 2 == 0) {
                players[((hands % 4) + 1 + i) % 4]->add_card(pack.deal_one());
            }
                players[((hands % 4) + 1 + i) % 4]->add_card(pack.deal_one());
                players[((hands % 4) + 1 + i) % 4]->add_card(pack.deal_one());
          
        }
        // 2323 pattern
        for (int i = 0; i < players.size(); ++i) {
                players[((hands % 4) + 1 + i) % 4]->add_card(pack.deal_one());
                players[((hands % 4) + 1 + i) % 4]->add_card(pack.deal_one());
            if (i % 2 == 1) {
                players[((hands % 4) + 1 + i) % 4]->add_card(pack.deal_one());
            }
        }
        upcard = pack.deal_one();
    }

    void make_trump() {
        bool is_dealer = false;
        Suit order_up_suit = upcard.get_suit();
        const int MAX_ROUNDS = 2;

        for (int round = 1; round <= MAX_ROUNDS; ++round) {
            for (int i = 0; i < players.size(); ++i) {
                if (i == (hands % 4)) {
                    is_dealer = true;}
                if (players[((hands % 4) + 1 + i) % 4]->make_trump(
                        upcard, is_dealer, round, order_up_suit)) {
                    trump_suit = order_up_suit;
                    if (round == 1) {
                        dealer->add_and_discard(upcard);
                    }
                    cout << players[((hands % 4) + 1 + i) % 4]->get_name()
                         << " orders up " << trump_suit << endl;
                    if ((((hands % 4) + 1 + i) % 4) % 2 == 0) {
                        team_called_trump = 1;
                    }if ((((hands % 4) + 1 + i) % 4) % 2 == 1) {
                        team_called_trump = 2;
                    }return;
                } else { cout << players[((hands % 4) + 1 + i) % 4]->get_name() 
                    << " passes" << endl;
                }
            }
        }
    }

    void play_hand() {
        const int tricksInHand = 5;
        // int defaultleadPlayerIndex = 1;
        Card high_card_first;
        Card high_card_second;
        Card ultimate_high_card;

        Player *lead;

        for (int i = 0; i < tricksInHand; ++i) {
            if (i == 0) {
                lead = left_to_dealer;
                winnerPlayerIndex = (winnerPlayerIndex + (hands % 4))%4;} else {
                lead = players[(winnerPlayerIndex) % 4];
            }
            Card ledcard = lead->lead_card(trump_suit); operator<<(cout, ledcard);
            cout << " led by " << lead->get_name() << endl;
            Card a = 
            players[(winnerPlayerIndex + 1) % 4]->play_card(ledcard, trump_suit);
            cout << a; cout << " played by " << 
            players[(winnerPlayerIndex + 1) % 4]->get_name() << endl;Card b = 
            players[(winnerPlayerIndex + 2) % 4]->play_card(ledcard, trump_suit);
            cout << b; cout << " played by " << 
            players[(winnerPlayerIndex + 2) % 4]->get_name() << endl;
            Card c =
             players[(winnerPlayerIndex + 3) % 4]->play_card(ledcard, trump_suit);
            cout << c; cout << " played by " << 
            players[(winnerPlayerIndex + 3) % 4]->get_name()<< endl;
            
            
            if (Card_less(a, b, ledcard, trump_suit)) {high_card_first = b;
            } else { high_card_first = a;
            } if (Card_less(c, ledcard, ledcard, trump_suit))
             { high_card_second = ledcard;
            } else { high_card_second = c;}if 
            (Card_less(high_card_first, high_card_second, ledcard, trump_suit)) {
                ultimate_high_card = high_card_second;} else {
                ultimate_high_card = high_card_first;
            }if (ultimate_high_card == ledcard) { winnerPlayerIndex = 
            (winnerPlayerIndex) % 4;
            } else if (ultimate_high_card == b) {winnerPlayerIndex 
            = (winnerPlayerIndex + 2) % 4;
            } else if (ultimate_high_card == a) { winnerPlayerIndex 
            = (winnerPlayerIndex + 1) % 4;
            } else if (ultimate_high_card == c) {winnerPlayerIndex 
            = (winnerPlayerIndex + 3) % 4;
            }

            if (winnerPlayerIndex % 2 == 0) {
                team1_trick_wins_hand++;
            } else if (winnerPlayerIndex % 2 == 1) {
                team2_trick_wins_hand++;
            }
            cout << players[winnerPlayerIndex]->get_name() 
            << " takes the trick" << endl
                 << endl;
        }
    }

    void score() {
        if (team_called_trump == 1) {
            if (team1_trick_wins_hand == 3 || team1_trick_wins_hand == 4)
             { team1_points++;
                cout << players[0]->get_name() << " and " 
                << players[2]->get_name()
                     << " win the hand" << endl;
            } else if (team1_trick_wins_hand == 5) {team1_points += 2;
                cout << players[0]->get_name() << " and " 
                << players[2]->get_name()
                     << " win the hand" << endl;
                cout << "march!" << endl;
            } else if (team1_trick_wins_hand <= 2) {team2_points += 2;
                cout << players[1]->get_name() << " and " 
                << players[3]->get_name()
                     << " win the hand" << endl; cout << "euchred!" << endl;
            }
        } else if (team_called_trump == 2) {
            if (team2_trick_wins_hand == 3 || team2_trick_wins_hand == 4) {
                team2_points++;
                cout << players[1]->get_name() << " and " 
                << players[3]->get_name()
                     << " win the hand" << endl;
            } else if (team2_trick_wins_hand == 5) {
                team2_points += 2;
                cout << players[1]->get_name() << " and " 
                << players[3]->get_name()
                     << " win the hand" << endl; cout << "march!" << endl;
            } else if (team2_trick_wins_hand <= 2) {
                team1_points += 2;
                cout << players[0]->get_name() << " and " 
                << players[2]->get_name()
                     << " win the hand" << endl; cout << "euchred!" << endl;
            }
        }
        cout << players[0]->get_name() << " and " 
        << players[2]->get_name() << " have "
             << team1_points << " points" << endl;
        cout << players[1]->get_name() << " and " 
        << players[3]->get_name() << " have "
             << team2_points << " points" << endl << endl;
    }
};

int main(int argc, char **argv) {
    // read in command line arguments
    string executable_file = argv[0];
    string pack_filename = argv[1];
    string shuffle_decision = argv[2];
    int points_to_win = stoi(argv[3]);
    string name_0 = argv[4];
    string type_0 = argv[5];
    string name_1 = argv[6];
    string type_1 = argv[7];
    string name_2 = argv[8];
    string type_2 = argv[9];
    string name_3 = argv[10];
    string type_3 = argv[11];

    // checking for errors
    if (argc != 12 || !(points_to_win <= 100 && points_to_win >= 1) ||
        (shuffle_decision != "shuffle" && shuffle_decision != "noshuffle") ||
        (type_0 != "Simple" && type_0 != "Human") ||
        (type_1 != "Simple" && type_1 != "Human") ||
        (type_2 != "Simple" && type_2 != "Human") ||
        (type_3 != "Simple" && type_3 != "Human")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    } else {
        cout << executable_file << " " << pack_filename << " " 
        << shuffle_decision << " "
             << points_to_win << " " << name_0 << " " << type_0 
             << " " << name_1 << " "
             << type_1 << " " << name_2 << " " << type_2 << " " 
             << name_3 << " " << type_3
             << " " << endl;
    }

    ifstream ifs(pack_filename);
    if (!(ifs.is_open())) {
        cout << "Error opening " << pack_filename << endl;
    }

    Pack p_in(ifs);

    std::vector<Player *> players;
    players.push_back(Player_factory(name_0, type_0));
    players.push_back(Player_factory(name_1, type_1));
    players.push_back(Player_factory(name_2, type_2));
    players.push_back(Player_factory(name_3, type_3));
    
    Game game(p_in, shuffle_decision, points_to_win, players);
    game.play();

    // end of the game do everything above this
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
    return 0;
}
