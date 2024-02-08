#include <iostream>
#include "input_file.cpp"
using namespace std;

int main(){
    cout << "Selamat datang!" << endl;
    cout << "Pilih menu:" << endl;
    cout << "1. Matriks dan sekuens permainan dibaca dari file .txt" << endl;
    cout << "2. Matriks dan sekuens permainan dihasilkan otomatis oleh program" << endl;

    cout << "Masukkan menu yang Anda pilih: ";
    int choice;
    cin >> choice;

    while(!(choice == 1 || choice == 2)){
        cout << "Pilihan tidak valid!" << endl;
        cout << "Masukkan menu yang Anda pilih: ";
        cin >> choice;
    }

    if(choice == 1){
        input_file();
    }
    else{
        cout << "pilihan 2" << endl;
    }
}