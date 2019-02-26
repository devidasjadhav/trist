#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


struct node_s {
    struct node_s * next;
    struct node_s * prev;
};

typedef int (* cmp_user_data_var)(struct node_s * , struct node_s *);

struct node_user_data {
    struct node_s node;
    int key;
};

#define CONTAINER_OF(node_ptr,type,member) ((type *)(node_ptr - offsetof(type , member)))
struct node_user_data * head_node = NULL;
struct node_user_data * root_node = NULL;
int node_count = 0;

int cmp_user_data_func(struct node_s * node1 , struct node_s * node2){

    return ((CONTAINER_OF(node1,struct node_user_data,node)->key) - (CONTAINER_OF(node2,struct node_user_data,node)->key));
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

int iterate_list( struct node_s * head){
    for(struct node_s * node = head; node != NULL ; node = node->next){
        printf("%d\n",CONTAINER_OF(node,struct node_user_data,node)->key); 
    }
    return 0;
}
struct node_s * create_node(int key){
    struct node_user_data * temp_user_node = malloc(sizeof(struct node_user_data));
    //TODO code for return failure
    temp_user_node->key = key;
    return (&temp_user_node->node);
}

int main(){
    struct node_s * head;
    struct node_s * nnode;
    head = NULL;
    insert_node(create_node(11),&head,cmp_user_data_func);
    iterate_list(head);
    insert_node(create_node(21),&head,cmp_user_data_func);
    iterate_list(head);
    insert_node(create_node(51),&head,cmp_user_data_func);
    iterate_list(head);
    insert_node(create_node(41),&head,cmp_user_data_func);
    iterate_list(head);
    insert_node(create_node(31),&head,cmp_user_data_func);
    iterate_list(head);
    for(struct node_s * node = head; node != NULL ; ){	
        printf("test\n");
        nnode = node->next;
        remove_node(node,&head,cmp_user_data_func);
        free(CONTAINER_OF(node,struct node_user_data,node));
        node = nnode;
    }
    return 0;
}
