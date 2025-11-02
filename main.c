#include <stdio.h>
#include "diccionario.h"
#include "Utils.h"


/// ===============================================
/// ============ LOTES DE PRUEBA  =================
/// ===============================================

static void print_info(void* p){
    t_info i=*(t_info*)p;
    printf("\n%s => %d", i.clave, *(int*)i.valor);
}

// --------------------------------------------------------
// =========== LOTE 1: Inserciones simples =================
// --------------------------------------------------------
void lote1_basico() {
    printf("\n========== LOTE 1: Inserciones simples ==========\n");

    t_diccionario *dic = crear_dic(HASHSIZE);
    int v1 = 1, v2 = 2, v3 = 3;

    poner_dic(dic, "uno", &v1, sizeof(int));
    poner_dic(dic, "dos", &v2, sizeof(int));
    poner_dic(dic, "tres", &v3, sizeof(int));

    int valor;
    if (obtener_dic(dic, "dos", &valor, sizeof(int)))
        printf("obtener_dic('dos') = %d\n", valor);
    else
        printf("No se encontró clave 'dos'\n");

    printf("Diccionario Resultante:");
    recorrer_dic(dic, HASHSIZE, print_info);
    destruir_dic(dic, HASHSIZE);
}

// --------------------------------------------------------
// =========== LOTE 2: Reemplazo de valores ================
// --------------------------------------------------------
void lote2_reemplazo() {
    printf("\n========== LOTE 2: Reemplazo de valores ==========\n");

    t_diccionario *dic = crear_dic(HASHSIZE);
    int a = 10, b = 20, c = 99;

    poner_dic(dic, "perro", &a, sizeof(int));
    poner_dic(dic, "gato", &b, sizeof(int));
    poner_dic(dic, "perro", &c, sizeof(int));  // reemplaza el valor

    int valor;
    if (obtener_dic(dic, "perro", &valor, sizeof(int)))
        printf("Valor actual de 'perro' = %d\n", valor);

    printf("Diccionario Resultante:");
    recorrer_dic(dic, HASHSIZE, print_info);
    destruir_dic(dic, HASHSIZE);
}

// --------------------------------------------------------
// =========== LOTE 3: Colisiones controladas ==============
// --------------------------------------------------------
void lote3_colisiones() {
    printf("\n========== LOTE 3: Colisiones ==========\n");

    t_diccionario *dic = crear_dic(HASHSIZE);
    int v1 = 111, v2 = 222, v3 = 333;

    poner_dic(dic, "abc", &v1, sizeof(int));
    poner_dic(dic, "acb", &v2, sizeof(int)); // debería colisionar
    poner_dic(dic, "cab", &v3, sizeof(int)); // otra colisión posible

    printf("Valor del hash de 'abc' = %d\n", hash("abc"));
    printf("Valor del hash de 'acb' = %d\n", hash("acb"));
    printf("Valor del hash de 'cab' = %d\n", hash("cab"));

    int valor;
    if (obtener_dic(dic, "acb", &valor, sizeof(int)))
        printf("obtener_dic('acb') = %d\n", valor);

    printf("Diccionario Resultante:");
    recorrer_dic(dic, HASHSIZE, print_info);
    destruir_dic(dic, HASHSIZE);
}

// --------------------------------------------------------
// =========== LOTE 4: Eliminación =========================
// --------------------------------------------------------
void lote4_eliminacion() {
    printf("\n========== LOTE 4: Eliminación ==========\n");

    t_diccionario *dic = crear_dic(HASHSIZE);
    int v1 = 1, v2 = 2, v3 = 3;

    poner_dic(dic, "uno", &v1, sizeof(int));
    poner_dic(dic, "dos", &v2, sizeof(int));
    poner_dic(dic, "tres", &v3, sizeof(int));

    printf("Eliminando 'dos'...\n");
    int valor_sacado;
    if (sacar_dic(dic, "dos", &valor_sacado, sizeof(int)))
        printf("Valor eliminado: %d\n", valor_sacado);
    else
        printf("No se encontró la clave 'dos' para eliminar\n");

    if (!obtener_dic(dic, "dos", &valor_sacado, sizeof(int)))
        printf("Comprobación: 'dos' ya no está en el diccionario\n");

    printf("Diccionario Resultante:");
    recorrer_dic(dic, HASHSIZE, print_info);
    destruir_dic(dic, HASHSIZE);
}

// --------------------------------------------------------
// =========== LOTE 5: Carga grande ========================
// --------------------------------------------------------
void lote5_carga_grande() {
    printf("\n========== LOTE 5: Carga grande ==========\n");

    t_diccionario *dic = crear_dic(HASHSIZE);
    char clave[10];
    int valor;

    for (int i = 1; i <= 20; i++) {
        sprintf(clave, "k%d", i);
        valor = i * 100;
        poner_dic(dic, clave, &valor, sizeof(int));
    }

    printf("Diccionario Resultante:");
    recorrer_dic(dic, HASHSIZE, print_info);
    destruir_dic(dic, HASHSIZE);
}

/// =====================================
/// ============ MAIN ===================
/// =====================================


int main(){
    menu();

    //lote1_basico();
    //lote2_reemplazo();
    //lote3_colisiones();
    //lote4_eliminacion();
    //lote5_carga_grande();
    return 0;

}

