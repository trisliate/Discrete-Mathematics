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
} Function;

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

void initMatrix(Function *func) {
    int i, j;
    for (i = 0; i < func->sizeA; i++) {
        for (j = 0; j < func->sizeB; j++) {
            func->relationMatrix[i][j] = 0;
        }
    }
}

void inputFunction(Function *func) {
    int i;
    char a, b;
    char line[100];
    int idxA, idxB;
    int validPairs = 0;
    int result;
    
    printf("\n输入关系f中序偶的个数: ");
    scanf("%d", &func->numPairs);
    getchar();  // 清除换行符
    
    printf("输入关系的序偶 (格式: a b，两个元素用空格分隔):\n");
    for (i = 0; i < func->numPairs; i++) {
        printf("第%d个序偶: ", i + 1);
        
        // 使用 fgets 读取一整行，避免缓冲区问题
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("  [错误] 输入失败\n");
            i--;
            continue;
        }
        
        // 用 sscanf 解析一整行
        result = sscanf(line, "%c %c", &a, &b);
        
        if (result != 2) {
            printf("  [错误] 输入格式不正确，请输入两个元素（如: a b）\n");
            i--;
            continue;
        }
        
        idxA = findIndex(func->setA, func->sizeA, a);
        idxB = findIndex(func->setB, func->sizeB, b);
        
        if (idxA == -1 || idxB == -1) {
            printf("  [错误] (%c, %c) 不在相应集合中\n", a, b);
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
        printf("<%c,%c>", func->pairs[i][0], func->pairs[i][1]);
        if (i < func->numPairs - 1) printf(", ");
    }
    printf("}\n");
}

void outputFunctionMatrix(Function *func) {
    int i, j;
    printf("\n【关系矩阵 M(f)】\n");
    printf("    ");
    for (j = 0; j < func->sizeB; j++) {
        printf("%6c", func->setB[j]);
    }
    printf("\n");
    
    for (i = 0; i < func->sizeA; i++) {
        printf("%3c ", func->setA[i]);
        for (j = 0; j < func->sizeB; j++) {
            printf("%6d", func->relationMatrix[i][j]);
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
    memset(&func, 0, sizeof(Function));
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
