#include <stdio.h>                                                              //bibliotecas necessarias
#include <stdlib.h>

typedef struct Lua {                                                            //criação do struct lua para ser usado dentro de planeta
    int raio_lua;
    char nome[100];
} Lua;

typedef struct Planeta {                                                        //criação do struct planeta para ser usado dentro de sistema_solar
    int quantidade_de_lua, raio_planeta;
    char nome[100];
    Lua *lua;                                                                   //sub struct que relaciona as informações de luas com as demais
} Planeta;

typedef struct Sistema_Solar {                                                  //struct principal que descreve um sistema inteiro com todas as informações
    int tempo, raio_Sol, quantidade_de_planeta;
    char nome[100];
    Planeta *planeta;                                                           //sub struct que relaciona as informações de planetas com as demais 
} Sistema_Solar;

void liberar_memoria(Sistema_Solar *sistemas, int n) {                          // roda duas iterações que passam por toda a alocação dinamica de planetas luas e por fim sistemmas e limpa tudo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < sistemas[i].quantidade_de_planeta; j++) {
            free(sistemas[i].planeta[j].lua);
        }
        free(sistemas[i].planeta);
    }
    free(sistemas);
}
    int n;                                                                      //variavel da quantidade de sistemas desejados

void LeLua(Lua *luas, int n) {                                                                                                  //roda uma iteração para ler todas as n luas presentes em um planeta x
    for (int i = 0; i < n; i++) {
        scanf("%s %d", luas[i].nome, &luas[i].raio_lua);
    }
}

void LePlaneta(Planeta *planetas, int n) {                                                                                      //roda uma iteração que lê tudo sobre um planeta para cada planeta de um sistema de n planetas
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", planetas[i].nome, &planetas[i].raio_planeta, &planetas[i].quantidade_de_lua);
        planetas[i].lua = malloc(planetas[i].quantidade_de_lua * sizeof(Lua));
        LeLua(planetas[i].lua, planetas[i].quantidade_de_lua);                                                                  //passa a quantidade n de luas para a função que lê as luas
    }
}

void cadastro_sistemas(Sistema_Solar *sistemas, int n) {                                                                        //roda uma iteração que lê as informações de n sistemas solares 
    for (int i = 0; i < n; i++) {
        scanf("%d %s %d %d", &sistemas[i].tempo, sistemas[i].nome, &sistemas[i].raio_Sol, &sistemas[i].quantidade_de_planeta);
        sistemas[i].planeta = malloc(sistemas[i].quantidade_de_planeta * sizeof(Planeta));
        LePlaneta(sistemas[i].planeta, sistemas[i].quantidade_de_planeta);                                                      //passa a quantidade n de planetas para a função que lê os planetas
    }
}

int Comparador_Legal(Sistema_Solar sistemaA, Sistema_Solar sistemaB) {                          //função que compara a menor parte do array da ritação, no caso o lado esquerdo do array é nomeado de A e o esquerdo é nomeado de B
    int maior_planetaA = 0, maior_planetaB = 0, maior_luaA = 0, maior_luaB = 0;

    for (int i = 0; i < sistemaA.quantidade_de_planeta; i++) {                                  //iteração para encontrar o maior planeta do sistema A
        if (sistemaA.planeta[i].raio_planeta > maior_planetaA)
            maior_planetaA = sistemaA.planeta[i].raio_planeta;

        for (int j = 0; j < sistemaA.planeta[i].quantidade_de_lua; j++) {                       //iteração para encontra o maior planeta de B
            if (sistemaA.planeta[i].lua[j].raio_lua > maior_luaA)
                maior_luaA = sistemaA.planeta[i].lua[j].raio_lua;
        }
    }

    for (int i = 0; i < sistemaB.quantidade_de_planeta; i++) {                                  //iteração para encontrar a maior lua do sistema A
        if (sistemaB.planeta[i].raio_planeta > maior_planetaB)
            maior_planetaB = sistemaB.planeta[i].raio_planeta;

        for (int j = 0; j < sistemaB.planeta[i].quantidade_de_lua; j++) {                       //iteração para encontrar a maior lua do sistema 
            if (sistemaB.planeta[i].lua[j].raio_lua > maior_luaB)
                maior_luaB = sistemaB.planeta[i].lua[j].raio_lua;
        }
    }
    //nas linhas seguintes será feitos os testes condicionais descritos para definir se o sistema a esquerda é o mais interessante, se for o caso retorna 1 caso contrário retorna 0
    if (sistemaA.raio_Sol > sistemaB.raio_Sol)
        return 1;
    else if ((sistemaA.quantidade_de_planeta > sistemaB.quantidade_de_planeta) && (sistemaA.raio_Sol == sistemaB.raio_Sol))
        return 1;
    else if ((maior_planetaA > maior_planetaB) && (sistemaA.quantidade_de_planeta == sistemaB.quantidade_de_planeta))
        return 1;
    else if ((maior_luaA > maior_luaB) && (sistemaA.planeta->quantidade_de_lua == sistemaB.planeta->quantidade_de_lua) && (maior_planetaA == maior_planetaB))
        return 1;
    else if ((sistemaA.planeta->quantidade_de_lua > sistemaB.planeta->quantidade_de_lua) && (maior_planetaA == maior_planetaB))
        return 1;
    else if ((sistemaA.planeta->quantidade_de_lua == sistemaB.planeta->quantidade_de_lua) && (maior_luaA > maior_luaB) && (maior_planetaA == maior_planetaB))
        return 1;
    else if ((sistemaA.tempo > sistemaB.tempo) && (maior_luaA == maior_luaB) && (maior_planetaA == maior_planetaB))
        return 1;
    else
        return 0;
}



