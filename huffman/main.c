#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue.h"
#include "Tree.h"
#include "HashFunctions.h"
#include <openssl/md5.h>
#include <dirent.h>
#include<windows.h>



int get_bit_at_position(unsigned int character, int position) {
	unsigned int mask = 1 << position; /*Pega o binário de 1 "000000001" e desloca a esquerda N vezes.*/
	return (mask & character); /*Retorna exatamente o binário da quantidade de posicoes que deslocamos o 1.*/
	/*	Ex: Caracter A, Posicion 2;
        Binário do 1 '00000001', deslocando 6 pra esquerda: '01000000';
        retorna a operação AND entre o Binário do A '01000001' e '01000000'.
        retorna '01000000';	*/
}
int set_bit_at_position(unsigned int character, int position) {
	unsigned int mask = 1 << position; /*Pega o binário de 1 "000000001" e desloca a esquerda N vezes.*/
	return (mask | character);
}
char* get_extension(char *path){
    int i;
    unsigned int tam;


    unsigned char bit;
    char *e = strrchr (path, '.');

    if (e == NULL)
        e = ".";
    if(strlen(e)> 6){
        printf("Extensão grande demais");
    }
    else{
        e = e+1;
    }

    return e;
}

unsigned int get_extension_length(char *ext){
    unsigned int tam;
    tam = strlen(ext);
    return tam;
}

unsigned int get_filename_length(char *path, unsigned int tam_ext){
         int tam = strlen(path) - (tam_ext+1);
        return (unsigned int)(tam);
}

unsigned int get_password_length(char *password){
        unsigned int tam = strlen(password);
        return (unsigned int)(tam);
}

unsigned char* get_filename(char *path, unsigned int tam_ext){
    unsigned char *buffer;
    int tam = strlen(path) - (tam_ext+1);
    buffer = (unsigned char*) malloc(sizeof(unsigned char)*tam);
    int c =0;
     while (c < tam) {
      buffer[c] = path[c];
      c++;
   }
   buffer[c] = '\0';


    return buffer;
}

unsigned char* createMd5(const char* password){
     unsigned char digest[16];

    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, password, strlen(password));
    MD5_Final(digest, &ctx);

    char * mdString = (char*)malloc(sizeof(char)*33);
    int i;
    for ( i = 0; i < 16; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

   return mdString;

}

void descomprimir(FILE *input_file,char * path) {
    int trash_size = get_trash_size(input_file); /*Pega o tamanho do lixo.*/
    Tree_Node *huff_tree = get_tree(input_file); /*Cria lê a árvore do arquivo e a reconstrói.*/
    Tree_Node *current_Node = huff_tree; /*Cria um nó auxiliar pro início da árvore.*/
    FILE *outputFile = fopen(path,"wb+");

    unsigned int currentByte = getc(input_file);/*Variável pro char atual.*/
    unsigned int nextByte; /*Variável pro proximo char atual.*/
    int bit;/*Auxiliar pro for*/

    while((nextByte=getc(input_file))!=EOF){/*Verifica se o proximo char não é o final do arquivo, e armazena ele.*/
        for(bit = 7;bit >= 0 ;bit--){ /*For começando do primeiro bit do 7 bit, contando da direita pra esquerda.*/
            if(get_bit_at_position(currentByte,bit)){ /*Verifica cada bit do caracter, se nao for 0, ele vai pra esquerda da árvore.*/
                if(current_Node->right != NULL)
                    current_Node = current_Node->right; /*Atualiza o nó atual da árvore pra o nó a direita.*/
            }
            else /*Se for 0, ele vai pra esquerda da árvore.*/
                if(current_Node->left != NULL)
                    current_Node = current_Node->left;/*Atualiza o nó atual da árvore pra o nó a direita.*/

            if(current_Node->isLeaf == 1){/*Se o nó que chegamos for uma folha, escrevemos ele no arquivo.*/
                fprintf(outputFile,"%c",current_Node->ch);
                current_Node = huff_tree; /*Nó atual vai ser novamente o ínicio da árvore.*/
            }
        }
        currentByte = nextByte;/*Atualiza o byte atual do arquivo*/
    }

    /* Ultimo byte do arquivo.*/
    for(bit = 7;bit >= (signed int)trash_size ;bit--){ /*Repete o processo acima, mas não considera os bits de lixo */
        if(get_bit_at_position(currentByte,bit)){
            if(current_Node->right != NULL)
                current_Node = current_Node->right;
        }
        else
            if(current_Node->left != NULL)
                current_Node = current_Node->left;

        if(current_Node->isLeaf == 1){
            fprintf(outputFile,"%c",current_Node->ch);
            current_Node = huff_tree;
        }
    }
    fclose(input_file);
    fclose(outputFile);
    //printf ("Descompressao completa!\nArquivo:descompressed\nTamanho do lixo:%d\nTamanho da arvore:%d\n",trash_size,size_tree(huff_tree));
}

