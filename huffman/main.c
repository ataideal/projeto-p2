#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue.h"
#include "Tree.h"

unsigned int get_trash_size(FILE *input_file) {
	unsigned int trash_size = 0;
	unsigned int first_byte;
	fseek(input_file, 0, SEEK_SET);
	first_byte = getc(input_file);
	trash_size = (unsigned int)(first_byte >> (5));
	return (trash_size);
}
unsigned int get_tree_size(FILE *input_file) {
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
unsigned int *get_tree_array(FILE *input_file, unsigned int * tree_size) {
    unsigned int i;

	/* cria um array com o tamanho da árvore recebido */
	int *tree_array;
    tree_array = (unsigned int *)malloc(sizeof(unsigned int)*((*tree_size)+2));
	/* vai até o terceito byte do arquivo para receber os caracteres (o ter-
	 * ceiro byte é o primeiro byte da árvore) */
	fseek(input_file, 2, 0);

	/* recebe os caracteres em sequencia tree_size vezes */
	for (i = 0; i < (*tree_size); i++) {
	tree_array[i] = getc(input_file);
        if(tree_array[i] == '\\'){
            (*tree_size)++;
            i++;
            tree_array[i] = getc(input_file);
        }
    }

    for (i = 0; i < (*tree_size); i++) {
            printf("%c",tree_array[i]);
    }
	return (tree_array); /* retorna o endereço para o array criado */
}

Tree_Node* fill_tree(Tree_Node * tree, unsigned int * vetor,int *atual,int tamanho){
    //printf ("%d ",*atual);
    if(*atual>tamanho)
        return NULL;

    if(vetor[*atual]=='\\' && (vetor[(*atual)+1]=='\\' || vetor[(*atual)+1]=='*')){
        (*atual)++;
        tree = create_tree_node_1(tree,vetor[*atual]);
        tree->isLeaf=1;
        (*atual)++;
        return tree;
    }

    if(tree==NULL)
        tree = create_tree_node_1(tree,vetor[*atual]);

    if(vetor[*atual]=='*'){
        (*atual)++;
        tree->isLeaf=0;
        tree->left = fill_tree(tree->left,vetor,atual,tamanho);
        tree->right = fill_tree(tree->right,vetor,atual,tamanho);
    }else{
        (*atual)++;
        tree->isLeaf=1;
    }

    return tree;
}

Tree_Node *get_tree(FILE *input_file){
    unsigned int tree_size = get_tree_size(input_file);
	/* recebe o array com a árvore em pré-ordem */
	unsigned int *tree_array;
	tree_array = get_tree_array(input_file, &tree_size);

    Tree_Node * tree = NULL;
    int atual=0;
    printf ("\n");
    tree = fill_tree(tree,tree_array,&atual,tree_size);
    printf ("\n%d\n",tree_size);
    print_preorder_tree(tree);

    return tree;
}




void create_hash(Tree_Node * tree,char hash[256][40],char binary[40]){
    if(isLeaf(tree)){
        sprintf(hash[(unsigned char)tree->ch],"%s",binary);
    }
    else{
        strcat(binary,"0");
        create_hash(tree->left,hash,binary);
        binary[strlen(binary)-1]='1';
        create_hash(tree->right,hash,binary);
        binary[strlen(binary)-1]='\0';
    }
}

void size_tree(Tree_Node* tree, int * size){
	if(tree==NULL)
        return;
    (*size)++;
    size_tree(tree->left,size);
    size_tree(tree->right,size);
}

int size_tree_1(Tree_Node* tree){
	if(tree==NULL)
        return 0;
    return 1 + size_tree_1(tree->left) + size_tree_1(tree->right);
}


int is_bit_set(unsigned int character, int position) {
	unsigned int mask = 1 << position;
	return (mask & character);
}

void descomprimir(FILE *input_file) {
                int trash_size = get_trash_size(input_file);
                //printf("%d\n", trash_size);
                //printf("%d\n", get_tree_size(arquivo));
                Tree_Node *huff_tree = get_tree(input_file);
                Tree_Node *current_Node = huff_tree;
                FILE *outputFile = fopen("descompressed.txt","wb+");

                unsigned int currentByte = getc(input_file);
                int bit;
                unsigned int nextByte;
                while((nextByte=getc(input_file))!=EOF){
                    for(bit = 7;bit >= 0 ;bit--){
                            if(is_bit_set(currentByte,bit)){
                                if(current_Node->right != NULL)
                                    current_Node = current_Node->right;
                            }
                            else
                                if(current_Node->left != NULL)
                                    current_Node = current_Node->left;
                            if(current_Node->isLeaf == 1){
                                //printf("\nLeaf : %c",current_Node->ch);
                                fprintf(outputFile,"%c",current_Node->ch);
                                current_Node = huff_tree;
                            }
                    }
                    currentByte = nextByte;
                }

                 for(bit = 7;bit >= (signed int)trash_size ;bit--){

                    if(is_bit_set(currentByte,bit)){
                                if(current_Node->right != NULL)
                                    current_Node = current_Node->right;
                            }
                            else
                                if(current_Node->left != NULL)
                                    current_Node = current_Node->left;
                            if(current_Node->isLeaf == 1){
                                //printf("\nLeaf : %c",current_Node->ch);
                                fprintf(outputFile,"%c",current_Node->ch);
                                current_Node = huff_tree;
                            }
                 }

}



/**< apsokdopaskdopasokpdopsadsda */
int main(){
    printf("Huffman Decode!\n");
    char texto[100];
    scanf ("%s",texto);
    FILE * arquivo = fopen(texto,"rb");
    printf("\n1 -- Comprimir\n2 -- Descomprimir\n");
    int pick = 2;
    scanf("%d",&pick);
     int i;
            int vetor[256];
    switch(pick){
        case 2:
            descomprimir(arquivo);
            break;
        case 1:


            for(i=0;i<256;i++){
                vetor[i]=0;
            }
            unsigned int ch;
            while((ch = getc(arquivo))!=EOF){
                vetor[ch]++;
            }
        //    printf ("quantidade:%d",a);
            fclose(arquivo);
            /*
            for(i=0;i<256;i++){
                printf ("%d %d\n",i,vetor[i]);
            }*/
            //qsort(vetor,256,sizeof(Contar),cmpfunc);
            Priority_Queue * pq = create_priority_queue(); // fazer priority queue de nodes
            Tree * tree = create_tree();
            for(i=0;i<256;i++){
                if(vetor[i] !=0){
                    Tree_Node * a = create_tree_node();
                    a->priority = vetor[i];
                    a->isLeaf=1;
                    a->ch = i; //sprintf(a->ch,"%c",i);
                    pq = enqueue_pq(pq,a);
                    //tree->size++;
                }//printf ("char:%c freq:%d\n",vetor[i].ch,vetor[i].frequency);
            }
            //
            while(size_pq(pq)>1){
                Tree_Node * x1 = dequeue_pq(pq);
                Tree_Node * x2 = dequeue_pq(pq);
                Tree_Node * p = create_tree_node();
                p->priority = x1->priority + x2->priority;
                p->right = x2;
                p->left = x1;
                p->isLeaf=0;
                p->ch='*';//sprintf(p->ch,"*");
                pq = enqueue_pq(pq,p);

                //tree->size++;
            }

            tree->root = dequeue_pq(pq);
            size_tree(tree->root,&tree->size);
            //print_preorder_tree(tree->root);

            char hash[256][40];
            char binary [40];
            binary[0]='\0';
            create_hash(tree->root,hash,binary);

           /* for(i=0;i<256;i++){
                printf ("%c(%d): %s\n",i,i,hash[i]);
            }*/


            printf ("size:%d\n",tree->size);
            int bits_size=0;
            for(i=0;i<256;i++){
                bits_size += strlen(hash[i]) * vetor[i];
            }
            printf ("size bits:%d\n",bits_size);
            int garbage = 8 - bits_size%8;
             if (garbage==8)
                garbage=0;
            printf ("lixo:%d\n",garbage);


            char lixo[3];
            char tamanho[13];
            itoa(garbage,lixo,2);
            itoa(tree->size,tamanho,2);

            char first[16];
            first[0]='\0';
            int aux1 = 3-strlen(lixo);

            if(aux1==1)
                sprintf(first,"0");
            if(aux1==2)
                sprintf(first,"00");

            strcat(first,lixo);
            int aux = 13-strlen(tamanho);
            while(aux-- != 0)
                strcat(first,"0");
            strcat (first,tamanho);

            printf ("first:%s\n",first);

            FILE *output_file;
            arquivo = fopen(texto,"rb");
            output_file = fopen("compressed.huff", "wb+");
            print_preorder_tree(tree->root);
            printf_first_bits_in_file(first,output_file);
            print_preorder_tree_in_file(tree->root,output_file);
            print_content_in_file(hash,arquivo,output_file);
            fclose(arquivo);
            fclose(output_file);


            return 0;
            break;
    }
    return 0;
}
