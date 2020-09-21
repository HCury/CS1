//Henrique Cury
//he200230
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListyString.h"
#define ERR_1 1


ListyNode *createNode(char n);

//done(?)
int processInputFile(char *filename){
  FILE *fp;
  ListyString *listy;
  char *str;
  char read[1024];
  char specialChar[10];
  char key[10];
  int i;
  fp = fopen(filename, "r");
  if(fp == NULL)
    return 1;
  fscanf(fp, "%s ", read);
  str = malloc(sizeof(char) * (strlen(read) + 1));
  strcpy(str, read);
  listy = createListyString(str);
  while(!feof(fp)){
    fscanf(fp, "%s ", specialChar);
    switch(specialChar[0]){
      case '@':
        fscanf(fp, "%s %s", key, read);
        replaceChar(listy, key[0], read);
        break;
      case '+':
        fscanf(fp, "%s", read);
        listyCat(listy, read);
        break;
      // in this case ('-'), when i try to replace the char with a
      // empty character it crashes. The replaceChar() function is
      // having some issue with putting in a empty char. (?)
      case '-':
        fscanf(fp, "%s", key);
        replaceChar(listy, key[0], " ");
        break;
      case '~':
        reverseListyString(listy);
        break;
      case '?':
        printf("%d\n", listyLength(listy));
        break;
      case '!':
        printListyString(listy);
        break;
      default:
        break;
    }
  }
  fclose(fp);
  return 0;
}

//done?
ListyString *createListyString(char* str){
  int i;
  ListyString *listy;
  ListyNode *node1;
  listy = malloc(sizeof(ListyString));
  listy->head = NULL;
  if(listy == NULL)
    return NULL;
  if(str == NULL || (strcmp(str, "") == 0)){
    listy->length = 0;
    return listy;
  }
  listy->head = createNode((char) str[0]);
  node1 = listy->head;
  //creating a node for every char in the string then setting the pointer to next
  for(i = 1; i < strlen(str); i++){
    node1->next = createNode((char) str[i]);
    node1 = node1->next;
  }
  //listy->length++; does not work here
  listy->length = strlen(str);
  return listy;
}

//done
ListyString *destroyListyString(ListyString *listy){
  int i;
  ListyNode *temp;
  //guard against segfault
  if(listy == NULL)
    return NULL;
  //if head has nothing in it free it
  if(listy->head == NULL){
    free(listy->head);
    free(listy);
    return NULL;
  }
  //goes through the linked string and freeing whilst not losing reference to the head
  while(listy->head != NULL){
    temp = listy->head;
    listy->head = listy->head->next;
    free(temp);
  }
  free(listy->head);
  free(listy);
  return NULL;
}

//done
ListyString *cloneListyString(ListyString *listy){
  ListyString *newListy;
  ListyNode *node1;
  ListyNode *node2;
  //guarding
  if(listy == NULL)
    return NULL;
  // if our head is null we need to create an empty listy
  if(listy->head == NULL)
    return createListyString("");
  newListy = malloc(sizeof(ListyString));
  //guarding
  if(newListy == NULL)
    return NULL;
  node1 = listy->head;
  newListy->head = createNode(node1->data);
  node2 = newListy->head;
  //creates a node for every node in the first linked list
  for(node1 = listy->head->next; node1 != NULL; node1 = node1->next){
    node2->next = createNode(node1->data);
    node2 = node2->next;
  }
  //setting the clones length to the length of the original
  newListy->length = listy->length;
  return newListy;
}

//done(?)
void replaceChar(ListyString *listy, char key, char *str){
  int i;
  ListyNode *node1;
  ListyNode *node2;
  ListyNode *head;
  ListyNode *prev;
  if(listy == NULL || listy->head == NULL)
    return;
  for(node1 = listy->head; node1 != NULL; prev = node1, node1 = node1->next){
    if(node1->data == key){
      if(str == NULL || strcmp(str, "") == 0){
          prev->next = node1->next;
          free(node1);
          node1 = prev;
          listy->length--;
      }
      if(strlen(str) > 1){
        for(i = 0; i < strlen(str); i++){
          if(i != strlen(str) - 1){
            node1->data = str[i];
            node2 = malloc(sizeof(ListyNode));
            node2->next = node1->next;
            node1->next = node2;
            node1 = node1->next;
            listy->length++;
          }
          else
            node1->data = str[i];
        }
      }
      if(strlen(str) == 1)
        node1->data = str[0];
    }
  }
}

//done
void reverseListyString(ListyString *listy){
  ListyNode *prev = NULL;
  ListyNode *head;
  ListyNode *next;
  //"guarding" against segfault
  if (listy == NULL || listy->head == NULL)
    return;
  head = listy->head;
  //going through list
  while(head != NULL){
    //reversing
    next = head->next;
    head->next = prev;
    prev = head;
    head = next;
  }
  //new head
  listy->head = prev;
}

// done(?)
ListyString *listyCat(ListyString *listy, char *str){
  int i;
  ListyNode *node;
  if(listy == NULL && str == NULL)
    return NULL;
  if(str == NULL || (strcmp(str, "") == 0))
    return listy;
  if(listy == NULL)
    return createListyString(str);
  if(listy->head == NULL){
    listy->head = createNode((char) str[0]);
    node = listy->head;
    for(i = 1; i < strlen(str); i++){
      node->next = createNode((char) str[i]);
      node = node->next;
    }
    listy->length = strlen(str);
    return listy;
  }
  //going to end to cat
  node = listy->head;
  while(node->next != NULL)
    node = node->next;
  // cat
  for(i = 0; i < strlen(str); i++){
    node->next = createNode((char) str[i]);
    node = node->next;
  }
  listy->length = listy->length + strlen(str);
  return listy;
}

//done
int listyCmp(ListyString *listy1, ListyString *listy2){
  int i;
  ListyNode *node1;
  ListyNode *node2;
  //checking if parameters are invalid
  if(listy1 == NULL && listy2 != NULL)
    return 1;
  if(listy1 != NULL && listy2 == NULL)
    return 1;
  if(listy1 == NULL && listy2 == NULL)
    return 0;
  if(listy1->head == NULL && listy2->head == NULL)
    return 0;
  if(listy1->length > listy2->length)
    return 1;
  if(listy1->length < listy2->length)
    return 1;
  node1 = listy1->head;
  node2 = listy2->head;
  //strcmp
  for(i = 0; i < listy1->length; i++){
    if(node1->data != node2->data)
      return 1;
    node1 = node1->next;
    node2 = node2->next;
  }
  return 0;
}

//done
int listyLength(ListyString *listy){
  //protecting against segfault
  if(listy == NULL)
    return -1;
  if(listy != NULL && listy->head == NULL)
    return 0;
  return listy->length;
}

//done
void printListyString(ListyString *listy){
    int i;
    ListyNode *node1;
    //null or empty string
    if(listy == NULL || listy->head == NULL){
      printf("(empty string)\n");
      return;
    }
    node1 = listy->head;
    // print every character in the listy
    while(node1 != NULL){
      printf("%c", node1->data);
      node1 = node1->next;
    }
    printf("\n");
}

//done
double difficultyRating(void){
  return 5.0;
}

//done
double hoursSpent(void){
  return 40.0;
}


ListyNode *createNode(char n){
  // needed this function to create a node
    ListyNode *node1 = malloc(sizeof(ListyNode));
    node1 -> data = n;
    node1 -> next = NULL;
    return node1;
}


int main(int argc, char **argv){
  processInputFile(argv[1]);
  return 0;
}
