#include <vector>
#include <iostream>

using namespace std;

class SuffixArray {
    private:
    string s;
    void sortStartingFromKthChar(int k) {
        int bufSize = max(300, len);
        vector<int> cnt(bufSize, 0);
        for (int i = 0; i < len; i++) {
            cnt[i + k < len ? RA[i + k] : 0]++;
        }

        int sum = 0;
        for (int i = 0; i < bufSize; i++) {
            int t = cnt[i];
            cnt[i] = sum;
            sum += t;
        }

        vector<int> tempSA(len);
        for (int i = 0; i < len; i++) {
            tempSA[cnt[SA[i] + k < len ? RA[SA[i] + k] : 0]++] = SA[i];
        }

        SA = tempSA;
    }

    void fillLCP() {
        vector<int> phi(len);
        vector<int> plcp(len);
        phi[SA[0]] = -1;
        for (int i = 1; i < len; i++) {
            phi[SA[i]] = SA[i-1];
        }
        int L = 0;
        for (int i = 0; i < len; i++) {
            if (phi[i] == -1) {
                plcp[i] = 0;
                continue;
            }
            while (s[i + L] == s[phi[i] + L]) L++;
            plcp[i] = L;
            L = max(L-1, 0);
        }
        for (int i = 0; i < len; i++) {
            LCP[i] = plcp[SA[i]];
        }
    }

    public:
    int len;
    vector<int> SA;
    vector<int> RA;
    vector<int> LCP;
    SuffixArray(string s): SA(len), RA(len), LCP(len), len(s.size() + 1) {
        s.push_back('$');
        this->s = s;

        for (int i = 0; i < len; i++) {
            RA[i] = s[i];
            SA[i] = i;
        }

        for (int k = 1; k < len; k <<= 1) {
            sortStartingFromKthChar(k);
            sortStartingFromKthChar(0);

            vector<int> tempRA(len);
            int r = 0;
            tempRA[SA[0]] = 0;
            for (int i = 1; i < len; i++) {
                /* one of the rank is different, assign different rank */
                if (RA[SA[i]] != RA[SA[i-1]] || RA[SA[i] + k] != RA[SA[i-1] + k]) {
                    r++;
                }
                tempRA[SA[i]] = r;
            }

            RA = tempRA;
        }

        fillLCP();
    }

    void print() {
        for (int i = 0; i < len; i++) {
            cout << SA[i] << ' ' << LCP[i] << ' ' << s.substr(SA[i]) << '\n';
        }
    }
};

int main() {
    string test = "GATAGACA";
    SuffixArray sa(test);
    sa.print();
}