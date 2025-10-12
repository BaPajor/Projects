import time
from datetime import datetime

# plik z tekstem do przepisania
TEXT_FILE = "random_words.txt"
# plik z wynikami
RESULTS_FILE = "results.txt"

def load_text(filename):
    try:
        with open(filename, "r") as f:
            text = f.read()
    except FileNotFoundError:
        print(f"Nie znaleziono pliku {filename}")
        exit(1)

    # podział tekstu na slowa
    words = text.replace("\n", " ").split()
    return words

def get_word_count(max_words):
    while True:
        try:
            n = int(input(f"Podaj liczbę słów (1-{max_words}): "))
            if 1 <= n <= max_words:
                return n
            else:
                print(f"Podaj liczbę od 1 do {max_words}\n")
        except ValueError:
            print("Liczba nie jest całkowita\n")

def display_text(words):
    # wyświetlamy po 20 słów w linii
    for i in range(0, len(words), 20):
        line = " ".join(words[i:i+20])
        print(line)

def typing_test():
    input("\nNaciśnij Enter aby rozpocząć...")

    # odliczanie do rozpoczecia testu
    for i in range(3, 0, -1):
        print(i, end=" ", flush=True)
        time.sleep(1)

    start_time = time.time()
    typed_text = input("\nStart!\n")
    end_time = time.time()

    # czas trwania testu
    time_taken = end_time - start_time

    return typed_text, time_taken

def score_calculator(text_words, typed_text, time_taken):
    original_text = " ".join(text_words)
    errors = 0

    # porównanie tekstu napisanego z oryginałem
    for i in range(min(len(original_text), len(typed_text))):
        if original_text[i] != typed_text[i]:
            errors += 1
    errors += abs(len(original_text) - len(typed_text))

    # obliczenie dokładności
    accuracy = max(0, (1 - errors / len(original_text)) * 100)

    # obliczenie słów na minutę
    word_count = len(typed_text.split())
    wpm = (word_count / time_taken) * 60
    
    print("\n=== WYNIKI ===")
    print(f"Czas: {time_taken:.2f} sekund")
    print(f"Słów na minutę (WPM): {wpm:.1f}")
    print(f"Dokładność: {accuracy:.1f}%")
    print(f"Błędów: {errors}")

    return accuracy, errors, wpm

def save_result(word_count, time_taken, accuracy, wpm):
    now = datetime.now()
    timestamp = now.strftime("%Y-%m-%d %H:%M:%S") 
    with open(RESULTS_FILE, "a") as f:
        f.write(f"{timestamp} - Słów: {word_count}, Czas: {time_taken:.2f}s, WPM: {wpm:.1f}, Dokładność: {accuracy:.1f}%\n")
    print(f"Wynik zapisany w pliku {RESULTS_FILE}\n")

def main():
    print("=== TEST SZYBKIEGO PISANIA ===")
    words = load_text(TEXT_FILE)

    while True:
        n = get_word_count(len(words))
        selected_words = words[:n]

        print("\n=== Tekst do przepisania ===")
        display_text(selected_words)

        typed, duration = typing_test()
        acc, err, wpm = score_calculator(selected_words, typed, duration)

        # opcja zapisania wyniku
        save_option = input("\nChcesz zapisać wynik do pliku? (t/n): ")
        if save_option == "t":
            save_result(n, duration, acc, wpm)

        # opcja powtórzenia testu lub wyjścia
        retry = input("Chcesz spróbować jeszcze raz? (t/n): ")
        if retry != "t":
            print("Do zobaczenia")
            break
        else:
            print("\nRozpoczynamy nowy test...\n")
            time.sleep(1)

if __name__ == "__main__":
    main()
