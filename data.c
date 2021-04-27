
/**
 * @file data.c
 */
#include "data.h"

/**
 * \brief Macro que assiste na inicialização das funções DataVal.
 * Devolve um apontador para o valor convertido do void* respetivo ao data recebido.
 */
#define DataVal(_name, _type)              \
    _type *DataVal##_name(Data *data) {    \
        return (_type*) data->value;       \
    }

/** \brief Inicialização da função DataValCHAR. */
DataVal(CHAR, char)
/** \brief Inicialização da função algorítmica DataValLONG. */
DataVal(LONG, long)
/** \brief Inicialização da função algorítmica DataValDOUBLE. */
DataVal(DOUBLE, double)
/** \brief Inicialização da função algorítmica DataValSTRING. */
DataVal(STRING, char) //não faz nada diferente do DataValCHAR (lê o primeiro do array)

/**
 * \brief Macro que assiste na inicialização das funções CreateData.
 * Devolve um Data com o argumento val guardado na memória de endereço void*,
 * e com o tipo respetivo à função.
 * @param _name Tipo da função algorítmica.
 * @param _type tipo da val.
 */
#define CreateData(_name, _type)                       \
    Data CreateData##_name(_type val) {                \
        _type *vp = (_type*) malloc(sizeof(_type));    \
        *vp = val;                                     \
        Data op = {_name, vp};                         \
        return op;                                     \
    }
/** \brief Inicialização da função algorítmica CreateDataCHAR. */
CreateData(CHAR, char)
/** \brief Inicialização da função algorítmica CreateDataLONG. */
CreateData(LONG, long)
/** \brief Inicialização da função algorítmica CreateDataDOUBLE. */
CreateData(DOUBLE, double)

/**
 * \brief Função que cria um Data com o Tipo STRING.
 * @param val Endereço da string a se guardar.
 * @return devolve um Data do Tipo STRING.
 */
Data CreateDataSTRING(char *val) {
    char *vp = strdup(val);
    Data op = {STRING, vp};
    return op;
}

/**
 * \brief Função que converte um Data com qualquer Tipo num Data com Tipo DOUBLE.
 * @param d Endereço de um Data.
 */
void DataToDOUBLE(Data *d) {
    double val;
    switch (d->tipo){
        case CHAR:
        case LONG:{
            val = (double) *(DataValLONG(d));
            break;
        }
        case STRING:{
            val = strtod(DataValCHAR(d), NULL);
            break;
        }
        default:
            return;
    }
    double *vp = (double *) realloc(d->value, sizeof(double));
    *vp = val;
    d->value = vp;
    d->tipo = DOUBLE;
}

/**
 * \brief Função que converte um Data com qualquer Tipo num Data com Tipo LONG.
 * @param d Endereço de um Data
 */
void DataToLONG(Data *d) {
    long val;
    switch (d->tipo){
        case STRING:{
            val = strtol(DataValCHAR(d), NULL, 10);
            break;
        }
        case DOUBLE: {
            val = (long) *(DataValDOUBLE(d));
            break;
        }
        default:
            d->tipo = LONG;
            return;
    }
    long *vp = (long *) realloc(d->value, sizeof(long));
    *vp = val;
    d->value = vp;
    d->tipo = LONG;
}

/**
 * \brief Função que converte um Data com qualquer Tipo num Data com Tipo CHAR.
 * @param d Endereço de um data
 */
void DataToCHAR(Data *d) {
    switch (d->tipo) {
        case STRING: {
            char val = *DataValCHAR(d);
            char *vp = (char *) realloc(d->value, sizeof(char));
            *vp = val;
            d->value = vp;
            break;
        }
        case CHAR:
            break;
        default: {
            DataToLONG(d);
            break;
        }
    }
    d->tipo = CHAR;
}

/**
 * \brief Função que duplica um Data.
 *
 * @param target Endereço de um Data.
 * @return Devolve o duplo do Data.
 */
Data DataDup(Data *target) {
    Data data;
    switch (target->tipo) {
        case LONG: {
            data = CreateDataLONG(*DataValLONG(target));
            break;
        }
        case DOUBLE: {
            data = CreateDataDOUBLE(*DataValDOUBLE(target));
            break;
        }
        case CHAR: {
            data = CreateDataCHAR(*DataValCHAR(target));
            break;
        }
        case STRING: {
            data = CreateDataSTRING(DataValSTRING(target));
            break;
        }
    }
    return data;
}

/**
 * \brief Função que imprime um certo elemento de acordo com o seu Tipo.
 * @param data Elemento a imprimir.
 */
void PrintData(Data *data) {
    switch (data->tipo) {
        case LONG:
            printf("%ld", *(long*)(data->value));
            break;
        case DOUBLE:
            printf("%g", *(double*)(data->value));
            break;
        case CHAR:
            printf("%c", *((char*)(data->value)));
            break;
        case STRING:
            printf("%s", (char*)data->value);
            break;
    }
}

/** \brief Função que Troca dois apontadores de Datas.
 *  @param d1 Endereço de um Data.
 *  @param d2 Endereço de um Data.
*/  
void SwapDataPointers (Data *d1, Data *d2){
    Data temp = *d1;
    *d1 = *d2;
    *d2 = temp; 
}
