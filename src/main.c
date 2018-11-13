#include <stdio.h>
#include <assert.h>
#include "mylist.h"

/*
 * 1. 规定只能表达式只能计算+/-运算
 * 2. 规定常数项的次数只能是1
*/

//封装表达式项类型
typedef struct {
  char _ch;//常/变量标志
  int _num;//系数
  int _power;//次数
}item;

void CreatExp(PNode* exp);
void Opposite(PNode* list);
void ExpressionPrint(PNode list);
void DestroyExp(PNode* head);
PNode ExpressionAdd(PNode list1, PNode list2);
PNode ExpressionSub(PNode list1, PNode list2);

//销毁
void DestroyExp(PNode* head){
  assert(head); 
  ListDestroy(head);
}

//给每一项的系数乘以-1
void Opposite(PNode* list){
  PNode tmp = *list; 
  while(tmp != NULL){
    tmp->_elem = -tmp->_elem;
    tmp = tmp->_next;
  }
}

//输出
void ExpressionPrint(PNode list){
  assert(list);
  PNode tmp = list;
  while(tmp != NULL){
    if(tmp->_elem > 0 && tmp != list){
      printf(" +");
    }
    //如果变量的次数不为1
    if(tmp->_ch != '#' && tmp->_power != 1){
      printf(" %d%c^%d", tmp->_elem, tmp->_ch, tmp->_power);
    }//如果变量的次数为1
    else if(tmp->_ch != '#' && tmp->_power == 1){
      printf(" %d%c", tmp->_elem, tmp->_ch);
    }//输出常量
    else if(tmp->_ch == '#'){
      printf(" %d", tmp->_elem);
    }
    tmp = tmp->_next;
  }//end while(tmp != NULL)
  printf("\n");
}

//加法
PNode ExpressionAdd(PNode list1, PNode list2){
  if(list1 == NULL) return list2;
  if(list2 == NULL) return list1;
  //拿着链表1中的项遍历链表2中的项
  PNode tmp1 = list1;
  PNode tmp2 = list2;
  PNode new_list;
  ListInit(&new_list);
  while(tmp1 != NULL){
    while(tmp2 != NULL){
      if(tmp1->_ch == tmp2->_ch && tmp1->_power == tmp2->_power){
        ListAdd(&new_list, tmp1->_elem + tmp2->_elem, tmp1->_ch, tmp1->_power);
        break;
      }
      tmp2 = tmp2->_next;
    }//end while(tmp2 != NULL)
    //如果没找到相同类型的项，则将链表1中的项添加到新链表中
    if(NULL == tmp2){
      ListAdd(&new_list, tmp1->_elem, tmp1->_ch, tmp1->_power);
    }//end while(tmp1 != NULL)
    tmp1 = tmp1->_next;//指向链表1的指针向后走
    tmp2 = list2;//让指向链表2的指针重新指向链表2的头部
  }
  PNode tmp3 = new_list;
  //将链表2中没有添加到新链表中的项找出来添加到新链表
  while(tmp2 != NULL){
    while(tmp3 != NULL){
      if(tmp2->_ch == tmp3->_ch && tmp2->_power == tmp3->_power){
        break; 
      }
      tmp3 = tmp3->_next;
    }//end while(tmp3 != NULL)
    if(NULL == tmp3){
      ListAdd(&new_list, tmp2->_elem, tmp2->_ch, tmp2->_power);
    }
    tmp2 = tmp2->_next;
    tmp3 = new_list;
  }//end while(tmp2 != NULL)
  return new_list;
}

//减法
PNode ExpressionSub(PNode list1, PNode list2){
  Opposite(&list2);
  PNode result = ExpressionAdd(list1, list2);
  return result;
}

//创建表达式
void CreatExp(PNode* exp){
  int m = 0; //表示表达式的项数
  ListInit(exp);
  printf("输入表达式的项数:");
  scanf("%d", &m);
  item tmp;
  for(int i = 0; i < m; ++i){
    printf("输入第%d项的系数:", i + 1);
    scanf("%d", &tmp._num);
    scanf("%*[^\n]");scanf("%*c");
    printf("输入第%d项的变量(常数项则输入#):", i + 1);
    scanf("%c", &tmp._ch);
    scanf("%*[^\n]");scanf("%*c");
    printf("输入第%d项的次方:", i + 1);
    scanf("%d", &tmp._power);
    ListAdd(exp, tmp._num, tmp._ch, tmp._power);
  }
}

//测试用例1
void test1() {
  PNode list_1;
  ListInit(&list_1);
  ListAdd(&list_1, 3, 'x', 29);
  ListAdd(&list_1, -2, 'x', 12);
  ListAdd(&list_1, 3, '#', 1);
  ExpressionPrint(list_1);
  PNode list_2;
  ListInit(&list_2);
  ListAdd(&list_2, 5, 'x', 29);
  ListAdd(&list_2, 4, 'x', 20);
  ListAdd(&list_2, 1, 'x', 2);
  ListAdd(&list_2, 12, '#', 1);
  ExpressionPrint(list_2);
  PNode result1 = ExpressionAdd(list_1, list_2);
  PNode result2 = ExpressionSub(list_1, list_2);
  ExpressionPrint(result1);
  ExpressionPrint(result2);
}

int main(){
  test1();
  return 0;
}
