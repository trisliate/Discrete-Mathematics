    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_ELEMENTS 50
    #define MAX_PAIRS 100

    typedef struct {
        char setA[MAX_ELEMENTS];
        int sizeA;
        char setB[MAX_ELEMENTS];
        int sizeB;
        int relationMatrix[MAX_ELEMENTS][MAX_ELEMENTS];
        char pairs[MAX_PAIRS][2];
        int numPairs;
    } Relation;

    int findIndex(char set[], int size, char element) {
        int i;
        for (i = 0; i < size; i++) {
            if (set[i] == element) {
                return i;
            }
        }
        return -1;
    }

    void inputSet(char set[], int *size, const char *name) {
        int i;
        printf("输入集合%s的元素个数: ", name);
        scanf("%d", size);
        printf("依次输入集合%s的各元素 (空格分隔，可以是数字或字母): ", name);
        for (i = 0; i < *size; i++) {
            scanf(" %c", &set[i]);
        }
    }

    void initMatrix(Relation *rel) {
        int i, j;
        for (i = 0; i < rel->sizeA; i++) {
            for (j = 0; j < rel->sizeB; j++) {
                rel->relationMatrix[i][j] = 0;
            }
        }
    }

    void inputRelation(Relation *rel) {
        int i;
        char a, b;
        int idxA, idxB;
        int validPairs = 0;
        
        printf("\n输入关系R中序偶的个数: ");
        scanf("%d", &rel->numPairs);
        
        printf("输入关系的序偶 (格式: a b):\n");
        for (i = 0; i < rel->numPairs; i++) {
            printf("第%d个序偶: ", i + 1);
            scanf(" %c %c", &a, &b);
            
            idxA = findIndex(rel->setA, rel->sizeA, a);
            idxB = findIndex(rel->setB, rel->sizeB, b);
            
            if (idxA == -1 || idxB == -1) {
                printf("  [错误] (%c, %c) 不符合定义\n", a, b);
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

    void outputRelationSet(Relation *rel) {
        int i;
        printf("\n========================================\n");
        printf("【关系R的集合表达式】\n");
        printf("R = {");
        for (i = 0; i < rel->numPairs; i++) {
            printf("<%c,%c>", rel->pairs[i][0], rel->pairs[i][1]);
            if (i < rel->numPairs - 1) printf(", ");
        }
        printf("}\n");
    }

    void outputRelationMatrix(Relation *rel) {
        int i, j;
        printf("\n【关系矩阵 M(R)】\n");
        printf("     ");
        for (j = 0; j < rel->sizeB; j++) {
            printf("%6c", rel->setB[j]);
        }
        printf("\n");
        
        for (i = 0; i < rel->sizeA; i++) {
            printf("%3c ", rel->setA[i]);
            for (j = 0; j < rel->sizeB; j++) {
                printf("%6d", rel->relationMatrix[i][j]);
            }
            printf("\n");
        }
    }

    void outputDomain(Relation *rel) {
        int i, j;
        char domainSet[MAX_ELEMENTS];
        int domainSize = 0;
        char element;
        int found;
        
        printf("\n【定义域 domR】\n");
        printf("domR = {");
        
        for (i = 0; i < rel->numPairs; i++) {
            element = rel->pairs[i][0];
            found = 0;
            for (j = 0; j < domainSize; j++) {
                if (domainSet[j] == element) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                domainSet[domainSize++] = element;
            }
        }
        
        for (i = 0; i < domainSize; i++) {
            printf("%c", domainSet[i]);
            if (i < domainSize - 1) printf(", ");
        }
        printf("}\n");
    }

    void outputRange(Relation *rel) {
        int i, j;
        char rangeSet[MAX_ELEMENTS];
        int rangeSize = 0;
        char element;
        int found;
        
        printf("【值域 ranR】\n");
        printf("ranR = {");
        
        for (i = 0; i < rel->numPairs; i++) {
            element = rel->pairs[i][1];
            found = 0;
            for (j = 0; j < rangeSize; j++) {
                if (rangeSet[j] == element) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                rangeSet[rangeSize++] = element;
            }
        }
        
        for (i = 0; i < rangeSize; i++) {
            printf("%c", rangeSet[i]);
            if (i < rangeSize - 1) printf(", ");
        }
        printf("}\n");
        printf("========================================\n");
    }

    int main() {
        printf("========================================\n");
        printf("实验一：关系的概念\n");
        printf("========================================\n\n");
        
        Relation rel;
        memset(&rel, 0, sizeof(Relation));
        inputSet(rel.setA, &rel.sizeA, "A");
        inputSet(rel.setB, &rel.sizeB, "B");
        initMatrix(&rel);
        inputRelation(&rel);
        outputRelationSet(&rel);
        outputRelationMatrix(&rel);
        outputDomain(&rel);
        outputRange(&rel);
        
        printf("\n按任意键退出...");
        getchar();
        getchar();
        
        return 0;
    }