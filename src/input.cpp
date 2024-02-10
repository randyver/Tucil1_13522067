#include <iostream>
#include <sstream>
#include <fstream>
#include "solve.cpp"
using namespace std;

void output(){
    
}

void input_file() {
    string filename;
    cout << "Masukkan nama file: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "File not found." << endl;
        return;
    }

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

    cout << "--------------------------------- SOLUSI OPTIMAL --------------------------------" << endl;
    vector<string> temp, optimal;
    vector<pair<int, int>> optimal_coord, current_cord;
    vector<vector<bool>> taken;
    solve(arr, buffer_size, seq, temp, optimal, optimal_coord, current_cord, matrix_width);
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
    cout << "Ukuran matriks (baris, kolom): ";
    cin >> matrix_height >> matrix_width;
    cout << "Jumlah sekuens: ";
    cin >> num_sequence;
    cout << "Ukuran maksimal sekuens: ";
    cin >> max_sequence_length;

    seq = generate_random_sequences(num_sequence, max_sequence_length, tokens, g);
    arr = generate_random_matrix(matrix_width, matrix_height, num_token, tokens);
    print_matrix(arr);
    print_sequences(seq);
    
    cout << "--------------------------------- SOLUSI OPTIMAL --------------------------------" << endl;
    vector<string> temp, optimal;
    vector<pair<int, int>> optimal_coord, current_cord;
    vector<vector<bool>> taken;
    solve(arr, buffer_size, seq, temp, optimal, optimal_coord, current_cord, matrix_width);
    
}
