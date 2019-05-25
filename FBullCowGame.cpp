#include "FBullCowGame.h"
#include <map>
#define TMap std::map // to make syntax unreal friendly

FBullCowGame::FBullCowGame() {
	Reset();
}

void FBullCowGame::Reset() {

	bGameIsWon = false;

	MyCurrentTry = 1;

	const FString HIDDEN_WORD = "muskan"; // this word must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	return;
}

int FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries = { {3,5} ,{4,5},{5,7},{6,10},{7,10} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int FBullCowGame::GetCurrentTry() const{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) {
	// if the guess isn't isogram, 
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}

	// if the guess isn't all lowercase,
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}

	// if the guess length is wrong, 
	else if (Guess.length() != MyHiddenWord.length()) {
		return EGuessStatus::World_Length;
	}

	// otherwise
	else {
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments turns and return counts

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	// increment the turn number
	MyCurrentTry++;
	
	// setup a return variable
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();
	
	
	// loop through all letters in the hidden word
	for (int32 HdnChar = 0; HdnChar < HiddenWordLength; HdnChar++) {
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[HdnChar]){
				// if they are in the same place
				if (HdnChar == GChar){
					// increment bulls
					BullCowCount.Bulls++;
				} else {
					// increment cows
					BullCowCount.Cows++;
				}
			}
		}
	}	
	
	// if thhey match then 
	   // increment bulls if they are in the same place
	   // increment cows if not
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) {
	// treat 0 and 1 letter word as isograms because the letter can't be repeated
	if (Guess.length() <= 1) {
		return true;
	}
		
	// setup a map
	TMap<char , bool> LetterSeen;

	// loop through all the letters in the map
	for (auto Letter : Guess) { // for all letters of the hidden word
		Letter = tolower(Letter); // handle mixed case
		
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) {
	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
