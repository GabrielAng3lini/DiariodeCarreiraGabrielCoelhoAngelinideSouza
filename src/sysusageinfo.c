#include <stdio.h>
#include <stdlib.h>                       
#include <string.h>
#include <sys/statvfs.h>   // Biblioteca POSIX para operações de estatísticas do sistema de arquivos no Linux

// Função para checar o uso de memória RAM lendo /proc/meminfo
void check_memory() { 
    FILE *file = fopen("/proc/meminfo", "r"); 
    if (file == NULL) { 
        perror("Erro ao abrir /proc/meminfo");
        return;
    }

    char buffer[128]; 
    unsigned long total_mem = 0, free_mem = 0, buffers = 0, cached = 0; // Iniciando variáveis

    while (fgets(buffer, sizeof(buffer), file) != NULL) { 
        // Tratamento limpo para evitar warnings de corpo vazio no compilador
        if (sscanf(buffer, "MemTotal: %lu kB", &total_mem) == 1) continue;
        if (sscanf(buffer, "MemFree: %lu kB", &free_mem) == 1) continue;
        if (sscanf(buffer, "Buffers: %lu kB", &buffers) == 1) continue;
        if (sscanf(buffer, "Cached: %lu kB", &cached) == 1) continue;
    }
    fclose(file); 

    unsigned long used_mem = total_mem - (free_mem + buffers + cached); // Determinando uso real de memória 
    double mem_percentage = (double)used_mem / total_mem * 100.0; // Porcentagem de uso da RAM 

    printf("[MEMÓRIA RAM]\n");
    printf("  Total: %lu MB\n", total_mem / 1024); 
    printf("  Uso  : %.2f%%\n", mem_percentage);
    if (mem_percentage > 85.0) { 
        printf("  [ALERTA] Uso de RAM acima de 85%%!\n");
    }
    printf("----------------------------------------\n");
}

// Função para checar o espaço em disco usando statvfs no diretório raiz (/)
void check_disk() {
    struct statvfs stats; // Separando espaço de status do sistema de arquivos

    if (statvfs("/", &stats) != 0) { // Checagem de leitura da pasta raiz do Linux
        perror("Erro ao ler estatísticas do disco");
        return;
    }

    unsigned long total_blocks = stats.f_blocks; 
    unsigned long free_blocks = stats.f_bfree;
    
    unsigned long total_gb = (total_blocks * stats.f_frsize) / (1024 * 1024 * 1024); 
    unsigned long free_gb = (free_blocks * stats.f_frsize) / (1024 * 1024 * 1024); 
    unsigned long used_gb = total_gb - free_gb; 
    
    double disk_percentage = ((double)(total_blocks - free_blocks) / total_blocks) * 100.0; // Definindo disco em porcentagem 

    printf("[DISCO PRINCIPAL (/)]\n");
    printf("  Total: %lu GB\n", total_gb);
    printf("  Usado: %lu GB (%.2f%%)\n", used_gb, disk_percentage);
    printf("  Livre: %lu GB\n", free_gb);
    printf("----------------------------------------\n");
}

int main() {
    printf("========================================\n");
    printf("     UBUNTU SYS - MEM DISK DIAGNOSTIC\n");
    printf("========================================\n\n");

    check_memory(); 
    check_disk(); // Chamando função para execução

    printf("Diagnóstico de sistema concluído.\n");
    return 0;
}
