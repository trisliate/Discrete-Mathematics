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

void outputRelationMatrix(RelationA *rel, const char *label) {
    int i, j;
    printf("\n【%s】\n", label);
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

void reflexiveClosure(RelationA *rel, int closure[][MAX_ELEMENTS]) {
    int i, j;
    for (i = 0; i < rel->sizeA; i++) {
        for (j = 0; j < rel->sizeA; j++) {
            closure[i][j] = rel->relationMatrix[i][j];
        }
        closure[i][i] = 1;
    }
}

void symmetricClosure(RelationA *rel, int closure[][MAX_ELEMENTS]) {
    int i, j;
    for (i = 0; i < rel->sizeA; i++) {
        for (j = 0; j < rel->sizeA; j++) {
            closure[i][j] = rel->relationMatrix[i][j];
            if (rel->relationMatrix[j][i] == 1) {
                closure[i][j] = 1;
            }
        }
    }
}

void outputClosure(RelationA *rel, int closure[][MAX_ELEMENTS], const char *type) {
    int i, j;
    printf("\n【%s闭包的关系矩阵】\n", type);
    printf("      ");
    for (j = 0; j < rel->sizeA; j++) {
        printf("%5d", rel->setA[j]);
    }
    printf("\n");
    
    for (i = 0; i < rel->sizeA; i++) {
        printf("%5d", rel->setA[i]);
        for (j = 0; j < rel->sizeA; j++) {
            printf("%5d", closure[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("========================================\n");
    printf("实验四：关系的闭包\n");
    printf("========================================\n\n");
    
    RelationA rel;
    inputSet(&rel);
    initMatrix(&rel);
    inputRelation(&rel);
    outputRelationMatrix(&rel, "原关系R的矩阵");
    
    int reflexiveClosureMatrix[MAX_ELEMENTS][MAX_ELEMENTS];
    int symmetricClosureMatrix[MAX_ELEMENTS][MAX_ELEMENTS];
    
    reflexiveClosure(&rel, reflexiveClosureMatrix);
    symmetricClosure(&rel, symmetricClosureMatrix);
    
    printf("\n========================================\n");
    outputClosure(&rel, reflexiveClosureMatrix, "自反");
    outputClosure(&rel, symmetricClosureMatrix, "对称");
    printf("========================================\n");
    
    printf("\n按任意键退出...");
    getchar();
    getchar();
    
    return 0;
}
