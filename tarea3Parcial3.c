#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pila - stack
//  - Apilar, apilan - desapilan
//  - Acciones - apilar, desapilar
//  - Necesitamos:  un arreglo que almacene la información
//                  un indice que nos diga donde esta el último alemento de la pila
//  - Función Apilar:
            // 1.  Verificar que exista espacio en la Pila
            // 2.  Si hay espacio
            //     2.1 Incrementa tope
            //     2.2 Coloca el valor en la posición de tope
            //     2.3 Regresa 1 porque si pudo insertar
            // 3.  Si no hay espacio
            //     3.1 Regresa 0 porque no pudo insertar
//  - Función Desapilar:
//         1. Verificiar que existan elementos en la Pila
//         2. Si hay elementos
//            2.1 Sacar el elemento de la posición tope
//            2.2 Decrementar tope
//            2.3 Regresar el elemento que sacó de la pila
//            2.4 Regresar un 1 porque si pudo desapilar
//         3. Si no hay elementos
//            3.1 Regresa 0 porque no pudo desapilar

#define TAM_PILA 20

struct struct_pila
{
    char datos[TAM_PILA];
    int tope;
};

typedef struct struct_pila Pila;

void inicializaPila(Pila *p);
int apila(Pila *p, char dato);
int desapilar(Pila *p, char *dato);
int jerarquia(char simbolo);

int main ()
{
    Pila pila;
    int post[TAM_PILA];
    char infija[TAM_PILA];
    int tamano, i, pos;

    int pudoApilar;
    int pudoDesapilar;
    char dato;

    inicializaPila(&pila);

    printf("Ingrese una expresion infija: ");
    scanf("%s", infija);

    pos = -1;

    tamano = strlen(infija);
    for(i = 0; i < tamano; i++)
    {
        dato = infija[i];
        if(dato == '(')
        {
            apila(&pila, dato);
        }else if (dato == ')')
        {
            while(pila.datos[pila.tope] != '(')
            {
                pos++;
                desapilar(&pila, &dato);
                post[pos] = dato;
            }
        }
        else if((dato >= 'A') && (dato <= 'Z') || (dato >= 'a') && (dato <= 'z'))
        {
            pos ++;
            post[pos] = dato;
        }else 
        {
            while(pila.tope > -1 && (jerarquia(dato) <= jerarquia(pila.datos[pila.tope])))
            {
                pos++;
                desapilar(&pila, &dato);
                post[pos] = pila.datos[pila.tope];
            }
        
        apila(&pila, dato);
        }
        
    }
    
    while(pila.tope > -1)
    {
        pos++;
        desapilar(&pila, &dato);
        post[pos] = dato;
    }

    printf("La expresión postfija es: ");
    for(i = 0; i <= pos; i++)
    {
        printf("%c", post[i]);
    }


/*    do
    {
        printf("Dame un caracter: ");
        scanf("%c", &dato);

        fflush(stdin);

        pudoApilar = apila(&pila, dato);
    } while (pudoApilar == 1);
    
do
{
    pudoDesapilar = desapilar(&pila, &dato);
    if(pudoDesapilar == 1)
    {
    printf("%c\n", dato);
    }

} while (pudoDesapilar == 1);
*/

    return 0;
}

int jerarquia(char simbolo)
{
    int jerarquia;
    
    switch (simbolo)
    {
    case '^': jerarquia = 3;
        break;
    case '/': jerarquia = 2;
        break;
    case '*': jerarquia = 2;
        break;
    case '-': jerarquia = 1;
        break;
    case '+': jerarquia = 1;
        break;
    case '(': jerarquia = 0;
        break;
    case ')': jerarquia = 0;
        break;
    default:
        break;
    }

    return jerarquia;
}

void  inicializaPila(Pila *p)
{
    // (*p).tope
    p->tope = -1;
}

int apila(Pila *p, char dato)
{
    int pudoApilar = 0;

    if(p->tope < TAM_PILA - 1) //SI HAY ESPACIO EN LA PILA
    {
        p->tope++; // p->tope += 1; p->tope +1;
        p->datos[p->tope] = dato;

        pudoApilar = 1;
    }

    return pudoApilar;
}

int desapilar(Pila *p, char *dato)
{
    int pudoDesapilar = 0;

    if(p->tope > -1) // Hay valores
    {
        *dato = p->datos[p->tope];
        p->tope--;
        pudoDesapilar = 1;
    }

    return pudoDesapilar;

}