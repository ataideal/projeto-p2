#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

Tree_Node * create_tree_node(){/*Cria um novo nó de árvore vazio.*/
    Tree_Node * a = (Tree_Node*)malloc(sizeof(Tree_Node));
    a->left = NULL;
    a->right = NULL;
    a->priority = 0;
    a->isLeaf=0;
    return a;
}
Tree_Node * create_tree_node_ch(unsigned int ch){ /*Cria um novo nó e seta o char.*/
    Tree_Node * a = (Tree_Node*)malloc(sizeof(Tree_Node));
    a->ch = ch;
    a->left = NULL;
    a->right = NULL;
    a->isLeaf=0;
    a->priority = 0;
    return a;
}

Tree * create_tree(){ /*Cria um nova árvore.*/
    Tree *a = (Tree*)malloc(sizeof(Tree));
    a->size = 0;
    a->root = NULL;
    return a;
}
int isLeaf(Tree_Node * tree){ /*Verifica se o nó da árvore é folha.*/
    return tree->isLeaf;
}
void print_preorder_tree(Tree_Node * tree){/*Imprime a árvore em pré-ordem no console.*/
    if(tree!=NULL){
        if((tree->ch=='*' || tree->ch=='\\') && isLeaf(tree))/*Se o char do nó foi '*' ou '\' e o nó for folha, irá imprimir um '\' antes.*/
            printf("\\%c", tree->ch);
        else
            printf("%c", tree->ch);
        print_preorder_tree(tree->left);
        print_preorder_tree(tree->right);
    }
}

void print_preorder_tree_in_file(Tree_Node * tree, FILE *file){/*Imprime a árvore em pré-ordem no arquivo.*/

    if(tree!=NULL){
        if((tree->ch=='*' || tree->ch=='\\') && isLeaf(tree))/*Se o char do nó foi '*' ou '\' e o nó for folha, irá imprimir um '\' antes.*/
            fprintf(file, "\\%c", tree->ch);
        else
            fprintf(file, "%c", tree->ch);

        print_preorder_tree_in_file(tree->left, file);
        print_preorder_tree_in_file(tree->right,file);
    }

}

void print_content_in_file(char * hash[256], FILE *arq,FILE *file){/*Transforma o texto para nova representação em binário, junta os bits de 8 em 8, transforma em um caracter e imprime no arquivo comprimido.*/
    char buffer[512]; /*Cria um string de buffer pra armazenar os bits.*/
    buffer[0]='\0';
    char aux[8];/*Cria um auxiliar para armazenar os 8 bits que será transformado em caracter.*/
    aux[0]='\0';
    unsigned int caracter;
    printf("\n");
    while((caracter = getc(arq))!=EOF){ /*Loop para ler todos os caracteres do arquivo.*/
        strcat(buffer,hash[(unsigned char)caracter]); /*Copia a hash do caracter lido para o buffer.*/
        //printf ("%c",caracter);
        while(strlen(buffer)>=8){ /*Loop para enquanto o buffer for maior que 8, transformar em caracteres.*/
            strncat(aux,buffer,8);/*Copia os 8 primeiros bits do buffer pro auxiliar, que vai ser transformado em caracter codificado.*/
            char ch = (int)strtol(aux,NULL,2);/*Função strtol, recebe uma ponteiro pra string, um ponteiro pro ponteiro da string, e a base que a string está, e transforma para decimal.*/
            fprintf(file,"%c", ch); /*Imprime o caracter codificado no arquivo.*/
            aux[0]='\0'; /*Zera o axiliar.*/
            sprintf(buffer,"%s",buffer+8);/*Empurra a string buffer 8 casas a esquerda.*/
        }
    }
    printf ("last buffer:%s\n",buffer);
    if(strlen(buffer)>0){ /*Se o buffer for maior que 0, ainda existe o ultimo byte pra ser codificado.*/
        while(strlen(buffer)<8)/*Loop para preencher com 0 o final do buffer.*/
            strcat(buffer,"0");
        strncat(aux,buffer,8);
        printf ("last byte:%s\n",aux);
        char ch = (int)strtol(aux,NULL,2);
        fprintf(file,"%c", ch);
    }
}

void printf_first_bits_in_file(char first[16],FILE * file){/* Imprime os 2 primeiros bytes referentes ao tamanho lixo e tamanho da árvore.*/
    char aux[8]; /*Cria um auxiliar para armazenar os 8 bits que será transformado em caracter.*/
    strncpy (aux,first,8);/*Copia os 8 primeiros bits da string first para o auxiliar.*/
    long long int c1 = strtol(aux,NULL,2);/*Função strtol, recebe uma ponteiro pra string, um ponteiro pro ponteiro da string, e a base que a string está, e transforma para decimal.*/
    long long int c2 = strtol(first+8,NULL,2); /*Usa a função strtol para pegar os 8 ultimos bits da string first.*/
    unsigned char ch1=(int)c1,ch2=(int)c2; /*Converte pra char os bytes.*/
    fprintf(file,"%c%c", ch1,ch2);
}

