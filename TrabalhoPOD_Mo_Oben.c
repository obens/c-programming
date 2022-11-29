
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

//Struct que representa a data.
typedef struct {
	int dia;
	int mes;
        int ano;
} Date;

// Estrutura que contém os campos dos registros das tarefas
struct REC {
       char nome[50];
       int prioridade;
       Date entrega; 
	  struct REC *next; // implemente como lista, como árvore BST, AVL...
	  //struct REC *prev;
};
typedef struct REC Task;
void setData(Date *dt, int d,int m, int a)
{
  dt->dia=d;
  dt->mes=m;
  dt->ano=a;
}
void printData(Date d)
{
  printf("Date: %d/%d/%d\n",d.dia,d.mes,d.ano);
}
Task *getLast(Task *p)
{
 Task *aux=p;
  for (aux=p;aux->next!=NULL;aux=aux->next);
  return aux;
}

// Permite o cadastro de uma tarefa

Task *getTask(Task *f)
{
 Task *p, *aux;
  int d,m,a;
  p=(Task *)malloc(sizeof(Task));
  printf("Nome: ");
  scanf("%s",p->nome);
  printf("prioridade");
  scanf("%d",&p->prioridade);
  printf("data: ");
  scanf("%d %d %d",&d,&m,&a);
  setData(&p->entrega,d,m,a);
  p->next=NULL;
  if (f==NULL)
     f=p;
  else
  {
    aux=getLast(f);
    aux->next=p;
  }
  return f;
}


// Permite excluir uma tarefa
Task *delTask (Task *lista)
{
  char nome[50];
  scanf("%s", nome);
  Task *aux=lista, *prev=lista;
  while (strcmp(aux->nome, nome) != 0 && aux!=NULL)
  {
    prev=aux;
    aux=aux->next;
  }
  if (aux==NULL)
  {
    printf("Id não encontrado!\n");
    return lista;
  }
  prev->next=aux->next;
  if (aux==lista)
     lista=aux->next;
  free(aux);
  return lista;
}

// Lista o conteudo da lista de tarefas (todos os campos)
void listTasks (Task *lista){
 Task *aux;
  for (aux=lista;aux!=NULL;aux=aux->next)
  {
    printf("nome: %s\n",aux->nome);
    printf("prioridade: %d\n",aux->prioridade);
    printData(aux->entrega);
    printf("--------------\n");
  }    
}

// Permite consuLtar uma tarefa da lista pelo nome
void queryTask (Task *lista)
{
  char nome[50];
	scanf("%s", nome);
  Task *aux;
  for (aux=lista;aux!=NULL;aux=aux->next)
  {
    if (strcmp(aux->nome, nome) == 0) {
      printf("nome: %s\n",aux->nome);
      printf("prioridade: %d\n",aux->prioridade);
      printData(aux->entrega);
      printf("--------------\n");
    }
  }   
}

// Permite a atualização dos dados de uma tarefa
Task *upTask (Task *lista)
{
    Task *p;
    int d,m,a;
    p=(Task *)malloc(sizeof(Task));
    printf("Nome: ");
    scanf("%s",p->nome);
    printf("prioridade");
    scanf("%d",&p->prioridade);
    printf("data: ");
    scanf("%d %d %d",&d,&m,&a);
    setData(&p->entrega,d,m,a);
    Task *aux;
    for (aux=lista;aux!=NULL;aux=aux->next)
    {
      if (strcmp(aux->nome, p->nome) == 0) {
        aux->prioridade = p->prioridade;
        aux->entrega = p->entrega;
      }
    }

    return lista;
}

Task *lerArquivo(Task *f) {
     FILE *file;
     file = fopen("tarefas.txt", "rt");
     if (!file) return NULL;
     Task *aux = malloc(sizeof(Task));
     char nome[50];
     int dia;
     int mes;
     int ano;
     int prioridade;
     while (fscanf(file, "%s %d %d %d %d\n", nome, &prioridade, &dia, &mes, &ano) != EOF) {
     printf("aqui\n");
        Task *p = malloc(sizeof(Task));
        strcpy(p->nome, nome);
        p->prioridade = prioridade;
        setData(&p->entrega, dia, mes, ano);
        p->next = NULL;
        if (f==NULL)
          f=p;
        else
        {
          aux=getLast(f);
          aux->next=p;
        }
      }
    fclose(file);
    return f;
} 

void escreverArquivo(Task *lista) {
  Task *aux;
  FILE *file;
  file = fopen("tarefas.txt", "wt");
  for (aux=lista;aux!=NULL;aux=aux->next)
  {
    fprintf(file, "%s %d %d %d\n", lista->nome, lista->prioridade, lista->entrega.dia, lista->entrega.mes, lista->entrega.ano);
  } 
  fclose(file);
}

// Programa principal

int main()

{

Task *p;
//Task *first;//=NULL;
Task *first =NULL;
Task *aux;
    int op=0;
    Task t;
    first = lerArquivo(first);
	 while (op!=EXIT)
    {
  	printf("%d Finaliza",EXIT);
        printf("\n: ");
        scanf("%d",&op);
          switch(op){
              case 1 :
		            first = getTask(first);// inserir
                break;	
              case 2 : 
                first = delTask(first);//deletar
                break;
              case 3 : 
                first = upTask(first);//atualizar
                break;
              case 4 : queryTask(first);//busccar
                break;
              case 5 : listTasks(first);//listar
              break;
          }
    }
    escreverArquivo(first);

    return 0;
}




