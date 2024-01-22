#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

typedef struct block{
    char id;
    struct block* next;
} block_list;

typedef struct node{
    int id;
    int block_count;
    block_list* block;
    struct node* next;
} node_list;

void add_nodeu(char* nid);
void remove_nodeu(char* nid);
void add_blocku(int bid, int nid);
void remove_blocku(int bid, int nid);
void ls_typical_func(int pnt);
void synch();
void Process_entered_commands(char** command, int count);
char* my_read_txtf();
int synchron_check();
void node_sync_output_bpp(int flag);
void quit_part_eoc();
void save_to_file_elems();

#endif