unsigned int get_ext_length(FILE* input_file){
    unsigned int ext_length = 0;
	unsigned int ch;
	ch = getc(input_file);
	ext_length = (unsigned int)(ch >> (5));
	return ext_length;
}

char * get_ext(FILE* input_file, int ext_length){

    char * ext = (char*)malloc(sizeof(char)*(ext_length+1));
	int i;
	for(i=0;i<ext_length;i++)
        ext[i] = getc(input_file);
    ext[i]='\0';
	return ext;
}

char * get_password(FILE* input_file){
    char * pass = (char*)malloc(sizeof(char)*33);
	int i;
	for(i=0;i<32;i++)
        pass[i] = getc(input_file);
    pass[i]='\0';
	return pass;
}

unsigned int get_filename_length_file(FILE* input_file){
    unsigned int filename_length = 0;
	unsigned int ch;
	ch = getc(input_file);
	filename_length = (unsigned int)ch;
	return filename_length;
}

char * get_filename_file(FILE* input_file,int filename_length){
    char * filename = (char*)malloc(sizeof(char)*(filename_length+1));
	int i;
	for(i=0;i<filename_length;i++)
        filename[i] = getc(input_file);
    filename[i]='\0';
	return filename;
}
FILE* create_dir(FILE* json){
    char temp[10000];
   memset(temp,0,strlen(temp));

    char ch;

    while((ch = getc(json)) != EOF){


        if(ch == '{'){
            int count = 0;
             memset(temp,0,strlen(temp));
             ch = getc(json);
            while(ch != ',' && ch != '}'){

                if(ch == '\\'){
                    ch = getc(json);
                }

                temp[count] = ch;
                count++;
                 ch = getc(json);

            }

            CreateDirectory (temp, NULL);

        }
        else{

             memset(temp,0,strlen(temp));
            int count = 0;
            if(ch == '}' || ch == ',')
                ch = getc(json);
            while(ch != ',' && ch != '}'){

                if(ch == '\\'){
                    ch = getc(json);
                }

                temp[count] = ch;
                count++;
                ch = getc(json);
            }

            FILE *temp_file = fopen(temp,"w+");

            memset(temp,0,strlen(temp));

            count = 0;
            if(ch == '}')
                ch = getc(json);

            ch = getc(json);
            while(ch != ',' && ch != '}'){
                if(ch == '\\'){
                    ch = getc(json);
                }
                temp[count] = ch;
                count++;
                ch = getc(json);
            }
             printf("%s",temp);
            fprintf(temp_file,"%s",temp);
            fclose(temp_file);
         }
    }
}
FILE* create_json(char *path,FILE *temp_json){
    DIR *dir;
    dir = opendir(path);

    fprintf(temp_json,"{%s,", path);
    struct dirent *dp,*aux;
    aux = readdir (dir);

    while((dp = aux) != NULL){

        if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
        {
            aux = readdir(dir);
            continue;
        } else if(get_extension_length(get_extension(dp->d_name)) == 0){
            char temp_filename[1000];
            strcpy(temp_filename,path);
            strcat(temp_filename,"/");
            strcat(temp_filename,dp->d_name);

            create_json(temp_filename,temp_json);
        }
        else{
            char ch;
            char temp_filename[1000];
            strcpy(temp_filename,path);
             strcat(temp_filename,"/");
            strcat(temp_filename,dp->d_name);

            FILE *new_file = fopen(temp_filename,"rb");

            fprintf(temp_json,"%s,",temp_filename);
            while((ch = getc(new_file)) != EOF){

               if(ch == ',' || ch == '\\'){
                fprintf(temp_json,"\\");
               }
                fprintf(temp_json,"%c",ch);
            }



        }
        aux = readdir(dir);
        if(aux != NULL){
            fprintf(temp_json,",");
        }

    }
     fprintf(temp_json,"}");

     closedir(dir);

}

