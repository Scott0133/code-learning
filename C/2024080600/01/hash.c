// 哈希表(Hash Table)
// 特点：数据元素关键字与其存储地址直接相关
// 常见hash设置方法:
//      除留余数法
//      直接定址法（适合关键字基本连续的情况）
//      数字分析法（r个数码在各位上出现频率不一定相同，例如手机号）
//      平方取中法（此方法得到的散列地址与关键字每位都有联系
//
// 常见处理hash冲突方法：
//      开放定址法:（只能进行逻辑删除）
//          1. 线性探测法（易产生堆积问题）
//          2. 平方探测法（散列表长度m必须是一个可以表示为4j+3的素数，才能探测所有位置）
//          3. 伪随机序列法



// 顺序表定义hashtable
// 除留余数法，冲突处理方法为线性探测法
// BUG
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define TRUE 0
#define FALSE 1
#define MAXSIZE 20 // 定义最大表长20
#define HASHSIZE 12 // 定义hash大小值12
#define INF 9999 // 定义越界数据（空）
int Temp[] = {19,14,23,1,68,20,84,27,55,11,10,79}; // 全局变量定义测试数组
int num = 0; // 全局变量，定义测试数组计数

typedef struct HashTable { // 定义hash表结构体
    //int data; // 存放的数据元素
    int hash_arr[MAXSIZE]; // 定义表hash_arr[]，初始化为MAXSIZE
    // struct HashTable* nextarr;
    int count; // 当前数据元素个数
}HashTable;

void Init_HashTable(HashTable *H); // 初始化hash表
int Hash(int *Temp); // 除留余数法返回值
int Hash_test(int key);
int Insert_HashTable(HashTable *H, int key); // 插入元素到hash表
int Search_HashTable(HashTable H,int key); // 在hash表中寻找元素e，并返回

int main()
{
    HashTable H; // 定义hash表 T
    Init_HashTable(&H); // 初始化hash表
    // int ret = Hash(Temp);
    // printf("%d" , ret);
    Insert_HashTable(&H, Hash(Temp));
    Insert_HashTable(&H, Hash(Temp));
    Insert_HashTable(&H, Hash(Temp));
    Insert_HashTable(&H, Hash(Temp));
    Insert_HashTable(&H, Hash(Temp));
    Insert_HashTable(&H, Hash(Temp));
    Insert_HashTable(&H, Hash(Temp));
    Insert_HashTable(&H, Hash(Temp));
    Search_HashTable(H, 11);

    return 0;
}

int Hash(int *Temp)
{
    int ret = Temp[num] % HASHSIZE; // 返回Hash值
    num++;
    return ret;
}

int Hash_test(int key)
{
    return key % HASHSIZE;
}

void Init_HashTable(HashTable *H)
{
    H->count = 0; // 初始化元素数量0
    for (int i=0; i<MAXSIZE; i++)
    {
        H->hash_arr[i] = INF; // 初始化线性表为INF
    }
}

int Insert_HashTable(HashTable *H, int key) // 插入元素到hash表，使用除留余数法
{
    int addr; // 定义插入元素值地址
    
    addr = key; // key为hash计算后的值
    while (H->hash_arr[addr] != INF) // 此地址已有元素，冲突
    {
        addr = (addr + 1) % HASHSIZE; // 线性探测法处理冲突，找到地址
    }
    H->hash_arr[addr] = key;
    return TRUE;
}

int Search_HashTable(HashTable H, int key) // 在表H中查找关键字key，若存在则返回key，若不存在则返回false
{
    int addr;
    addr = Hash_test(key);
    while (H.hash_arr[addr] != key) // 当此地址没有关键字
    {
        addr = (addr + 1) % HASHSIZE; // 线性探测法处理冲突，找到下一个地址
        if (H.hash_arr[addr] == INF || addr == Hash_test(key)) // 当找到最后一个元素，或元素存在
        {
            return FALSE; // 查找失败
        }
    }
    return TRUE; // 查找成功
}