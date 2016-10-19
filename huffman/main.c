#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue.h"
#include "Tree.h"
#include "HashFunctions.h"
#include <openssl/md5.h>
#include <dirent.h>
#include <windows.h>
#include <stdbool.h>
#include "comp_descomp.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_memfile.h>
//#include "interface_allegro5.h"

     const int LARGURA_TELA = 640; //Atributos da tela
     const int ALTURA_TELA = 480;

    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_BITMAP *botao_sair = NULL, *area_central = 0,*fundo=NULL,*botao_exit=NULL;
    ALLEGRO_BITMAP *compactar = NULL, *descompactar = NULL, *menu_program = NULL, *OK = NULL;
    ALLEGRO_BITMAP *nivel1 = NULL, *nivel2 = NULL, *nivel3 = NULL;
    char string[30]; //nome do arquivo;
    char senha[30];
    int operation;
    int nivel;

void menu();
void tela_compac();
void tela_descomp();

void print_text();
void pegar_arquivo();
void manipular_entrada(ALLEGRO_EVENT evento);

void pegar_senha(); //Depois de ter pego a entrada do arquivo
void print_text_senha();
void manipular_entrada_senha();

void pegar_senha()
{
    bool concluido=false;
    bool sair=false;

        fundo = al_load_bitmap("Implementando Interface/imagens/bg_senha.jpg");
        al_draw_bitmap(fundo,0,0,0);
        botao_exit = al_load_bitmap("Implementando Interface/imagens/sair.jpg");
        menu_program = al_load_bitmap("Implementando Interface/imagens/menu.jpg");
        OK = al_load_bitmap("Implementando Interface/imagens/ok.jpg");

        al_draw_bitmap(botao_exit,LARGURA_TELA - al_get_bitmap_width(botao_exit) - 10,
                        ALTURA_TELA - al_get_bitmap_height(botao_exit) - 10, 0);
        while(!sair)
        {
            al_draw_bitmap(fundo,0,0,0);
            al_draw_bitmap(botao_exit,LARGURA_TELA - al_get_bitmap_width(botao_exit) - 10,
                        ALTURA_TELA - al_get_bitmap_height(botao_exit) - 10, 0);
            al_draw_bitmap(menu_program,250,420,0);
            al_draw_bitmap(OK,390,420,0);

            while(!al_is_event_queue_empty(fila_eventos))
            {
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos,&evento);
                //DEBUG;
                if(!concluido)
                { //printf ("oioioi\n");
                    manipular_entrada_senha(evento);
                    if(evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
                    {
                    concluido=true;
                    }

                }

                 if(evento.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                {
                 if(evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_exit)-10 && evento.mouse.x <= LARGURA_TELA
                        - 10 && evento.mouse.y <= ALTURA_TELA - 10 && evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_exit)
                       -10)
                    {
                        sair = true;
                        //finalizar();
                        return ;
                    }
                if(evento.mouse.x >= 390 && evento.mouse.x <= 510 && evento.mouse.y <= 540 && evento.mouse.y >= 420)
                    {
                        if(strlen(senha)==0)
                        {
                            al_show_native_message_box(NULL, "WinFAKE",
                            "Por favor, insira uma senha!\n",NULL,
                            NULL, ALLEGRO_MESSAGEBOX_WARN);
                            continue; //aviso para caso o usuario não coloque nada no campo
                        }

                        concluido=true;
                        sair=true;
                    }
                if(evento.mouse.x >= 250 && evento.mouse.x <= 370 && evento.mouse.y <= 540 && evento.mouse.y >= 420)
                    {
                        string[0] = '\0';
                        senha[0] = '\0';
                        menu();
                    }

                }

                if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                {
                    sair = true;
                }


            }

       print_text_senha();
       al_flip_display();

    }

    if(operation==0)
    {
                al_show_native_message_box(NULL, "WinFAKE",
                "Arquivo comprimido com sucesso!", NULL,
                NULL, ALLEGRO_MESSAGEBOX_WARN);
                //finalizar(); //Pode colocar essa opção de fechar o programa ou não, para tirar só colocar // antes
                //string[0]='\0';
                //senha[0]='\0';
                return ;

    }
    else
    {

        al_show_native_message_box(NULL, "WinFAKE",
                "Arquivo descomprimido com sucesso!\n",NULL,
                NULL, ALLEGRO_MESSAGEBOX_WARN);
                //finalizar();  //Pode colocar essa opção de fechar o programa ou não, para tirar só colocar // antes
                //string[0]='\0';
                //senha[0]='\0';
                return ;
    }

}

