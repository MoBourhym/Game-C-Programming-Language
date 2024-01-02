#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "text_art.h"
#include "color.h"
#include "menu.h"
#include "Draw.h"




Position Snoopy;
Ball_str Ball;
Ball_str *pointeur_Ball = &Ball;
Position fruit_tab[4];
Position Obstacle_tab[4];

int i;
int test_snoopyX, test_snoopyY;
int *snoopy_x = &Snoopy.x, *snoopy_y = &Snoopy.y;
int *p_fruitX, *p_fruitY;
int score = 0;
int *p_score = &score;

char key;
char *p_key = &key;
int pause = 0;
int *p_pause = &pause;
int obstacle = 0;
int *p_obstacle = &obstacle;
int hearts = 3;  // Number of hearts
int p_hearts = &hearts;
int timer = 300;  // Initial timer value in seconds

void initialize();
void initialize_game();
void game_logic();
void displayInfo();

int main(){
    initialize();
    world_game();
    if(menu_select() == 1){
        system("cls");
        initialize_game();
        displayInfo();
        if((drawFrontMenu() == '\r')&&(drawFrontMenu() == '\r')){
            do {
                game_logic();
                timer--;
            } while (key != 'q');
        }
    }
    return 0;
}





initialize(){
    int i;
    srand(time(NULL));
    Snoopy.x = 20, Snoopy.y = 12; //initialiser la position de snoopy
    //initialiser les positions des fruits par hasard
    fruit_tab[0].x = 3, fruit_tab[0].y = 5;
    fruit_tab[1].x = 3, fruit_tab[1].y = MAP_SIZE_H+4;
    fruit_tab[2].x = MAP_SIZE_W+1, fruit_tab[2].y = 5;
    fruit_tab[3].x = MAP_SIZE_W+1, fruit_tab[3].y = MAP_SIZE_H+4;
    //meme chose pour les obstacles
    for(i=0 ; i<4 ; i++){
        Obstacle_tab[i].x = rand() % 40 + 2;
        Obstacle_tab[i].y = rand() % 10 + 8;
    }
    //initialser la position de la balle
    Ball.Pos.x = MAP_SIZE_W / 4, Ball.Pos.y = MAP_SIZE_H / 4;
    // Initialiser les directions de la balle
    Ball.Dir_x = 1, Ball.Dir_y = 1;
}

initialize_game(){
    char map[MAP_SIZE_H][MAP_SIZE_W] ={0};
    draw_Wall(map);
    draw_Snoopy(Snoopy.x, Snoopy.y);
    drawBall(Ball.Pos.x, Ball.Pos.y,fruit_tab,Obstacle_tab);
    for(i=0 ; i<4 ; i++){
        p_fruitX = &fruit_tab[i].x;
        p_fruitY = &fruit_tab[i].y;
        draw_Fruit(p_fruitX, p_fruitY);
    }
    snoopy_text();
    for(i=0 ; i<4 ; i++) draw_Obstacle(i, Obstacle_tab);
}

game_logic(){
    goto_xy(Snoopy.x, Snoopy.y);
    printf(" ");
    if(_kbhit()){
        key = getch();
        test_snoopyX = Snoopy.x;
        test_snoopyY = Snoopy.y;
        // Move Snoopy based on the pressed key
        move_snoopy(key,snoopy_x,snoopy_y,Obstacle_tab,obstacle,p_pause);
        // Check if Snoopy's position matches the fruit's position
        if(test_snoopyX != Snoopy.x || test_snoopyY != Snoopy.y){
            for(i=0 ; i<4 ; i++){
                p_fruitX = &fruit_tab[i].x;
                p_fruitY = &fruit_tab[i].y;
                eat_fruit(Snoopy.x,Snoopy.y,p_fruitX,p_fruitY,p_score);
            }
        }
    }
    // Redraw Snoopy in the new position
    draw_Snoopy(Snoopy.x, Snoopy.y);
    move_ball(pointeur_Ball,fruit_tab,Obstacle_tab);
    pause_test(key,Snoopy,Obstacle_tab,p_obstacle,p_pause);
    displayInfo();
    colesion_test(Ball, Snoopy, p_key, p_hearts);
    test_win(timer, hearts, score);
    if(timer <= 0) key = 'q';
    if(key == 'q' || timer <= 0) goto_xy(0,MAP_SIZE_H+6);
}

displayInfo(){
    // Display score, hearts, and timer information at the top and bottom
    goto_xy(0, 2);
    printf("\tScore: %d ", score);
    goto_xy(26,2);
    set_color(12);
    printf("hearts x%d",hearts);
    set_color(15);
    printf("\n");
    printf("\n");
    goto_xy(12,3);
    printf("Time: %d ", timer);
    goto_xy(21,3);
    printf(" s");
}
