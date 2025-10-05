from typing import Dict, List 

def BFS(G: Dict[int, List[int]], s: int):
    No = {}  # Słownik przechowujący numery odwiedzonych wierzchołków
    No[s] = 1  # Inicjalizacja — wierzchołek startowy otrzymuje numer 1
    licz = 1
    spojnosc = False
    cyklicznosc = False
    poprzedni = {}

    fifo = [s]  # Kolejka FIFO dla wierzchołków do odwiedzenia
    while fifo:
        v = fifo.pop(0)  # Pobranie pierwszego wierzchołka z kolejki
        print("nr", licz, "->", v, end=", ")
        for i in G[v]:
            if i not in No:  # Jeśli wierzchołek sąsiedni nie został odwiedzony
                fifo.append(i)           # Dodaj go do kolejki
                No[i] = No[v] + 1        # Nadaj mu numer kolejny względem poprzednika
                poprzedni[i] = v         # Zapisz poprzednika
            elif i != poprzedni[v]:      # Wykrycie cyklu — sąsiad odwiedzony, ale nie jest poprzednikiem
                cyklicznosc = True
        licz += 1

    # Sprawdzenie, czy graf jest spójny
    if len(No) == len(G):
        spojnosc = True
    print("\nSpójność grafu:", spojnosc)
    print("Cykliczność grafu:", cyklicznosc)
    print()

G1: Dict[int, List[int]] = {
    1: [4, 8, 3, 7, 6],
    2: [10, 8],
    3: [9, 8, 1],
    4: [1, 10, 9, 8, 5, 7],
    5: [10, 9, 7, 4],
    6: [8, 1],
    7: [5, 8, 4, 1],
    8: [1, 10, 3, 4, 6, 7, 2],
    9: [3, 5, 4],
    10: [2, 5, 4, 8]
}

G2: Dict[int, List[int]] = {
    1: [3, 2, 4, 5, 10],
    2: [8, 4, 5, 1, 3, 10],
    3: [1, 5, 2, 4, 9],
    4: [2, 1, 10, 3, 5, 9],
    5: [6, 2, 3, 8, 1, 4],
    6: [8, 9, 5, 10],
    7: [],
    8: [2, 9, 6, 5],
    9: [8, 6, 10, 3, 4],
    10: [9, 4, 2, 6, 1]
}

G3: Dict[int, List[int]] = {
    1: [2,4,6],
    2: [3, 1],
    3: [2],
    4: [1,5],
    5: [4],
    6: [8],
    8: [6,10],
    10: [8,9],
    9: [10,7],
    7: [9]
}

print("Graf spójny z cyklami:")
BFS(G1, 1)

print("Graf niespójny z cyklami:")
BFS(G2, 1)

print("Graf spójny acykliczny:")
BFS(G3, 1)