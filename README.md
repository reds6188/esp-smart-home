# esp-smart-home
Smart Home with ESP32

## Aggiornare la Web UI
La Web UI è contenuta nella cartella `data`.
Ad ogni modifica, aprire il terminale ed eseguire il seguente comando:

```bash
python scripts/text2hex.py
```

Ogni file contenuto nella cartella `data` viene convertito in una variabile array di esadecimali con nome `NOME_ESTENSIONE`