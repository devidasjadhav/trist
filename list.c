#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "list.h"

int insert_node(struct node_s * new_node, struct node_s ** head , cmp_user_data_var cmp_user_data){
    struct node_s * node_last;
    int ret;
    if(*head == NULL){
        *head = new_node;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        return 0;
    }
    for(struct node_s * node = *head; node != NULL ; node = node->next){
        ret = cmp_user_data(node,new_node);
        if(ret >= 0){
            if(node->prev == NULL){
                *head = new_node;
            }
            else {
                 node->prev->next = new_node;
            }
            new_node->prev = node->prev;
            node->prev = new_node;
            new_node->next = node;
            return ret;
        }
        else {
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
                del_node = node;
                if(node->next == NULL){
                    return -3;
                }
                *head = node->next;
                node->next->prev = NULL;
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

int iterate_list( struct node_s * head,print_func pfunc){
    for(struct node_s * node = head; node != NULL ; node = node->next){
	    pfunc(node);
    }
    return 0;
}

int insert_node_to_left(struct node_s * new_node, struct node_s ** head , struct node_s * node){
	struct node_s * node_temp;
	if(new_node == NULL){
		return -1;
		//handle this case
	}
	if(node == NULL){
		*head = node_temp;
		new_node->prev = NULL;
		new_node->next = NULL;
		return 0;
	}
	node_temp = node->prev;
	if(node_temp == NULL){
		if(node != *head){
			return -2;
		}
		*head = new_node;
		new_node->prev = NULL;
		new_node->next = node;
		return 0;
	}

	node->prev = new_node;
	new_node->next = node;
	new_node->prev = node_temp;
	node_temp->next = new_node;
	return 1;
}

int insert_node_to_right(struct node_s * new_node, struct node_s ** head , struct node_s * node){
	struct node_s * node_temp;
	if(new_node == NULL){
		return -1;
		//handle this case
	}
	if(node == NULL){
		*head = node_temp;
		new_node->prev = NULL;
		new_node->next = NULL;
		return 0;
	}
	node_temp = node->next;

	node->next = new_node;
	new_node->prev = node;
	new_node->next = node_temp;
	if(node_temp != NULL){
		node_temp->prev = new_node;
	}
	return 1;
}

int delete_intermediate_node(struct node_s ** head , struct node_s * node){
	struct node_s *del_node, *prev_delnode,*next_delnode;
	if(node == NULL){
		return -1;
	}
	if(node == *head){
		*head == NULL;
		return 0;
	}
	prev_delnode = node->prev;
	next_delnode = node->next;
	if(prev_delnode == NULL){
		return -3;
		//very unlikely as head will have this property
	}
	prev_delnode->next = next_delnode;
	next_delnode->prev = prev_delnode;
	return 1;
}

int insert_appr(struct node_s ** head,struct node_s * base_node ,struct node_s * new_node , cmp_user_data_var cmp_user_data_func){
	struct node_s * node;
	int32_t ret,lr;
        ret = cmp_user_data_func(base_node,new_node);
        lr = (ret < 0) ? 1 : 0;
	node = where_to_insert(base_node,new_node,lr,cmp_user_data_func);

	if(lr == 1)
		return insert_node_to_left(new_node,head,node);
	else
		return insert_node_to_right(new_node,head,node);
}


struct node_s * where_to_insert(struct node_s * base_node ,struct node_s * new_node, int lr , cmp_user_data_var cmp_user_data_func){
	
	struct node_s *loop_node, *prev_node = NULL;
	int32_t ret;

	if((base_node == NULL)||(new_node == NULL)){
		return NULL;
	}

	for(loop_node = base_node; loop_node != NULL; loop_node = ((lr == 0) ? loop_node->prev : loop_node->next)){
		ret = cmp_user_data_func(loop_node,new_node);
		if(ret == 0){
			return NULL;
		}
		else if((lr==0)?(ret < 0):(ret > 0)){
//			return ((lr==0)? loop_node : prev_node);
			return loop_node;			
		}
		
		if(loop_node != NULL){
			prev_node = loop_node;
		}
	}
	return prev_node;	
}

