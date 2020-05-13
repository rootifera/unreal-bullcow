// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    SetupGame();

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug Line
    PrintLine(TEXT("Number of Possible Words is %i"), Words.Num());
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() -1)];
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("You have %i lives availabe"), Lives);

    const TCHAR HW[] = TEXT("cakes");
    HW;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine("\nWanna play again?");
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{

    // is the guess incorrect, if so give warning and decrement life.

    // is the guess correct?
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    // check if the Guess and HiddenWord are same Len, if not give a warning.
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters! Try again!"));
        return;
    }

    PrintLine(TEXT("Lost a life"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left, GGWP"));
        PrintLine(TEXT("\nThe hidden word was %s"), *HiddenWord);
        EndGame();
        return;
    }

    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
{

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &ArrayToValidate) const
{

    TArray<FString> ValidWords;

    for (auto Item : ArrayToValidate)
    {
        if (Item.Len() >= 4 && Item.Len() <= 8)
        {
            if (IsIsogram(Item))
            {
                ValidWords.Emplace(Item);
            }
        }
    }

    return ValidWords;
}