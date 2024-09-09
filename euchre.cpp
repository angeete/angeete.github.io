#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"
using namespace std;

class Game {
 public:
  void play(){
    while(score1 < max_points && score2 < max_points){
      cout << "Hand " << hand << endl;
      shuffle();
      int dealer = hand % 4;
      cout << *players[dealer] << " deals" << endl;
      deal(players[dealer], players[(dealer + 1) % 4],
           players[(dealer + 2) % 4],players[(dealer + 3) % 4]);
      make_trump((dealer + 1) % 4);
      int tempScore1 = 0;
      int tempScore2 = 0;
      int led = (dealer + 1) % 4;
      for(int i = 0; i < 5; i++){
        play_hand(tempScore1, tempScore2, led, trump);
      }
      end_hand(tempScore1, tempScore2);
      cout << *players[0] << " and " << *players[2] << " have " << 
           score1 << " points" << endl;
      cout << *players[1] << " and " << *players[3] << " have " << 
           score2 << " points" << endl << endl;
      hand++;
    }
    if(score1 >= max_points){
      cout << *players[0] << " and " << *players[2] << " win!" << endl;
    } else if(score2 >= max_points){
      cout << *players[1] << " and " << *players[3] << " win!" << endl;
    }
    end_game();
  }
  
  void playerMake(Player *one, Player *two, Player *three, Player *four){
    players.push_back(one);
    players.push_back(two);
    players.push_back(three);
    players.push_back(four);
  }

  Game(string inPack, string shuffled, int max){
    if(shuffled == "shuffle"){
        shuffles = true;
    }
    
    ifstream fin;
    fin.open(inPack);
    pack = Pack(fin);

    max_points = max;
  } 
  
 private:
  vector<Player*> players;
  Pack pack;
  bool shuffles = false;
  int max_points;
  int score1 = 0;
  int score2 = 0;
  int hand = 0;
  Suit trump;  
  Card upCard;
  int trumper;

  void shuffle(){
    if(shuffles){
      pack.shuffle();
    }
  }

  void deal(Player *one, Player *two, Player *three, Player *four){
    pack.reset();
    for(int i = 0; i < 20; i++){
      if(i < 3 || (i < 12 && i > 9)){
        two->add_card(pack.deal_one());
      } else if ((i > 2 && i < 5) || (i < 15 && i > 11)){
        three->add_card(pack.deal_one());
      } else if ((i > 4 && i < 8) || (i < 17 && i > 14)){
        four->add_card(pack.deal_one());
      } else if ((i > 7 && i < 10) || (i < 20 && i > 16)){
        one->add_card(pack.deal_one());
      }
    }
    upCard = pack.deal_one();
  }

  void make_trump(int lead){
    cout << upCard << " turned up" << endl;
    int round = 1;
    
    for(int i = 0; i < 8; i++){
      if(i == 4){
        round = 2;
      }

      if(make_trump_helper(i, round, lead) == 1){
        return;
      }
    }
  }

  int make_trump_helper(int i, int round, int lead){
    if(i == 3 || i == 7){
      if(players[(lead + i) % 4]->make_trump(upCard, true, round, trump)){
        cout << *players[(lead + i) % 4] << " orders up " << trump 
              << endl << endl; 
        if(round == 1){
          players[lead - 1]->add_and_discard(upCard);
        }
        trumper = (lead + i) % 4;
        return 1;
      } else {
        cout << *players[(lead + i) % 4] << " passes" << endl;
      }
    } else {
      if(players[(lead + i) % 4]->make_trump(upCard, false, round, trump)){
        cout << *players[(lead + i) % 4] << " orders up " << trump 
              << endl << endl;          
        if(round == 1){
          players[(lead + 3) % 4]->add_and_discard(upCard);
        }      
        trumper = (lead + i) % 4;
        return 1;
      } else {
        cout << *players[(lead + i) % 4] << " passes" << endl;
      }
    }
    return 0;
  }

