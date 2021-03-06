#include <stdio.h>
#include <stdlib.h>
#define DEBUG printf ("AQUI\n");
#define MAX_SIZE 5

int count[MAX_SIZE];
struct Node
{
    int value;
    struct Node *next;
    struct Node *prev;
};
typedef struct Node Node;

Node *newDoubList(Node *list)
{
    return NULL;
}
int isEmpty(Node *first)
{
    return (first==NULL);
}

Node *insertNode (Node *first, int conteudo)
{
    Node *newNode = (Node *) malloc (sizeof(Node));
    newNode->value = conteudo;
    newNode->next = first;
    newNode->prev = NULL;
        if(first!=NULL)
        {
            first->prev = newNode;
        }
    return newNode;
}

void searchNode (Node *first, int conteudo)
{
    Node *aux = first;
    int i=0;
        while(aux!=NULL)
        {
            if(aux->value == conteudo)
            {
                printf ("ACHOU NA POSICAO %d!\n",i);
                return ;
            }
            aux=aux->next;
            i++;
        }
}

Node *removeNode (Node *first, int conteudo)
{
    Node *aux;

        aux=first;
            while(aux!=NULL)
            {
                if(aux->value == conteudo)
                {
                    printf ("Elemento %d removido!\n",conteudo);
                    if(aux->next==NULL)
                    {
                        aux=aux->prev;
                        Node *p;
                        p=aux->prev;
                        p->next=NULL;

                        free(aux);
                        return p;
                    }
                    else if (aux->prev == NULL)
                    {
                        aux=aux->next;
                        Node *p;
                        p = aux->next;
                        p->prev = NULL;
                        free(aux);
                        return first;
                    }
                    else
                    {
                        aux->prev->next = aux->next;
                        aux->next->prev = aux->prev;
                        free (aux);
                        return first;
                    }

                }

                aux=aux->next;
            }
}

Node *MoveToFront (Node *first,int conteudo)
{
    Node *aux;
    aux=first;
     while(aux!=NULL)
            { //DEBUG;
                if(aux->value == conteudo)
                {
                    printf ("Elemento %d achado!\n",conteudo);
                    if(aux->next==NULL)
                    {
                        aux->prev->next=NULL;
                        aux->next=first;
                        aux->prev=NULL;
                        first->prev=aux;

                        return aux;

                    }
                    else if (aux->prev == NULL)
                    {
                        return aux;

                    }
                    else
                    {


                        aux->prev->next = aux->next;
                        aux->next->prev = aux->prev;
                        aux->next=first;
                        aux->prev=NULL;
                        first->prev=aux;
                        return aux;
                    }

                }

                aux=aux->next;
            }
            printf ("Elemento n�o existe!\n");
            return first;
}

Node *TransposeMethod (Node *first, int conteudo)
{
    Node *aux = first;
    int flag = 0;
        while(aux!=NULL)
        {

            if(aux->value==conteudo)
            {
                if(aux != first){
                    Node *p;
                    p = aux->prev;
                    if( p->prev != NULL){

                        p->prev->next = aux;
                        flag = 0;
                    }
                    else{
                        flag = 1;
                    }
                    if( aux->next != NULL){
                        aux->next->prev = p;
                    }
                    p->next = aux->next;
                    aux->prev = p->prev;

                    aux->next = p;
                    p->prev = aux;
                    if(!flag)
                        first = aux;

                    }
                      return first;


                }
                else
                    return first;

            }


            aux = aux->next;
        }


void countMethod(Node *first, int element){
 Node *aux = first;
 int countLocal = 0;
        while(aux!=NULL)
        {
             if(aux->value==element)
                {
                    count[countLocal]++;

                }
            countLocal++;
            aux = aux->next;
        }
}

void printDoublyLinkedBackward(Node *first)
{
    Node *aux;
    aux = first;
        while (aux!=NULL)
        {

            if(aux!=NULL) printf ("%d",aux->value);
            aux=aux->next;
            if(aux!=NULL)printf("-");
        }
        printf ("\n");

}



int main ()
{
    Node *list = newDoubList(list);



    int element,i;
    for(i = 0; i<MAX_SIZE;i++){
        count[i] = 0;
    }

        //printf ("Insira 5 elementos : \n");
        for(i=0;i<MAX_SIZE;i++)
        {
            scanf ("%d",&element);
                list = insertNode(list,element);
        }//printf ("\n");

        printDoublyLinkedBackward(list);

        //printf ("Escolha o elemento : \n");
        while(1)
        {
            scanf ("%d",&element);
            //searchNode(list,element);
                if(element==-1) break;

            //Transpose Method
            //list = TransposeMethod(list,element);

            //CountMethod
            //countMethod(list,element);

            //Imprime Count
            //for(i = 0; i<MAX_SIZE;i++){
              //printf("%d", count[i]);
            //}

            //MoveToFrontMethod
           //list = MoveToFront(list,element);

           //Imprime List
            //printDoublyLinkedBackward(list);
        }



    return 0;
}
