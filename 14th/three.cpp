#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 去除字符串表示的大整数前导零（保留至少一位数字，并处理 "0" 和 "-0"）
string trim_zeros(const string &s) {
    if (s.empty()) return "0";
    int start = (s[0] == '-') ? 1 : 0;
    int first_non_zero = start;
    while (first_non_zero < s.size() && s[first_non_zero] == '0') ++first_non_zero;
    if (first_non_zero == s.size()) return "0";          // 全是零
    string res;
    if (s[0] == '-') res += '-';
    res += s.substr(first_non_zero);
    return res;
}

// 比较两个正整数字符串的大小（不含符号）
// 返回：1 表示 a > b, -1 表示 a < b, 0 表示相等
int compare_positive(const string &a, const string &b) {
    if (a.size() != b.size()) return (a.size() > b.size()) ? 1 : -1;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return (a[i] > b[i]) ? 1 : -1;
    }
    return 0;
}

// 大数加法（两个正整数字符串）
string add_positive(const string &a, const string &b) {
    string res;
    int i = a.size() - 1, j = b.size() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res.push_back('0' + sum % 10);
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

// 大数减法（两个正整数字符串，假设 a >= b）
string subtract_positive(const string &a, const string &b) {
    string res;
    int i = a.size() - 1, j = b.size() - 1, borrow = 0;
    while (i >= 0) {
        int diff = (a[i] - '0') - borrow;
        if (j >= 0) diff -= (b[j--] - '0');
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.push_back('0' + diff);
        --i;
    }
    reverse(res.begin(), res.end());
    // 去除前导零（结果至少一位）
    return trim_zeros(res);
}

// 大数乘法（两个正整数字符串）
string multiply_positive(const string &a, const string &b) {
    int len_a = a.size(), len_b = b.size();
    string res(len_a + len_b, '0');
    for (int i = len_a - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len_b - 1; j >= 0; --j) {
            int sum = (a[i] - '0') * (b[j] - '0') + (res[i + j + 1] - '0') + carry;
            res[i + j + 1] = '0' + sum % 10;
            carry = sum / 10;
        }
        res[i] += carry; // 注意这里可能累加进位到高位，但 i 位初始为 '0'，可以直接加
    }
    return trim_zeros(res);
}

// 计算平方：返回两个绝对值的平方（正整数字符串）
string square(const string &num) {
    string abs_num = (num[0] == '-') ? num.substr(1) : num;
    return multiply_positive(abs_num, abs_num);
}

int main() {
    string A, B;
    cin >> A >> B;

    // 去除可能的前导零
    A = trim_zeros(A);
    B = trim_zeros(B);

    string A2 = square(A);
    string B2 = square(B);

    // 计算 A2 - B2（均为非负）
    string result;
    int cmp = compare_positive(A2, B2);
    if (cmp == 0) {
        result = "0";
    } else if (cmp > 0) {
        result = subtract_positive(A2, B2);
    } else {
        result = "-" + subtract_positive(B2, A2);
    }

    cout << result << endl;
    return 0;
}