void print_text_senha()
{
    if (strlen(senha) > 0)
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(fonte)) / 2,
                     ALLEGRO_ALIGN_CENTRE, senha);

    }
}

void manipular_entrada_senha(ALLEGRO_EVENT evento)
{
    if(evento.type==ALLEGRO_EVENT_KEY_CHAR)
    {
        if(strlen(senha)<=30)
        {
            char temp[] = {evento.keyboard.unichar, '\0'};

            if(evento.keyboard.unichar >= ' ' && evento.keyboard.unichar <='~')
            {
                strcat(senha,temp);
            }


        }
        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(senha) != 0)
        {
            senha[strlen(senha) - 1] = '\0';
        }
    }
}

    void print_text()
    {
    if (strlen(string) > 0)
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(fonte)) / 2,
                     ALLEGRO_ALIGN_CENTRE, string);

    }
    }

     void finalizar()
    {
    al_destroy_bitmap(fundo);
    al_destroy_font(fonte);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
    }

    void tela_descomp()
    {
    operation=1;
    fundo = al_load_bitmap("Implementando Interface/imagens/bg_descompac.jpg");
    al_draw_bitmap(fundo, 0, 0, 0);
    botao_exit = al_load_bitmap("Implementando Interface/imagens/sair.jpg");

    nivel1 = al_create_bitmap(100,50);
    nivel2 = al_create_bitmap(100,50);
    nivel3 = al_create_bitmap(100,50);

    nivel1 = al_load_bitmap("Implementando Interface/imagens/nivel1.jpg");
    nivel2 = al_load_bitmap("Implementando Interface/imagens/nivel2.jpg");
    nivel3 = al_load_bitmap("Implementando Interface/imagens/nivel3.jpg");
    menu_program = al_load_bitmap("Implementando Interface/imagens/menu.jpg");

    al_draw_bitmap(nivel1,100,150,0);
    al_draw_bitmap(nivel2,250,150,0);
    al_draw_bitmap(nivel3,400,150,0);
    al_draw_bitmap(menu_program,250,420,0);

    al_draw_bitmap(botao_exit,LARGURA_TELA - al_get_bitmap_width(botao_exit) - 10,
                            ALTURA_TELA - al_get_bitmap_height(botao_exit) - 10, 0);
    al_flip_display();
    int exit=0;
    while(!exit)
    {
         while(!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos,&evento);
            //se o evento foi de clicar
            if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if(evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_exit)-10 && evento.mouse.x <= LARGURA_TELA
                        - 10 && evento.mouse.y <= ALTURA_TELA - 10 && evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_exit)
                       -10)
                {
                    exit = 1;
                    finalizar();
                    return ;
                }
                if(evento.mouse.x>=100 && evento.mouse.x<= 220 && evento.mouse.y <= 200 && evento.mouse.y >=150)
                {
                    printf ("ENTROU NO NIVEL 1!\n");
                    nivel=1;
                    pegar_arquivo();
                }
                if(evento.mouse.x>=250 && evento.mouse.x<= 370 && evento.mouse.y <= 200 && evento.mouse.y >=150)
                {
                    printf ("ENTROU NO NIVEL 2!\n");
                    pegar_arquivo();
                }
                if(evento.mouse.x>=400 && evento.mouse.x<= 520 && evento.mouse.y <= 200 && evento.mouse.y >=150)
                {
                    printf ("ENTROU NO NIVEL 3!\n");
                    nivel=3;
                    pegar_arquivo();
                }
                if(evento.mouse.x>=250 && evento.mouse.x <=370 && evento.mouse.y <=540 && evento.mouse.y>=420)
                {
                    printf ("VOLTOU PARA O MENU!\n");
                    menu();
                }
            }
        }

    }
    return ;

    }

    void manipular_entrada(ALLEGRO_EVENT evento)
    {
    if(evento.type==ALLEGRO_EVENT_KEY_CHAR)
    {
        if(strlen(string)<=30)
        {
            char temp[] = {evento.keyboard.unichar, '\0'};

            if(evento.keyboard.unichar >= ' ' && evento.keyboard.unichar <='~')
            {
                strcat(string,temp);
            }


        }
        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(string) != 0)
        {
            string[strlen(string) - 1] = '\0';
        }
    }
    }

    void pegar_arquivo()
    {

    bool concluido=false;
    bool sair=false;

        fundo = al_load_bitmap("Implementando Interface/imagens/bg_white.jpg");
        al_draw_bitmap(fundo,0,0,0);
        botao_exit = al_load_bitmap("Implementando Interface/imagens/sair.jpg");
        menu_program = al_load_bitmap("Implementando Interface/imagens/menu.jpg");
        OK = al_load_bitmap("Implementando Interface/imagens/ok.jpg");


        al_draw_bitmap(botao_exit,LARGURA_TELA - al_get_bitmap_width(botao_exit) - 10,
                        ALTURA_TELA - al_get_bitmap_height(botao_exit) - 10, 0);
        while(!sair)
        {
            al_draw_bitmap(fundo,0,0,0);
            al_draw_bitmap(botao_exit,LARGURA_TELA - al_get_bitmap_width(botao_exit) - 10,
                        ALTURA_TELA - al_get_bitmap_height(botao_exit) - 10, 0);
            al_draw_bitmap(menu_program,250,420,0);
            al_draw_bitmap(OK,390,420,0);

            while(!al_is_event_queue_empty(fila_eventos))
            {
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos,&evento);
                //DEBUG;
                if(!concluido)
                { //printf ("oioioi\n");
                    manipular_entrada(evento);

                    if(evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
                    {
                    concluido=true;
                    }

                }
                if(evento.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                {
                 if(evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_exit)-10 && evento.mouse.x <= LARGURA_TELA
                        - 10 && evento.mouse.y <= ALTURA_TELA - 10 && evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_exit)
                       -10)
                    {
                        sair = true;
                        finalizar();
                        return ;
                    }
                if(evento.mouse.x >= 390 && evento.mouse.x <= 510 && evento.mouse.y <= 540 && evento.mouse.y >= 420)
                    {
                        if(strlen(string)==0)
                        {
                            al_show_native_message_box(NULL, "WinFAKE",
                            "Por favor, coloque o nome do arquivo!\n",NULL,
                            NULL, ALLEGRO_MESSAGEBOX_WARN);
                            continue; //aviso para caso o usuario não coloque nada no campo
                        }

                        concluido=true;
                        sair=true;
                    }
                if(evento.mouse.x >= 250 && evento.mouse.x <= 370 && evento.mouse.y <= 540 && evento.mouse.y >= 420)
                    {
                        string[0] = '\0';
                        senha[0] = '\0';
                        menu();
                    }

                }

                if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                {
                    sair = true;
                }


            }

       print_text();
       al_flip_display();
    //al_rest(5.0);
    }
    printf ("%s\n",string);
    remove("temp_json.txt");
    FILE *temp_json;
    temp_json = fopen("temp_json.txt","a");
    create_json(string,temp_json);

    FILE * arquivo = fopen(string,"rb");
    //char *ext = get_extension(string);

    //create_json(string,temp_json);

    //FILE * arquivo = fopen(string,"rb");


    pegar_senha();
    printf("%s\n",senha);
    unsigned char *md5 = createMd5(senha);

    char *ext = get_extension(string);
    unsigned int ext_length = get_extension_length(ext);
    unsigned char *filename = get_filename(string,ext_length);
    unsigned int filename_length = get_filename_length(string,ext_length);
    printf("%s\n",string);
    printf ("%s\n",senha);


    if(nivel==1 && operation==0)
    {
     comprimir(arquivo,string,"compressed.huff");

    }
    else if(nivel==3 && operation==0)
    {
     compressao_tripla(arquivo,string,md5,ext,ext_length,filename,filename_length);

    }

    else if(nivel==1 && operation==1)
    {
     descomprimir(arquivo,"descompressed");

    }
    else if(nivel==3 && operation==1)
    {
     descompressao_tripla(arquivo,md5);
    }


    return ;
}

    void tela_compac()
    {
    operation=0;
    fundo = al_load_bitmap("Implementando Interface/imagens/bg_compac.jpg");
    al_draw_bitmap(fundo, 0, 0, 0);
    botao_exit = al_load_bitmap("Implementando Interface/imagens/sair.jpg");

    nivel1 = al_create_bitmap(100,50);
    nivel2 = al_create_bitmap(100,50);
    nivel3 = al_create_bitmap(100,50);


    nivel1 = al_load_bitmap("Implementando Interface/imagens/nivel1.jpg");
    nivel2 = al_load_bitmap("Implementando Interface/imagens/nivel2.jpg");
    nivel3 = al_load_bitmap("Implementando Interface/imagens/nivel3.jpg");
    menu_program = al_load_bitmap("Implementando Interface/imagens/menu.jpg");

    al_draw_bitmap(nivel1,100,150,0);
    al_draw_bitmap(nivel2,250,150,0);
    al_draw_bitmap(nivel3,400,150,0);
    al_draw_bitmap(menu_program,250,420,0);

    al_draw_bitmap(botao_exit,LARGURA_TELA - al_get_bitmap_width(botao_exit) - 10,
                            ALTURA_TELA - al_get_bitmap_height(botao_exit) - 10, 0);
    al_flip_display();
    bool exit=false;
    while(!exit)
    {
         while(!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos,&evento);
            //se o evento foi de clicar
            if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if(evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_exit)-10 && evento.mouse.x <= LARGURA_TELA
                        - 10 && evento.mouse.y <= ALTURA_TELA - 10 && evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_exit)
                       -10)
                {
                    exit = true;
                }
                if(evento.mouse.x>=100 && evento.mouse.x<= 220 && evento.mouse.y <= 200 && evento.mouse.y >=150)
                {
                    printf ("ENTROU NO NIVEL 1!\n");
                    nivel=1;
                    pegar_arquivo();
                }
                if(evento.mouse.x>=250 && evento.mouse.x<= 370 && evento.mouse.y <= 200 && evento.mouse.y >=150)
                {
                    printf ("ENTROU NO NIVEL 2!\n");
                    pegar_arquivo();
                }
                if(evento.mouse.x>=400 && evento.mouse.x<= 520 && evento.mouse.y <= 200 && evento.mouse.y >=150)
                {
                    printf ("ENTROU NO NIVEL 3!\n");
                    nivel=3;
                    pegar_arquivo();
                }
                if(evento.mouse.x>=250 && evento.mouse.x <=370 && evento.mouse.y <=540 && evento.mouse.y>=420)
                {
                    printf ("VOLTOU PARA O MENU!\n");
                    menu();
                }
            }
        }

    }

    return ;

}

    void menu()
    {

    bool sair=false;
    botao_exit = al_create_bitmap(100,50);
    compactar = al_create_bitmap(100,50);
    descompactar = al_create_bitmap(100,50);

    fundo = al_load_bitmap("Implementando Interface/imagens/bg_menu.jpg");
    al_draw_bitmap(fundo, 0, 0, 0);
    botao_exit = al_load_bitmap("Implementando Interface/imagens/sair.jpg");
    compactar = al_load_bitmap("Implementando Interface/imagens/compactar.jpg");
    descompactar = al_load_bitmap("Implementando Interface/imagens/descompactar.jpg");
    al_draw_bitmap(botao_exit,LARGURA_TELA - al_get_bitmap_width(botao_exit) - 10,
                            ALTURA_TELA - al_get_bitmap_height(botao_exit) - 10, 0);

    al_draw_bitmap(compactar,100,150,0);
    al_draw_bitmap(descompactar,400,150,0);
    al_flip_display();


        while(!sair)
        {

            //Para verificar se há eventos na fila
            while(!al_is_event_queue_empty(fila_eventos))
            {
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos,&evento);
                //Se o evento foi de clicar
                if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) //Se fosse MOUSE_AXES, seria só passar o mouse por cima
                {
                    if(evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_exit)-10 && evento.mouse.x <= LARGURA_TELA
                        - 10 && evento.mouse.y <= ALTURA_TELA - 10 && evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_exit)
                       -10)
                    {
                        sair = true;

                        return ;
                    }
                    if(evento.mouse.x >= 100 && evento.mouse.x <= 220 && evento.mouse.y <= 200 && evento.mouse.y >= 150)
                    {
                           printf ("ENTROU NA COMPACTACAO!\n");
                        tela_compac();
                        return ;
                    }
                    if(evento.mouse.x >= 400 && evento.mouse.x <= 500 && evento.mouse.y <= 200 && evento.mouse.y >= 150)
                    {
                           printf ("ENTROU NA DESCOMPACTACAO!\n");
                        tela_descomp();
                        return ;
                    }
                }
            }
        }
    return ;
    }


