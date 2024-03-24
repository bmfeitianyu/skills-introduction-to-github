#include<stdio.h>
#include<string.h>
#include<stdbool.h>
 
void input(int* a) {
    char s[10000];
    int i;
    scanf("%s", s);
    a[0] = strlen(s);
    //首个数组元素用以存放数组长度
    //（好处：在传参的时候可以一并将长度传过去，不用多设参数）
    for (int i = a[0]; i > 0; i--)a[i] = s[a[0] - i] - '0';
}
 
void numcpy(int* p, int* q, int n) {
    p[0] = q[0] + n;
    //确定temp的位数
    for (int i = p[0]; i >= p[0] - q[0] + 1; i--)p[i] = q[i - n];
    //将b右移n位数
}
 
bool check(int* a, int* temp) {
    //判断a和temp的大小，a>=temp返回true，反之返回false。
    if (a[0] > temp[0])return true;
    else if (a[0] < temp[0])return false;
    //先通过位数进行比较，减少循环次数
    for (int i = a[0]; i > 0; i--) {
        //由高位到低位进行检查，在不等的情况下就可以直接判断
        if (temp[i] > a[i])return false;
        else if (a[i] > temp[i])return true;
    }
    return true;
}
 
void subtraction(int* a, int* temp) {
    for (int i = 1; i<=a[0]; i++) {
        if (a[i] < temp[i]) {
            a[i + 1]--;
            a[i] += 10;
        }
        a[i] = a[i] - temp[i];
    }
    int i = a[0];
    while (a[i] == 0) {
        a[0]--;
        i--;
    }
}
 
int main() {
    int a[10000], b[10000], ans[10000] = { 0 };
    input(a);
    input(b);
    ans[0] = a[0] - b[0] + 1;
    if (ans[0] < 0) {
        printf("0\n");
        return 0;
    }  
    for (int i = ans[0]; i > 0; i--) {
        int temp[10000] = { 0 };

        numcpy(temp, b, i - 1);
   
        while (check(a, temp)) {
            subtraction(a, temp);
            ans[i]++;
        }
    }
    for (int i = ans[0]; i > 0; i--) {
        if (i == ans[0] && ans[ans[0]] == 0)continue;
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}
