#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll sum_of_squares_of_digits(ll n) {
    ll result = 0;
    while (n > 0) {
        ll digit = n % 10;
        result += digit * digit;
        n /= 10;
    }
    return result;
}

// Forward declaration with the correct signature
long long countRec(long long n, ll pos, vector<vector<long long>>& dp, vector<vector<vector<long long>>>& memo, bool isUpperBound, const vector<ll>& digits);

long long countUpTo(long long n, long long limit, vector<vector<long long>>& dp, vector<vector<vector<long long>>>& memo) {
    if (n < 0) return 0;
    if (limit == 0) return n == 0;

    vector<ll> digits;
    ll temp = limit;
    while (temp > 0) {
        digits.push_back(temp % 10);
        temp /= 10;
    }
    reverse(digits.begin(), digits.end());

    return countRec(n, digits.size(), dp, memo, true, digits);
}

long long countRec(long long n, ll pos, vector<vector<long long>>& dp, vector<vector<vector<long long>>>& memo, bool isUpperBound, const vector<ll>& digits) {
    if (n < 0) return 0;
    if (pos == 0) return n == 0;
    if (!isUpperBound && dp[pos][n] != -1) return dp[pos][n];
    if (isUpperBound && memo[pos][n][digits[digits.size() - pos]] != -1) return memo[pos][n][digits[digits.size() - pos]];

    long long count = 0;
    ll limit = isUpperBound ? digits[digits.size() - pos] : 9;
    for (ll i = 0; i <= limit; ++i) {
        count += countRec(n - i * i, pos - 1, dp, memo, isUpperBound && i == limit, digits);
    }

    if (isUpperBound) {
        return memo[pos][n][digits[digits.size() - pos]] = count;
    } else {
        return dp[pos][n] = count;
    }
}

long long countInRange(ll n, long long a, long long b, vector<vector<long long>>& dp, vector<vector<vector<long long>>>& memo) {
    return countUpTo(n, b, dp, memo) - countUpTo(n, a - 1, dp, memo);
}

int main() {
    const ll maxN = 1215;
    long long a, b;
    const ll maxDigits = 17;
    const ll maxDigitValue = 9;
    cin >> a >> b;
    vector<ll> v = { 1, 7, 10, 13, 19, 23, 28, 31, 32, 44, 49, 68, 70, 79, 82, 86, 91, 94, 97, 100, 103, 109, 129, 130, 133, 139, 167, 176, 188, 190, 192, 193, 203, 208, 219, 226, 230, 236, 239, 262, 263, 280, 291, 293, 301, 302, 310, 313, 319, 320, 326, 329, 331, 338, 356, 362, 365, 367, 368, 376, 379, 383, 386, 391, 392, 397, 404, 409, 440, 446, 464, 469, 478, 487, 490, 496, 536, 556, 563, 565, 566, 608, 617, 622, 623, 632, 635, 637, 638, 644, 649, 653, 655, 656, 665, 671, 673, 680, 683, 694, 700, 709, 716, 736, 739, 748, 761, 763, 784, 790, 793, 802, 806, 818, 820, 833, 836, 847, 860, 863, 874, 881, 888, 899, 901, 904, 907, 910, 912, 913, 921, 923, 931, 932, 937, 940, 946, 964, 970, 973, 989, 998, 1000, 1003, 1009, 1029, 1030, 1033, 1039, 1067, 1076, 1088, 1090, 1092, 1093, 1112, 1114, 1115, 1121, 1122, 1125, 1128, 1141, 1148, 1151, 1152, 1158, 1177, 1182, 1184, 1185, 1188, 1209, 1211, 1212, 1215};
    
    if (a == b) {
        ll ssss = sum_of_squares_of_digits(a);

        bool found = false;

        for (ll i=0; i<v.size(); i++) {
            if (ssss == v[i]) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "1" << endl;
        }
        else {
            cout << "0" << endl;
        }

        return 0;
    }
    
    vector<vector<long long>> dp(maxDigits + 1, vector<long long>(maxN + 1, -1));
    vector<vector<vector<long long>>> memo(maxDigits + 1, vector<vector<long long>>(maxN + 1, vector<long long>(maxDigitValue + 1, -1)));
    long long sum = 0;
    for (ll n = 0; n < v.size(); ++n) {
        sum += countInRange(v[n], a, b, dp, memo);
    }
    cout << sum << endl;
    return 0;
}