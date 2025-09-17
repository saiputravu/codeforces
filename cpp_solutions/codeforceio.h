#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T> T read() {
    T value;
    cin >> value;
    cin.ignore();
    return value;
}

template <typename T> vector<T> read_line(char delim = ' ') {
    vector<T> result;
    string line, inline_buf;
    T t;

    getline(cin, line);
    istringstream iss(line);

    while (iss >> t)
        result.push_back(t);

    return result;
}