void descompressao_completa(FILE *input_file,char * md5) {
    int trash_size = get_trash_size(input_file); /*Pega o tamanho do lixo.*/
    Tree_Node *huff_tree = get_tree(input_file); /*Cria lê a árvore do arquivo e a reconstrói.*/
    Tree_Node *current_Node = huff_tree; /*Cria um nó auxiliar pro início da árvore.*/

    unsigned int ext_length = get_ext_length(input_file);
    char * ext = get_ext(input_file,ext_length);
    char * pass = get_password(input_file);
    unsigned int filename_length = get_filename_length_file(input_file);
    char * filename = get_filename_file(input_file,filename_length);

    printf ("\n\nEXT_LENGTH:%u\nEXT:%s\nFILENAME_LENGTH:%u\nFILENAME:%s\nMD5:%s\nPASS:%s\n\n",ext_length,ext,filename_length,filename,md5,pass);
    if (strcmp(md5,pass)!=0){
        printf ("Senha incorreta!\n");
        return ;
    }
    FILE *outputFile = fopen(strcat(strcat(filename,"."),ext),"wb+");

    unsigned int currentByte = getc(input_file);/*Variável pro char atual.*/
    unsigned int nextByte; /*Variável pro proximo char atual.*/
    int bit;/*Auxiliar pro for*/

    while((nextByte=getc(input_file))!=EOF){/*Verifica se o proximo char não é o final do arquivo, e armazena ele.*/
        for(bit = 7;bit >= 0 ;bit--){ /*For começando do primeiro bit do 7 bit, contando da direita pra esquerda.*/
            if(get_bit_at_position(currentByte,bit)){ /*Verifica cada bit do caracter, se nao for 0, ele vai pra esquerda da árvore.*/
                if(current_Node->right != NULL)
                    current_Node = current_Node->right; /*Atualiza o nó atual da árvore pra o nó a direita.*/
            }
            else /*Se for 0, ele vai pra esquerda da árvore.*/
                if(current_Node->left != NULL)
                    current_Node = current_Node->left;/*Atualiza o nó atual da árvore pra o nó a direita.*/

            if(current_Node->isLeaf == 1){/*Se o nó que chegamos for uma folha, escrevemos ele no arquivo.*/
                fprintf(outputFile,"%c",current_Node->ch);
                current_Node = huff_tree; /*Nó atual vai ser novamente o ínicio da árvore.*/
            }
        }
        currentByte = nextByte;/*Atualiza o byte atual do arquivo*/
    }

    /* Ultimo byte do arquivo.*/
    for(bit = 7;bit >= (signed int)trash_size ;bit--){ /*Repete o processo acima, mas não considera os bits de lixo */
        if(get_bit_at_position(currentByte,bit)){
            if(current_Node->right != NULL)
                current_Node = current_Node->right;
        }
        else
            if(current_Node->left != NULL)
                current_Node = current_Node->left;

        if(current_Node->isLeaf == 1){
            fprintf(outputFile,"%c",current_Node->ch);
            current_Node = huff_tree;
        }
    }
    fclose(input_file);
    fclose(outputFile);
    //printf ("Descompressao completa!\nArquivo:descompressed\nTamanho do lixo:%d\nTamanho da arvore:%d\n",trash_size,size_tree(huff_tree));
}

void print_ext_length_in_file(FILE * output_file,unsigned int ext_length){
    fprintf(output_file,"%c",(ext_length<<5));
}
void print_ext_in_file(FILE * output_file,char * ext){
    fprintf(output_file,"%s",ext);
}
void print_md5_in_file(FILE * output_file,unsigned char *md5){
    fprintf(output_file,"%s",md5);
}
void print_name_length_in_file(FILE * output_file,unsigned int filename_length){
    fprintf(output_file,"%c",filename_length);
}
void print_name_in_file(FILE * output_file,unsigned char *filename){
    fprintf(output_file,"%s",filename);
}

