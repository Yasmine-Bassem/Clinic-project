#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H


typedef struct p patient;

struct p
{
	u8 ID;
	u8 name[100];
	u8 age;
	u8 gender;
	u8 slot; //0-> no reservation
};

typedef struct n node;

struct n
{
	patient data;
	node *next;
};
extern node* head;
static node* createNode(patient data);//not for user
void insertAtLast(patient data);
void insertAtFront(patient data);
u32 getSizeList();
void deleteFront();
void deleteLast();

void deleteElement(patient data);



#endif