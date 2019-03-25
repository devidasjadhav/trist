
struct node_s {
    struct node_s * next;
    struct node_s * prev;
};

typedef int (* cmp_user_data_var)(struct node_s * , struct node_s *);


#define CONTAINER_OF(node_ptr,type,member) ((type *)(node_ptr - offsetof(type , member)))


typedef int (* print_func)(struct node_s * );

int insert_node(struct node_s * new_node, struct node_s ** head , cmp_user_data_var cmp_user_data);

int remove_node(struct node_s * del_node ,struct node_s ** head , int (*cmp_user_data)(struct node_s * , struct node_s *));

int iterate_list( struct node_s * head,print_func pfunc);

int insert_node_to_left(struct node_s * new_node, struct node_s ** head , struct node_s * node);

int insert_node_to_right(struct node_s * new_node, struct node_s ** head , struct node_s * node);

int delete_intermediate_node(struct node_s ** head , struct node_s * node);

struct node_s * where_to_insert(struct node_s * base_node ,struct node_s * new_node , int lr , cmp_user_data_var cmp_user_data_func);

int insert_appr(struct node_s ** head,struct node_s * base_node ,struct node_s * new_node , cmp_user_data_var cmp_user_data_func);
