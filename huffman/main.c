#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue.h"
#include "Tree.h"



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


/**< apsokdopaskdopasokpdopsadsda */
int main(){
    printf("Huffman!\n");
    char texto[100];
    scanf ("%s",texto);
    FILE * arquivo = fopen(texto,"rb");


    int i;
    int vetor[256];

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
    output_file = fopen("output.huff", "wb+");
    //print_preorder_tree(tree->root);
    printf_first_bits_in_file(first,output_file);
    print_preorder_tree_in_file(tree->root,output_file);
    print_content_in_file(hash,arquivo,output_file);
    fclose(arquivo);
    fclose(output_file);


    return 0;
}
