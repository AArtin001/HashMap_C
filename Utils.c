#include "Utils.h"
#include "diccionario.h"

void imprimir_info(void* p){
    t_info i = *(t_info*)p;
    printf("%s => %d\n", i.clave, *(int*)i.valor);
}

bool normalizar_palabra(char* p){
    int i = 0, j = (int)strlen(p) - 1, k = 0;;

    // Avanza 'i' hasta el primer caracter alfanumerico (letra o numero)
    while(i <= j && !isalnum((unsigned char)p[i]))
        i++;

    // Retrocede 'j' hasta el último caracter alfanumerico
    while(j >= i && !isalnum((unsigned char)p[j]))
        j--;

    // Si no quedan caracteres validos -> la palabra no sirve
    if(i > j){
        p[0] = '\0';
        return false;
    }

    //Nos fijamos que no haga overflow y copie la palabra en otro buffer
    for(int m = i; m <= j && k < MAX_PALABRA-1; ++m)
        p[k++] = p[m];
    p[k] = '\0';  // agrega terminador nulo

    // Pasa todo a minusculas
    for(int m = 0; p[m]; ++m)
        p[m] = (char)tolower((unsigned char)p[m]);

    // Devuelve true si hay al menos un caracter válido
    return p[0] != '\0';
}

void sumar_palabra(t_diccionario* dic, const char* palabra){
    int actual = 0;
    if(obtener_dic(dic, (char*)palabra, &actual, sizeof actual)) {
        int nuevo = actual + 1;
        poner_dic(dic, (char*)palabra, &nuevo, sizeof nuevo);
    } else {
        int uno = 1;
        poner_dic(dic, (char*)palabra, &uno, sizeof uno);
    }
}

int procesar_archivo(const char* path, t_diccionario* dic, t_stats* st){
    if(!path || !st) return 0;
    memset(st, 0, sizeof *st);

    FILE* f = fopen(path, "rt");
    if(!f){
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char palabra[MAX_PALABRA] = {0};
    int lpalabra = 0;
    int c;

    while((c = fgetc(f)) != EOF){
        unsigned char uc = (unsigned char)c;

        if(isspace(uc) || ispunct(uc)){ //si es separador o espacio
            if(lpalabra > 0){
                palabra[lpalabra] = '\0';
                if(normalizar_palabra(palabra)){
                    st->palabras++;
                    sumar_palabra(dic, palabra);
                }
                lpalabra = 0;
            }
            if(isspace(uc)){
                st->espacios++;
            }
            else{
                st->signos++;
            }
        } else {
            if(lpalabra < MAX_PALABRA-1){
                palabra[lpalabra++] = (char)uc;
            }
        }
    }
    /* último token si el archivo no acaba en separador */
    if(lpalabra > 0){
        palabra[lpalabra] = '\0';
        if(normalizar_palabra(palabra)){
            st->palabras++;
            sumar_palabra(dic, palabra);
        }
    }
    fclose(f);
    return 1;
}

void listar_apariciones(t_diccionario* dic){
    recorrer_dic(dic, HASHSIZE, imprimir_info);
}

long apariciones_de(t_diccionario* dic, const char* palabra){
    int out = 0;
    char w[MAX_PALABRA];
    strncpy(w, palabra, sizeof(w) - 1);
    w[sizeof(w) - 1] = '\0';
    if(!normalizar_palabra(w)){
        return 0;
    }

    if(obtener_dic(dic, w, &out, sizeof out)){
        return out;
    }

    return 0;
}


void menu(){
    char nombre[100];
    t_diccionario dic[HASHSIZE];
    crear_dic(dic, HASHSIZE);
    printf(" =========================================================\n");
    printf(" =                   PROCESADOR DE TEXTOS                =\n");
    printf(" =========================================================\n\n");
    printf("Ingrese el nombre del archivo a procesar. ej: texto.txt: ");
    scanf("%99s", nombre);
    printf("\nProcesando archivo '%s'...\n", nombre);
    t_stats st;

    if(!procesar_archivo(nombre, dic, &st)){
        printf("No se pudo procesar el archivo.\n");
        destruir_dic(dic, HASHSIZE);
        return;
    }

    int op;
    do{
        printf("\nMENU\n");
        printf("1) Estadisticas generales\n");
        printf("2) Listado apariciones (palabra: conteo)\n");
        printf("3) Buscar apariciones de una palabra\n");
        printf("0) Salir\n");
        printf("Opcion: ");
        if(scanf("%d", &op) != 1) break;
        getchar(); /* consumir \n */

        if(op == 1){
            printf("Palabras: %ld\nEspacios: %ld\nSignos: %ld\n",
                   st.palabras, st.espacios, st.signos);
        } else if(op == 2){
            listar_apariciones(dic);
        } else if(op == 3){
            char q[MAX_PALABRA];
            printf("Palabra: ");
            if(!fgets(q, sizeof q, stdin)) break;
            q[strcspn(q, "\r\n")] = '\0';
            long n = apariciones_de(dic, q);
            printf("'%s' aparece %ld vez/veces\n", q, n);
        }
    } while(op != 0);

    destruir_dic(dic, HASHSIZE);
}
