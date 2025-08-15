/**
 * 定义一个字符串 s 的“兄弟单词”为：将 s 重新排序后得到的与原字符串不同的新字符串。
 * 现在，对于给定的 n 个字符串和另一个单独的字符串 x，你需要解决两个问题：
 * 1. 统计这 n 个字符串中，有多少个是 x 的“兄弟单词”（注意，这 n 个字符串可能有重复，重复字符串分别计数）；
 * 2. 将这 n 个字符串中 x 的“兄弟单词”按字典序从小到大排序，输出排序后的第 k 个兄弟单词（从 1 开始计数）。
 *    特别地，如果不存在，则不输出任何内容。
 */

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <utility> // move
using namespace std;

constexpr char LOWER_BOUND = 'a';

constexpr size_t LOWER_ALPHABET_SIZE = 26;

using AlphabetCnt = array<char, LOWER_ALPHABET_SIZE>;

void lower_alphabet_cnt(string& s, AlphabetCnt& cnt) {
    for (size_t i = 0; i < LOWER_ALPHABET_SIZE; i++)
    {
        cnt[i] = 0;
    }
    for (auto &&c : s) {
        cnt[c-LOWER_BOUND]++;
    }
}

int main() {
    size_t number;
    cin >> number;
    vector<string> lower_words;
    lower_words.reserve(number);
    for (size_t i = 0; i < number; i++)
    {
        string s;
        cin >> s;
        lower_words.push_back(move(s));
    }

    string target_word;
    cin >> target_word;

    AlphabetCnt target_word_cnt;
    lower_alphabet_cnt(target_word, target_word_cnt);

    AlphabetCnt word_cnt;

    vector<string> brother_words;
    for (auto &&word : lower_words) {
        if (word.size() == target_word.size()) {
            if (word != target_word) {
                lower_alphabet_cnt(word, word_cnt);
                if (target_word_cnt == word_cnt) {
                    brother_words.push_back(move(word));
                }
            }
        }
    }
    
    cout << brother_words.size() << endl;

    size_t k;
    cin >> k;

    if (k <= brother_words.size()) {
        // sort(begin(brother_words), end(brother_words));
        nth_element(begin(brother_words), begin(brother_words) + k - 1, end(brother_words));
        cout << brother_words[k - 1] << endl;
    }
    
}