void comprimir (FILE * arquivo,char * path,char * output){
    int vetor[256]; /*Vetor para contar os caracteres.*/
    int i;
    for(i=0;i<256;i++){
        vetor[i]=0;
    }

    unsigned int ch;
    while((ch = getc(arquivo))!=EOF){/*Le todos os caracteres do arquivo, 1 por 1.*/
        vetor[ch]++;
    }
    fclose(arquivo);
    Priority_Queue * pq = create_priority_queue();/*Cria a PQ de nós de árvore.*/

    for(i=0;i<256;i++){ /*For para inserir todos os caracteres na arvore.*/
        if(vetor[i] !=0){ /*Verifica se esse caracter existe no texto.*/
            Tree_Node * a = create_tree_node(); /*Cria o nó que vai ser adicionado na árvore.*/
            a->priority = vetor[i]; /*Prioridade do nó será a quantidade de vezes que o caracter aparece no texto.*/
            a->isLeaf=1;/*Todos os caracteres do texto são folhas.*/
            a->ch = i; /*Seta o char no nó.*/
            pq = enqueue_pq(pq,a); /*Insere o nó na PQ*/
        }
    }
    while(size_pq(pq)>1){ /*Faz um loop que junta todos os nós, até sobrar somente um nó (nó raiz).*/
        Tree_Node * x1 = dequeue_pq(pq); /* Pega o nó com menor prioriodade da árvore.*/
        Tree_Node * x2 = dequeue_pq(pq);/* Pega o nó com menor prioriodade da árvore.*/
        Tree_Node * p = create_tree_node(); /*Cria um novo nó.*/
        p->priority = x1->priority + x2->priority; /*Novo nó tem a soma das prioridades de x1 e x2.*/
        p->left = x1; /* Nó da esquerda será o x1.*/
        p->right = x2; /* Nó da direita será o x2.*/
        p->isLeaf=0; /*O nó p será a junção de 2 nós, portanto não é folha */
        p->ch='*'; /*Seto '*' para o nó.*/
        pq = enqueue_pq(pq,p); /*Insiro este novo nó na PQ.*/
    }
    Tree * tree = create_tree();/*Cria a árvore.*/
    tree->root = dequeue_pq(pq);/*A árvore será o nó restante da PQ.*/
    tree->size = size_tree(tree->root); /*Percorre toda a árvore e conta os nós.*/

    char * hash[256]; /* Cria um 'hashmap' que vai armazenar a nova representação de bits de cada caracter do texto. 256 porque é quantos caracteres existem, e 40 porque é o tamanho 'máximo' da representação.*/
    for(i=0;i<256;i++){
        hash[i]=NULL;
    }
    char binary [256]; /* String auxiliar para usar no preenchimento da hashh.*/
    binary[0]='\0'; /*Zerando a String auxiliar.*/
    create_hash(tree->root,hash,binary); /*Função para preencher a hash recursivamente.*/
    int bits_size=0; /*Variável para saber quantos bits o novo texto terá.*/
    for(i=0;i<256 && hash[i]!=NULL;i++){
        bits_size += strlen(hash[i]) * vetor[i]; /*Multiplica a quantidade de bits da nova representação pela quantidade de vez que o caracter aparece no texto, e soma para a quantidade total de bits.*/
    }

    int garbage = 8 - bits_size%8; /* Calcula o tamanho do lixo. Pega o resto da divisão do tamanho de bits total por 8, e subtrai de 8.*/
    if (garbage==8)/*Se o cálculo do lixo der 8, é porque não existe lixo.*/
        garbage=0;


    char lixo[3]; /*String para o tamanho do lixo em bits.*/
    char tamanho[13];/*String para o tamanho da árvore em bits.*/
    itoa(garbage,lixo,2); /*Escreve na string o tamanho do lixo em binário.*/
    itoa(tree->size,tamanho,2); /*Escreve na string o tamanho da árvore em binário.*/

    char first[16]; /* Variável que será os 2 dois primeiros bytes do arquivo, em binário.*/
    first[0]='\0';

    int aux1 = 3-strlen(lixo); /* Verifica com quantos bits ele escreveu o lixo. */
    while(aux1-- != 0) /* Completar com '0' a quantidade de bits que faltar.*/
        strcat(first,"0");
    strcat(first,lixo); /*Escrever os bits do lixo na string dos 16 primeiros bits.*/

    int aux = 13-strlen(tamanho); /* Verifica com quantos bits ele escreveu o tamanho da árvore. */
    while(aux-- != 0) /* Completar com '0' a quantidade de bits que faltar.*/
        strcat(first,"0");

    strcat (first,tamanho); /*Escrever os bits da árvore na string dos 16 primeiros bits.*/

    FILE *output_file = fopen(output, "wb+");  /*Cria o arquivo de saída da compressão.*/
    arquivo = fopen(path,"rb"); /*Abre novamente o arquivo que será comprimido.*/
    printf_first_bits_in_file(first,output_file);/*Transforma os 16 primeiros bits em 2 bytes, e imprime no arquivo de saída.*/
    print_preorder_tree_in_file(tree->root,output_file); /*Imprime a árvore em pré-ordem no arquivo de saída.*/
    print_content_in_file(hash,arquivo,output_file); /*Imprime o texto comprimido.*/

    printf ("Compressao completa!\nArquivo:compressed.huff\nTamanho do lixo:%d\nTamanho da arvore:%d\n",garbage,tree->size);

    fclose(arquivo);
    fclose(output_file);
}

