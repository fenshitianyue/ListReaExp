#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mylist.h"

void ListInit(PNode* head){
  assert(head);
  *head = NULL;
}


//添加
int ListAdd(PNode* head, DataType elem, Variate ch, int Power){
  assert(head);
  if(NULL == *head){
    *head = (PNode)malloc(sizeof(Node));
    (*head)->_elem = elem;
    (*head)->_ch = ch;
    (*head)->_power = Power;
    (*head)->_next = NULL;
  }else{
    PNode tmp = *head;
    while(tmp->_next != NULL){
      tmp = tmp->_next;
    }
    tmp->_next = (PNode)malloc(sizeof(Node));
    tmp->_next->_elem = elem;
    tmp->_next->_ch = ch;
    tmp->_next->_power = Power;
    tmp->_next->_next = NULL;
  }
  return 1;
}
//删除:默认为尾删
int ListDel(PNode *head){
  assert(head);
  if(NULL == *head){
    return 0;
  }
  PNode tmp = *head;
  PNode tmp_pre;
  while(tmp != NULL){
    tmp_pre = tmp;
    tmp = tmp->_next;
  }
  tmp_pre->_next = NULL;
  free(tmp);
  tmp = NULL;
  return 1;
}
//查找
PNode ListFind(const PNode head, DataType elem){
  if(NULL == head){
    return NULL;
  }
  PNode tmp = head;
  while(tmp != NULL && tmp->_elem != elem){
    tmp = tmp->_next;
  }
  if(tmp != NULL){
    return tmp;
  }
  return NULL;
}
//修改
int ListChange(PNode* head, DataType dst, DataType elem){
  if(NULL == head){
    return 0;
  } 
  PNode tmp = *head;
  while(tmp != NULL && tmp->_elem != dst){
    tmp = tmp->_next;
  }
  if(tmp == NULL){
    return 0;
  }
  tmp->_elem = elem;
  return 1;
}
//输出
void ListPrint(const PNode head){
  if(NULL == head){
    return;
  }
  PNode tmp = head;
  while(tmp != NULL){
    printf("%d ", tmp->_elem);
    tmp = tmp->_next;
  }
}
//销毁
void ListDestroy(PNode* head){
  if(NULL == head || NULL == *head) return;
  while(*head != NULL){
    ListDel(head);
  } 
}

