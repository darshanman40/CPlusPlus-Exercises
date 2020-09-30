//
//  TripleGameX.cpp
//  
//
//  Created by Darshan Manchekar on 8/31/19.
//

#include <iostream>
#include <ctime>

void PrintIntroduction(int Difficulty)
{
    std::cout << "\n\nYou are breaking into a level " << Difficulty;
    std::cout << " secure server room...\nEnter the correct code to continue...\n\n";
}

bool PlayGame(int Difficulty)
{
    
     PrintIntroduction(Difficulty);
    
    //Declare 3 number code
    const int OffSet = 1;
    int CodeA = rand() % Difficulty + OffSet; // 4;
    int CodeB = rand() % Difficulty + OffSet; // 3;
    int CodeC = rand() % Difficulty + OffSet; // 2;
    
    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;
    
    //Print sum and product to terminal
    std::cout << "\n+ There are 3 numbers in the code";
    std::cout << "\n+ The codes add-up to: " << CodeSum;
    std::cout << "\n+ The codes multiply to give: " << CodeProduct;
    
    int GuessA, GuessB, GuessC;
    std::cout << std::endl;
    std::cin >> GuessA >> GuessB >> GuessC;
    
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;
    
    
    //Check if the player guess is correct
    if (GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        std::cout << "\n*** Well done agent you extracted the file! ***";
        return true;
    }
    else
    {
        std::cout << "\n*** You entered the wrong code! Careful agent! Try Again! ***";
        return false;
    }
    
    return true;
}


int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        return -1;
    }
    srand(time(NULL)); // create new sequence based on time of day
    int LevelDifficulty = 1;
    int MaxDifficulty = std::atoi(argv[1]);
    
    std::cout << "\nYou are secret Agent Breaking into facility to extract files. Good Luck!\n";
    while (LevelDifficulty <= MaxDifficulty) // loop game untill all levels are completed
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear(); // clears any errors
        std::cin.ignore(); // Discards the buffer
        if (bLevelComplete) {
            // Increase the level of difficulty
            ++LevelDifficulty;
        }
    }
    std::cout << "\n*** Great work agent! You got all the files! Now get out of there ***\n";
    
    
    return 0;
}
