#!/bin/bash

#Sciezka do plikow
LOGFILE="sample.log"
OUTPUT="./reports/report_$(date +%Y%m%d_%H%M%S).txt"

# Sprawdź, czy plik istnieje
if [ ! -f "$LOGFILE" ]; then
    echo "Błąd: plik $LOGFILE nie istnieje."
    exit 1
fi

echo "Analizuję plik: $LOGFILE"
echo "Raport zapisany do: $OUTPUT"
echo "============================" > "$OUTPUT"

# Policz wystąpienia kluczowych słów
echo "[Statystyki]" >> "$OUTPUT"
echo "ERROR: $(grep -c 'ERROR' $LOGFILE)" >> "$OUTPUT"
echo "WARNING: $(grep -c 'WARNING' $LOGFILE)" >> "$OUTPUT"
echo "INFO: $(grep -c 'INFO' $LOGFILE)" >> "$OUTPUT"

# Najczęściej powtarzające się wpisy (top 5)
echo "" >> "$OUTPUT"
echo "[Top 5 najczęściej powtarzających się wpisów]" >> "$OUTPUT"
grep -oE "ERROR|WARNING|INFO" $LOGFILE | sort | uniq -c | sort -nr | head -5 >> "$OUTPUT"

# Najnowsze wpisy (ostatnie 10 linii)
echo "" >> "$OUTPUT"
echo "[Ostatnie 10 wpisów]" >> "$OUTPUT"
tail -n 10 $LOGFILE >> "$OUTPUT"

echo "Analiza zakończona. Sprawdź plik $OUTPUT"
