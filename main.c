#include <stdio.h>
#include <stdlib.h>

typedef struct _Intervalo {
  int inicio;
  int ultimo;
} Intervalo;

typedef struct _GNodo {
  void* data;
  struct _GNodo* next;
} GNodo;

typedef GNodo* GList ;

GList initialization_glist() {
  return NULL;
}

GList alloc_gnodo() {
  GNodo* gn = malloc(sizeof(struct _GNodo));
  return gn;
}

GList prepend_glist(GList lista, void* data) {
  GList nuevaLista;
  nuevaLista = alloc_gnodo();
  nuevaLista->data = data;
  nuevaLista->next = lista;
  return nuevaLista;
}

void* get_data_glist(GList lista, int pos) {
  GList tmp = NULL;
  while (pos-- > 0 && lista) {
    tmp = lista->next;
    lista = NULL;
    lista = tmp;
    tmp = NULL;
  }
  return lista ? lista->data : 0;
}

int funcion_comparacio(Intervalo* primero, Intervalo* segundo) {
  return primero->ultimo < segundo->ultimo;
}

void glist_intercambiar(GList nodoA, GList nodoB) {
  void* nodoC = nodoB->data;
  nodoB->data = nodoA->data;
  nodoA->data = nodoC;
}

GList glist_selection_sort(GList lista) {
  if (lista == NULL){
    return NULL;
  }
  GList nodo = lista;
  for (;nodo->next != NULL; nodo = nodo->next) {
    GList aux = nodo;
    GList nodo2 = nodo->next;
    for (;nodo2 != NULL; nodo2 = nodo2->next) {
      if (funcion_comparacio(nodo2->data, aux->data)) {
        aux = nodo2;
      }
    }
    if (aux != nodo) {
      glist_intercambiar(nodo, aux);
    }
  }
  return lista;
}

int empty_glist(GList lista) {
  return lista == NULL;
}

int largo_glist(GList lista) {
  int largo = 0;
  for (GList start = lista; !empty_glist(start); start = start->next) largo++;
  return largo;
}

void glist_destruir_int(GList lista){
  GList proximo = lista;
  GList actual;
  for (; proximo != NULL;) {
    actual = proximo;
    proximo = proximo->next;
    free (actual);
  }
  lista = NULL;
  }

void glist_destruir_intervalo(GList lista){
  GList proximoDos = lista;
  GList actualDos;
  for (; proximoDos != NULL;) {
    actualDos = proximoDos;
    proximoDos = proximoDos->next;
    Intervalo* data = actualDos->data;
    free (data);
    free (actualDos);
  }
  lista = NULL;
}

int greedy_de_actividades(GList grilla) {
  grilla = glist_selection_sort(grilla);
//solucion_Parcial = set_Vacio()
  GList solucion = initialization_glist();
  int cantidadActividades = 0;

  if (grilla != NULL){
//solucion_Temporal, el primer nodo de la grilla ordenada
//inicializada por definicion de greedy lo agrego como
//solucion parcial
    Intervalo* primeraAct = get_data_glist(grilla, 0);
    solucion = prepend_glist(solucion, primeraAct);
  }
//Largo de la grilla
  int largoGrilla = largo_glist(grilla);
  int indiceI = 0;
  int indiceJ = 1;
// !set_es_vacio(C) && !es_solucion(solucion_Parcial)
  while (!empty_glist(grilla) && !(cantidadActividades > 0) && indiceJ < largoGrilla) {
//Extraigo los candidatos, por ahora soluciones temporales
//vuelo a invocar por indices a la variable primeraAct
    Intervalo* actPosJ = get_data_glist(grilla, indiceJ);
    Intervalo* actPosI = get_data_glist(grilla, indiceI);
//Aplico funcion es_solucion_parcial(soluciones_temporales)
    if (actPosJ->inicio >= actPosI->ultimo){
//Voy construyendo mi solucion parcial a base de mis temporales, es como si
//a cantidadActividades le sumara 1, ya que es su cardinal por eso me
//parece que la glist solucion y cantidadActividades son sol_Parciales
      solucion = prepend_glist(solucion, actPosJ);
      indiceI = indiceJ;
      indiceJ++;
    }
    else {
        indiceJ++;
    }
  }
  cantidadActividades = largo_glist(solucion);
//Aplico la !es_solucion(solucion_Parcial)
  if (!(cantidadActividades > 0)) {
//No encontró solucion set.vacio(), libero la memoria
//de solamente los nodos de la glist y no de la data
//es decir del esqueleto de la glist, porque sino
//se me liberan los nodos de las actividades cuyo
//cardinal es el resultado
    glist_destruir_int(solucion);
    return 0;
  }
  glist_destruir_int(solucion);
  return cantidadActividades;
}

int main()
{
    int cantidad, indice = 0;
    GList listaInterv = initialization_glist();
    printf("Inserte la cantidad de intervalos: ");
    scanf("%d", &cantidad);

    while (cantidad > 0) {
      int inicio, fin;
      printf("Inserte los datos del intervalo %i : ", ++indice);
      printf("\nInicio : ");
      scanf("%d", &inicio);
      printf("Fin : ");
      scanf("%d", &fin);
      Intervalo* interv = malloc(sizeof(struct _Intervalo));
      interv->inicio = inicio;
      interv->ultimo = fin;
      listaInterv = prepend_glist(listaInterv, interv);
      cantidad--;
    }
    int actividades = greedy_de_actividades(listaInterv);
    printf("La cantidad maxima de actividades es: %i\n", actividades);
    glist_destruir_intervalo(listaInterv);
    return 0;
}
