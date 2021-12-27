#include <iostream>
#include <fstream> 
#include <time.h>
#include <string>
#include <algorithm>

using namespace std;

int guessed = false;
int guessCount;
int guessRemaining;
string word;
int revealedChars[40] = {};
int unrevealedChars;
string wordArray[1000] = {};

int randomNumber(int digits){
  int random = rand() % digits;
return random;
}

void generateWord(){
  word = wordArray[randomNumber(1000)];
  for (int i = 0; i < word.size(); i++){
   revealedChars[i] = 95;
  }
}

void revealChar() {
int loop = 0;
  while(loop == 0) {
     for (int i=0; i < 40; i++) {
        int randomNum = randomNumber(word.size());
       int randChar = word[randomNum];
      if (i == randomNum && revealedChars[i] == 95) {
        revealedChars[i] = randChar;
        loop = 1;
        break;
      }
    }
  }
}

void printCurrentText() {
for (int i = 0; i < word.size(); i++){
    cout << char(revealedChars[i]) << " ";
  }
}


void wordGuess() {

  string input;
  cout << "Guess this word (" << guessRemaining << "/" << guessCount << " new letter reveal!): " << "\n";
  guessRemaining--;
  printCurrentText();
  cout << "\n";
  cin >> input;
  if (input == word) {
    guessed = true;
  }
}

void gameLoop() {
  while (guessed == false) {
    int blankLeft=0;
      for (int i = 0; i < guessCount; i++) {
          for (int i=0; i < 40; i++) {
             if (revealedChars[i] == 95) {
               blankLeft++;
              }
          }
         if (blankLeft==0) {return;}
          wordGuess();
          if(guessed == true) {break;}
      }
    guessRemaining = guessCount;
    revealChar();
  }
}

int main() {
    srand(time(NULL));
    char replay = 'Y';
  ifstream words;
  words.open("words.txt");

string line;
for (int i=0;i < 1000;i++){
  getline(words, line);
  wordArray[i] = line;
}

    cout << "Welcome to the word guessing game! this is a simple, text-based game where you have to guess the word, have fun!" << "\n";
    cout << "How many guesses do you want to have before adding a letter?: ";
    
    cin >> guessCount;
    guessRemaining = guessCount;
    generateWord();
    revealChar();
    gameLoop();

    while (replay == 'Y') {
      if (guessed==true){
        cout << "Congratulations! The word was: " << word << "!" << "\n";
        cout << "Do you want to play again? (Y/N)" << "\n";
        cin >> replay;
        guessed = false;
      }
      else if (guessed==false){
        cout << "You lost! The word was: " << word << "!" << "\n";
        cout << "Do you want to play again? (Y/N)" << "\n";
        cin >> replay;
        guessed = false;
      }

    if (replay == 'Y') {
      generateWord();
      revealChar();
      gameLoop();
    }
  }
  return 0;
}