#include <stdio.h>
#include <string.h>

#define MXWORDLEN 1000
#define MXSTRLEN 10000

int cnt_a(const char *word) {
    int cnt = 0;
    while (*word) {
        if (*word == 'a') {
            cnt++;
        }
        word++;
    }
    return cnt;
}

int main() {
    char str[MXSTRLEN] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    char word[MXWORDLEN];
    char mxword[MXWORDLEN] = "";
    int mxcnt = 0;

    char *token = strtok(str, " ,.");

    while (token != NULL) {
        int ccnt = cnt_a(token);
        if (ccnt > mxcnt) {
            mxcnt = ccnt;
            strcpy(mxword, token);
        }
        token = strtok(NULL, " ,.");
    }

    if (mxcnt > 0) {
        printf("Word with max 'а': %s\n", mxword);
        printf("Count of 'а': %d\n", mxcnt);
    } else {
        printf("'а' not found.\n");
    }
}