int main(){
    printf("Huffman Decode!\n");

    al_init();//Iniciando allegro
    al_init_image_addon();
    janela = al_create_display(LARGURA_TELA,ALTURA_TELA); //Criando display
    al_set_window_title(janela,"WinFAKE");
    al_install_mouse(); //ativando o uso do mouse
    al_set_system_mouse_cursor(janela,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT); //Default para usar o cursor padrão
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    fonte = al_load_font("Implementando Interface/constan.ttf",20,0); //Carregando a fonte
    al_set_system_mouse_cursor(janela,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT); //Usando mouse na aplicação
    fila_eventos = al_create_event_queue(); //Criando evento para receber os comandos
    al_register_event_source(fila_eventos,al_get_mouse_event_source()); //Fazendo com que pegue os comandos do mouse
    al_register_event_source(fila_eventos,al_get_keyboard_event_source()); //Fazendo com que pegue os comandos do teclado

    menu();


   /*char path[1000];
    gets(path);
    remove("temp_json.txt");
    FILE *temp_json;
    temp_json = fopen("temp_json.txt","a");
    create_json(path,temp_json);

    FILE * arquivo = fopen(path,"rb");
    char senha[100];
    gets(senha);
    unsigned char *md5 = createMd5(senha);

    char *ext = get_extension(path);
    unsigned int ext_length = get_extension_length(ext);
    unsigned char *filename = get_filename(path,ext_length);
    unsigned int filename_length = get_filename_length(path,ext_length);
    printf("%s\n",path);
    printf("%s\n",senha);
    printf("\n1 -- Comprimir\n2 -- Descomprimir\n3 -- Compressao 3x\n4 -- Descompressao 3x\n");
    int pick;
    scanf("%d",&pick);


    switch(pick){

        case 4:
            descompressao_tripla(arquivo,md5);
            break;
        case 3:
            compressao_tripla(arquivo,path,md5,ext,ext_length,filename,filename_length);
            break;
        case 2:
            descomprimir(arquivo,"descompressed");
            break;
        case 1:
            comprimir(arquivo,path,"compressed.huff");
            break;
    }*/
    return 0;
}
