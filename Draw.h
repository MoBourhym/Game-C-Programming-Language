#define MAP_SIZE_W 40
#define MAP_SIZE_H 20

typedef struct {
    int x;
    int y;
}Position;

typedef struct {
    Position Pos;
    int Dir_x;
    int Dir_y;

}Ball_str;

void goto_xy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void draw_Wall(char map[MAP_SIZE_H][MAP_SIZE_W]){
    int h, w;
    set_color(255);
    for(h=3; h<=MAP_SIZE_H +4; h++){
        for(w=0; w<=MAP_SIZE_W +1; w++){
            goto_xy(w+1,h+1);
            if(h==3 || w==0 || h==MAP_SIZE_H+4 || w==MAP_SIZE_W+1)
                printf("\xDB ");
        }
        printf("\n");
    }
}
void draw_Snoopy(int x, int y) {
    goto_xy(x, y);
    set_color(11);
    printf("O");
    set_color(15);
}
void drawBall(int x, int y, Position fruit[], Position Obstacle[]) {
    for(int i=0;i<4;i++){
        if((x != fruit[i].x || y != fruit[i].y) && (x != Obstacle[i].x || y != Obstacle[i].y)){
            goto_xy(x,y);
            set_color(12);
            printf("O");
            set_color(15);
        }
    }
}
void clearBall(int x, int y) {
    goto_xy(x, y);
    printf(" ");
}
void draw_Fruit(int *x, int *y) {
    int val_x = *x, val_y = *y;
    goto_xy(val_x, val_y);
    set_color(14); // Yellow color for fruit
    printf("$");
    set_color(15); // Reset to default color
}
void draw_Obstacle(int i, Position Obstacle[]){
    goto_xy(Obstacle[i].x, Obstacle[i].y);
    set_color(6);
    printf("\xB2");
    set_color(15);
}

