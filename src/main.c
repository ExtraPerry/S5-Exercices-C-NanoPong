#include <nanolib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "nanopong/nanopong.h"


// void init_game()
// {
//   write_column_MAX7219(1, 0b00111000);
//   write_column_MAX7219(5, 0b00001000);
//   write_column_MAX7219(8, 0b00111000);
// }

void init_potentiometers()
{
  init_pin_ADC(A0);
  init_pin_ADC(A1);
  init_ADC(ADC_AVCC, ADC_RIGHT_ADJUST, ADC_NO_INTERRUPT, ADC_PRESCALER_128);

  //printf("A0: %d ; A1: %d ", potA0, potA1);
}

void led()
{
  init_output_GPIO(D2);
  write_output_GPIO(D2, HIGH);
  init_output_GPIO(D3);
  write_output_GPIO(D3, HIGH);
  init_output_GPIO(D4);
  write_output_GPIO(D4, HIGH);
  init_output_GPIO(D5);
  write_output_GPIO(D5, HIGH);
  init_output_GPIO(D6);
  write_output_GPIO(D6, HIGH);
  init_output_GPIO(D7);
  write_output_GPIO(D7, HIGH);
}

int main(void) {
  
  sei();
  init_block_USART0();
  init_potentiometers();
  init_MAX7219();
  clear_MAX7219();
  led();
  set_brightness_MAX7219(0b00001111);

  _delay_ms(500);

  t_game game = init_game();
  uint8_t counter = 1;
  
  //Default Screen in console (only values should be replaced rather than writing new lines).
  printf("---------------------------------Status-----------------------------------\n");
  printf("Left Paddle (player-1) = %d | Right Paddle (player-2) = %d\n", game.players[0].paddlePosition, game.players[1].paddlePosition);
  printf("Ball is at : x = %d | y = %d | direction = %s\n", game.ball.x, game.ball.y, getDirectionString(game.ball));
  printf("Current score : player-1 = %d | player-2 = %d\n", game.players[0].score, game.players[1].score);
  printf("--------------------------------------------------------------------------\n");

  for(;;) {
    game = init_game();
    displayPointsLed(game);
    draw_game(game);
    printf("Game started: %u\n", game.isGameStarted);

    while(game.players[0].score < 3 && game.players[1].score < 3) {
      game.ball = initBall(); //Reset the ball for play.

      clear_MAX7219();
      draw_game(game);

      while(((game.ball.x > 0 && game.ball.x < 7) || (game.ball.y >= 0 && 7 <= game.ball.y))) {
        //printf("-------------------------------Loop-Cycle-%d-------------------------------\n", counter);

        updatePaddles(&game);

        if (counter >= 6) {
          game.ball = updateBall(game);
          counter = 0;
        }
    
        clear_MAX7219();
        draw_game(game);
    
        _delay_ms(100);
        counter++;
      }

    //printf("-----------------------------Match-Completed------------------------------\n");
    if (game.ball.x == 0) {
      game.players[1].score++;
      //printf(" !!! EVENT !!! - Right player(2) scored a goal.\n");
    } else if (game.ball.x == 7) {
      game.players[0].score++;
      //printf(" !!! EVENT !!! - Left player(1) scored a goal.\n");
    } else {
      //printf(" !!! ERROR !!! - Something went wrong with where the ball finished the current game.\n");
    }
    printf("Current score : player-1 = %d | player-2 = %d\n", game.players[0].score, game.players[1].score);
    displayPointsLed(game);
    }
  }
  
  return 0;
}