int size_tree(Tree_Node* tree){ /*Conta o tamanho de nós da árvore.*/
	if(tree==NULL)
        return 0;
    if((tree->ch=='*' || tree->ch=='\\') && isLeaf(tree))
        return 2 + size_tree(tree->left) + size_tree(tree->right);
    return 1 + size_tree(tree->left) + size_tree(tree->right);
}

unsigned int get_trash_size(FILE *input_file) { /* Pega o tamanho do lixo no primeiro byte.*/
	unsigned int trash_size = 0;
	unsigned int first_byte;
	fseek(input_file, 0, SEEK_SET);
	first_byte = getc(input_file);
	trash_size = (unsigned int)(first_byte >> (5));
	return (trash_size);
}

unsigned int get_tree_size(FILE *input_file) {/* Pega o tamanho da arvore juntandos os 2 primeiros bytes e desconsiderando o 3 primeiros bits.*/
	unsigned int tree_size;
	unsigned char first_byte;
	unsigned int second_byte;

	fseek(input_file, 0, SEEK_SET); /* volta ao início do arquivo */

	/* recebe os dois primeiros bytes do arquivo */
	first_byte = getc(input_file);
	second_byte = getc(input_file);

	/* apaga os três primeiros bits do primeiro byte, pois só interessa os 5
	 * bits restantes */
	first_byte = (first_byte << 3);
	first_byte = (first_byte >> 3);

	/* o tamanho da árvore é a união entre os 5 últimos bits do primeiro byte
	 * e o segundo byte */
	tree_size = ((first_byte << 8) | second_byte);

	return (tree_size); /* retorna o valor que estava escrito */
}

unsigned int *get_tree_array(FILE *input_file, unsigned int * tree_size) { /*Lê a arvore e armazena em um array.*/
    unsigned int i;

	/* cria um array com o tamanho da árvore recebido */
	unsigned int *tree_array;
    tree_array = (unsigned int *)malloc(sizeof(unsigned int)*(*tree_size)); /*Tamanho da arvore +2 porque pra representar os nós '\' e '*' precisamos de 1 caracter a mais pra cada.*/
	/* vai até o terceito byte do arquivo para receber os caracteres (o ter-
	 * ceiro byte é o primeiro byte da árvore) */
	fseek(input_file, 2, 0);

	/* recebe os caracteres em sequencia tree_size vezes */
	for (i = 0; i < (*tree_size); i++) {
	tree_array[i] = getc(input_file);
    }

    for (i = 0; i < (*tree_size); i++) {
            printf("%c",tree_array[i]);
    }

	return (tree_array); /* retorna o endereço para o array criado */
}

Tree_Node* fill_tree(Tree_Node * tree, unsigned int * vetor,int *atual,int tamanho){ /*Reconstrói a árvore com o vetor tree_array. */
    if(*atual>tamanho)
        return NULL;

    if(vetor[*atual]=='\\' && (vetor[(*atual)+1]=='\\' || vetor[(*atual)+1]=='*')){ /* Se tiver um '\' ele verifica o proximo caracter do arquivo e adiciona na árvore.*/
        (*atual)++;
        tree = create_tree_node_ch(vetor[*atual]); /* Cria um nó novo e seta o caracter.*/
        tree->isLeaf=1; /*Seta como folha.*/
        (*atual)++;
        return tree; /*Sobe retorna a tree para dar o backtrack na árvore, pois é uma folha */
    }

    if(tree==NULL) /* Se o nó estiver NULL, ele cria o nó novo com o caracter.*/
        tree = create_tree_node_ch(vetor[*atual]);/* Cria um nó novo e seta o caracter.*/

    if(vetor[*atual]=='*'){ /*Se o caracter adicionado for '*' então não é uma folha, logo iremos preencher a esquerda e a direita desse nó.*/
        (*atual)++;
        tree->isLeaf=0;
        tree->left = fill_tree(tree->left,vetor,atual,tamanho);
        tree->right = fill_tree(tree->right,vetor,atual,tamanho);
    }else{ /*Se for diferente de '*' então foi é uma folha da árvore.*/
        (*atual)++;
        tree->isLeaf=1;/*Seta como folha.*/
    }

    return tree; /*Retorna o nó.*/
}

Tree_Node *get_tree(FILE *input_file){ /*Função para ler a árvore do arquivo. */
    unsigned int tree_size = get_tree_size(input_file);
	/* recebe o array com a árvore em pré-ordem */
	unsigned int *tree_array;
	tree_array = get_tree_array(input_file, &tree_size);/*Joga a árvore num array. */

    Tree_Node * tree = NULL;
    int atual=0;
    tree = fill_tree(tree,tree_array,&atual,tree_size); /*Reconstrói a árvore.*/
    return tree;
}

