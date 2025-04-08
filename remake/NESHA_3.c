#include "raylib.h"
#define SCREENWIDTH 1000
#define SCREENHEIGHT 600

Texture2D nesha_D;
Texture2D nesha_A;
Texture2D nesha_front;
Texture2D nesha_jump;
Texture2D nesha_squat;
Texture2D background;
Texture2D floor;
Music music;

typedef struct{
   float posX;
   float posY;
}imagem;


imagem img[4]= {0, 0,
                0,305,
             -127,-427,
                0,-110};
    
    float speed = 2.0;
    float scrollingBack = 0.0f;
    bool background_direction = true;
    
    void Background(Texture2D texture);
    void Nesha_move_background(Texture2D texture);
    void Floor(Texture2D texture);
    void Draw_Nesha(Texture2D texture);
    void UpdateAnimation(int *framesCounter, int *currentFrame, Rectangle *frameRec, int framesSpeed, Texture2D texture);

int main()
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "NESHA");
    InitAudioDevice();
    
    background = LoadTexture("NESHA_ANIMATIONS//fundo_nesha02.png");
    floor = LoadTexture("NESHA_ANIMATIONS//chao.png");
    nesha_D = LoadTexture("//NESHA_ANIMATIONS//Nesha_D.png");
    nesha_A = LoadTexture("//NESHA_ANIMATIONS//Nesha_A.png");
    nesha_front = LoadTexture("//NESHA_ANIMATIONS//Nesha_FRENTE.png");
    nesha_jump = LoadTexture("//NESHA_ANIMATIONS//Nesha_PULAR.png");
    nesha_squat = LoadTexture("//NESHA_ANIMATIONS//Nesha_AGACHAR.png");
    music = LoadMusicStream("//MUSIC//NeshaTheme.mp3");
    //obstaculo = LoadTexture("obstaculos.png");
    
    PlayMusicStream(music);
    
    Rectangle frameRec = { 0.0f, 0.0f, (float)nesha_jump.width/5, (float)nesha_jump.height };
    Vector2 origin = { frameRec.width / 2, frameRec.height / 2 };
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    
    SetTargetFPS(60); //velocidade da Nesha
    
    while(!WindowShouldClose())
    {   
        UpdateMusicStream(music);
        
        Nesha_move_background(background);//Fundo se mov. no sentindo contrario a nesha
        
        BeginDrawing();
            
            Background(background);//Configuração do fundo
            
            Floor(floor);//configuração chão
            
            //Obstaculo(obstaculo);//configuracao obstaculos
            
            //Configuração da Nesha
            if (background_direction) 
                Draw_Nesha(nesha_front);
            else 
                Draw_Nesha(nesha_A);
            
            //Animação
            UpdateAnimation(&framesCounter, &currentFrame, &frameRec, framesSpeed, nesha_jump);

    
            //Configuração dos limites da tela
            if (img[1].posX < -50) 
                img[1].posX = -50;
            else if (img[1].posX > 800) 
                img[1].posX = 800;
            
    
            //Configuração dos botões
            if(IsKeyDown(KEY_D))
            {
                Background(background);
                Floor(floor);
                //Obstaculo(obstaculo);
                Draw_Nesha(nesha_D);
                img[1].posX+=speed;
            } 
           
            if(IsKeyDown(KEY_A))
            {
                Background(background);
                Floor(floor);
                //Obstaculo(obstaculo);
                Draw_Nesha(nesha_A);
                img[1].posX-=speed;
            }
            
            if(IsKeyDown(KEY_W))//pular
            {
                Background(background);
                Floor(floor);
                //Obstaculo(obstaculo);
                DrawTexturePro(nesha_jump, frameRec, (Rectangle){ img[1].posX+32, img[1].posY+32, frameRec.width * 2.5f, frameRec.height * 2.5f }, origin, 0.0f, WHITE);
            }
            
            if(IsKeyDown(KEY_S))//abaixar
            {    
                Background(background);
                Floor(floor);
                //Obstaculo(obstaculo);
                Draw_Nesha(nesha_squat);
            }
        EndDrawing();
    }
    
    StopMusicStream(music);
    UnloadTexture(background); 
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

void Background(Texture2D texture)
{
    ClearBackground(RAYWHITE); 
    DrawTextureEx(texture, (Vector2){ scrollingBack, img[0].posY }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(texture, (Vector2){ texture.width*2 + scrollingBack, img[0].posY }, 0.0f, 2.0f, WHITE);
}

void Nesha_move_background(Texture2D texture)
{
    if (IsKeyDown(KEY_D)) {
            scrollingBack -= speed; //nesha p/ direita -> fundo p/ esquerda
            background_direction = true;
        }
        else if (IsKeyDown(KEY_A)) {
            scrollingBack += speed; // nesha p/ esquerda -> fundo p/ direita
            background_direction = false;
        }
        
        if (scrollingBack <= -texture.width * 2) {
            scrollingBack = 0;
        }
        else if (scrollingBack >= texture.width * 2) {
            scrollingBack = 0;
        }
}

void Floor(Texture2D texture)
{
    DrawTextureEx(texture, (Vector2){scrollingBack, img[2].posY }, 0.0f, 2.0f, WHITE); 
    DrawTextureEx(texture, (Vector2){texture.width*8 + scrollingBack, img[2].posY }, 0.0f, 2.0f, WHITE);
}

/*void Obstaculo (Texture2D texture)
{
    DrawTextureEx(texture, (Vector2){scrollingBack, img[3].posY }, 0.0f, 2.0f, WHITE); 
    DrawTextureEx(texture, (Vector2){texture.width*8 + scrollingBack, img[4].posY }, 0.0f, 1.0f, WHITE);
}
*/

void Draw_Nesha(Texture2D texture)
{
    DrawTextureEx(texture, (Vector2){ img[1].posX, img[1].posY }, 0, 2.5f, WHITE);
}

void UpdateAnimation(int *framesCounter, int *currentFrame, Rectangle *frameRec, int framesSpeed, Texture2D texture)
    {
        (*framesCounter)++;

        if (*framesCounter >= (60 / framesSpeed))
        {
            *framesCounter = 0;
            (*currentFrame)++;

            if (*currentFrame > 4)
                *currentFrame = 0;

            frameRec->x = (float)(*currentFrame) * (float)texture.width / 5;
        }
    }