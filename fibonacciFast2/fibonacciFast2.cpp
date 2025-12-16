#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <fstream>
using namespace std;
using boost::multiprecision::cpp_int;
using namespace std::chrono;

void printerThing(const cpp_int& eggs) {
	string resultThing = eggs.str(10);
    ofstream textFile("fibonacci.txt");
	textFile.write(resultThing.c_str(), resultThing.size());
    textFile.close();
}

vector<vector<cpp_int>> multiplyMatrixes(const vector<vector<cpp_int>>& x, const vector<vector<cpp_int>>& y) {
    return {
        {x[0][0] * y[0][0] + x[0][1] * y[1][0],
        x[0][0] * y[0][1] + x[0][1] * y[1][1]},
        {x[1][0] * y[0][0] + x[1][1] * y[1][0],
        x[1][0] * y[0][1] + x[1][1] * y[1][1]}
    };
}

vector<vector<cpp_int>> squareMatrix(vector<vector<cpp_int>> e, long long n) {
    vector<vector<cpp_int>> result = { {1,0},{0,1} };
    while (n > 0) {
        if (n & 1) result = multiplyMatrixes(result, e);
        e = multiplyMatrixes(e, e);
        n >>= 1;
    }
    return result;
}

cpp_int fibonacciMainFunction(long long n) {
    if (n <= 1) return n;
    vector<vector<cpp_int>> mainMatrix = { {1 , 1},{1 , 0} };
    return squareMatrix(mainMatrix, n - 1)[0][0];
}

int main() {
    ios::sync_with_stdio(false);
    long long nThTerm;
    cout << "What nth term do you want?:";
    cin >> nThTerm;
    auto start = high_resolution_clock::now();
    cpp_int finalResult = fibonacciMainFunction(nThTerm);
    auto end = high_resolution_clock::now();
    auto duration_micro = duration_cast<microseconds>(end - start).count();
    auto duration_sec = duration_cast<duration<double>>(end - start).count();
    cout << "It took " << duration_micro << " microseconds (" << duration_sec << " seconds)\n";
    printerThing(finalResult);
    cout << "Open fibonacci.txt. The number is ready.\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}
