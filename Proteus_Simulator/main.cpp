#include "FEHLCD.h"
#include "FEHImages.h"
#include "FEHLCD.h"
#include "bits/stdc++.h"
#include "FEHUtility.h"
#include "LCDColors.h"
#include "FEHRandom.h"

using namespace std;

int runGame();
void displayGameOver(int);
void displayScores(int []);
void waitForBackButton();

int main()
{
    // FEHImage startButton;
    // startButton.Open("Untitled.png");
    // startButton.Draw(0,0);

    int xPosition, yPosition;
    int highScoreList[4] = {4,3,2,1};

    while (1) {
        LCD.Clear();
        FEHImage titleScreen;
        titleScreen.Open("New Piskel.png");
        titleScreen.Draw(0,0);

        while(!LCD.Touch(&xPosition, &yPosition)){}

        /* plays the game*/
        if(xPosition <= 80 /*&& yPosition > 100*/){
            LCD.Clear();
            // runs the game and writes the game over screen with its output
            int score = runGame();
            // add line to add score to highScoreList
            highScoreList[3] = score;
            sort(highScoreList, highScoreList + 4, greater<int>());
            displayGameOver(score);

            LCD.WriteLine("click in the upper right to go back");

            waitForBackButton();

        /* score board*/
        }else if(xPosition <= 160 && xPosition > 80){
            displayScores(highScoreList);
            LCD.WriteLine("click in the upper right to go back");
            waitForBackButton();

        /* displays the instructions*/
        }else if(xPosition <= 240 && xPosition > 160){
            LCD.Clear();
            LCD.WriteLine("instructions clicked");
            LCD.WriteLine(" ");
            LCD.WriteLine(" ");
            LCD.WriteLine("Click on the buttons on the screen to move your character. Your goal is to make it to the very end on the right, avoiding any falls to your death.");
            LCD.WriteLine("click in the upper right to go back");

            waitForBackButton();

        /* displays the credits*/
        }else if(xPosition <= 320 && xPosition > 240){
            LCD.Clear();
            LCD.WriteLine("credits clicked");
            LCD.WriteLine(" ");
            LCD.WriteLine(" ");
            LCD.WriteLine("Made by Erol and Nolan");
            LCD.WriteLine("click in the upper right to go back");

            waitForBackButton();



        }


    }
    return 0;
}

/* runs the game and returns the score*/
int runGame(){
    LCD.WriteLine("Play Game Here");
    return Random.RandInt();
}

/* prints the game over screen with the results from the game*/
void displayGameOver(int score){
    // TODO
}

/* clears the screen and displays the top 3 high scores*/
void displayScores(int highScoreList[]){
    int xPosition, yPosition;
    LCD.Clear(BLACK);
    LCD.WriteLine("Top Scores");
    LCD.WriteLine("1: " + to_string(highScoreList[0]));
    LCD.WriteLine("2: " + to_string(highScoreList[1]));
    LCD.WriteLine("3: " + to_string(highScoreList[2]));
}

/* creates a white square in the top right and puases the program until the user clicks it*/
void waitForBackButton(){
    int xPosition=0, yPosition=0;
    FEHImage backButton;
    backButton.Open("New Piskel.png");
    backButton.Draw(270,0);

    while(xPosition < 270 || yPosition > 50){
        while(!LCD.Touch(&xPosition, &yPosition));
    }

    while(LCD.Touch(&xPosition, &yPosition)){}
    LCD.Clear();


}