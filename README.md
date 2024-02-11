# Cyberpunk 2077 Breach Protocol Solver (Tugas Kecil 1 Strategi Algoritma 2023/2024)

## Deskripsi
Breach Protocol adalah minigame meretas dalam permainan video Cyberpunk 2077. Ini melibatkan pemilihan token alfanumerik dari matriks untuk mencocokkan sekuens tertentu dalam buffer. Pemain bergerak dalam pola bergantian antara horizontal dan vertikal di matriks, memulai dari baris paling atas. Token dalam buffer dapat digunakan untuk lebih dari satu sekuens, dan setiap sekuens memiliki bobot hadiah yang berbeda. Permainan berlanjut sampai semua sekuens dicocokkan atau buffer penuh. Repository ini adalah penyelesaian breach protocol dengan algoritma brute force.

## Requirements
C++ language

## How to compile
1. Clone repository ini
```
git clone https://github.com/randyver/Tucil1_13522067.git
```
2. Buka terminal di direktori yang berisi kode program kemudian ke folder src
3. Compile program dengan perintah
```
g++ -o ..\bin\main main.cpp
```

## How to run
1. Masuk ke folder bin yang berisi executable file lalu jalankan perintah
```
.\main.exe
```

## Fitur
Menyelesaikan Breach Protocol dengan dua cara masukan, yaitu membaca matriks dan sekuens permainan pada file .txt yang berada di folder test/input atau membuat matriks dan sekuens permainan secara otomatis oleh program. Hasil program dapat disimpan pada file .txt yang berada di folder test/output.

## Identitas
Randy Verdian (13522067)