#include <iostream>
#include "IO.cpp"
using namespace std;

int main() {
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "                      Cyberpunk 2077 Breach Protocol Solver                    " << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    int choice;
    string continueChoice;

    do {
        cout << endl << "Pilih menu:" << endl;
        cout << "1. Matriks dan sekuens permainan dibaca dari file .txt" << endl;
        cout << "2. Matriks dan sekuens permainan dihasilkan otomatis oleh program" << endl;
        cout << "Masukkan menu yang Anda pilih: ";
        cin >> choice;

        while (!(choice == 1 || choice == 2)) {
            cout << "Pilihan tidak valid!" << endl;
            cout << "Masukkan menu yang Anda pilih: ";
            cin >> choice;
        }

        if (choice == 1) {
            input_file();
        } else {
            input_automatic();
        }

        cout << "Apakah Anda ingin melanjutkan permainan? (y/n): ";
        cin >> continueChoice;

    } while (continueChoice == "y");

    return 0;
}
