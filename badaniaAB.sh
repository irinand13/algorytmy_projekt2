#!/bin/bash

EXE="./cmake-build-debug-wsl/algorytmy_projekt2"
GLOWNY_FOLDER="Wyniki_Benchmarkow"

N_IT="50"
GESTOSC_STALA_A="50"
ROZMIAR_STALY_B="200"

ROZMIARY_A=(30 60 90 120 150)
GESTOSCI_B=(25 50 75 99)


PROBLEMY=(0 1 2)

if [ ! -d "$GLOWNY_FOLDER" ]; then
    mkdir -p "$GLOWNY_FOLDER"
fi

uruchom_benchmark() {
    local subfolder=$1
    local plik_wynikowy=$2
    local problem_num=$3
    local wierzcholki=$4
    local gestosc=$5

    local path="$GLOWNY_FOLDER/$subfolder"
    if [ ! -d "$path" ]; then
        mkdir -p "$path"
    fi
    local res_file="$path/$plik_wynikowy"

    # Definiujemy zmienną na początku funkcji - teraz będzie widoczna wszędzie poniżej!
    local wierzcholek_koncowy=$((wierzcholki - 1))

    echo -e "\e[36mRunner (n=$N_IT) -> ${subfolder} | Prob=$problem_num | V=$wierzcholki | D=$gestosc%\e[0m"

    if [ "$problem_num" == "0" ]; then
        $EXE --benchmark -p "$problem_num" -a "0" -s "0" -l "$wierzcholki" -d "$gestosc" -n "$N_IT" -r "$res_file"

    elif [ "$problem_num" == "1" ]; then
        $EXE --benchmark -p "$problem_num" -a "0" -s "0" -l "$wierzcholki" -d "$gestosc" -n "$N_IT" -r "$res_file" -c "0" -e "$wierzcholek_koncowy"

    elif [ "$problem_num" == "2" ]; then
        $EXE --benchmark -p "$problem_num" -a "0" -s "0" -l "$wierzcholki" -d "$gestosc" -n "$N_IT" -r "$res_file" -c "0" -e "$wierzcholek_koncowy"
    fi
}

echo -e "\n\e[33m=======================================================\e[0m"
echo -e "\e[33m--- URUCHAMIAM BADANIE A (Wplyw rozmiaru, Gestosc 50%) ---\e[0m"
echo -e "\e[33m=======================================================\e[0m"

for prob in "${PROBLEMY[@]}"; do
    for v in "${ROZMIARY_A[@]}"; do
        nazwa_pliku="wyniki_${prob}_V${v}.csv"
        uruchom_benchmark "badanie_A" "$nazwa_pliku" "$prob" "$v" "$GESTOSC_STALA_A"
    done
done

echo -e "\n\e[33m=======================================================\e[0m"
echo -e "\e[33m--- URUCHAMIAM BADANIE B (Wplyw gestosci, V = $ROZMIAR_STALY_B) ---\e[0m"
echo -e "\e[33m=======================================================\e[0m"

for prob in "${PROBLEMY[@]}"; do
    for d in "${GESTOSCI_B[@]}"; do
        nazwa_pliku="wyniki_${prob}_D${d}.csv"
        uruchom_benchmark "badanie_B" "$nazwa_pliku" "$prob" "$ROZMIAR_STALY_B" "$d"
    done
done

echo -e "\n\e[32m--- WSZYSTKIE POMIARY ZAKONCZONE POMYSLNIE ---\e[0m"