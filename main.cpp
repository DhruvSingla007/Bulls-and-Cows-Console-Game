/*
This is the console executable, that makes use of the BullCow class
This acts as a view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using Ftext = std::string;
using int32 = int;

// instantiate a new game
FBullCowGame BCGame;

// declaring the functions
void PrintIntro();
void PlayGame();
Ftext GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

int main() {

	do
	{
		// INTRODUCE THE GAME
		PrintIntro();

		// PLAY THE GAME
		PlayGame();
	} 
	
	while (AskToPlayAgain());

}

// printing the intro of the game to the console
void PrintIntro() {
	//constexpr int32 WORD_LENGTH = BCGame.GetHiddenWordLength;
	std::cout << "Welcome to the bulls and cows game\n\n";
	std::cout << "Can you guess " << BCGame.GetHiddenWordLength() << " letter word" << std::endl;
	return;
}

Ftext GetValidGuess() {

	// declaring the status
	EGuessStatus Status;
	Ftext Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << " :: Enter your Guess : ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram word" << std::endl;
			break;
		case EGuessStatus::World_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter lowercase letters." << std::endl;
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get a valid status
	return Guess;
}

void PlayGame() {

	// reset the game
	BCGame.Reset();

	// get the max tries
	int32 MaxTries = BCGame.GetMaxTries();

	/*loop asking for guesses while the game is not WON
	and there is still tries remaining*/
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		
		// getting a valid guess
		Ftext Guess = GetValidGuess();

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of bulls and cows
		std::cout << "Bulls : " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows : " << BullCowCount.Cows << std::endl;

		std::cout << "Your Guess was : " << Guess << std::endl;
	}

	// TODO summarise game
	PrintGameSummary();
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n) : ";
	Ftext Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "\n\nCongratulations! you have won the game :)\n\n";
	} 
	if (BCGame.GetCurrentTry() > BCGame.GetMaxTries()) {
		std::cout << "\n\nBetter luck next time\n\n";
	}
	return;
}
