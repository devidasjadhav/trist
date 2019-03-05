#include <stdio.h>
#include <stdlib.h>
//#include "slab.h"

#define setBit(v,n) (v |= 1 << n)
#define clrBit(v,n) (v &= ~(1 << n))
#define isBitSet(v,n) (v & (1 << n))

struct slab_head {
	void * ptr;
	char alloc_book;
	char alloc_num;
	size_t size;
	int num_objects;
	struct slab_head * prev;
	struct slab_head * next;
} slb_head;

struct slab_head * slab_init(size_t size , int num){
	slb_head.ptr = malloc(256);
	if(slb_head.ptr == NULL)
		return NULL;
	slb_head.alloc_book = 0;
	slb_head.alloc_num = 0;
	slb_head.size = size;
	slb_head.num_objects = num;
	slb_head.next = NULL;
	slb_head.prev = NULL;
	return &slb_head;
}

void * slab_alloc(struct slab_head * slb_ptr){
    int i;
	if(slb_ptr->alloc_num == 255)
		return NULL;
	//TODO allocate one more and attach it to next
	//TODO check nibbles reducing unneccesary trversal
	for(i=0;i<256;i++){
	if(isBitSet(slb_ptr->alloc_book,i) == 0){
		setBit(slb_ptr->alloc_book,i);
		slb_ptr->alloc_num++;
		return (slb_ptr->ptr + i*slb_ptr->size);
	}
	// use gcc macro Unlikely
	return NULL;	
    }
}

int slab_free(struct slab_head * slb_ptr,void * ptr){
	if(ptr == NULL)
		return -1;
	int diff = ptr - slb_ptr->ptr;
	if((diff > 0)&&(diff < (256* slb_ptr->size))){
		if((diff % slb_ptr->size) != 0){
			//allignment mismatch
			return -2;
		}
		clrBit(slb_ptr->alloc_book,(diff/slb_ptr->size));
	}
//TODO check if this ptr is part of next and next till next is NULL
	return 0;
}

int slab_deinit(struct slab_head * slb_ptr){
    free(slb_ptr->ptr);
	return 0;
	//free slb_ptr in future when we dynamically allocate it
}



struct user_data {
int x;
char test[1024];
};
#define split_number(n,l,r,b) l = (n >> b);                 \
    r = n - (l << b);           \

int main(){
/*	struct slab_head * sh;
	sh = slab_init(sizeof(struct user_data),1000);

	for(i=0;i < 1000 ; i++){
		slab_arr[i] = slab_alloc(sh);
	}

	for(i=0;i < 1000 ; i++){
		slab_free(sh,slab_arr[i]);
	}

	slab_deinit(sh);
*/
    long num = 0xFFFF55AA,num_left,num_right,base=16;
    while(base != 0){
    split_number(num,num_left,num_right,base)
    switch(left_num){
        case 0:
                    base /= 2;

    printf("%X %X = %X",num_left , num_right , num );
    return 0;
}
