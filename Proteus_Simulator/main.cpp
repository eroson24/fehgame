#include "FEHLCD.h"
#include "FEHImages.h"
#include "FEHLCD.h"
#include "bits/stdc++.h"
#include "FEHUtility.h"
#include "LCDColors.h"
#include "FEHRandom.h"
#include "string.h"

#define PLAYER_HEIGHT 17
#define PLAYER_WIDTH 15
#define JUMP_HEIGHT 10
#define MOVEMENT_SPEED 4
#define BLOCK_WIDTH 20

using namespace std;

int runGame();
void displayGameOver(int);
void displayScores(int []);
void waitForBackButton();
/* a class that stores data relating to the player including position, velocity, and sprites*/
class Player{
    public:
        Player();
        int xPosition;
        int yPosition;
        int xVelocity;
        int yVelocity;
        char walkCycle[30][29];
        char walkCycleLeft[30][34];

        int startTime;
        bool isValidMovement(int, int);
};
void updateGameView(Player);

int main()
{
    int xPosition, yPosition;
    int highScoreList[4] = {0,0,0,0};

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

            /* shows game over screen with score*/
            displayGameOver(score);

        /* score board*/
        }else if(xPosition <= 160 && xPosition > 80){
            displayScores(highScoreList);
            LCD.WriteLine("click in the upper right to go back");
            waitForBackButton();

        /* displays the instructions*/
        }else if(xPosition <= 240 && xPosition > 160){
            LCD.Clear();
            LCD.WriteLine("Instructions:");
            LCD.WriteLine(" ");
            LCD.WriteLine(" ");
            LCD.WriteLine("Click on the buttons at the top to move your character. Your goal is to make it to the very end on the right, avoiding any falls to your death.");
            LCD.WriteLine("Click the arrow in the top right to go back.");

            waitForBackButton();

        /* displays the credits*/
        }else if(xPosition <= 320 && xPosition > 240){
            LCD.Clear();
            LCD.SetFontColor(BLUE);
            LCD.WriteLine("Credits:");
            LCD.WriteLine(" ");
            LCD.WriteLine(" ");

            LCD.SetFontColor(WHITE);
            LCD.WriteLine("Made by Erol and Nolan.");
            LCD.WriteLine("Click in the upper");
            LCD.WriteLine("right to go back.");

            waitForBackButton();



        }


    }
    return 0;
}

/* runs the game and returns the score*/
int runGame(){
    int x,y;
    Player player;
    FEHIcon::Icon buttons[5];
    char Labels[5][20] = {"ul","l","u","ur", "r"};
    FEHIcon::DrawIconArray(buttons, 1, 5, 0, 210, 80, 90, Labels, GOLD, WHITE);
    LCD.Clear();

    /* while the player isn't at the end and the time hasn't reached the limit yet*/
    while(!(player.yPosition < 120 && player.xPosition < 30) && static_cast<int>(round(TimeNow() - player.startTime)) < 600){
        if(player.yPosition > 240){
            return -1;
        }

        /* friction*/
        if(player.xVelocity > MOVEMENT_SPEED){
            player.xVelocity -= MOVEMENT_SPEED;
        } else if (player.xVelocity < -MOVEMENT_SPEED){
            player.xVelocity += MOVEMENT_SPEED;
        } else{
            player.xVelocity = 0;
        }



        if(LCD.Touch(&x,&y)){

            /* right button */
            if(buttons[3].Pressed(x,y, 1)){
                player.xVelocity += MOVEMENT_SPEED;

            /* jump button*/
            }else if(buttons[2].Pressed(x,y, 1) && !player.isValidMovement(0,1)){
                player.yVelocity -= JUMP_HEIGHT;
            
            /* jump left button*/
            }else if(buttons[0].Pressed(x,y, 1)){
                if (!player.isValidMovement(0,1)){
                    player.yVelocity -= JUMP_HEIGHT;
                }
                player.xVelocity -= MOVEMENT_SPEED;

            /* left button*/
            }else if(buttons[1].Pressed(x,y, 1)){
                player.xVelocity -= MOVEMENT_SPEED;

            /* jump right button*/
            }else if(buttons[4].Pressed(x,y, 1)){
                if (!player.isValidMovement(0,1)){
                    player.yVelocity -= JUMP_HEIGHT;
                }
                player.xVelocity += MOVEMENT_SPEED;

            }

        }

        player.yVelocity++; // gravity


        /* makes the player move as far as possible in the x direction*/
        while(abs(player.xVelocity) > 0 ){
            if(player.isValidMovement(player.xVelocity, 0)){
                player.xPosition += player.xVelocity;
                break;
            }else{
                player.xVelocity-= player.xVelocity/abs(player.xVelocity);
            }
        }

        /* makes the player move as far as possible in the y direction*/
        while(abs(player.yVelocity) > 0 ){
            if(player.isValidMovement(0, player.yVelocity)){
                player.yPosition += player.yVelocity;
                break;
            }else{
                player.yVelocity -= player.yVelocity/abs(player.yVelocity);
            }
        }

        updateGameView(player);
        Sleep(10);      
    }
    /* returns 600 - time elapsed*/ 
    return 600 - static_cast<int>(round(TimeNow() - player.startTime));
}

