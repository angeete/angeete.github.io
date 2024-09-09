#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <array>

using namespace std;

  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(){
  next = 0;
  for(int i = 0; i < PACK_SIZE; i++){
    if(i < 6){
      cards[i] = Card(static_cast<Rank>(i + 7) , SPADES);
    } else if (i < 12){
      cards[i] = Card(static_cast<Rank>(i + 1) , HEARTS);
    } else if (i < 18){
      cards[i] = Card(static_cast<Rank>(i - 5) , CLUBS);
    } else if (i < 24){
      cards[i] = Card(static_cast<Rank>(i - 11) , DIAMONDS);
    }
  }
}

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(istream& pack_input){
  next = 0;
  string word;
  int wordNum = 1;
  int cardNum = 0;
  Rank rank;
  Suit suit;
  while(pack_input >> word){
    if(wordNum % 3 == 1){
      if(word == "Nine"){
        rank = NINE;
      }else if(word == "Ten"){
        rank = TEN;
      }else if(word == "Jack"){
        rank = JACK;
      }else if(word == "Queen"){
        rank = QUEEN;
      }else if(word == "King"){
        rank = KING;
      }else if(word == "Ace"){
        rank = ACE;
      }
    }
    if(wordNum % 3 == 0){
      if(word == "Spades"){
        suit = SPADES;
      }else if(word == "Hearts"){
        suit = HEARTS;
      }else if(word == "Clubs"){
        suit = CLUBS;
      }else if(word == "Diamonds"){
        suit = DIAMONDS;
      }
      cards[cardNum] = Card(rank, suit);
      cardNum++;
    }
    wordNum++;
  }
}
  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
  next++;
  return cards[next - 1];
}

  // EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){
  next = 0;
}

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){
  array<Card, PACK_SIZE / 2> deckTop;
  array<Card, PACK_SIZE / 2> deckBottom;
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < PACK_SIZE; j++){
      if (j < 12){
        deckTop[j] = cards[j];
      }else if(j < PACK_SIZE){
        deckBottom[j - 12] = cards[j];
      }
    }
    
    for(int k = 0; k < PACK_SIZE; k++){
      if (k % 2 == 0){
        cards[k] = deckBottom[k / 2];
      } else if (k % 2 == 1){
        cards[k] = deckTop[(k - 1) / 2];
      }
    }
  }
  reset();
}

  // EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
  if(next == PACK_SIZE){
    return true;
  }
  return false;
}