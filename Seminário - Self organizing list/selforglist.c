#include <stdio.h>
#include <stdlib.h>

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
                return 0;
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

Node *MoveToFront (Node *first,int element)
{

}

void printDoublyLinkedBackward(Node *first)
{
    Node *aux;
        while (aux!=NULL)
        {
            if(aux!=NULL) printf ("%d\n",aux->conteudo);
            aux=aux->next;
        }

}

int main ()
{
    Node *list = createList();





    return 0;
}
