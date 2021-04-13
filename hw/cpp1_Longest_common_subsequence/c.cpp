//最长公共子序列
//Longest common-subsequence problem
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
#include<vector>
#define DEBUG_INFO 
enum arrow{left, up, upperleft};
std::vector<char> LCS(char* s1, char* s2);//Longest common subsequence
int main(void){
    char* s1,*s2;
    std::vector<char> s3;
    s1 = "ABCBDAB";
    s2 = "BDCABA";
    s3 = LCS(s1,s2);
    printf("\n");
    for(int i=s3.size()-1; i >=0;  i--){
        printf(" %c ",s3[i]);
    }
    printf("\nexit 0\n");

    return 0;
}

std::vector<char> LCS(char* s1, char* s2){
    int m = strlen(s1), n = strlen(s2);
    int table[m+1][n+1];//(m+1)-by-(n+1)
    int direction[m][n];//m-by-n
    for(int i = 0; i <= m; i++){table[i][0] = 0;}
    for(int i = 1; i <= n; i++){table[0][i] = 0;}
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(s1[i-1] == s2[j-1]){
                table[i][j] = table[i-1][j-1] + 1;
                direction[i-1][j-1] = upperleft;
            }
            else if(table[i][j-1] <= table[i-1][j]){
                    table[i][j] = table[i-1][j];
                    direction[i-1][j-1] = up;
                }
            else{
                    table[i][j] = table[i][j-1];
                    direction[i-1][j-1] = left;
            }
        }
    }

#ifdef DEBUG_INFO
    printf("\n");
    for(int i = 0; i <= m; ++i){
        for (int j = 0; j <= n; ++j){
             if(i ==0 | j==0){
               printf("\033[43;30m%d  \033[0m",table[i][j]);
             }
             else printf("\033[44;32m%d  \033[0m" , table[i][j]);
        }printf("\n");
    }
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            if(direction[i][j] == left){
                printf(" ← ");
            }
            else if(direction[i][j] == up){
                printf(" ↑ ");
            }
            else if(direction[i][j] == upperleft){
                printf(" ↖ ");
            }
        }
        printf("\n");
    }
#endif
    std::vector<char> target{};
    int i,j;
    printf("\n");
    for(i = m - 1, j = n - 1 ; i >= 0 && j >= 0 ;){
            if(direction[i][j] == up){i--;printf(" ↑ ");}
            else if(direction[i][j] == left){j--; printf(" ← ");}
            else if(direction[i][j] == upperleft){target.push_back(std::move(s1[i]));i--;j--;printf(" ↖ ");}
            else printf("WHAT!!!!\n");
    }
    return target;
}
