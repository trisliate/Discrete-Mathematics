#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS 50
#define MAX_PAIRS 100

typedef struct {
    int matrix[MAX_ELEMENTS][MAX_ELEMENTS];
    int sizeA, sizeB, sizeC;
    char setA[MAX_ELEMENTS];
    char setB[MAX_ELEMENTS];
    char setC[MAX_ELEMENTS];
} CompositeRelation;

int findIndex(char set[], int size, char element) {
    int i;
    for (i = 0; i < size; i++) {
        if (set[i] == element) {
            return i;
        }
    }
    return -1;
}

void outputMatrix(int matrix[][MAX_ELEMENTS], int rows, int cols, 
                  char rowSet[], char colSet[], const char *name) {
    int i, j;
    printf("\n【%s的关系矩阵】\n", name);
    printf("    ");
    for (j = 0; j < cols; j++) {
        printf("%6c", colSet[j]);
    }
    printf("\n");
    
    for (i = 0; i < rows; i++) {
        printf("%3c ", rowSet[i]);
        for (j = 0; j < cols; j++) {
            printf("%6d", matrix[i][j]);
        }
        printf("\n");
    }
}

void computeComposite(int R[][MAX_ELEMENTS], int S[][MAX_ELEMENTS],
                      int result[][MAX_ELEMENTS],
                      int sizeA, int sizeB, int sizeC) {
    int i, j, k;
    for (i = 0; i < sizeA; i++) {
        for (k = 0; k < sizeC; k++) {
            result[i][k] = 0;
            for (j = 0; j < sizeB; j++) {
                if (R[i][j] == 1 && S[j][k] == 1) {
                    result[i][k] = 1;
                    break;
                }
            }
        }
    }
}

int main() {
    CompositeRelation comp;
    int R[MAX_ELEMENTS][MAX_ELEMENTS];
    int S[MAX_ELEMENTS][MAX_ELEMENTS];
    int result[MAX_ELEMENTS][MAX_ELEMENTS];
    int i, j, numR, numS, idxA, idxB, idxC;
    char a, b, c;
    
    memset(&comp, 0, sizeof(CompositeRelation));
    memset(R, 0, sizeof(R));
    memset(S, 0, sizeof(S));
    memset(result, 0, sizeof(result));
    
    printf("========================================\n");
    printf("实验三：关系的复合运算\n");
    printf("========================================\n\n");
    
    printf("输入关系R的信息:\n");
    printf("集合A元素个数: ");
    scanf("%d", &comp.sizeA);
    printf("输入集合A的元素 (空格分隔，可以是数字或字母): ");
    for (i = 0; i < comp.sizeA; i++) {
        scanf(" %c", &comp.setA[i]);
    }
    
    printf("集合B元素个数: ");
    scanf("%d", &comp.sizeB);
    printf("输入集合B的元素 (空格分隔，可以是数字或字母): ");
    for (i = 0; i < comp.sizeB; i++) {
        scanf(" %c", &comp.setB[i]);
    }
    
    printf("关系R的序偶个数: ");
    scanf("%d", &numR);
    printf("输入R的序偶 (格式: a b):\n");
    for (i = 0; i < numR; i++) {
        printf("第%d个: ", i + 1);
        scanf(" %c %c", &a, &b);
        idxA = findIndex(comp.setA, comp.sizeA, a);
        idxB = findIndex(comp.setB, comp.sizeB, b);
        if (idxA != -1 && idxB != -1) {
            R[idxA][idxB] = 1;
        }
    }
    
    printf("\n输入关系S的信息:\n");
    printf("集合C元素个数: ");
    scanf("%d", &comp.sizeC);
    printf("输入集合C的元素 (空格分隔，可以是数字或字母): ");
    for (i = 0; i < comp.sizeC; i++) {
        scanf(" %c", &comp.setC[i]);
    }
    
    printf("关系S的序偶个数: ");
    scanf("%d", &numS);
    printf("输入S的序偶 (格式: b c):\n");
    for (i = 0; i < numS; i++) {
        printf("第%d个: ", i + 1);
        scanf(" %c %c", &b, &c);
        idxB = findIndex(comp.setB, comp.sizeB, b);
        idxC = findIndex(comp.setC, comp.sizeC, c);
        if (idxB != -1 && idxC != -1) {
            S[idxB][idxC] = 1;
        }
    }
    
    printf("\n========================================\n");
    outputMatrix(R, comp.sizeA, comp.sizeB, comp.setA, comp.setB, "R");
    outputMatrix(S, comp.sizeB, comp.sizeC, comp.setB, comp.setC, "S");
    
    computeComposite(R, S, result, comp.sizeA, comp.sizeB, comp.sizeC);
    outputMatrix(result, comp.sizeA, comp.sizeC, comp.setA, comp.setC, "R∘S");
    
    printf("========================================\n");
    
    printf("\n按任意键退出...");
    getchar();
    getchar();
    
    return 0;
}
