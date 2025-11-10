#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 50
#define MAX_PAIRS 100

typedef struct {
    int setA[MAX_ELEMENTS];
    int sizeA;
    int setB[MAX_ELEMENTS];
    int sizeB;
    int relationMatrix[MAX_ELEMENTS][MAX_ELEMENTS];
    int pairs[MAX_PAIRS][2];
    int numPairs;
} Function;

int findIndex(int set[], int size, int element) {
    int i;
    for (i = 0; i < size; i++) {
        if (set[i] == element) {
            return i;
        }
    }
    return -1;
}

void inputSet(int set[], int *size, const char *name) {
    int i;
    printf("输入集合%s的元素个数: ", name);
    scanf("%d", size);
    printf("依次输入集合%s的各元素: ", name);
    for (i = 0; i < *size; i++) {
        scanf("%d", &set[i]);
    }
}

void initMatrix(Function *func) {
    int i, j;
    for (i = 0; i < func->sizeA; i++) {
        for (j = 0; j < func->sizeB; j++) {
            func->relationMatrix[i][j] = 0;
        }
    }
}

void inputFunction(Function *func) {
    int i, a, b;
    int idxA, idxB;
    int validPairs = 0;
    
    printf("\n输入关系f中序偶的个数: ");
    scanf("%d", &func->numPairs);
    
    printf("输入关系的序偶 (格式: a b):\n");
    for (i = 0; i < func->numPairs; i++) {
        printf("第%d个序偶: ", i + 1);
        scanf("%d %d", &a, &b);
        
        idxA = findIndex(func->setA, func->sizeA, a);
        idxB = findIndex(func->setB, func->sizeB, b);
        
        if (idxA == -1 || idxB == -1) {
            printf("  [错误] (%d, %d) 不符合定义\n", a, b);
            i--;
            continue;
        }
        
        func->pairs[validPairs][0] = a;
        func->pairs[validPairs][1] = b;
        func->relationMatrix[idxA][idxB] = 1;
        validPairs++;
    }
    func->numPairs = validPairs;
}

void outputFunctionSet(Function *func) {
    int i;
    printf("\n【关系f的集合表达式】\n");
    printf("f = {");
    for (i = 0; i < func->numPairs; i++) {
        printf("<%d,%d>", func->pairs[i][0], func->pairs[i][1]);
        if (i < func->numPairs - 1) printf(", ");
    }
    printf("}\n");
}

void outputFunctionMatrix(Function *func) {
    int i, j;
    printf("\n【关系矩阵 M(f)】\n");
    printf("      ");
    for (j = 0; j < func->sizeB; j++) {
        printf("%5d", func->setB[j]);
    }
    printf("\n");
    
    for (i = 0; i < func->sizeA; i++) {
        printf("%5d", func->setA[i]);
        for (j = 0; j < func->sizeB; j++) {
            printf("%5d", func->relationMatrix[i][j]);
        }
        printf("\n");
    }
}

int isFunction(Function *func) {
    int i, j, count;
    for (i = 0; i < func->sizeA; i++) {
        count = 0;
        for (j = 0; j < func->sizeB; j++) {
            if (func->relationMatrix[i][j] == 1) {
                count++;
            }
        }
        if (count != 1) {
            return 0;
        }
    }
    return 1;
}

int isInjective(Function *func) {
    int i, j, count;
    for (j = 0; j < func->sizeB; j++) {
        count = 0;
        for (i = 0; i < func->sizeA; i++) {
            if (func->relationMatrix[i][j] == 1) {
                count++;
            }
        }
        if (count > 1) {
            return 0;
        }
    }
    return 1;
}

int isSurjective(Function *func) {
    int i, j, found;
    for (j = 0; j < func->sizeB; j++) {
        found = 0;
        for (i = 0; i < func->sizeA; i++) {
            if (func->relationMatrix[i][j] == 1) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

void analyzeFunctionType(Function *func) {
    printf("\n========================================\n");
    printf("【函数类型分析】\n");
    
    if (!isFunction(func)) {
        printf("❌ 不是函数\n");
        printf("原因：存在A中的元素对应B中0个或多于1个的元素\n");
    } else {
        printf("✓ 是函数\n");
        int injective = isInjective(func);
        int surjective = isSurjective(func);
        
        printf("  - 单射(Injective): %s\n", injective ? "是" : "否");
        printf("  - 满射(Surjective): %s\n", surjective ? "是" : "否");
        printf("\n  - 函数类型: ");
        
        if (injective && surjective) {
            printf("【双射(一一对应)】\n");
            printf("    (既是单射又是满射，存在反函数)\n");
        } else if (injective) {
            printf("【单射(但非满射)】\n");
            printf("    (不同的A中元素映射到不同的B中元素)\n");
        } else if (surjective) {
            printf("【满射(但非单射)】\n");
            printf("    (B中每个元素都有原像，但不是一对一)\n");
        } else {
            printf("【普通函数】\n");
            printf("    (既不是单射也不是满射)\n");
        }
    }
    printf("========================================\n");
}

int main() {
    printf("========================================\n");
    printf("实验五：函数的定义与类型\n");
    printf("========================================\n\n");
    
    Function func;
    inputSet(func.setA, &func.sizeA, "A");
    inputSet(func.setB, &func.sizeB, "B");
    initMatrix(&func);
    inputFunction(&func);
    outputFunctionSet(&func);
    outputFunctionMatrix(&func);
    analyzeFunctionType(&func);
    
    printf("\n按任意键退出...");
    getchar();
    getchar();
    
    return 0;
}
