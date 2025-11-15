#include <iostream>
#include <string>
using namespace std;

int main() {
    string text, pattern;
    cin >> text >> pattern;

    int n = text.size();
    int m = pattern.size();
    int pHash = 0, tHash = 0;
    int d = 256;
    int q = 101;
    int h = 1;

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        pHash = (d * pHash + pattern[i]) % q;
        tHash = (d * tHash + text[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (pHash == tHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                cout << "Pattern found at index " << i << endl;
        }

        if (i < n - m) {
            tHash = (d * (tHash - text[i] * h) + text[i + 1]) % q;
            if (tHash < 0)
                tHash += q;
        }
    }

    return 0;
}
