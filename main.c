#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "list.h"


struct head_file {
    uint8_t version;
    uint32_t nr;
    time_t rec_update_time;
    time_t media_upgrade_time;
    uint64_t rev1;
    uint32_t rev2;
};






struct emp_s {
    struct node_s node;
    uint32_t eid;
    uint8_t name[64];
    uint8_t exp;
};

struct mgr_s {
	struct emp_s;
	char report [10][64];
};

struct dir_s {
	struct mgr_s;
	char report [10][64];
	char secretary[64];
};





int cmp_user_data_func(struct node_s * node1 , struct node_s * node2){

    return ((CONTAINER_OF(node1,struct emp_s,node)->eid) - (CONTAINER_OF(node2,struct emp_s,node)->eid));
}

int print_emp(struct node_s * node){
	struct emp_s * temp_user_node;
	temp_user_node = CONTAINER_OF(node,struct emp_s,node);
        printf("%4d,%64s,%d\n",temp_user_node->eid,temp_user_node->name,temp_user_node->exp); 
}


struct node_s * create_node(uint32_t eid,uint8_t * name,uint8_t exp){
    struct emp_s * temp_user_node = malloc(sizeof(struct emp_s));
    //TODO code for return failure
    temp_user_node->eid = eid;
    temp_user_node->exp = exp;
    strcpy(temp_user_node->name,name);
    return (&temp_user_node->node);
}


int main(){
    struct node_s * head;
    struct node_s * nnode , *l_node, *r_node;
    struct node_s * i_node;
    head = NULL;
    insert_node(create_node(11,"Eleven",6),&head,cmp_user_data_func);
    insert_node(create_node(99,"Twenty-One",10),&head,cmp_user_data_func);
    nnode =  create_node(55,"Fifty-Five",10);
    insert_node(nnode,&head,cmp_user_data_func);
    i_node = create_node(41,"Forty-One",9);
    insert_appr(&head,nnode ,i_node , cmp_user_data_func);
    i_node = create_node(31,"Thity-One",9);
    insert_appr(&head,nnode ,i_node , cmp_user_data_func);
    i_node = create_node(51,"Thity-One",9);
    insert_appr(&head,nnode ,i_node , cmp_user_data_func);
    i_node = create_node(61,"Thity-One",9);
    insert_appr(&head,nnode ,i_node , cmp_user_data_func);
    i_node = create_node(71,"Thity-One",9);
    insert_appr(&head,nnode ,i_node , cmp_user_data_func);
    i_node = create_node(81,"Thity-One",9);
    insert_appr(&head,nnode ,i_node , cmp_user_data_func);
    i_node = create_node(91,"Thity-One",9);
    insert_appr(&head,nnode ,i_node , cmp_user_data_func);

    i_node = create_node(65,"Fifteen",7);
    //compare left or right
    insert_appr(&head,nnode ,i_node , cmp_user_data_func);
    i_node = create_node(21,"Thity-One",9);
    insert_appr(&head,nnode ,i_node , cmp_user_data_func);
/*    l_node = where_to_insert(nnode ,i_node , cmp_user_data_func);

    insert_node_to_right(i_node,&head,l_node);

    i_node = create_node(66,"Fifteen",7);
    //compare left or right
    r_node = where_to_insert(nnode ,i_node , cmp_user_data_func);

    insert_node_to_left(i_node,&head,r_node);
*/

    iterate_list(head,print_emp);

    for(struct node_s * node = head; node != NULL ; ){	
        printf("test\n");
        nnode = node->next;
        remove_node(node,&head,cmp_user_data_func);
        free(CONTAINER_OF(node,struct emp_s,node));
        node = nnode;
    }
    return 0;
}
