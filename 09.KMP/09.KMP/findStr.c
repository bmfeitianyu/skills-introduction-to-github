#include "findStr.h"

int strAssign(StrType *str, const char *ch) {
	// str如果已经指向了数据，释放原空间再重新赋值
	if (str->str) {
		free(str->str);
	}
	// 计算ch的长度
	int len = 0;
	while (ch[len]) {
		++len;
	}
	if (len == 0) {
		str->str = NULL;
		str->length = 0;
	} else {
		str->str = (char *) malloc(sizeof(char ) * (len + 2));
		// 填充到串，0索引不填，\0填充到串中
		for (int i = 0; i <= len; ++i) {
			str->str[i + 1] = ch[i];
		}
		str->length = len;
	}

	return 0;
}

void releaseStr(StrType *str) {
	if (str) {
		if (str->str) {
			free(str->str);
		}
	}
}

int index_simple(const StrType *str, const StrType *subStr) {
	int i = 1;
	int j = 1;
	int k = i;      // k作为记录员（假设值）
	while (i <= str->length && j <= subStr->length) {
		if (str->str[i] == subStr->str[j]) {
			++i;
			++j;
		} else {
			i = ++k;
			j = 1;
		}
	}
	if (j > subStr->length) {
		return k;
	} else {
		return 0;
	}
}

void getNext(const StrType *subStr, int next[]) {
	int i = 1, j = 0;
	next[1] = 0;
	while (i < subStr->length) {
		if (j == 0 || subStr->str[i] == subStr->str[j]) {
			++i;
			++j;
			next[i] = j;
		} else {
			j = next[j];
		}
	}
}

int indexKMP(const StrType *str, const StrType *subStr, const int *next) {
	int i = 1;
	int j = 1;

	while (i <= str->length && j <= subStr->length) {
		if (j == 0 || str->str[i] == subStr->str[j]) {
			++i;
			++j;
		} else {
			j = next[j];
		}
	}
	if (j > subStr->length) {
		return i - subStr->length;
	} else {
		return 0;
	}
}
