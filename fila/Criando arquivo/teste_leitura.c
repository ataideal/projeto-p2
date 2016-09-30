#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Node
{
    int element;
    int priority;
    struct Node *next;
};

typedef struct Node Node;
struct priorityQueue
{
    int compara;
    int trocas;
    Node *First;
};
typedef struct priorityQueue priorityQueue;

int isEmpty (priorityQueue *pq)
{
    return (pq->First==NULL);
}

priorityQueue *createPriorityQueue()
{
    priorityQueue *newP = (priorityQueue*) malloc (sizeof(priorityQueue));
    newP->trocas=0;
    newP->compara=0;
    newP->First=NULL;
    return newP;
}

priorityQueue *enqueue (priorityQueue *pq, int elemento, int p)
{
    Node *aux;
    aux = (Node*) malloc (sizeof (Node));
    aux->element=elemento;
    aux->priority=p;
    pq->trocas++;

        if(isEmpty(pq) || p > pq->First->priority)
        {  //printf ("aqui");
            aux->next=pq->First;
            pq->First = aux;
            pq->compara++;
        }
        else
        {   Node *current;
            current=pq->First;

            while(current->next!=NULL && current->next->priority>p)
            { pq->compara++;
                current=current->next;
            }
            aux->next=current->next;
            current->next=aux;
        }

        return pq; //Pois tem que atualizar a cabeça da fila mesmo que não tenha sido inserido em ultimo ou primeiro.
}

void imprimirDados (priorityQueue *pq)
{
    FILE *arq;
    arq = fopen("comparações_pq_decrescente.txt", "a");

    fprintf (arq,"%d ",pq->trocas);
    fprintf(arq,"%d\n", pq->compara);

    fclose(arq);
}

int dequeue (priorityQueue *pq)
{
    if(!isEmpty(pq))
    {
        int i=pq->First->element;
        Node *current = pq->First;
        pq->First = pq->First->next;
        free(current);

        return i;
    }
    else
    {
        printf ("empty");
    }
}

int main ()
{
    priorityQueue *pq;
    pq = createPriorityQueue();
    int element;
    FILE *arq;

    arq = fopen("dados_entrada_decrescente.txt", "r");
    if(arq==NULL)
    {
        printf ("Nao deu\n");
        return ;
    }

    int i;
    int contador=50;
        i=0;
    while (!feof(arq))
    {
        fscanf(arq,"%d",&element);
        enqueue(pq,element,element);
        //printf ("%d - %d\n",i,element);
    i++;
        if(i==contador)
        {
            imprimirDados(pq);
            contador+=50;
            pq->compara=0;
        }
        if(i==500) break;

    }




    fclose(arq);
    printf ("Dados lidos!\n");

    return 0;
}
