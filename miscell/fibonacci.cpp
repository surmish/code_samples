#include <iostream>
#include<map>
#include<vector>

using namespace std;

map <int,long unsigned> fibonacci_map {{0,0},{1,1}};

long unsigned fibonacci (int n) {
    if ( n <= 1) {
        return fibonacci_map[n];
    } else if (!fibonacci_map[n]) {
        fibonacci_map[n] = (fibonacci(n-1) + fibonacci(n-2));
        return fibonacci_map[n];
    } else {
        return fibonacci_map[n];
    }
}

int main () {

    int n;
    cout << "How many fibonacci numbers do you wish to see? (n <= 94 due to long unsigned range)" << endl;
    cin >> n;

    cout << "The first " << n << " fibonacci numbers are" << endl ;

    for (int i = 0; i < n; i++)
        cout << "Fibonacci(" << i << ") = " << fibonacci(i) << endl;

    return 0;
}
