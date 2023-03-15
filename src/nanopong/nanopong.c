#include "nanopong.h"

t_ball initBall() {
    int rX = 3;
    int rY = 3;
    int rDirection = 0;

    //Randomise the x starting point.
    if (rand() % 2 == 0) {
        rX = 3;
    } else {
        rX = 4;
    }

    //Randomise the y starting point.
    if (rand() % 2 == 0) {
        rY = 3;
    } else {
        rY = 4;
    }

    //Randomise the direction.
    if (rand() % 2 == 0) { //Left or Right
        if (rand() % 2 == 0) { //Horizontal or Diagonal
            if (rand() % 2 == 0) {  //If (Diagonal) Up or Down
                rDirection = Diagonal_Up_Left;
            } else {
                rDirection = Diagonal_Down_Left;
            }
        } else {
            rDirection = Left;
        }
    } else {
        if (rand() % 2 == 0) { //Horizontal or Diagonal
            if (rand() % 2 == 0) {  //If (Diagonal) Up or Down
                rDirection = Diagonal_Up_Right;
            } else {
                rDirection = Diagonal_Down_Right;
            }
        } else {
            rDirection = Right;
        }
    }

    //Create the ball.
    t_ball ball;
    ball.direction = rDirection;
    ball.x = rX;
    ball.y = rY;

    return ball;
}

t_player initPlayer() {
    int rPosition = 4;

    //Randomise the paddle starting point.
    if (rand() % 2 == 0) {
        rPosition = 3;
    } else {
        rPosition = 4;
    }

    //Create the player.
    t_player player;
    player.paddlePosition = rPosition;
    player.score = 0;

    return player;
}

void updateBall(t_ball ball, t_player player1, t_player player2) {

}