void move_snoopy(char key, int *snoopy_x, int *snoopy_y, Position Obstacle[], int obstacle, int *pause){
    int x = *snoopy_x, y = *snoopy_y;
    if(*pause != 1){
        switch (key) {
            case 72:
                if((y > 5) && (y != Obstacle[0].y+1 || x!=Obstacle[0].x)&&(y != Obstacle[1].y+1 || x!=Obstacle[1].x)&&
                   (y != Obstacle[2].y+1 || x!=Obstacle[2].x)&&(y != Obstacle[3].y+1 || x!=Obstacle[3].x)){
                    y--;
                    *snoopy_y = y;
                }
                else if(y > 5 && obstacle == 1){
                    y--;
                    *snoopy_y = y;
                }
            break;
            case 80:
                if((y <= MAP_SIZE_H+3) && (y != Obstacle[0].y-1 || x!=Obstacle[0].x)&&(y != Obstacle[1].y-1 || x!=Obstacle[1].x)&&
                   (y != Obstacle[2].y-1 || x!=Obstacle[2].x)&&(y != Obstacle[3].y-1 || x!=Obstacle[3].x)){
                    y++;
                    *snoopy_y = y;
                }
                else if(y <= MAP_SIZE_H+3 && obstacle == 1){
                        y++;
                        *snoopy_y = y;
                }
            break;
            case 75:
                if((x > 3) && (x != Obstacle[0].x+1 || y!= Obstacle[0].y)&&(x != Obstacle[1].x+1 || y!=Obstacle[1].y)&&
                   (x != Obstacle[2].x+1 || y!=Obstacle[2].y)&&(x != Obstacle[3].x+1 || y!=Obstacle[3].y)){
                    x--;
                    *snoopy_x = x;
                }
                else if(x > 3 && obstacle == 1){
                    x--;
                    *snoopy_x = x;
                }
            break;
            case 77:
                if((x <= MAP_SIZE_W) && (x != Obstacle[0].x-1 || y!= Obstacle[0].y)&&(x != Obstacle[1].x-1 || y!=Obstacle[1].y)&&
                   (x != Obstacle[2].x-1 || y!=Obstacle[2].y)&&(x != Obstacle[3].x-1 || y!=Obstacle[3].y)){
                    x++;
                    *snoopy_x = x;
                }
                else if(x <= MAP_SIZE_W && obstacle == 1){
                    x++;
                    *snoopy_x = x;
                }
            break;
            case 'p':
                *pause = 1;
            break;
        }
    }
}
void move_ball(Ball_str *p_Ball, Position fruit[], Position Obstacle[]){
    int ballSpeed = 70;
    int test = 0;
    // Erase the previous ball position
        if((p_Ball->Pos.x == fruit[0].x && p_Ball->Pos.y == fruit[0].y)||(p_Ball->Pos.x == fruit[1].x && p_Ball->Pos.y == fruit[1].y)||
           (p_Ball->Pos.x == fruit[2].x && p_Ball->Pos.y == fruit[2].y)||(p_Ball->Pos.x == fruit[3].x && p_Ball->Pos.y == fruit[3].y)){
            for(int i=0;i<4;i++){
                if(fruit[i].x == p_Ball->Pos.x && fruit[i].y == p_Ball->Pos.y){
                    draw_Fruit(&fruit[i].x, &fruit[i].y);
                }
            }
        }
        else if((p_Ball->Pos.x == Obstacle[0].x && p_Ball->Pos.y == Obstacle[0].y)||(p_Ball->Pos.x == Obstacle[1].x && p_Ball->Pos.y == Obstacle[1].y)||
           (p_Ball->Pos.x == Obstacle[2].x && p_Ball->Pos.y == Obstacle[2].y)||(p_Ball->Pos.x == Obstacle[3].x && p_Ball->Pos.y == Obstacle[3].y)){
            for(int i=0;i<4;i++){
                if(Obstacle[i].x == p_Ball->Pos.x && Obstacle[i].y == p_Ball->Pos.y){
                    draw_Obstacle(i,Obstacle);
                }
            }
        }
        else clearBall(p_Ball->Pos.x, p_Ball->Pos.y);
        // Update the ball position
        p_Ball->Pos.x += p_Ball->Dir_x;
        p_Ball->Pos.y += p_Ball->Dir_y;
        // Check for collisions with the screen borders
        if (p_Ball->Pos.x <= 3 || p_Ball->Pos.x >= MAP_SIZE_W) {
            p_Ball->Dir_x *= -1; // Reverse direction in X
        }
        if (p_Ball->Pos.y <= 5 || p_Ball->Pos.y > MAP_SIZE_H+3){
            p_Ball->Dir_y *= -1; // Reverse direction in Y
        }
        // Draw the ball at the new position
        drawBall(p_Ball->Pos.x, p_Ball->Pos.y,fruit,Obstacle);
        // Introduce a delay for the ball's movement
        Sleep(ballSpeed);
}
void obstacle_test(char key, int x, int y, Position Obstacle[], int *obstacle){
    if((x==Obstacle[0].x-1 && y==Obstacle[0].y) || (x==Obstacle[0].x+1 && y==Obstacle[0].y)||
       (y==Obstacle[0].y-1 && x==Obstacle[0].x) || (y==Obstacle[0].y+1 && x==Obstacle[0].x)||
       (x==Obstacle[1].x-1 && y==Obstacle[1].y) || (x==Obstacle[1].x+1 && y==Obstacle[1].y)||
       (y==Obstacle[1].y-1 && x==Obstacle[1].x) || (y==Obstacle[1].y+1 && x==Obstacle[1].x)||
       (x==Obstacle[2].x-1 && y==Obstacle[2].y) || (x==Obstacle[2].x+1 && y==Obstacle[2].y)||
       (y==Obstacle[2].y-1 && x==Obstacle[2].x) || (y==Obstacle[2].y+1 && x==Obstacle[2].x)||
       (x==Obstacle[3].x-1 && y==Obstacle[3].y) || (x==Obstacle[3].x+1 && y==Obstacle[3].y)||
       (y==Obstacle[3].y-1 && x==Obstacle[3].x) || (y==Obstacle[3].y+1 && x==Obstacle[3].x)){
            if(*obstacle == 0){
                goto_xy(80,16);
                printf("press s to escape the obstacle...");
            }
            if(key == 's'){
                goto_xy(x,y);
                printf(" ");
                *obstacle = 1;
            }
    }
    else{
        goto_xy(80,16);
        printf("                                 ");
    }
}
void eat_fruit(int x, int y, int *fruitX, int *fruitY, int *score){
    if (x == *fruitX && y == *fruitY) {
        // Increase score and generate a new random position for the fruit
        *score += 100;
    }
}
void pause_test(char key, Position Snoopy, Position Obstacle[],int *p_obstacle, int *p_pause){
    if(*p_pause == 0){
        obstacle_test(key,Snoopy.x,Snoopy.y,Obstacle,p_obstacle);
    }
    else {
        goto_xy(80,14);
        printf("press Entrer to back ...");
        if(key == '\r'){
            *p_pause = 0;
            goto_xy(80,14);
            printf("                        ");
        }
    }
}
void colesion_test(Ball_str Balle, Position Snoopy, char *key, int *p_hearts){
    if(Balle.Pos.x == Snoopy.x && Balle.Pos.y == Snoopy.y){
        (*p_hearts)--;
    }
    if(*p_hearts == 0){
        *key = 'q';
    }
}
int drawFrontMenu() {
    char keyInput;
    goto_xy(47, 1);
    printf("=====================================================");
    goto_xy(47, 2);
    set_color(9);
    printf("       =              S N O O P Y              =");
    goto_xy(47, 3);
    printf("=====================================================\n");
    set_color(14);
    goto_xy(47,23);
    set_color(22);
    printf(" >> Made by ABDERZZAK HADDANI , MOHAMMED BOURHYM .");
    set_color(14);
    while (1) {
        keyInput = getKeyDown();
        if (keyInput == '\r') break;
        //if (keyInput == 't' || keyInput == 'T') break;
        goto_xy(60, 17);
        set_color(11);
        printf(" === press Entrer to start ===");
        set_color(7);
        Sleep(500);
        goto_xy(60, 17);
        printf("                               ");
        Sleep(500);
    }
    return keyInput;
}
int getKeyDown() {
    int key = -1;
    for (int i = 8; i <= 255; i++) {
        if (GetAsyncKeyState(i) & 0x8001) {
            key = i;
            break;
        }
    }
    return key;
}
void test_win(int timer, int hearts, int score){
    if(timer <= 0 || hearts == 0){
        if(score < 400) you_lose();
        else if(score == 400) you_win();
    }
}