void compressao_completa(FILE * arquivo,char * path,unsigned char * md5, char * ext,unsigned int ext_length,unsigned char * filename,unsigned int filename_length){
    int vetor[256]; /*Vetor para contar os caracteres.*/
    int i;
    for(i=0;i<256;i++){
        vetor[i]=0;
    }

    unsigned int ch;
    while((ch = getc(arquivo))!=EOF){/*Le todos os caracteres do arquivo, 1 por 1.*/
        vetor[ch]++;
    }
    fclose(arquivo);
    Priority_Queue * pq = create_priority_queue();/*Cria a PQ de nós de árvore.*/

    for(i=0;i<256;i++){ /*For para inserir todos os caracteres na arvore.*/
        if(vetor[i] !=0){ /*Verifica se esse caracter existe no texto.*/
            Tree_Node * a = create_tree_node(); /*Cria o nó que vai ser adicionado na árvore.*/
            a->priority = vetor[i]; /*Prioridade do nó será a quantidade de vezes que o caracter aparece no texto.*/
            a->isLeaf=1;/*Todos os caracteres do texto são folhas.*/
            a->ch = i; /*Seta o char no nó.*/
            pq = enqueue_pq(pq,a); /*Insere o nó na PQ*/
        }
    }
    while(size_pq(pq)>1){ /*Faz um loop que junta todos os nós, até sobrar somente um nó (nó raiz).*/
        Tree_Node * x1 = dequeue_pq(pq); /* Pega o nó com menor prioriodade da árvore.*/
        Tree_Node * x2 = dequeue_pq(pq);/* Pega o nó com menor prioriodade da árvore.*/
        Tree_Node * p = create_tree_node(); /*Cria um novo nó.*/
        p->priority = x1->priority + x2->priority; /*Novo nó tem a soma das prioridades de x1 e x2.*/
        p->left = x1; /* Nó da esquerda será o x1.*/
        p->right = x2; /* Nó da direita será o x2.*/
        p->isLeaf=0; /*O nó p será a junção de 2 nós, portanto não é folha */
        p->ch='*'; /*Seto '*' para o nó.*/
        pq = enqueue_pq(pq,p); /*Insiro este novo nó na PQ.*/
    }
    Tree * tree = create_tree();/*Cria a árvore.*/
    tree->root = dequeue_pq(pq);/*A árvore será o nó restante da PQ.*/
    tree->size = size_tree(tree->root); /*Percorre toda a árvore e conta os nós.*/

    char * hash[256]; /* Cria um 'hashmap' que vai armazenar a nova representação de bits de cada caracter do texto. 256 porque é quantos caracteres existem, e 40 porque é o tamanho 'máximo' da representação.*/
    for(i=0;i<256;i++){
        hash[i]=NULL;
    }
    char binary [256]; /* String auxiliar para usar no preenchimento da hashh.*/
    binary[0]='\0'; /*Zerando a String auxiliar.*/
    create_hash(tree->root,hash,binary); /*Função para preencher a hash recursivamente.*/
    int bits_size=0; /*Variável para saber quantos bits o novo texto terá.*/
    for(i=0;i<256 && hash[i]!=NULL;i++){
        bits_size += strlen(hash[i]) * vetor[i]; /*Multiplica a quantidade de bits da nova representação pela quantidade de vez que o caracter aparece no texto, e soma para a quantidade total de bits.*/
    }

    int garbage = 8 - bits_size%8; /* Calcula o tamanho do lixo. Pega o resto da divisão do tamanho de bits total por 8, e subtrai de 8.*/
    if (garbage==8)/*Se o cálculo do lixo der 8, é porque não existe lixo.*/
        garbage=0;


    char lixo[3]; /*String para o tamanho do lixo em bits.*/
    char tamanho[13];/*String para o tamanho da árvore em bits.*/
    itoa(garbage,lixo,2); /*Escreve na string o tamanho do lixo em binário.*/
    itoa(tree->size,tamanho,2); /*Escreve na string o tamanho da árvore em binário.*/

    char first[16]; /* Variável que será os 2 dois primeiros bytes do arquivo, em binário.*/
    first[0]='\0';

    int aux1 = 3-strlen(lixo); /* Verifica com quantos bits ele escreveu o lixo. */
    while(aux1-- != 0) /* Completar com '0' a quantidade de bits que faltar.*/
        strcat(first,"0");
    strcat(first,lixo); /*Escrever os bits do lixo na string dos 16 primeiros bits.*/

    int aux = 13-strlen(tamanho); /* Verifica com quantos bits ele escreveu o tamanho da árvore. */
    while(aux-- != 0) /* Completar com '0' a quantidade de bits que faltar.*/
        strcat(first,"0");

    strcat (first,tamanho); /*Escrever os bits da árvore na string dos 16 primeiros bits.*/

    FILE *output_file = fopen("temp_file", "wb+");  /*Cria o arquivo de saída da compressão.*/
    arquivo = fopen(path,"rb"); /*Abre novamente o arquivo que será comprimido.*/
    printf_first_bits_in_file(first,output_file);/*Transforma os 16 primeiros bits em 2 bytes, e imprime no arquivo de saída.*/
    print_preorder_tree_in_file(tree->root,output_file); /*Imprime a árvore em pré-ordem no arquivo de saída.*/
    print_ext_length_in_file(output_file,ext_length);
    print_ext_in_file(output_file,ext);
    print_md5_in_file(output_file,md5);
    print_name_length_in_file(output_file,filename_length);
    print_name_in_file(output_file,filename);
    print_content_in_file(hash,arquivo,output_file); /*Imprime o texto comprimido.*/

    //printf ("Compressao completa!\nArquivo:compressed.huff\nTamanho do lixo:%d\nTamanho da arvore:%d\n",garbage,tree->size);

    fclose(arquivo);
    fclose(output_file);

}

