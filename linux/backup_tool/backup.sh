#!/bin/bash


# Konfiguracja
SOURCE_DIR="./reports"
BACKUP_DIR="./backups"
MAX_BACKUPS=3

# Sprawdzenie, czy podano katalog
if [ -z "$SOURCE_DIR" ]; then
    echo "Użycie: $0 $SOURCE_DIR"
    exit 1
fi

# Sprawdzenie, czy katalog źródłowy istnieje
if [ ! -d "$SOURCE_DIR" ]; then
    echo "Błąd: katalog $SOURCE_DIR nie istnieje."
    exit 1
fi

# Tworzenie katalogu backup jeśli nie istnieje
mkdir -p "$BACKUP_DIR"

# Tworzenie archiwum
DATE=$(date +%Y%m%d)
ARCHIVE_NAME="backup-$DATE.tar.gz"

# Kopiowanie katalogu i tworzenie archiwum
tar -czf "$BACKUP_DIR/$ARCHIVE_NAME" -C "$(dirname "$SOURCE_DIR")" "$(basename "$SOURCE_DIR")"

echo "Backup utworzony: $BACKUP_DIR/$ARCHIVE_NAME"

# Usuwanie starych kopii
cd "$BACKUP_DIR" || exit
BACKUPS_TO_DELETE=$(ls -1t backup-*.tar.gz | tail -n +$((MAX_BACKUPS + 1)))

if [ ! -z "$BACKUPS_TO_DELETE" ]; then
    echo "Usuwanie starych backupów:"
    echo "$BACKUPS_TO_DELETE"
    rm -f $BACKUPS_TO_DELETE
fi