  void play_hand(int &team1, int &team2, int &leader, Suit trump){
    Card card1 = players[leader]->lead_card(trump);
    cout << card1 << " led by " << *players[leader] << endl;

    Card card2 = players[(leader + 1) % 4]->play_card(card1, trump);
    cout << card2 << " played by " << *players[(leader + 1) % 4] << endl;

    Card card3 = players[(leader + 2) % 4]->play_card(card1, trump);
    cout << card3 << " played by " << *players[(leader + 2) % 4] << endl;
    
    Card card4 = players[(leader + 3) % 4]->play_card(card1, trump);
    cout << card4 << " played by " << *players[(leader + 3) % 4] << endl;

    if(Card_less(card2, card1, card1, trump) && 
       Card_less(card3, card1, card1, trump) &&
       Card_less(card4, card1, card1, trump)){

      cout << *players[leader] << " takes the trick" << endl << endl;
    } else if(Card_less(card1, card2, card1, trump) && 
              Card_less(card3, card2, card1, trump) &&
              Card_less(card4, card2, card1, trump)){
      
      cout << *players[(leader + 1) % 4] << " takes the trick" << endl << endl;
      leader = (leader + 1) % 4;
    } else if(Card_less(card1, card3, card1, trump) && 
              Card_less(card2, card3, card1, trump) &&
              Card_less(card4, card3, card1, trump)){
      
      cout << *players[(leader + 2) % 4] << " takes the trick" << endl << endl;
      leader = (leader + 2) % 4;
    } else if(Card_less(card1, card4, card1, trump) && 
              Card_less(card2, card4, card1, trump) &&
              Card_less(card3, card4, card1, trump)){
      
      cout << *players[(leader + 3) % 4] << " takes the trick" << endl << endl;
      leader = (leader + 3) % 4;
    }

    if(leader % 2 == 0){
      team1++;
    }else{
      team2++;
    }
  }

  void end_hand(int tempScore1, int tempScore2){
    if(trumper % 2 == 0){
      if(tempScore1 == 3 || tempScore1 == 4){
        cout << *players[0] << " and " << *players[2] << " win the hand" << endl;
        score1++;
      } else if(tempScore1 == 5){
        cout << *players[0] << " and " << *players[2] << " win the hand" << endl;
        cout << "march!" << endl;
        score1 = score1 + 2;
      } else if(tempScore2 > 2){
        cout << *players[1] << " and " << *players[3] << " win the hand" << endl;
        cout << "euchred!" << endl;
        score2 = score2 + 2;
      }
    } else if(trumper % 2 == 1){
      if(tempScore2 == 3 || tempScore2 == 4){
        cout << *players[1] << " and " << *players[3] << " win the hand" << endl;
        score2++;
      } else if(tempScore2 == 5){
        cout << *players[1] << " and " << *players[3] << " win the hand" << endl;
        cout << "march!" << endl;
        score2 = score2 + 2;
      } else if(tempScore1 > 2){
        cout << *players[0] << " and " << *players[2] << " win the hand" << endl;
        cout << "euchred!" << endl;
        score1 = score1 + 2;
      }
    }
  }
  void end_game(){
    for (size_t i = 0; i < players.size(); ++i) {
      delete players[i];
    }
  }
};
int main(int argc, char **argv) {
  if((argc != 12)||(string(argv[2])!="shuffle"&&string(argv[2])!="noshuffle")||
    (stoi(argv[3])<1||stoi(argv[3])>100)||
    (string(argv[5])!="Simple"&&string(argv[5])!="Human")||
    (string(argv[7])!="Simple"&&string(argv[7])!="Human")||
    (string(argv[9])!="Simple"&&string(argv[9])!="Human")||
    (string(argv[11])!="Simple"&&string(argv[11])!="Human")){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    return 1;
  }
  string infile = string(argv[1]);
  ifstream fin;
  fin.open(infile);
  if (!fin.is_open()){
    cout << "Error opening " << infile << endl;
    return 2;
  }
  cout << string(argv[0]) << " " << string(argv[1]) << " ";
  cout << string(argv[2]) << " " << string(argv[3]) << " ";
  cout << string(argv[4]) << " " << string(argv[5]) << " ";
  cout << string(argv[6]) << " " << string(argv[7]) << " ";
  cout << string(argv[8]) << " " << string(argv[9]) << " ";
  cout << string(argv[10]) << " " << string(argv[11]) << " " << endl;
  Player *one = Player_factory(string(argv[4]), string(argv[5]));
  Player *two = Player_factory(string(argv[6]), string(argv[7]));
  Player *three = Player_factory(string(argv[8]), string(argv[9]));
  Player *four = Player_factory(string(argv[10]), string(argv[11]));
  string shuffled = string(argv[2]);
  Game game(string(argv[1]), shuffled, atoi(argv[3]));
  game.playerMake(one, two, three, four);
  game.play();
}