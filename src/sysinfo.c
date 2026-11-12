#include <stdio.h>
#include <stdlib.h>

#define PROC_CPU_FILE "/proc/cpuinfo"

int main() {
    
    FILE *file = fopen(PROC_CPU_FILE, "r"); //navega e abre o arquivo que contem os dados da cpu 
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo /proc/cpuinfo");
        return 1;
    }

    char buffer[256]; 
    printf("Lendo informacoes da CPU direto do Kernel do Ubuntu\n\n");

  
    int linhas = 0; //variavel contador 
    while (fgets(buffer, sizeof(buffer), file) != NULL && linhas < 15) { //laço que percorre e exibe informação de cada linha
        printf("%s", buffer);
        linhas++;
    }

  
    fclose(file);//fecha arquivo 
    
    printf("\nLeitura concluída\n");
    return 0;//encerra programa
}
