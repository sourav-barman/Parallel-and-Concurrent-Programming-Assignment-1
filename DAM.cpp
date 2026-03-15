#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;

struct data {
    vector <long long> ranges;
    vector <long long> values;
};

atomic <long long> counter{0};

bool isSelfDivide(long long number);
void threadWork(int chunk, int maxRange, data *p);

int main() {
    auto startTime = chrono::high_resolution_clock::now();
    int n, m, c; // N = 10^n, m = No_of_threads, c = Chunk_Size  
    fstream fp;

    fp.open("inp-params.txt", ios::in);
    if (!fp) {
        cout << "Cannot open file.";
        return 1;
    } else {
        string line, token;
        getline(fp, line); // Skip First Line 
        getline(fp, line); // Read Second Line
        istringstream ss(line);
        getline(ss, token, ',');
        n = stoi(token);
        getline(ss, token, ',');
        m = stoi(token);
        getline(ss, token, ',');
        c = stoi(token);
        fp.close();
    }

    data d[m];
    long long N = pow(10, n);

    vector <thread> threads;
    for (int i = 0; i < m; ++i) {
        threads.push_back(thread(threadWork, c, N, &d[i]));
    }
    for (int i = 0; i < m; ++i) {
        threads[i].join();
    }
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    cout << endl << "****** Dynamic Allocation Method ******" << endl << endl;
    cout << "Range = 1 to " << N << "| No of Threads = " << m << "| Chunk Size = " << c << endl;
    cout << endl << "Numbers Allocation:" << endl << endl;
    for (int i = 0; i < m; ++i) {
        cout << "Thread" << (i+1) << ": ";
        for (long long range : d[i].ranges) {
            cout << range << " to " << (range + c -1) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;
    cout << "Thread-wise Self Dividing Numbers Identification:" << endl << endl;
    for (int i = 0; i < m; ++i) {
        cout << "Thread" << (i+1) << ": ";
        for (long long value : d[i].values) {
            cout << value << " ";
        }
        cout << endl;
    }
    cout << endl << "All Self Dividing Numbers in the range 1 to " << N << " :" << endl;
    for (int i = 0; i < m; i++) {
        for (long long val : d[i].values) {
            cout << val << " ";
        }
    }
    cout << endl << endl << "DAM Time: " << duration.count() << " ns" << endl;
    
    return 0;
}

bool isSelfDivide(long long number) {
    int digit;
    for (long long x = number; x != 0; x = x / 10) {
        digit = x % 10;
        if ((digit == 0) || (number % digit) != 0) 
            return false;
    }
    return true;
}

void threadWork(int chunk, int maxRange, data *p) {
    long long startValue = counter.fetch_add(chunk);
    long long endValue = startValue + chunk;
    while (endValue <= maxRange) {
        p->ranges.push_back(startValue + 1);
        for (long long i = startValue + 1; i <= endValue; ++i) {
            if (isSelfDivide(i)) {
                p->values.push_back(i);
            }                
        }
        startValue = counter.fetch_add(chunk);
        endValue = startValue + chunk;
    } 
}