/* updates the game for the given player class*/
void updateGameView(Player player){
    FEHImage background;
    background.Open("level1.png");
    background.Draw(0,0);
    FEHImage buttonImages[5];
    buttonImages[0].Open("up-left-arrow.png");
    buttonImages[1].Open("left-arrow.png");
    buttonImages[2].Open("up-arrow.png");
    buttonImages[3].Open("right-arrow.png");
    buttonImages[4].Open("up-right-arrow.png");
    for(int i = 0; i < 5; i ++){
        buttonImages[i].Draw(85 + i*30, 2);
    }

    int index =  static_cast<int>(round((TimeNow() - player.startTime) * 40)) % 30;

    FEHImage drawPlayer;
    if(player.xVelocity > 0){
        drawPlayer.Open(player.walkCycle[index]);
    }else if(player.xVelocity < 0){
        drawPlayer.Open(player.walkCycleLeft[index]);
    }else{
        drawPlayer.Open("playeridleframe1.png");
    }
    drawPlayer.Draw(player.xPosition - PLAYER_HEIGHT/2, player.yPosition);

    LCD.WriteAt(static_cast<int>(round(TimeNow() - player.startTime)), 279,  13 );


}

/* prints the game over screen with the results from the game*/
void displayGameOver(int score){
    LCD.Clear();
    if(score == -1){
        LCD.WriteLine("You didn't finish :(");
    }else{
        LCD.WriteLine("Congratulations! ");
        LCD.WriteLine("Your score was: " + to_string(score));
    }
    waitForBackButton();
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

/* creates a symbol in the top right and puases the program until the user clicks it*/
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

/* 
Checks if the players velocity can be added to its position without colliding with an object.
Way too many if statements.
*/
bool Player::isValidMovement(int deltax, int deltay){
    int proposedx = xPosition + deltax;
    bool result = true;
    
    if(proposedx <= 0 || proposedx >= 320){
        result = false;
    }
    /* first layer*/
    if(proposedx > 0 && proposedx <= (3*BLOCK_WIDTH) ){
        if(yPosition + deltay + PLAYER_HEIGHT > 220){
            result = false;
        }
    } else if(proposedx >= 4*BLOCK_WIDTH && proposedx < 5*BLOCK_WIDTH){
        if(yPosition + deltay + PLAYER_HEIGHT > 220){
            result = false;
        }
    } else if(proposedx >= 5*BLOCK_WIDTH && proposedx < 6*BLOCK_WIDTH){
        if(yPosition + deltay + PLAYER_HEIGHT > 199){
            result = false;
        }
    }else if(proposedx >= 6*BLOCK_WIDTH && proposedx < 7*BLOCK_WIDTH){
        if(yPosition + deltay + PLAYER_HEIGHT > 178){
            result = false;
        }
    }else if(proposedx >= 9*BLOCK_WIDTH && proposedx < 10*BLOCK_WIDTH){
        if(yPosition + deltay + PLAYER_HEIGHT > 179){
            result = false;
        }
    } else if(proposedx >= 11 * BLOCK_WIDTH && proposedx < 14*BLOCK_WIDTH ){
        if(yPosition + deltay + PLAYER_HEIGHT > 179){
            result = false;
        }
    } else if(proposedx >= 14 * BLOCK_WIDTH && proposedx < 15*BLOCK_WIDTH ){
        if(yPosition + deltay + PLAYER_HEIGHT > 158){
            result = false;
        }
    }else if(proposedx >= 15 * BLOCK_WIDTH && proposedx < 16*BLOCK_WIDTH ){
        if(yPosition + deltay + PLAYER_HEIGHT > 137){
            result = false;
        }
    }

    /* second layer*/
    if(proposedx >= 252 && proposedx < 272){
        if(yPosition + deltay + PLAYER_HEIGHT > 109 && yPosition + deltay < 129){
                result= false;
        }
    }else if(proposedx >= 214 && proposedx < 233 ){
        if(yPosition + deltay + PLAYER_HEIGHT > 108 && yPosition + deltay < 128){
                result= false;
        }
    }else if(proposedx >= 166 && proposedx < 185 ){
        if(yPosition + deltay + PLAYER_HEIGHT > 103 && yPosition + deltay  < 123){
                result= false;
        }
    }else if(proposedx >= 108 && proposedx < 127 ){
        if(yPosition + deltay + PLAYER_HEIGHT > 110 && yPosition + deltay  < 130){
                result= false;
        }
    }else if(proposedx >= 18 && proposedx < 77 ){
        if(yPosition + deltay + PLAYER_HEIGHT > 105 && yPosition + deltay  < 125){
                result= false;
        }
    }

    return result;

}

/* constructor that sets the player at the default starting position with no velocity, and intializes its walk cycle*/
Player::Player(){
    xPosition = 5; 
    yPosition = 140; 
    xVelocity = 0; 
    yVelocity = 0;

    for(int i = 0; i < 8; i++){
        strcpy(walkCycle[i], "walkcycle/pixil-frame-0.png");
        strcpy(walkCycleLeft[i], "walkcycle_left/pixil-frame-0.png");

    }
    for(int i = 0; i < 3; i++){
        strcpy(walkCycle[i + 8], "walkcycle/pixil-frame-1.png");
        strcpy(walkCycleLeft[i + 8], "walkcycle_left/pixil-frame-1.png");

    }
    for(int i = 0; i < 2; i++){
        strcpy(walkCycle[i + 11], "walkcycle/pixil-frame-2.png");
        strcpy(walkCycleLeft[i + 11], "walkcycle_left/pixil-frame-2.png");

    }
    for(int i = 0; i < 2; i++){
        strcpy(walkCycle[i + 13], "walkcycle/pixil-frame-3.png");
        strcpy(walkCycleLeft[i + 13], "walkcycle_left/pixil-frame-3.png");

    }
    for(int i = 0; i < 8; i++){
        strcpy(walkCycle[i + 15], "walkcycle/pixil-frame-4.png");
        strcpy(walkCycleLeft[i + 15], "walkcycle_left/pixil-frame-4.png");

    }
    for(int i = 0; i < 3; i++){
        strcpy(walkCycle[i + 23], "walkcycle/pixil-frame-5.png");
        strcpy(walkCycleLeft[i + 23], "walkcycle_left/pixil-frame-5.png");

    }
    for(int i = 0; i < 2; i++){
        strcpy(walkCycle[i + 26], "walkcycle/pixil-frame-6.png");
        strcpy(walkCycleLeft[i + 26], "walkcycle_left/pixil-frame-6.png");

    }
    for(int i = 0; i < 2; i++){
        strcpy(walkCycle[i + 28], "walkcycle/pixil-frame-7.png");
        strcpy(walkCycleLeft[i + 28], "walkcycle_left/pixil-frame-7.png");

    }

    startTime = TimeNow();
}