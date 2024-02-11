#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>
using namespace std;

struct sequences {
    vector<string> token;
    int reward;
};

// Fungsi untuk mencetak vektor string
void print_vector(vector<string> v) {
    for (string s : v) {
        cout << s << " ";
    }
    cout << endl;
}

void print_coordinates(vector<pair<int, int>>& coordinates) {
    cout << "Koordinat: " << endl;
    for (const auto& coord : coordinates) {
        cout << "(" << coord.second + 1 << ", " << coord.first + 1 << ") " << endl;
    }
    cout << endl;
}

bool contains_sequence(const vector<string>& v, const sequences& s) {
    if(v.size() >= s.token.size()){
        for (size_t i = 0; i <= v.size() - s.token.size(); ++i) {
            auto it = search(v.begin() + i, v.end(), s.token.begin(), s.token.end());
            if (it != v.end()) {
                return true;
            }
        }
        return false;
    }
    return false;
}
  

// Fungsi untuk menghitung total bobot hadiah dari sebuah vektor string berdasarkan sekuens-sekuens yang ada
int calculate_reward(vector<string>& v, vector<sequences>& seq) {
    int total = 0;
    for (sequences s : seq) {
        if (contains_sequence(v, s)) {
            total += s.reward;
        }
    }
    return total;
}

// Fungsi untuk menghasilkan semua kemungkinan kombinasi token yang memenuhi aturan permainan   
void generate_combinations(vector<vector<string>>& arr, int& buffer_size, vector<sequences>& seq, vector<string>& temp, vector<string>& optimal, vector<pair<int, int>>& optimal_coord, vector<pair<int, int>>& current_coord, vector<vector<bool>>& taken,int row, int col, int dir, int& max_reward) {

    temp.push_back(arr[row][col]);
    taken[row][col] = true;
    current_coord.push_back(make_pair(row, col));

    if (temp.size() < buffer_size){

        dir = 1 - dir;
        // Jika horizontal, coba semua kemungkinan kolom di baris yang sama
        if (dir == 0) {
            for (int j = 0; j < arr[0].size(); j++) {
                if (j != col && !taken[row][j]) {
                    generate_combinations(arr, buffer_size, seq, temp, optimal, optimal_coord, current_coord, taken, row, j, dir, max_reward);
                }
            }
        }
        // Jika vertikal, coba semua kemungkinan baris di kolom yang sama
        if (dir == 1) {
            for (int i = 0; i < arr.size(); i++) {
                if (i != row && !taken[i][col]) {
                    generate_combinations(arr, buffer_size, seq, temp, optimal, optimal_coord, current_coord, taken, i, col, dir, max_reward);
                }
            }
        }

    }

    // Jika size temp udah maksimal
    else if (temp.size() == buffer_size) {
        bool valid = false;
        for(int j = 0; j < seq.size(); j++){
            if(contains_sequence(temp, seq[j])){
                valid = true;
                break;
            }
        }
        if(valid){
            if(calculate_reward(temp, seq) > max_reward){
                max_reward = calculate_reward(temp, seq);
                optimal = temp;
                optimal_coord = current_coord;
            }
        }

    }

    taken[row][col] = false;
    temp.pop_back();
    current_coord.pop_back();

}


void solve(vector<vector<string>>& arr, int& buffer_size, vector<sequences>& seq, vector<string>& temp, vector<string>& optimal, vector<pair<int, int>>& optimal_coord, vector<pair<int, int>>& current_coord, int matrix_width, int& max_reward, int& time){
    max_reward = 0;
    vector<vector<bool>> taken(arr.size(), vector<bool>(arr[0].size(), false));

    auto start_time = chrono::high_resolution_clock::now();

    // mulai dari baris pertama
    for (int j = 0; j < matrix_width; j++) {
        generate_combinations(arr, buffer_size, seq, temp, optimal, optimal_coord, current_coord, taken, 0, j, 0, max_reward);
    }
    
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    time = duration.count();


}

// Fungsi untuk menghasilkan matriks secara acak
vector<vector<string>> generate_random_matrix(int matrix_width, int matrix_height, int num_token, vector<string> tokens) {

    srand(time(0));
    random_shuffle(tokens.begin(), tokens.end());

    vector<vector<string>> matrix(matrix_height, vector<string>(matrix_width));
    int token_index = 0;
    for (int i = 0; i < matrix_height; ++i) {
        for (int j = 0; j < matrix_width; ++j) {
            matrix[i][j] = tokens[token_index];
            ++token_index;
            if (token_index == num_token) {
                token_index = 0;
                random_shuffle(tokens.begin(), tokens.end());
            }
        }
    }

    return matrix;
}


vector<sequences> generate_random_sequences(int num_sequence, int max_sequence_length, vector<string> tokens, mt19937& g) {
    vector<sequences> random_sequences;

    // Buat distribusi untuk panjang sekuens dan hadiah
    uniform_int_distribution<int> num_tokens_distribution(2, max_sequence_length);
    uniform_int_distribution<int> reward_distribution(10, 50);
    uniform_int_distribution<int> token_distribution(0, tokens.size() - 1);

    for (int i = 0; i < num_sequence; ++i) {
        sequences seq;
        int seq_length = num_tokens_distribution(g);

        // Ambil token secara acak dari vektor tokens
        for (int j = 0; j < seq_length; ++j) {
            int token_index = token_distribution(g);
            seq.token.push_back(tokens[token_index]);
        }

        seq.reward = reward_distribution(g);
        random_sequences.emplace_back(seq);
    }

    return random_sequences;
}


// Fungsi untuk mencetak matriks
void print_matrix(const vector<vector<string>>& matrix) {
    cout << "Matriks:" << endl;
    for (const auto& row : matrix) {
        for (const string& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Fungsi untuk mencetak sequence
void print_sequences(const vector<sequences>& seq) {
    cout << "Sequence dan reward: " << endl;
    for (const sequences& s : seq) {
        print_vector(s.token);
        cout << s.reward << endl;
    }
}