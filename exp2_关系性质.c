#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 50
#define MAX_PAIRS 100

typedef struct {
    int setA[MAX_ELEMENTS];
    int sizeA;
    int relationMatrix[MAX_ELEMENTS][MAX_ELEMENTS];
    int pairs[MAX_PAIRS][2];
    int numPairs;
} RelationA;

int findIndex(int set[], int size, int element) {
    int i;
    for (i = 0; i < size; i++) {
        if (set[i] == element) {
            return i;
        }
    }
    return -1;
}

void inputSet(RelationA *rel) {
    int i;
    printf("输入集合A的元素个数: ");
    scanf("%d", &rel->sizeA);
    printf("依次输入集合A的各元素: ");
    for (i = 0; i < rel->sizeA; i++) {
        scanf("%d", &rel->setA[i]);
    }
}

void initMatrix(RelationA *rel) {
    int i, j;
    for (i = 0; i < rel->sizeA; i++) {
        for (j = 0; j < rel->sizeA; j++) {
            rel->relationMatrix[i][j] = 0;
        }
    }
}

void inputRelation(RelationA *rel) {
    int i, a, b;
    int idxA, idxB;
    int validPairs = 0;
    
    printf("\n输入关系R中序偶的个数: ");
    scanf("%d", &rel->numPairs);
    
    printf("输入关系的序偶 (格式: a b):\n");
    for (i = 0; i < rel->numPairs; i++) {
        printf("第%d个序偶: ", i + 1);
        scanf("%d %d", &a, &b);
        
        idxA = findIndex(rel->setA, rel->sizeA, a);
        idxB = findIndex(rel->setA, rel->sizeA, b);
        
        if (idxA == -1 || idxB == -1) {
            printf("  [错误] (%d, %d) 不符合定义\n", a, b);
            i--;
            continue;
        }
        
        rel->pairs[validPairs][0] = a;
        rel->pairs[validPairs][1] = b;
        rel->relationMatrix[idxA][idxB] = 1;
        validPairs++;
    }
    rel->numPairs = validPairs;
}

void outputRelationMatrix(RelationA *rel) {
    int i, j;
    printf("\n【关系矩阵 M(R)】\n");
    printf("      ");
    for (j = 0; j < rel->sizeA; j++) {
        printf("%5d", rel->setA[j]);
    }
    printf("\n");
    
    for (i = 0; i < rel->sizeA; i++) {
        printf("%5d", rel->setA[i]);
        for (j = 0; j < rel->sizeA; j++) {
            printf("%5d", rel->relationMatrix[i][j]);
        }
        printf("\n");
    }
}

int isReflexive(RelationA *rel) {
    int i;
    for (i = 0; i < rel->sizeA; i++) {
        if (rel->relationMatrix[i][i] == 0) {
            return 0;
        }
    }
    return 1;
}

int isIrreflexive(RelationA *rel) {
    int i;
    for (i = 0; i < rel->sizeA; i++) {
        if (rel->relationMatrix[i][i] == 1) {
            return 0;
        }
    }
    return 1;
}

int isSymmetric(RelationA *rel) {
    int i, j;
    for (i = 0; i < rel->sizeA; i++) {
        for (j = 0; j < rel->sizeA; j++) {
            if (rel->relationMatrix[i][j] != rel->relationMatrix[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

int isAntiSymmetric(RelationA *rel) {
    int i, j;
    for (i = 0; i < rel->sizeA; i++) {
        for (j = 0; j < rel->sizeA; j++) {
            if (i != j && rel->relationMatrix[i][j] == 1 && rel->relationMatrix[j][i] == 1) {
                return 0;
            }
        }
    }
    return 1;
}

int isTransitive(RelationA *rel) {
    int i, j, k;
    for (i = 0; i < rel->sizeA; i++) {
        for (j = 0; j < rel->sizeA; j++) {
            for (k = 0; k < rel->sizeA; k++) {
                if (rel->relationMatrix[i][j] == 1 && rel->relationMatrix[j][k] == 1) {
                    if (rel->relationMatrix[i][k] == 0) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

void checkProperties(RelationA *rel) {
    printf("\n========================================\n");
    printf("【关系性质判断】\n");
    
    printf("(1) 自反关系: %s\n", isReflexive(rel) ? "是" : "否");
    printf("(2) 反自反关系: %s\n", isIrreflexive(rel) ? "是" : "否");
    printf("(3) 对称关系: %s\n", isSymmetric(rel) ? "是" : "否");
    printf("(4) 反对称关系: %s\n", isAntiSymmetric(rel) ? "是" : "否");
    printf("(5) 传递关系: %s\n", isTransitive(rel) ? "是" : "否");
    
    printf("========================================\n");
}

int main() {
    printf("========================================\n");
    printf("实验二：关系的性质\n");
    printf("========================================\n\n");
    
    RelationA rel;
    inputSet(&rel);
    initMatrix(&rel);
    inputRelation(&rel);
    outputRelationMatrix(&rel);
    checkProperties(&rel);
    
    printf("\n按任意键退出...");
    getchar();
    getchar();
    
    return 0;
}
