#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


struct node_s {
    struct node_s * next;
    struct node_s * prev;
};

typedef int (* cmp_user_data_var)(struct node_s * , struct node_s *);

struct node_user_data {
    struct node_s node;
    uint32_t key;
    uint8_t name[64];
    uint8_t exp;
};

#define CONTAINER_OF(node_ptr,type,member) ((type *)(node_ptr - offsetof(type , member)))
struct node_user_data * head_node = NULL;
struct node_user_data * root_node = NULL;
int node_count = 0;

int cmp_user_data_func(struct node_s * node1 , struct node_s * node2){

    return ((CONTAINER_OF(node1,struct node_user_data,node)->key) - (CONTAINER_OF(node2,struct node_user_data,node)->key));
}

typedef int (* print_func)(struct node_s * );

int print_emp(struct node_s * node){
	struct node_user_data * temp_user_node;
	temp_user_node = CONTAINER_OF(node,struct node_user_data,node);
        printf("%4d,%64s,%d\n",temp_user_node->key,temp_user_node->name,temp_user_node->exp); 
}

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

struct node_s * where_to_insert(struct node_s * base_node ,struct node_s * new_node , char left_right , cmp_user_data_var cmp_user_data_func){
	
	struct node_s *loop_node, *prev_node = NULL;
	
	if((base_node == NULL)||(new_node == NULL)){
		return NULL;
	}

	for(loop_node = base_node; loop_node != NULL; loop_node = ((left_right == 0) ? loop_node->prev : loop_node->next)){
		
		if(!(cmp_user_data_func(loop_node,new_node))){
			return loop_node;
		}
		
		if(loop_node != NULL){
			prev_node = loop_node;
		}
	}
/*
	if( prev_node == NULL){
		return NULL;
	}
*/
	return prev_node;	
}

struct node_s * create_node(uint32_t key,uint8_t * name,uint8_t exp){
    struct node_user_data * temp_user_node = malloc(sizeof(struct node_user_data));
    //TODO code for return failure
    temp_user_node->key = key;
    temp_user_node->exp = exp;
    strcpy(temp_user_node->name,name);
    return (&temp_user_node->node);
}


//=========================================================================================
//
//=========================================================================================
//
/*
struct head_struct {
    struct node_s mid;
    int num_left;
    int num_right;
    int balanced;
    int key_mid;
    struct node_s *head;
};

int comp_mid_func(int key,struct head_struct * head_var){
    return (key - head_var->key_mid);
}

int init_head_struct(struct head_struct * head_var){
    head_var->num_left = 0;
    head_var->num_right = 0;
    head_var->balanced = 0;
    head_var->key_mid = 0;
    head_var->head = NULL;
}

int insert_before_node(struct  node_s *node_to_insert,struct node_s * node_after, struct node_s **head){
    if(node_after == *head){
        node_to_insert->next = node_after;
        node_to_insert->prev = node_after->prev;



int ins_node(int key,struct head_struct * head_var ){
    if(head_var->head == NULL){
        //list is empty or not initialised
    //TODO add insert after node and insert before node so that we can isert befor and after node
    insert_node(create_node(key),&head_var->head,cmp_user_data_func);


*/

int main(){
    struct node_s * head;
    struct node_s * nnode;
    head = NULL;
    insert_node(create_node(11,"Eleven",6),&head,cmp_user_data_func);
    insert_node(create_node(21,"Twenty-One",10),&head,cmp_user_data_func);
    nnode =  create_node(25,"Twenty-Five",10);
    insert_node(nnode,&head,cmp_user_data_func);
    insert_node(create_node(41,"Forty-One",9),&head,cmp_user_data_func);
    insert_node(create_node(31,"Thity-One",9),&head,cmp_user_data_func);

    iterate_list(head,print_emp);

    for(struct node_s * node = head; node != NULL ; ){	
        printf("test\n");
        nnode = node->next;
        remove_node(node,&head,cmp_user_data_func);
        free(CONTAINER_OF(node,struct node_user_data,node));
        node = nnode;
    }
    return 0;
}
