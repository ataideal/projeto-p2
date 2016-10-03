#include <stdio.h>
#include <stdlib.h>
#define DEBUG printf ("AQUI\n");

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
            printf ("Elemento não existe!\n");
            return first;
}

Node *TransposeMethod (Node *first, int conteudo)
{
    Node *aux = first;
        while(aux!=NULL)
        {
            if(aux->value==conteudo)
            {
                if(aux->next==NULL)
                {
                    Node *p;
                    p = aux->prev;
                    Node *aux2;
                    aux2 = p;
                    p=aux;
                    aux=aux2;
                    /*aux->prev=p->prev;
                    aux->next=p;
                    p->next=NULL;
                    p->prev=aux;*/
                        //if(aux->prev==NULL) return aux;
                    return first;
                }
                else if (aux->prev==NULL)
                {
                    return first;
                }
                else
                {
                    Node *p;
                    p=aux->prev;
                    Node *aux2;
                    aux2 = aux;
                    aux=p;
                    p=aux2;
                    //free(aux2);
                    return first;

                }
            }


            aux = aux->next;
        }
}

void printDoublyLinkedBackward(Node *first)
{
    Node *aux;
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

        //printf ("Insira 5 elementos : \n");
        for(i=0;i<5;i++)
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

           //list = MoveToFront(list,element);
            list=TransposeMethod(list,element);
            printDoublyLinkedBackward(list);
        }



    return 0;
}
