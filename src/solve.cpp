#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
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

bool contains_sequence(const vector<string>& v, const sequences& s) {
    for (size_t i = 0; i <= v.size() - s.token.size(); ++i) {
        auto it = search(v.begin() + i, v.end(), s.token.begin(), s.token.end());
        if (it != v.end()) {
            return true;
        }
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
void generate_combinations(vector<vector<string>>& arr, int& buffer_size, vector<sequences>& seq, vector<string>& temp, vector<string>& optimal, int row, int col, int dir, int& max_reward) {

    static vector<vector<bool>> taken(arr.size(), vector<bool>(arr[0].size(), false));

    if (temp.size() < buffer_size){
        if (taken[row][col]) {
            return;
        }
        temp.push_back(arr[row][col]);
        taken[row][col] = true;

        // Ubah arah gerak sesuai dengan aturan permainan
        dir = 1 - dir;
        // Jika horizontal, coba semua kemungkinan kolom di baris yang sama
        if (dir == 0) {
            for (int j = 0; j < arr[0].size(); j++) {
                if (j != col) {
                    generate_combinations(arr, buffer_size, seq, temp, optimal, row, j, dir, max_reward);
                }
            }
        }
        // Jika vertikal, coba semua kemungkinan baris di kolom yang sama
        if (dir == 1) {
            for (int i = 0; i < arr.size(); i++) {
                if (i != row) {
                    generate_combinations(arr, buffer_size, seq, temp, optimal, i, col, dir, max_reward);
                }
            }
        }

        temp.pop_back();
        taken[row][col] = false;
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
            }
        }
        return;
    }

}

void solve(vector<vector<string>>& arr, int& buffer_size, vector<sequences>& seq, vector<string>& temp, vector<string>& optimal, int matrix_width){
    int max_reward = 0;

    auto start_time = chrono::high_resolution_clock::now();

    // mulai dari baris pertama
    for (int j = 0; j < matrix_width; j++) {
        generate_combinations(arr, buffer_size, seq, temp, optimal, 0, j, 0, max_reward);
    }
    
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    cout << "Best combination: ";
    print_vector(optimal);
    cout << "Reward: " << max_reward << endl;

    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

}