#include <iostream>
#include <array>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <fstream>

using namespace std;
using boost::multiprecision::cpp_int;

long long inputErrorChecker() {
    while (true) {
        long long nthTerm;
        bool isNumber = true;

        cout << "What nth term do you want?:";
        cin >> nthTerm;



        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input must be a number. Try again. \n";
            continue;
        }

        if (nthTerm < 0) {
            cout << "Input must be above 0. Try again \n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return nthTerm;
    }
}

void printResult(const cpp_int& finalResult) {
    string choice;
    while (true) {
        cout << "Do you want the result in this terminal window or in a txt file (type 'terminal' or 'txt'):";
        cin >> choice;

        if (choice == "terminal") {
            cout << finalResult << endl;
            break;
        }
        else if (choice == "txt") {
            ofstream textFile("fibonacci.txt");
            textFile << finalResult;
            cout << "Open fibonacci.txt. The number is ready. \n";
            break;
        }
        else { cout << "Invalid choice. Please type 'terminal' or 'txt'.\n"; }
    }
}

inline void multiplyMatrixes(const array<array<cpp_int,2>,2>& x, const array<array<cpp_int,2>,2>& y, array<array<cpp_int, 2>, 2>& r) {
    r[0][0] = x[0][0] * y[0][0] + x[0][1] * y[1][0];
    r[0][1] = x[0][0] * y[0][1] + x[0][1] * y[1][1];
    r[1][0] = x[1][0] * y[0][0] + x[1][1] * y[1][0];
    r[1][1] = x[1][0] * y[0][1] + x[1][1] * y[1][1];
}

array<array<cpp_int,2>,2> squareMatrix(array<array<cpp_int,2>,2> e, long long n) {

    array<array<cpp_int, 2>, 2> result = { {{1,0},{0,1}} };
    array<array<cpp_int, 2>, 2> temp;

    while (n > 0) {
        if (n % 2 == 1) multiplyMatrixes(result, e, temp), result = temp;
        multiplyMatrixes(e, e, temp), e = temp;
        n /= 2;
    }
    return result;
}

cpp_int fibonacciMainFunction(long long n) {
    if (n <= 1) return n;
    array<array<cpp_int, 2>, 2> mainMatrix = {{{cpp_int(1) , cpp_int(1)},{cpp_int(1) , cpp_int(0)}}};
    return squareMatrix(mainMatrix, n - 1)[0][0];
}

int main() {
    ios::sync_with_stdio(false);

    long long nthTerm = inputErrorChecker();

    auto start = std::chrono::high_resolution_clock::now();
    cpp_int finalResult = fibonacciMainFunction(nthTerm);
    auto end =std::chrono:: high_resolution_clock::now();

    auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    auto duration_sec = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    cout << "It took " << duration_micro << " microseconds (" << duration_sec << " seconds)\n";

    printResult(finalResult);
    cout << "Please press enter to exit.";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}
