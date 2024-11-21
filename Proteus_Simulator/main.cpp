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
void updateGameView(int, int);
bool isValidMovement(int, int, int, int);

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
        titleScreen.Open("title.png");
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
    float startTime = TimeNow();
    // LCD.WriteLine("Play Game Here");
    int x,y;
    int playerX = 0, playerY = 200;
    FEHIcon::Icon buttons[5];
    char Labels[5][20] = {"ul","l","u","ur", "r"};
    FEHIcon::DrawIconArray(buttons, 1, 5, 0, 210, 80, 90, Labels, GOLD, WHITE);
    LCD.Clear();

    FEHImage buttonImages[5];
    buttonImages[0].Open("up-left-arrow.png");
    buttonImages[1].Open("left-arrow.png");
    buttonImages[2].Open("up-arrow.png");
    buttonImages[3].Open("right-arrow.png");
    buttonImages[4].Open("up-right-arrow.png");
    for(int i = 0; i < 5; i ++){
        buttonImages[i].Draw(85 + i*30, 2);
    }


    while(playerX < 320){
        if(isValidMovement(playerX, playerY, 0, 1)){
            playerY++;
        }
        if(LCD.Touch(&x,&y)){
        if(buttons[3].Pressed(x,y, 1)){
            if(isValidMovement(playerX, playerY, 1, 0)){
                playerX++;
            }
        }else if(buttons[2].Pressed(x,y, 1)){
            if(isValidMovement(playerX, playerY, 0, -3)){
                playerY -= 3;
            }
        }

        }
        
        updateGameView(playerX, playerY);
        Sleep(10);      
    }
    waitForBackButton();
    return static_cast<int>(round(TimeNow() - startTime));
}

/* updates the game frame with the given x and y position*/
void updateGameView(int x, int y){
    //LCD.Clear(WHITE);
    LCD.SetFontColor(BLACK);
    LCD.FillRectangle(0, 35, 319, 204);
    LCD.SetFontColor(WHITE);

    /*
    FEHImage background;
    background.Open("background.png");
    background.Draw(0,0);
    */
    FEHImage buttons[5];
    buttons[0].Open("up-left-arrow.png");
    buttons[1].Open("left-arrow.png");
    buttons[2].Open("up-arrow.png");
    buttons[3].Open("right-arrow.png");
    buttons[4].Open("up-right-arrow.png");

    FEHImage player;
    player.Open("player.png");
    player.Draw(x, y);


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
    backButton.Open("backbutton.png");
    backButton.Draw(270,0);

    while(xPosition < 270 || yPosition > 50){
        while(!LCD.Touch(&xPosition, &yPosition));
    }

    while(LCD.Touch(&xPosition, &yPosition)){}
    LCD.Clear();
}

bool isValidMovement(int currentx, int currenty, int deltax, int deltay){
    if(currenty + deltay > 210 ){
        return false;
    }else{
        return true;
    }

}
