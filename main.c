#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*    解码字符串
*     参数： s - 待解码的字符串
*     返回： 解码后的字符串
*/
char* decodeString(char* s) {
    // 数字栈和字符串栈
    int Number_Stack[100];       // 数字栈 - 用来存储重复次数
    char* Str_Stack[100];        // 字符栈 - 用来存储部分结果字符串
    int top = -1;                // 栈顶指针

    int num = 0;                 // 当前累积的数字
    int current_capacity = 10;   // 当前字符串缓冲区的容量
    int current_len = 0;         // 当前字符串的长度
    char* current = (char*)malloc(current_capacity * sizeof(char));  // 申请当前字符串缓冲区的内存
    current[0] = '\0';           // 初始化为空字符串

    // 遍历字符串
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            // 累积数字
            num = num * 10 + (c - '0');
        } else if (c == '[') {
            // 将数字压入栈，并重置num
            Number_Stack[++top] = num;
            num = 0;

            // 将当前字符串压入栈
            Str_Stack[top] = (char*)malloc((current_len + 1) * sizeof(char));
            strcpy(Str_Stack[top], current);    //使用strcpy，拷贝字符串的值到栈中，以防后续操作错误修改栈中字符串

            // 重置当前字符串
            current_len = 0;
            current[0] = '\0';
        } else if (c == ']') {
            // 弹出数字k和字符串prev
            int k = Number_Stack[top];
            char* prev = Str_Stack[top];
            top--;

            // 计算重复字符串的长度,用来动态更新临时缓冲区的大小
            int repeated_len = current_len * k;
            char* repeated = (char*)malloc((repeated_len + 1) * sizeof(char));
            repeated[0] = '\0';

            // 重复当前字符串k次
            for (int j = 0; j < k; j++) {
                strcat(repeated, current);
            }

            // 拼接prev和repeated
            int new_len = strlen(prev) + repeated_len;
            char* new_current = (char*)malloc((new_len + 1) * sizeof(char));
            strcpy(new_current, prev);
            strcat(new_current, repeated);

            // 释放内存
            free(prev);
            free(repeated);
            free(current);

            // 更新当前字符串
            current = new_current;
            current_len = new_len;
            current_capacity = new_len + 1;
        } else {    // 处理字符情况
            if (current_len + 1 >= current_capacity) {
                // 动态扩展缓冲区
                current_capacity *= 2;
                current = realloc(current, current_capacity);
            }
            current[current_len++] = c;
            current[current_len] = '\0';
        }
    }

    return current;
}
