#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>



//elements definitions
typedef struct 
{
    Vector2 pos;
    Vector2 spd;
    int radius;
}Ball;
typedef struct
{
    Vector2 pos;
    Vector2 size;
    Vector2 spd;
    int score;
}Bar;

typedef enum
{
    GAME_PRESTART,//0
    GAME_RUNNING,//1
    GAME_OVER//2
}GAMESTATE;
// check the collision of the ball with the bars//checa a colisão da bola com as barras
bool checkcollision(Ball ball, Bar bar)
{
    return CheckCollisionCircleRec(ball.pos,ball.radius,(Rectangle){bar.pos.x,bar.pos.y,bar.size.x,bar.size.y});
}

int main(void){
    //window config//config da janela
    const int WINDOWHEIGHT = 600;
    const int WINDOWWIDHT = 800;
    Image icon = LoadImage("res/icon.ico");

    InitWindow(WINDOWWIDHT,WINDOWHEIGHT,"BONG ;3");
    SetWindowIcon(icon);

    SetTargetFPS(60);
    //audio config//confg. dos soms
    InitAudioDevice();
    Sound hitbar = LoadSound("res/hitbar.wav");
    Sound hitborder = LoadSound("res/hitborder.wav");
    Sound hitscore = LoadSound("res/hitscore.wav");

    
    //elements config//elementos
    //ball config//config da bola
    Ball ball;
    ball.pos.x = WINDOWWIDHT/2;
    ball.pos.y = WINDOWHEIGHT/2;
    ball.spd.x = 5; 
    ball.spd.y = 5;
    ball.radius = 10;
    int ballmspd[] = {1,-1};
    // bars config//config das barras
    Bar barleft;
    Bar barright;
    barleft.pos.x = 50;
    barleft.pos.y = (WINDOWHEIGHT/2)-50;
    barleft.spd.y = 10;
    barleft.size.x = 25;
    barleft.size.y = 100;
    barleft.score = 0;
    barright.pos.x = WINDOWWIDHT-50;
    barright.pos.y = (WINDOWHEIGHT/2)-50;
    barright.spd.y = 10;
    barright.size.x = 25;
    barright.size.y = 100;
    barright.score = 0;
    // decobars
    Bar decotop;
    Bar decobottom;
    decotop.pos.x = 0;
    decotop.pos.y = 0;
    decotop.size.x = WINDOWWIDHT;
    decotop.size.y = 25;
    decobottom.pos.x = 0;
    decobottom.pos.y = 580;
    decobottom.size.x = WINDOWWIDHT;
    decobottom.size.y = 25;
    // game config//config do jogo
    GAMESTATE gamestate = GAME_PRESTART;
    const int MAXPOINTS = 12;
    srand(0);
    //game loop
    while(!WindowShouldClose()){

        BeginDrawing();

            ClearBackground(BLACK);

            if(((IsKeyReleased(KEY_SPACE) )&& (gamestate == GAME_PRESTART || gamestate == GAME_OVER)) || ((IsKeyDown(KEY_SPACE) && IsKeyDown(KEY_LEFT_CONTROL)) && gamestate == GAME_RUNNING))
            {
                gamestate = GAME_RUNNING;
                barleft.score = 0;
                barright.score = 0;
                barleft.pos = (Vector2){50,(WINDOWHEIGHT/2)-50};
                barright.pos = (Vector2){WINDOWWIDHT-50,(WINDOWHEIGHT/2)-50};
                ball.pos = (Vector2){WINDOWWIDHT/2,WINDOWHEIGHT/2};
                int xfac = ballmspd[rand() % (sizeof(ballmspd)/sizeof(ballmspd[0]))];
                int yfac = ballmspd[rand() % (sizeof(ballmspd)/sizeof(ballmspd[0]))];
                printf("\nxfac: %d|yfac: %d",xfac,yfac);
                ball.spd = (Vector2){5*xfac,5*yfac};
                printf("\nball.spd.x: %lf|ball.spd.y: %lf",ball.spd.x,ball.spd.y);
            }
            if(gamestate == GAME_PRESTART)
            {
                DrawText("BONG", (WINDOWWIDHT/3),WINDOWHEIGHT/4,100,WHITE);
                DrawText("press spacebar to start",(WINDOWWIDHT/4),(WINDOWHEIGHT/2)+50,30,WHITE);
            }
            if(gamestate == GAME_RUNNING)
            {
                ball.pos.x += ball.spd.x;
                ball.pos.y += ball.spd.y;

                //movimentation//movimentação
                //left bar//barra esquerda
                if(IsKeyDown(KEY_W) && barleft.pos.y > 0)
                {
                    barleft.pos.y -= barleft.spd.y;
                }
                if(IsKeyDown(KEY_S) && barleft.pos.y + barleft.size.y < WINDOWHEIGHT)
                {
                    barleft.pos.y += barleft.spd.y;
                }
                //right bar//barra direita
                if(IsKeyDown(KEY_UP) && barright.pos.y > 0)
                {
                    barright.pos.y -= barright.spd.y;
                }
                if(IsKeyDown(KEY_DOWN) && barright.pos.y + barright.size.y < WINDOWHEIGHT)
                {
                    barright.pos.y += barright.spd.y;
                }
                //score
                if(ball.pos.x - ball.radius <= 0)
                {
                    barright.score++;
                    PlaySound(hitscore);
                    if(barright.score  >= MAXPOINTS)
                    {
                        gamestate = GAME_OVER;
                    }
                    else
                    {
                        ball.pos.x = WINDOWWIDHT/2;
                        ball.pos.y = WINDOWHEIGHT/2;
                    }

                }
                else if (ball.pos.x + ball.radius >= WINDOWWIDHT)
                {
                    barleft.score++;
                    PlaySound(hitscore);
                    if(barleft.score >= MAXPOINTS)
                    {
                        gamestate = GAME_OVER;
                    }
                    else
                    {
                        ball.pos.x = WINDOWWIDHT/2;
                        ball.pos.y = WINDOWHEIGHT/2;
                    }
                }
            }
            
            if(gamestate == GAME_OVER)
            {
                if(barleft.score == MAXPOINTS)
                {  
                    DrawText("BLUE TEAM WIN",WINDOWWIDHT/5,(WINDOWHEIGHT/2)-50,60,BLUE);
                    DrawText("Press spacebar to play again",WINDOWWIDHT/4,(WINDOWHEIGHT/2)+50,30,BLUE);
                }
                else if (barright.score == MAXPOINTS)
                {
                    DrawText("GREEN TEAM WIN",WINDOWWIDHT/5,(WINDOWHEIGHT/2)-50,60,GREEN);
                    DrawText("Press spacebar to play again",WINDOWWIDHT/4,(WINDOWHEIGHT/2)+50,30,GREEN);
                }
            }
            if(checkcollision(ball, barleft) || checkcollision(ball, barright))
            {ball.spd.x *= -1;PlaySound(hitbar);}//left bar || right bar
            if(checkcollision(ball, decotop) || checkcollision(ball, decobottom))
            {ball.spd.y *= -1;PlaySound(hitborder);}//top bar || bottom bar
            //if(ball.pos.x - ball.radius < 0 || ball.pos.x + ball.radius > WINDOWWIDHT){ball.spd.x *= -1;}//elastic walls
            
            //draw element//desenhar elemnetos
            //draw bars//barras
            //controllable//controlaveis
            DrawRectangle(barleft.pos.x,barleft.pos.y,25,100,BLUE);//left
            DrawRectangle(barright.pos.x,barright.pos.y,25,100,GREEN);//right
            //deco//decoração
            DrawRectangle(decotop.pos.x,decotop.pos.y,decotop.size.x,decotop.size.y,WHITE);//top
            DrawRectangle(decobottom.pos.x,decobottom.pos.y,decobottom.size.x,decobottom.size.y,WHITE);//bottom
            DrawRectangle(WINDOWWIDHT/2,0,5,WINDOWHEIGHT,WHITE);//rede

            //draw ball
            DrawCircle(ball.pos.x,ball.pos.y,10,RED);//desenhar a bola

            //UI
            char bluescore[4];
            char greenscore[4];
            sprintf(bluescore,"%d",barleft.score);
            sprintf(greenscore,"%d",barright.score);
            DrawText(bluescore,100,40,40,WHITE);
            DrawText(greenscore,WINDOWWIDHT-100,40,40,WHITE);
            
            //debug
            
            printf("\nball.speed: %lf,%lf", ball.spd.x,ball.spd.y);//ball speed
            printf("\nball.pos: %lf,%lf", ball.pos.x,ball.pos.y);// ball position
            printf("\nGAMESTATE: %d",gamestate);//gamestate
            
        EndDrawing();
    }
    // shutdown//desligar
    UnloadImage(icon);
    UnloadSound(hitbar);
    UnloadSound(hitborder);
    UnloadSound(hitscore);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}