//
// Created by iraan on 02.05.2026.
//

#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
using namespace std;


// Dynamiczna tablica, która jest inicjalizowana jako szablon
template<class T>
class Array {
private:
    int array_size;   //rozmiar tablicy
    T *data;  //wskażnik na dynamiczną tablicę danych

public:

    //konstrukor tablicy
    explicit Array(int size) {
        if (size > 0) {
            data = new T[size]{};
            array_size = size;
        } else {
            array_size = 0;
            throw std::invalid_argument("Array size must be greater than 0");
        }
    }


    //Konstruktor kopiujący
    //Tworzy kopię obiektu
    Array(const Array& other) {
        array_size = other.array_size;
        data = new T[array_size]; //alokacja pamięci

        for (int i = 0; i < array_size; i++) {
            data[i] = other.data[i];
        }
    }


    //operator przypisania
    Array& operator=(const Array& other) {
        if (this == &other) return *this;

        //zwolnienie pamięci, aby nie było wycieków pamięci
        delete[] data;


        array_size = other.array_size; //alokacja pamięci
        data = new T[array_size]; //kopiowanie danych


        for (int i = 0; i < array_size; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    //destruktor tabeli
    ~Array() {delete[] data;}

    //operator dostępu do elementów tabeli
    T& operator[](int index) {return data[index];}

   // Metoda dodawania wartości do tabeli
    void set(int index, const T& value) {
        if (index >= array_size || index < 0) {
            throw std::invalid_argument("Index out of range");
        }else{
            data[index] = value;
        }
    }

    // Metoda odczytywania tabeli
    void read() {
        cout<<"Array reading..."<<std::endl;
        for (int i = 0; i < array_size; i++) {
            std::cout<<data[i]<<std::endl;
        }
    }

    //Metoda zwracająca rozmiar tabeli
    int getSize() {return array_size;}

    void clear() {
        for (int i = 0; i < array_size; i++) {
            data[i] = T();
        }
    }
};

#endif //ARRAY_H
