#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_memfile.h>
#define DEBUG printf ("AQUI\n");

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int LARGURA_TELA = 640; //Atributos da tela
const int ALTURA_TELA = 480;

void menu();
void tela_compac();
void tela_descomp();

    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_BITMAP *botao_sair = NULL, *area_central = 0,*fundo=NULL,*botao_exit=NULL;
    ALLEGRO_BITMAP *compactar = NULL, *descompactar = NULL, *menu_program = NULL, *OK = NULL;
    ALLEGRO_BITMAP *nivel1 = NULL, *nivel2 = NULL, *nivel3 = NULL;
    char string[30]; //nome do arquivo;
    char senha[30];
    int operation;

void print_text();
void pegar_arquivo();
void manipular_entrada(ALLEGRO_EVENT evento);

void pegar_senha(); //Depois de ter pego a entrada do arquivo
void print_text_senha();
void manipular_entrada_senha();

    bool inicializar()
    {
        if(!al_init())
        {
            fprintf (stderr,"Falha ao inicializar init");
            return false;
        }

        if(!al_install_keyboard())
        {
            fprintf (stderr,"Falha ao inicializar teclado");
            return false;
        }

        if(!al_init_image_addon())
        {
            fprintf (stderr,"Falha ao inicializar init");
            return false;
        }
        al_init_font_addon();

        if (!al_init_ttf_addon())
        {
            fprintf(stderr, "Falha ao inicializar allegro_ttf.\n");
            return false;
        }

        janela = al_create_display(LARGURA_TELA,ALTURA_TELA);
        if(!janela)
        {
            fprintf(stderr, "Falha ao criar janela.\n");
            return false;
        }
        fila_eventos = al_create_event_queue();
        if(!fila_eventos)
        {
            fprintf(stderr, "Falha ao criar fila de eventos\n");
            return false;
        }

        al_set_window_title(janela,"WinFake");

        al_register_event_source(fila_eventos, al_get_display_event_source(janela));
        al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    return true;
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
    fundo = al_load_bitmap("imagens/bg_descompac.jpg");
    al_draw_bitmap(fundo, 0, 0, 0);
    botao_exit = al_load_bitmap("imagens/sair.jpg");

    nivel1 = al_create_bitmap(100,50);
    nivel2 = al_create_bitmap(100,50);
    nivel3 = al_create_bitmap(100,50);

    nivel1 = al_load_bitmap("imagens/nivel1.jpg");
    nivel2 = al_load_bitmap("imagens/nivel2.jpg");
    nivel3 = al_load_bitmap("imagens/nivel3.jpg");
    menu_program = al_load_bitmap("imagens/menu.jpg");

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
                }
                if(evento.mouse.x>=100 && evento.mouse.x<= 220 && evento.mouse.y <= 200 && evento.mouse.y >=150)
                {
                    printf ("ENTROU NO NIVEL 1!\n");
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

void tela_compac()
{
    operation=0;
    fundo = al_load_bitmap("imagens/bg_compac.jpg");
    al_draw_bitmap(fundo, 0, 0, 0);
    botao_exit = al_load_bitmap("imagens/sair.jpg");

    nivel1 = al_create_bitmap(100,50);
    nivel2 = al_create_bitmap(100,50);
    nivel3 = al_create_bitmap(100,50);


    nivel1 = al_load_bitmap("imagens/nivel1.jpg");
    nivel2 = al_load_bitmap("imagens/nivel2.jpg");
    nivel3 = al_load_bitmap("imagens/nivel3.jpg");
    menu_program = al_load_bitmap("imagens/menu.jpg");

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

void print_text()
{
    if (strlen(string) > 0)
    {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(fonte)) / 2,
                     ALLEGRO_ALIGN_CENTRE, string);

    }
}

void menu()
{
    bool sair=false;
    botao_exit = al_create_bitmap(100,50);
        compactar = al_create_bitmap(100,50);
        descompactar = al_create_bitmap(100,50);

    fundo = al_load_bitmap("imagens/bg_menu.jpg");
    al_draw_bitmap(fundo, 0, 0, 0);
    botao_exit = al_load_bitmap("imagens/sair.jpg");
    compactar = al_load_bitmap("imagens/compactar.jpg");
    descompactar = al_load_bitmap("imagens/descompactar.jpg");
    al_draw_bitmap(botao_exit,LARGURA_TELA - al_get_bitmap_width(botao_exit) - 10,
                            ALTURA_TELA - al_get_bitmap_height(botao_exit) - 10, 0);

    al_draw_bitmap(compactar,100,150,0);
    al_draw_bitmap(descompactar,400,150,0);
    al_flip_display();

    int i=0;
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

void pegar_arquivo()
{

    bool concluido=false;
    bool sair=false;

        fundo = al_load_bitmap("imagens/bg_white.jpg");
        al_draw_bitmap(fundo,0,0,0);
        botao_exit = al_load_bitmap("imagens/sair.jpg");
        menu_program = al_load_bitmap("imagens/menu.jpg");
        OK = al_load_bitmap("imagens/ok.jpg");


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
    pegar_senha();
    //finalizar();
    return ;
}

void pegar_senha()
{
    bool concluido=false;
    bool sair=false;

        fundo = al_load_bitmap("imagens/bg_senha.jpg");
        al_draw_bitmap(fundo,0,0,0);
        botao_exit = al_load_bitmap("imagens/sair.jpg");
        menu_program = al_load_bitmap("imagens/menu.jpg");
        OK = al_load_bitmap("imagens/ok.jpg");

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
                        finalizar();
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
                string[0]='\0';
                senha[0]='\0';
                return ;

    }
    else
    {

        al_show_native_message_box(NULL, "WinFAKE",
                "Arquivo descomprimido com sucesso!\n",NULL,
                NULL, ALLEGRO_MESSAGEBOX_WARN);
                //finalizar();  //Pode colocar essa opção de fechar o programa ou não, para tirar só colocar // antes
                string[0]='\0';
                senha[0]='\0';
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

int main(void)
{
    al_init();
    al_init_image_addon();
    janela = al_create_display(LARGURA_TELA,ALTURA_TELA);
    al_set_window_title(janela,"WinFAKE");
    al_install_mouse();
    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    if(!al_install_keyboard())
    {
        fprintf(stderr,"falha no keyboard!\n");
    }
    al_init_font_addon();
    if(!al_init_ttf_addon())
    {
        fprintf(stderr,"falha no addon da fonte!\n");
    }

    fonte=al_load_font("constan.ttf",20,0);
    if(!fonte)
    {
        fprintf(stderr,"Falha ao carregar a fonte!\n");
    }

        //Uso do mouse na aplicação
        al_set_system_mouse_cursor(janela,ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);


        fila_eventos = al_create_event_queue();

        //Tratar dos eventos vindos do mouse
        al_register_event_source(fila_eventos, al_get_mouse_event_source());
         al_register_event_source(fila_eventos, al_get_keyboard_event_source());

        menu(); //Começo do programa

    al_flip_display();





    //segurar o ambiente gráfico por 5 segundos
    //al_rest(5.0);


    finalizar();




    return 0;
}
