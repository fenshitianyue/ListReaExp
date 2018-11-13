#include <stdio.h>
#include "mylist.c"

/*
 * 1. 规定只能表达式只能计算+/-运算
 * 2. 规定常数项的次数只能是1
*/

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

//建立
void CreatExp(){

}
//销毁
void DestroyExp(PNode* head){
  assert(head); 
  ListDestroy(head);
}
//减法
void ExpressionSub(){

}


//测试用例
int main() {
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
  PNode result = ExpressionAdd(list_1, list_2);
  ExpressionPrint(result);
  return 0;
}
