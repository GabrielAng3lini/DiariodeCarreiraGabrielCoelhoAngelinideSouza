$target = "8.8.8.8"
$logPath = "C:\temp\ping_alert_log.txt"

# Garante que a pasta C:\temp existe
if (!(Test-Path "C:\temp")) {
    New-Item -ItemType Directory -Force -Path "C:\temp" | Out-Null
}

while ($true) {
    $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    $test = Test-Connection -ComputerName $target -Count 3 -Quiet

    if ($test) {
        "$timestamp - OK: Conexao ativa com $target" | Out-File -Append -FilePath $logPath
    } else {
        "$timestamp - FALHA: Sem resposta de $target" | Out-File -Append -FilePath $logPath

        # Exibe um alerta grafico na tela
        Add-Type -AssemblyName PresentationFramework
        [System.Windows.MessageBox]::Show("Atencao! O teste de ping para $target falhou as $timestamp.", "Alerta de Conexao - Ping", "OK", "Error")
    }

    # Aguarda 1 hora (3600 segundos) antes do proximo teste
    Start-Sleep -Seconds 3600
}