void ListaOrdenada(Sistema_Solar lista[], int n){                               //printa o resultado final da lista após a organização
    for(int i=0; i<n; i++){
        printf("%s\n" , lista[i].nome);
    }
}

void ritacao(Sistema_Solar lista[], Sistema_Solar Es[], int nEs, Sistema_Solar Di[], int nDi) { //inicia o processo de ritação (comparação e junção de termos do menor array) contendo em ordem o array principal inicialmente desorganizado, sua copia com apenas os termos mais a esquerda(Es), a quantidade de termos a esquerda(nEs), copia com apenas termos a direita(Di) e quantidade de termos a direita(nDi)
    int i = 0, j = 0, k = 0;                                                                    //cria 3 variaveis que seram usadas para se locomover nos arrays e subarrays: i corresponde ao array da esquerda, j ao da direita e k o principal

    while (i < nEs && j < nDi) {                                                                //iteração enquanto i for menor que o total do seu respectivo subarray e j também
        if (Comparador_Legal(Es[i],Di[j]) == 1){                                                //função que testa se o termo a esquerda do array é mais interessante que o da direta
            lista[k] = Es[i];                                                                   //caso sim substitui o array principal com o termo esquerdo
            i++;
        } else {
            lista[k] = Di[j];                                                                   //caso não substitui o array principal com o termo direito
            j++;
        }
        k++;
    }
    //as duas iterações seguintes garantem que todos os termos sejam usados para o array direito e o array esquerdo respectivamente
    while (i < nEs) {
        lista[k] = Es[i];
        i++;
        k++;
    }

    while (j < nDi) {
        lista[k] = Di[j];
        j++;
        k++;
    }
    ListaOrdenada(lista, n);
}

void BrometoSort(Sistema_Solar lista[], int n) {                                //recebe uma copia dos sistemas a serem comparados
    if (n < 2)                                                                  //regra de finalização para recursão, onde se um array tem apenas 1 termo não precisa ser ordenado
        return;

    int mid = n / 2;                                                            //corta o array pela metade e separa em lado esquerdo do array e lado direito do array
    Sistema_Solar Es[mid];
    Sistema_Solar Di[n-mid];

    for (int i=0; i<mid;i++) {                                                  //iteração da esquerda para formar o sub array
        Es[i] = lista[i];
    }

    for (int i=mid; i<n; i++) {                                                 //iteração da direita para formar o sub array
        Di[i-mid] = lista[i];
    }

    BrometoSort(Es, mid);                                                       //recursao para o lado esquerdo
    BrometoSort(Di, n-mid);                                                     //recursao para o lado direto
    ritacao(lista, Es, mid, Di, n-mid);                                         //quando todos os termos forem separados corretamente envia-os para a ritação
}

int main(){
    scanf("%d",&n);
    Sistema_Solar *sistemas = malloc(n*sizeof(Sistema_Solar));                  //alocação dinamica para os n termos desejados
    cadastro_sistemas(sistemas, n);                                             //função para leitura dinamica dos sistemas 
    BrometoSort(sistemas, n);                                                   //organização da lista lida
    liberar_memoria(sistemas, n);                                               //limpa a memoria dinamica usada no programa
    return 0;                                                                   //encerra retornando 0
}