void compressao_tripla (FILE * arquivo,char * path,unsigned char * md5, char * ext,unsigned int ext_length,unsigned char * filename,unsigned int filename_length){
    compressao_completa(arquivo,path,md5,ext,ext_length,filename,filename_length);
    printf ("Compressao-1\n");
    arquivo = fopen("temp_file", "rb");
    comprimir(arquivo,"temp_file","temp_file_1");
    //remove("temp_file");
    printf ("Compressao-2\n");
    arquivo = fopen("temp_file_1", "rb");
    comprimir(arquivo,"temp_file_1","compressed_3x.huff");
    //remove("temp_file_1");
    printf ("Compressao-3\n");
}

void descompressao_tripla(FILE * input_file, unsigned char * md5){
    descomprimir(input_file,"temp_1");
    printf ("Descompressao-1\n");
    input_file = fopen("temp_1","rb");
    descomprimir(input_file,"temp_2");
    printf ("Descompressao-2\n");
    remove("temp_1");
    input_file = fopen("temp_2","rb");
    descompressao_completa(input_file,(char*)md5);
    printf ("Descompressao-3\n");
    remove("temp_2");
}

int main(){
    printf("Huffman Decode!\n");
    char path[1000];
    gets(path);
    remove("temp_json.txt")
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
    }
    return 0;
}
