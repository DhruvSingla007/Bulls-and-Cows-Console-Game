#pragma once
#include<string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// include class keyword in enumerations because otherwise
// we can't make any other enumerations with the same word like OK
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	World_Length,
	Not_Lowercase
};

class FBullCowGame {
public:

	FBullCowGame(); // default constructor
	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString Guess);

	/*
	provide bulls and cows for counting bulls and cows, 
	and increading turn number
	*/

	FBullCowCount SubmitValidGuess(FString);


private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	//bool IsIsogram;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString);
	bool IsLowerCase(FString);
};