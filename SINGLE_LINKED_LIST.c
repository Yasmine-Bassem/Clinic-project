#include<stdio.h>
#include<stdlib.h> //malloc,calloc,....
#include"stdtypes.h"
#include"SINGLE_LINKED_LIST.h"

node* head = 0;//wild value without value so we initialize it
node* tail = 0;
u32 size = 0;

static node* createNode(patient data){//private
	
	node* newNode = (node*)malloc(sizeof(node));
	
	newNode -> data = data;
	newNode -> next = NULL;
	size++;
	return newNode;
	
}
void insertAtLast(patient data){
	
	node*newNode = createNode(data);
	
	if(head == 0){
		
		head = newNode;
	}else{
		
		tail -> next = newNode;
	}
	tail = newNode;
	newNode -> next = 0;
	
}

u32 getSizeList(){
	return size;
	
}
void deleteFront(){
	if(head == 0){
		return;
	}
	node* temp = head;
	if(head == tail){
		head = NULL;
		tail = NULL;
	} else {
		head = head->next;
	}
	free(temp);
	size--;
}
void deleteLast(){
	if(head == 0){
		return;
	} else if(head == tail){
		free(head);
		head = NULL;
		tail = NULL;
		size--;
	} else {
		node* temp = head;
		while(temp->next != tail){
			temp = temp->next;
		}
		free(tail);
		tail = temp;
		tail->next = NULL;
		size--;
	}
}
void deleteElement(patient data){
	if(head == 0){
		
		printf("\nThe list is Empty\n");
		
	}else if(tail->data.ID == data.ID){
		
			deleteLast();
			
	}else if(head->data.ID ==data.ID ){
		
			deleteFront();
			
	}else{
		node* temp = 0;
		node* current = head;
		
		while((current!= 0)  && (current-> data.ID != data.ID)){
			temp = current;
			current=current ->next;
		}

		if(current == 0){
			printf("Element is not in the list\n");
		}else{
			temp->next = current->next;
			free(current);
			size--;
		}
			
		}
		
	}


