#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "solve.cpp"
using namespace std;

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

    vector<string> temp, optimal;
    solve(arr, buffer_size, seq, temp, optimal, matrix_width);
}
