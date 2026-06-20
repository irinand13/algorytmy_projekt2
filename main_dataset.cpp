//
// Created by iraan on 20.06.2026.
//
#include <iostream>
#include "DatasetBenchmark.h"
using namespace std;

int main() {
    DatasetBenchmark::runMst("openflights_connected.txt", "wynik_dataset_mst.csv", 1);

    return 0;
}