#include <bits/stdc++.h>
#include "json.hpp"  

using namespace std;
using json = nlohmann::json;

long long toDecimal(const string &value, int base) {
    long long result = 0;
    for (char c : value) {
        int digit;
        if (c >= '0' && c <= '9') digit = c - '0';
        else if (c >= 'a' && c <= 'z') digit = 10 + (c - 'a');
        else if (c >= 'A' && c <= 'Z') digit = 10 + (c - 'A');
        else continue;
        result = result * base + digit;
    }
    return result;
}

vector<long long> multiplyPoly(const vector<long long> &a, const vector<long long> &b) {
    vector<long long> res(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            res[i + j] += a[i] * b[j];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input, line;
    while (getline(cin, line)) input += line;
    json j = json::parse(input);

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    vector<long long> roots;
    for (auto &el : j.items()) {
        if (el.key() == "keys") continue;
        int base = stoi(el.value()["base"].get<string>());
        string value = el.value()["value"].get<string>();
        roots.push_back(toDecimal(value, base));
    }

    vector<long long> selected(roots.begin(), roots.begin() + k);

    vector<long long> poly = {1};  
    for (long long r : selected) {
        vector<long long> term = {1, -r}; 
        poly = multiplyPoly(poly, term);
    }

    for (size_t i = 0; i < poly.size(); i++) {
        cout << poly[i] << (i + 1 == poly.size() ? "\n" : " ");
    }

    return 0;
}