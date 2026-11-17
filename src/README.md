Teste de conexão automático com checagem de ip
### O que ele faz?
Cria um log na pasta temp que informa hora, ip e status de conexão a cada uma em uma hora e em caso de falha exibe na tela para o usuário um alerta,esse também a cada uma em uma hora o informando diretamente que houve falha de conexão.    
Requisitos:

    Sistema Operacional Windows 10 ou 11.

    Windows PowerShell.

### Como Executar
1.Criar uma pasta no disco local com o nome temp;
2.Levar o arquivo monitor_ping.ps1 para dentro da pasta temp;
3.No Bloco de Notas criar um arquivo no formato .vbs contendo o codigo abaixo:
```vbscript
Set WshShell = CreateObject("WScript.Shell")
WshShell.Run "powershell.exe -ExecutionPolicy Bypass -File ""C:\temp\monitor_ping.ps1""", 0, False
```
4.Mover esse arquivo .vbs para área de trabalho
5.Duplo Clique no ícone na área de trabalho

# Ubuntu Utilitários de Sistema (`sysinfo` & `sysusageinfo`)

Conjunto de utilitários leves escritos em **C puro**, desenvolvidos para monitorar o sistema e auditar hardware diretamente pelo terminal do Ubuntu (sem a necessidade de interface gráfica).

---

## 1. `sysinfo` (Informações de Hardware)

### O que ele faz?
Captura dados estáticos de hardware e do sistema (como fabricante, modelo da CPU e especificações internas) diretamente das interfaces virtuais do kernel Linux (`/proc`), trazendo para o terminal informações que normalmente exigiriam navegar por menus gráficos de configuração.

## 2. `sysusageinfo` (Monitoramento em Tempo Real)
O que ele faz?

O programa interage diretamente com as interfaces do kernel Linux para capturar e exibir métricas vitais de hardware em tempo real:

Memória RAM: Calcula o uso real de memória subtraindo buffers e cache (/proc/meminfo).

Disco Principal: Analisa o espaço total, usado e livre do diretório raiz (/) utilizando chamadas de sistema POSIX (statvfs).

Isso substitui a necessidade de navegar por menus gráficos complexos para checar a saúde do sistema.

Requisitos:

    Sistema operacional Linux (Ubuntu ou distribuições baseadas em Debian).

    Compilador GCC (GNU Compiler Collection).

### Como Compilar e Executar
Certifique-se de ter o compilador GCC instalado e execute os comandos abaixo no terminal:

```bash
# Compilação do código-fonte
gcc src/sysinfo.c -o sysinfo -Wall -Wextra

# Execução do binário gerado
./sysinfo

# Compilação do código-fonte
gcc src/sysusageinfo.c -o sysusageinfo -Wall -Wextra

# Execução do binário gerado
./sysusageinfo
