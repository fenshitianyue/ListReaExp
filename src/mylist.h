#pragma once

typedef int DataType;
typedef char Variate;


typedef struct Node{
  DataType _elem; //系数
  Variate _ch;  //规定'#'表示此项没有变量
  int _power; //项的次方
  struct Node* _next;
}Node, *PNode;

//初始化*
void ListInit(PNode* head);
//添加
//--返回值说明--
//1 :成功
//0 :失败
int ListAdd(PNode* head, DataType elem, Variate ch, int Power);
//删除:默认为尾删
int ListDel(PNode* head);
//修改
int ListChange(PNode* head, DataType dst, DataType elem);
//查找
PNode ListFind(const PNode head, DataType elem);
//输出
void ListPrint(const PNode head);




