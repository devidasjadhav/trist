#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


struct node_s {
	struct node_s * next;
	struct node_s * prev;
};

struct node_user_data {
	struct node_s node;
	int key;
};

#define CONTAINER_OF(node_ptr) ((struct node_user_data *)(node_ptr - offsetof(struct node_user_data , node)))
	struct node_user_data * head_node = NULL;
	struct node_user_data * root_node = NULL;
	int node_count = 0;

int cmp_user_data_func(struct node_s * node1 , struct node_s * node2){
	
	return ((CONTAINER_OF(node1)->key) - (CONTAINER_OF(node2)->key));
}

int insert_node(struct node_s * new_node, struct node_s ** head , int (*cmp_user_data)(struct node_s * , struct node_s *)){
	struct node_s * node_last;
	int ret;
	if(*head == NULL){
		*head = new_node;
		(*head)->next = NULL;
		(*head)->prev = NULL;
		return 0;
	}
	for(struct node_s * node = *head; node != NULL ; node = node->next){
		ret = cmp_user_data(new_node,node);
		switch(ret){
		case 0:
		case 1: new_node->next  = node;
			new_node->prev = node->prev;
			node->prev = new_node;
			return ret;
		default:
			node_last = node;
		}
	}
	node_last->next = new_node;
	new_node->prev = node_last;
	new_node->next = NULL;
	return -1;
}

int remove_node(struct node_s * del_node ,struct node_s ** head , int (*cmp_user_data)(struct node_s * , struct node_s *)){
	char ret;
	if(*head == NULL){
		return 0;
	}
	// delete if head is same as del_node but you have to iterate over to get that node
	for(struct node_s * node = *head; node != NULL ; node = node->next){
		ret = cmp_user_data(del_node,node);
		if(ret == 0){
			if(node->prev == NULL){
				del_node = *head;
				if(node->next == NULL){
					return -3;
					}
				del_node->next->prev = node;
				*head = node;
				node->prev = NULL;
				return -2;
			}
			node->prev->next = node->next;
			node->next->prev = node->prev;
			del_node = node;
			//asuming del_node is not needed to be freed
		}
	}
	del_node = NULL;
	return -1;
}
		
struct node_s * create_node(int key){
	struct node_user_data * temp_user_node = malloc(sizeof(struct node_user_data));
	//TODO code for return failure
	temp_user_node->key = key;
	return (&temp_user_node->node);
}

int main(){
	struct node_s * head;
	struct node_s *temp;
	head = NULL;
	insert_node(create_node(11),&head,cmp_user_data_func);
	insert_node(create_node(21),&head,cmp_user_data_func);
	insert_node(create_node(31),&head,cmp_user_data_func);
	for(struct node_s * node = head; node != NULL ; node = node->next){	
		printf("test\n");
		temp = node;
		remove_node(node,&head,cmp_user_data_func);
		free(CONTAINER_OF(node));
		node = temp;
	}
	return 0;
}
