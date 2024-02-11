#include <iostream>
#include <sstream>
#include <fstream>
#include "solve.cpp"
using namespace std;

void print_solution(vector<vector<string>>& arr, int buffer_size, vector<sequences>& seq, int matrix_width) {
    cout << endl << "--------------------------------- SOLUSI OPTIMAL --------------------------------" << endl;
    vector<string> temp, optimal;
    vector<pair<int, int>> optimal_coord, current_cord;
    vector<vector<bool>> taken;
    int time, max_reward;

    solve(arr, buffer_size, seq, temp, optimal, optimal_coord, current_cord, matrix_width, max_reward, time);

    if(optimal.size() != 0){
        cout << "Reward terbesar: " << max_reward << endl;
        cout << "Buffer: ";
        print_vector(optimal);
        print_coordinates(optimal_coord);
    }
    else{
        cout << "Tidak ada solusi yang memenuhi." << endl;
    }

    cout << "Waktu eksekusi: " << time << " ms" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    string s;
    cout << endl << "Apakah Anda ingin menyimpan solusi? (y/n): ";
    cin >> s;
    if(s == "y"){
        string outputFileName;
        cout << "Masukkan nama file untuk menyimpan solusi: ";
        cin >> outputFileName;

        string filePath = "../test/output/" + outputFileName;

        ofstream outputFile(filePath);
        if (!outputFile.is_open()) {
            cerr << "Tidak dapat membuat file." << endl;
            return;
        }
        outputFile << endl << "--------------------------------- SOLUSI OPTIMAL --------------------------------" << endl;
        if(optimal.size() != 0){
            outputFile << "Reward terbesar: " << max_reward << endl;
            outputFile << "Buffer: ";
            for (string s : optimal) {
                outputFile << s << " ";
            }
            outputFile << endl;
            outputFile << "Koordinat: " << endl;
            for (const auto& coord : optimal_coord) {
                outputFile << "(" << coord.second + 1 << ", " << coord.first + 1 << ") " << endl;
            }
            outputFile << endl;
        }
        else{
            outputFile << "Tidak ada solusi yang memenuhi." << endl;
        }

        outputFile << "Waktu eksekusi: " << time << " ms" << endl;
        outputFile << "---------------------------------------------------------------------------------" << endl;

        outputFile.close();
        cout << "Penyimpanan berhasil!" << endl;
    }
}

void input_file() {
    string filename;
    ifstream inputFile;

    do {
        cout << "Masukkan nama file yang ingin dibaca: ";
        cin >> filename;

        string filePath = "../test/input/" + filename;

        inputFile.open(filePath);

        if (!inputFile.is_open()) {
            cerr << "File tidak ditemukan." << endl;
        }
    } while (!inputFile.is_open());

    int buffer_size;
    int matrix_width, matrix_height;
    inputFile >> buffer_size;
    inputFile >> matrix_width >> matrix_height;

    vector<vector<string>> arr(matrix_height, vector<string>(matrix_width));

    for (int i = 0; i < matrix_height; i++) {
        for (int j = 0; j < matrix_width; j++) {
            inputFile >> arr[i][j];
        }
    }

    int num_of_seq;
    inputFile >> num_of_seq;
    inputFile.ignore();

    vector<sequences> seq;

    for (int i = 0; i < num_of_seq; i++) {
        string line;
        getline(inputFile, line);
        stringstream ss(line);
        string seq_token;
        sequences temp;
        while (ss >> seq_token) {
            temp.token.push_back(seq_token);
        }
        int seq_reward;
        inputFile >> seq_reward;
        temp.reward = seq_reward;
        seq.push_back(temp);
        inputFile.ignore();
    }

    print_solution(arr, buffer_size, seq, matrix_width);
}

void input_automatic(){
    int num_token, buffer_size, matrix_height, matrix_width, num_sequence, max_sequence_length;
    vector<string> tokens;
    vector<vector<string>> arr;
    vector<sequences> seq;
    mt19937 g(time(0));

    cout << "Matriks dan sekuens permainan akan dibuat otomatis oleh program." << endl;
    cout << "Jumlah token unik: ";
    cin >> num_token;
    cout << "Token: ";
    for(int i = 0; i < num_token; i++){
        string token;
        cin >> token;
        tokens.push_back(token);
    }
    cout << "Ukuran buffer: ";
    cin >> buffer_size;
    cout << "Ukuran matriks (kolom, baris): ";
    cin >> matrix_width >> matrix_height;
    cout << "Jumlah sekuens: ";
    cin >> num_sequence;
    cout << "Ukuran maksimal sekuens: ";
    cin >> max_sequence_length;

    seq = generate_random_sequences(num_sequence, max_sequence_length, tokens, g);
    arr = generate_random_matrix(matrix_width, matrix_height, num_token, tokens);
    print_matrix(arr);
    print_sequences(seq);
    
    print_solution(arr, buffer_size, seq, matrix_width);
    
}
