// 给定一个非负整数金额num，不设置上限，用"零", "壹", "贰", "叁", "肆","伍","陆", "柒", "捌", "玖"表示
//输入num的中文表示。输入保证num不包含前导零
//输出中文大写，包含“元整”
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string chineseDigits[] = {"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};
string smallUnits[] = {"", "拾", "佰", "仟"};
// 大单位数组，每进4位换一个单位，支持到10^72
string bigUnits[] = {"", "万", "亿", "兆", "京", "垓", "秭", "穰", "沟", "涧", "正", "载", "极", "恒河沙", "阿僧祇", "那由他", "不可思议", "无量", "大数"};

// 处理4位以内数字的函数
string process_block(const string& block) {
    string res = "";
    bool needZero = false; // 记录是否遇到过 '0' 需要补“零”
    
    for (int i = 0; i < block.length(); i++) {
        int digit = block[i] - '0';
        int unit_index = block.length() - 1 - i;
        
        if (digit == 0) {
            needZero = true;
        } else {
            // 如果遇到非零数字前有连续的零，且这不是这组的首位输出
            if (needZero && !res.empty()) {
                res += chineseDigits[0];
            }
            res += chineseDigits[digit] + smallUnits[unit_index];
            needZero = false;
        }
    }
    return res;
}

string change_to_chinese(string num) {
    if (num == "0") return chineseDigits[0];

    string result = "";
    int len = num.length();
    int block_index = 0; // 当前大单位的索引
    bool lastBlockAllZero = false; // 记录上一个处理的4位块是否全为0

    // 从右往左，每4位切割一次
    for (int i = len; i > 0; i -= 4) {
        int start = max(0, i - 4);
        int length = i - start;
        string block = num.substr(start, length);
        
        // 检查该截取块是否全为0
        bool allZero = true;
        for (char c : block) {
            if (c != '0') {
                allZero = false;
                break;
            }
        }

        if (allZero) {
            // 处理形如 ...0000... 的情况，不需要加大单位（比如不说“零万”）
            lastBlockAllZero = true;
        } else {
            string block_chinese = process_block(block);
            
            // 是否在组与组之间补“零”：
            // 1. 如果低一级紧邻的块里含有非0元素，并且当前块以0结尾（如 1000 0001 -> 壹仟 万 零 壹）
            // 2. 或者低一级是一个全零块，且更低级有非0元素
            if (lastBlockAllZero || block.back() == '0') {
                if (!result.empty() && result.substr(0, 3) != "零") {
                    block_chinese += chineseDigits[0];
                }
            }
            
            // 加上大单位，并拼接到结果的最前面
            result = block_chinese + bigUnits[block_index] + result;
            lastBlockAllZero = false;
        }
        
        block_index++;
    }
    
    return result;
}

int main() {
    string s;
    while (cin >> s) { // 支持多次输入测试
        cout << change_to_chinese(s) << "元整" << endl;
    }
    return 0;
}