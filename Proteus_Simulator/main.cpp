#include "FEHLCD.h"
#include "FEHImages.h"
#include "FEHLCD.h"
#include "bits/stdc++.h"
#include "FEHUtility.h"
#include "LCDColors.h"
#include "FEHRandom.h"

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
void updateGameView(int, int, int);
class Player{
    private:

    public:
        Player(){xPosition = 5; yPosition = 100; xVelocity = 0; yVelocity = 0;}
        int xPosition;
        int yPosition;
        int xVelocity;
        int yVelocity;
        bool isValidMovement(int, int);
};
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
    double startTime = TimeNow();
    // LCD.WriteLine("Play Game Here");
    int x,y;
    Player player;
    FEHIcon::Icon buttons[5];
    char Labels[5][20] = {"ul","l","u","ur", "r"};
    FEHIcon::DrawIconArray(buttons, 1, 5, 0, 210, 80, 90, Labels, GOLD, WHITE);
    LCD.Clear();

    while(player.xPosition && player.yPosition < 240){

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

        /* gravity, this code will def make errors later. 
        The question is whether or not they are bad enough to make me wanna get good logic
        it is now later and I can confirm it is not working :(*/
        //player.yPosition += player.yVelocity;
        // if(player.isValidMovement(/*player.xPosition + player.xVelocity, player.yPosition + player.yVelocity, */0, 1)){
        //     player.yPosition -= player.yVelocity;
        //     player.yVelocity += 1;
        // } else{
        //     player.yVelocity = 0;
        // }
        player.yVelocity++;


        /*same here, i will be surprised if this works long term*/
        while(abs(player.xVelocity) > 0 ){
            if(player.isValidMovement(player.xVelocity, 0)){
                player.xPosition += player.xVelocity;
                break;
            }else{
                player.xVelocity-= player.xVelocity/abs(player.xVelocity);
            }
        }

        /*same here, i will be surprised if this works long term*/
        while(abs(player.yVelocity) > 0 ){
            if(player.isValidMovement(0, player.yVelocity)){
                player.yPosition += player.yVelocity;
                break;
            }else{
                player.yVelocity-= player.yVelocity/abs(player.yVelocity);
            }
        }


        updateGameView(player.xPosition, player.yPosition, static_cast<int>(round(TimeNow() - startTime)));
        Sleep(10);      
    }
    waitForBackButton();
    return 600 - static_cast<int>(round(TimeNow() - startTime));
}

/* updates the game frame with the given x and y position*/
void updateGameView(int x, int y, int time){

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

    FEHImage player;
    player.Open("playeridleframe1.png");
    player.Draw(x - PLAYER_HEIGHT/2, y);

    LCD.WriteAt(time, 279,  13 );


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

bool Player::isValidMovement(int deltax, int deltay){
    /* TODO: look into making it into a hashtable*/
    int proposedx = xPosition + deltax;
    if(proposedx >= 0 && proposedx <= (3*BLOCK_WIDTH) ){
        if(yPosition + deltay + PLAYER_HEIGHT > 220){
            return false;
        }else{
            return true;
        }
    } else if(proposedx >= 4*BLOCK_WIDTH && proposedx < 5*BLOCK_WIDTH){
        if(yPosition + deltay + PLAYER_HEIGHT > 220){
            return false;
        }else{
            return true;
        }
    } else if(proposedx >= 5*BLOCK_WIDTH && proposedx < 6*BLOCK_WIDTH){
        if(yPosition + deltay + PLAYER_HEIGHT > 198){
            return false;
        }else{
            return true;
        }
    }else if(proposedx >= 6*BLOCK_WIDTH && proposedx < 7*BLOCK_WIDTH){
        if(yPosition + deltay + PLAYER_HEIGHT > 178){
            return false;
        }else{
            return true;
        }
    }else if(proposedx >= 9*BLOCK_WIDTH && proposedx < 10*BLOCK_WIDTH){
        if(yPosition + deltay + PLAYER_HEIGHT > 178){
            return false;
        }else{
            return true;
        }
    }

    else{
        return true;
    }

}
