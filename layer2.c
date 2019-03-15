
int insert_node_l2(int key,struct head_struct * head_var){
    char ret;
    struct node_s *new_node, *mid = head_var->mid;
    new_node = create_node(key);
    ret = head_var->cmp_func(new_node,mid);
    if(ret <= 0){
        insert_left(new_node,head_var);
    }
    else {
        insert_right(new_node,head_var);
    }
    balance_mid(new_node,head_var);
    return ret;
}

int remove_node_l2(int key,struct head_struct * head_var){
    char ret;
    struct node_s 
