/* Projeto de LAED-I

   Nomes:
     Clara Freitas de Oliveira;
     Maria Clara de Carvalho Sousa Bertozi.
     
   "Nesha"
*/

#include "raylib.h"
#define SCREENWIDTH 1000
#define SCREENHEIGHT 600

Texture2D nesha_D;
Texture2D nesha_A;
Texture2D nesha_frente;
Texture2D nesha_pula;
Texture2D nesha_agacha;
Texture2D background;
Texture2D chao;
Texture2D obstaculo;
Music musica;
   
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
    bool DirecaoFundo = true;
    
   void Fundo( Texture2D texture);
   void Nesha_movimenta_fundo (Texture2D texture);
   void Chao (Texture2D texture);
   void Desenha_Nesha (Texture2D texture);
   void UpdateAnimation(int *framesCounter, int *currentFrame, Rectangle *frameRec, int framesSpeed, Texture2D texture);
   
int main()
{
    //confg. do titulxo e inicia a musica
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "NESHA");
    InitAudioDevice();
    
    //carrega as imagens(fundo, chao, obstaculos, neshas e musica)
    background = LoadTexture("fundo_nesha02.png");
    chao = LoadTexture("chao.png");
    obstaculo = LoadTexture("obstaculos.png");
    
    nesha_D = LoadTexture("Nesha_D.png");
    nesha_A = LoadTexture("Nesha_A.png");
    nesha_frente = LoadTexture("Nesha_FRENTE.png");
    nesha_pula = LoadTexture("Nesha_PULAR.png");
    nesha_agacha = LoadTexture("Nesha_AGACHAR.png");
    
    musica = LoadMusicStream("NeshaTheme.mp3");
    PlayMusicStream(musica);
    
    Rectangle frameRec = { 0.0f, 0.0f, (float)nesha_pula.width/5, (float)nesha_pula.height };
    Vector2 origin = { frameRec.width / 2, frameRec.height / 2 };
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    
    
    SetTargetFPS(60); //velocidade da Nesha
    
    while(!WindowShouldClose())
    {   
        UpdateMusicStream(musica);
        
        Nesha_movimenta_fundo(background);//Fundo se mov. no sentindo contrario a nesha
        
        BeginDrawing();
            
            Fundo (background);//Configuração do fundo
            
            Chao (chao);//configuração chão
            
            Obstaculo(obstaculo);//configuracao obstaculos
            
            //Configuração da Nesha
            if (DirecaoFundo) 
                Desenha_Nesha(nesha_frente);
            else 
                Desenha_Nesha(nesha_A);
            
            //Animação
            UpdateAnimation(&framesCounter, &currentFrame, &frameRec, framesSpeed, nesha_pula);

    
            //Configuração dos limites da tela
            if (img[1].posX < -50) 
                img[1].posX = -50;
            else if (img[1].posX > 800) 
                img[1].posX = 800;
            
    
            //Configuração dos botões
            if(IsKeyDown(KEY_D))
            {
                Fundo (background);
                Chao (chao);
                Obstaculo(obstaculo);
                Desenha_Nesha(nesha_D);
                img[1].posX+=speed;
            } 
           
            if(IsKeyDown(KEY_A))
            {
                Fundo (background);
                Chao (chao);
                Obstaculo(obstaculo);
                Desenha_Nesha(nesha_A);
                img[1].posX-=speed;
            }
            
            if(IsKeyDown(KEY_W))//pular
            {
                Fundo (background);
                Chao (chao);
                Obstaculo(obstaculo);
                DrawTexturePro(nesha_pula, frameRec, (Rectangle){ img[1].posX+32, img[1].posY+32, frameRec.width * 2.5f, frameRec.height * 2.5f }, origin, 0.0f, WHITE);
            }
            
            if(IsKeyDown(KEY_S))//abaixar
            {    
                Fundo (background);
                Chao (chao);
                Obstaculo(obstaculo);
                Desenha_Nesha(nesha_agacha);
            }
        EndDrawing();
    }
    
    StopMusicStream(musica);
    UnloadTexture(background); 
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

void Fundo(Texture2D texture)
{
    ClearBackground(RAYWHITE); 
    DrawTextureEx(texture, (Vector2){ scrollingBack, img[0].posY }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(texture, (Vector2){ texture.width*2 + scrollingBack, img[0].posY }, 0.0f, 2.0f, WHITE);
}

void Nesha_movimenta_fundo (Texture2D texture)
{
    if (IsKeyDown(KEY_D)) {
            scrollingBack -= speed; //nesha p/ direita -> fundo p/ esquerda
            DirecaoFundo = true;
        }
        else if (IsKeyDown(KEY_A)) {
            scrollingBack += speed; // nesha p/ esquerda -> fundo p/ direita
            DirecaoFundo = false;
        }
        
        if (scrollingBack <= -texture.width * 2) {
            scrollingBack = 0;
        }
        else if (scrollingBack >= texture.width * 2) {
            scrollingBack = 0;
        }
}

void Chao (Texture2D texture)
{
    DrawTextureEx(texture, (Vector2){scrollingBack, img[2].posY }, 0.0f, 2.0f, WHITE); 
    DrawTextureEx(texture, (Vector2){texture.width*8 + scrollingBack, img[2].posY }, 0.0f, 2.0f, WHITE);
}

void Obstaculo (Texture2D texture)
{
    DrawTextureEx(texture, (Vector2){scrollingBack, img[3].posY }, 0.0f, 2.0f, WHITE); 
    DrawTextureEx(texture, (Vector2){texture.width*8 + scrollingBack, img[4].posY }, 0.0f, 1.0f, WHITE);
}
void Desenha_Nesha (Texture2D texture)
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