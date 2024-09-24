// 线性探查散列表的实现
// 使用除留余数法
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define NotPresent -1
#define NeverUsed -99 // 元素为空的标记
typedef int BOOL;

typedef struct hashTable { // 散列表数据结构定义
    int M; // 散列表的长度
    int num; // 当前散列表存储元素的数量
    BOOL *empty; // empty标记数组
    int *elements; // 元素数组，为了简化程序，假设每一个元素只存储关键字
}HashTable;

void CreateHashTable(HashTable *ht, int size); // 初始化散列表
void DestroyHashTable(HashTable *ht); // 销毁散列表
void ClearHashTable(HashTable *ht); // 清空散列表
BOOL IsEmpty(HashTable *ht); // 判断散列表是否为空，若为空返回TRUE，否则返回FALSE
BOOL IsFull(HashTable *ht); // 判断散列表是否为满，若已满返回TRUE，否则返回FALSE
int Hash(int M, int key); // 基于除留余数法的散列函数
int Search(HashTable *ht, int key); // 在散列表ht中查找关键字值为key的元素，若存在，则返回该元素的位置；否则返回NotPresent
BOOL Insert(HashTable *ht, int key); // 在散列表中插入关键字值为key的元素
BOOL Delete(HashTable *ht, int key); // 在散列表中删除关键字值为key的元素
void Output(HashTable *ht); // 打印散列表对应的关键字值数组和empty数组

int main()
{
    HashTable ht;
    CreateHashTable(&ht, 20);
    Insert(&ht, 10);
    Insert(&ht, 8);
    Insert(&ht, 13);
    Insert(&ht, 54);
    Insert(&ht, 2);
    Insert(&ht, 98);
    Insert(&ht, 37);
    Insert(&ht, 82);
    Insert(&ht, 35);
    Insert(&ht, 33);
    Delete(&ht, 35);
    Output(&ht);
    int ret = Search(&ht, 82);
    int ret2 = Search(&ht, 83);
    printf("82 pos is %d\n", ret);
    printf("83 pos is %d\n", ret2);

    return 0;
}

void CreateHashTable(HashTable *ht, int size)
{
    int i;
    ht->M = size; // 散列表长度
    ht->num = 0; // 初始化散列表存储元素数量为0
    ht->empty = (BOOL *)malloc(sizeof(BOOL)); // 为empty标记创建变量空间
    ht->elements = (int *)malloc(sizeof(int)); // 为elements数组创建变量空间
    for (i=0; i<size; i++) { // 清空散列表操作
        ht->empty[i] = TRUE; // 将每个empty标记数组置空
        ht->elements[i] = NeverUsed; // 将每个元素数组初始化为空
    }
}
void DestroyHashTable(HashTable *ht)
{
    free(ht->empty);
    free(ht->elements);
}
void ClearHashTable(HashTable *ht)
{
    int i;
    ht->num = 0;
    for (i=0; i<ht->M; i++) {
        ht->empty[i] = TRUE;
        ht->elements[i] = NeverUsed;
    }
}
BOOL IsEmpty(HashTable *ht)
{
    if (ht->num == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
BOOL IsFull(HashTable *ht)
{
    if (ht->num == ht->M) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int Hash(int M, int key)
{
    return key % M;
}
int Search(HashTable *ht, int key)
{
    int anchor, pos;
    anchor = pos = Hash(ht->M, key); // 计算key的基地址
    do {
        if (ht->empty[pos]) { // 判断探查过程是否达空位置，若是，则返回NotPresent
            return NotPresent;
        }
        if (ht->elements[pos] == key) { // 若存在与key相等的关键字值，则搜索成功，返回所在位置
            return pos;
        }
        pos = (pos+1) % ht->M;
    } while (pos != anchor); // 当pos==anchor时，表面已搜索完整个散列表
    return NotPresent; // 已探查完散列表中的所有单元，但未找到key，返回NotPresent
}
BOOL Insert(HashTable *ht, int key)
{
    int anchor, i;
    if (IsFull(ht)) { // 若散列表已满，返回FALSE
        return FALSE;
    }
    if (Search(ht, key) != NotPresent) { // 若待插入元素已存在，则返回FALSE
        return FALSE;
    }
    i = anchor = Hash(ht->M, key); // 计算key的基地址
    do {
        if (ht->elements[i] == NeverUsed) { // 若当前位置未被占用，则将新元素存入当前位置
            ht->elements[i] = key; // 将key写入元素数组位置
            ht->empty[i] = FALSE; // 更新empty数组的信息
            ht->num++; // 散列表存储元素数量+1
            return TRUE;
        }
        i = (i+1) % ht->M; // 按照线性探查法考查下一个位置
    } while (i != anchor);
    return FALSE;
}
BOOL Delete(HashTable *ht, int key)
{
    if (IsEmpty(ht)) { // 若散列表为空，则删除失败，返回FALSE
        return FALSE;
    }
    int pos = Search(ht, key); // 查找关键字值为key的元素位置
    if (pos == NotPresent) { // 若被查找元素不存在，则直接返回NotPresent
        return NotPresent;
    } else {
        ht->elements[pos] = NeverUsed; // 元素位置置空
        ht->num--; // 散列表中元素数量减1
        return TRUE;
    }
}
void Output(HashTable *ht)
{
    int i;
    for (i=0; i<ht->M; i++) {
        printf("%d ", ht->elements[i]);
    }
    printf("\n");
    for (i=0; i<ht->M; i++) {
        printf("%d ", ht->empty[i]);
    }
    printf("\n");
}