#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "my_blockchain.h"

node_list *head = NULL;
int _node_count = 0;

int my_strlen(char* str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

int my_strcmp(char *str1, char *str2) {
    for(int i=0; str1[i] && str2[i]; i++)
        if(str1[i] != str2[i])
            return 1;
    return 0;
}

int my_atoi(char*str)
{ 
    int i=0, des, result_ans = 0; 
    while(str[i])
    {
        des = str[i] - '0';
        result_ans = 10*result_ans + des;
        i++;
    }
    
    return result_ans;
}

char* my_strcpy(char* param_1, char* param_2){
    for(int i = 0; i <= my_strlen(param_2); i++){
        param_1[i] = param_2[i];
    }
    return param_1;
}

void make_null_progg(char* string, int size)
{
    for(int i = 0; i < size; i++)
    {
        string[i] = '\0';
    }
}


int checking_uniq_of_nodees(int node_id)
{
    node_list* currentu = head;
    while(currentu)
    {
        if(currentu->id == node_id)
            return 0;
        currentu = currentu->next;
    }
    return 1;
}


int checking_uniq_of_blockks(block_list*currentu, int bid)
{
    while(currentu)
    {
        if(currentu->id == bid)
            return 0;
        currentu = currentu->next;
    }
    return 1;
}


void add_nodeu(char* nid) {
    int node_idu = my_atoi(nid);
    if(!checking_uniq_of_nodees(node_idu))
    {
        write(1, "this node already exists\n", 25);
        return;
    }
    _node_count++;
    node_list* list_cln = (node_list*)malloc(sizeof(node_list));
   
    list_cln->id = node_idu;
    list_cln->next = NULL;
    list_cln->block = NULL;
    list_cln->block_count=0;
    if (head == NULL)
        head = list_cln;
    else {
        node_list* currentu = head;
        while (currentu->next != NULL) {
            currentu = currentu->next;
        }
        currentu->next = list_cln;
    }
    write(1, "OK\n", 3);
}


void remove_nodeu(char* nid) {
    if (head == NULL) {
        write(1, "NOK: node not found\n", 20);
        return;
    }
    node_list* current_ver = head;
    node_list* prevu = NULL;

    while (current_ver != NULL) {
        if (current_ver->id == my_atoi(nid)){
            _node_count--;
            if (prevu == NULL) {
                head = current_ver->next;
            } else {
                prevu->next = current_ver->next ;
            }
            block_list* b_list_ctp = current_ver->block;
            while (b_list_ctp) {
                block_list* tempu = b_list_ctp;
                b_list_ctp = b_list_ctp->next;
                free(tempu);
            }
            free(current_ver);
            write(1, "OK\n", 3);
            return;
        }
        prevu = current_ver;
        current_ver = current_ver->next;
    }
    write(2, "NOK: node doesn't exist\n", 24);
}


void remove_blocku(int bid, int nid) {
    node_list* temp_rbf = head;
    while (temp_rbf) {
        if (temp_rbf->id == nid) {
            temp_rbf->block_count--;
            block_list* curr_rbf = temp_rbf->block;
            block_list* prevv = NULL;

            while (curr_rbf) {
                if (curr_rbf->id == bid) {
                    if (prevv == NULL) {
                        temp_rbf->block = curr_rbf->next;
                    } else {
                        prevv->next = curr_rbf->next;
                    }
                    free(curr_rbf);
                    write(1, "OK\n", 3);
                    return;
                }
                prevv = curr_rbf;
                curr_rbf = curr_rbf->next;
            }
            break;
        }
        temp_rbf = temp_rbf->next;
    }
    write(2, "NOK: block doesn't exist\n", 24);
}


void remove_blockud(int bid, int nid) {
    node_list* temp_rbf = head;
    while (temp_rbf) {
        if (temp_rbf->id == nid) {
            temp_rbf->block_count--;
            block_list* curr_rbf = temp_rbf->block;
            block_list* prevv = NULL;

            while (curr_rbf) {
                if (curr_rbf->id == bid) {
                    if (prevv == NULL) {
                        temp_rbf->block = curr_rbf->next;
                    } else {
                        prevv->next = curr_rbf->next;
                    }
                    free(curr_rbf);
                    return;
                }
                prevv = curr_rbf;
                curr_rbf = curr_rbf->next;
            }
            break;
        }
        temp_rbf = temp_rbf->next;
    }
    write(2, "NOK: block doesn't exist\n", 24);
}


void block_adding_pluss(int bid_g, block_list**temp)
{
    block_list* listt_ipf = (block_list*)malloc(sizeof(block_list));
    listt_ipf->id = bid_g;
    listt_ipf->next = NULL;
    if((*temp) == NULL)
        (*temp) = listt_ipf;
    else {
        block_list* b_head_ipf = (*temp);
        while (b_head_ipf->next) {
            b_head_ipf = b_head_ipf->next;
        }
        b_head_ipf->next = listt_ipf;
    }
}


void add_blocku(int bid, int nid) {
    node_list* tempp_ib = head;
    if (bid == 0) return;
    while (tempp_ib != NULL) {
        if (tempp_ib->id == nid) {
            if (bid != 0 && !checking_uniq_of_blockks(tempp_ib->block, bid)) {
                write(1, "this block already exists\n", 26);
                return;
            }
            tempp_ib->block_count++;
            block_adding_pluss(bid, &(tempp_ib->block));
            write(1, "OK\n", 3);
            return;
        }
        tempp_ib = tempp_ib->next;
    }
    write(2, "NOK: node doesn't exist\n", 24);
}


void add_block_secf(int bid_g, int nid_g){
    node_list* timp = head;
    if(bid_g == 0) return;
    while (timp != NULL){
        if (timp->id == nid_g){
            if(!checking_uniq_of_blockks(timp->block, bid_g) && bid_g != 0)
            {
                return;
            }
            timp->block_count++;
            block_adding_pluss(bid_g, &(timp->block));
            return;
        }
        timp = timp->next;
    }
}


void add_node_secf(char* nid) {
    int node_id_dn = my_atoi(nid);
    if(!checking_uniq_of_nodees(node_id_dn))
    {
        return;
    }
    _node_count++;
    node_list* list_im = (node_list*)malloc(sizeof(node_list));
   
    list_im->id = node_id_dn;
    list_im->next = NULL;
    list_im->block = NULL;
    list_im->block_count=0;
    if (head == NULL)
        head = list_im;
    else {
        node_list* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = list_im;
    }
}


void ls_typical_func(int pnt) {
    node_list* list_inls = head;
    if (pnt == 0) {
        while (list_inls) {
            printf("%d\n", list_inls->id);
            list_inls = list_inls->next;
        }
    }else if (pnt == 1) {
        while (list_inls) {
            printf("%d:", list_inls->id);
            block_list* b_list_ils = list_inls->block;
            while (b_list_ils) {
                printf(" %d", b_list_ils->id);
                if(b_list_ils->next != NULL)
                    printf(","); 
                b_list_ils = b_list_ils->next;
            }
            list_inls = list_inls->next;
            printf("\n");
        }
    }
}


char** my_split_fcw(char* inp, int *word_count) {
    int fst = 0, p = 0;
    char** save_ctw = (char**)malloc(4*sizeof(char*));
    for (int my_index = 0; my_index <= (int)strlen(inp); my_index++) {
        if (inp[my_index] == ' ' || inp[my_index] == '\0') {
            save_ctw[p] = (char*)calloc(my_index - fst + 1, sizeof(char));
            for (int temp = fst, a = 0; temp < my_index; temp++, a++) {
                save_ctw[p][a] = inp[temp];
            }
            (*word_count)++;
            fst = my_index + 1;
            p++;
        }
    }
    for(int i = 0; i >= 256; i++){
        free(inp);
    }
    free(inp);
    return save_ctw;
}


void add_block_secfto_all(char* g_bid) {
    int block_all_id_2 = my_atoi(g_bid);
    node_list* current_tvnd = head;

    while (current_tvnd != NULL) {
        add_block_secf(block_all_id_2, current_tvnd->id);
        current_tvnd = current_tvnd->next;
    }
    write(2, "OK\n", 3);
}


int check_type_fpc(char* string_g) {
    if (!my_strcmp(string_g, "node")) {
        return 0;
    } else if (!my_strcmp(string_g, "block")) {
        return 1;
    } else if (!my_strcmp(string_g, "-l")) {
        return 2;
    } else if (!my_strcmp(string_g, "*")) {
        return 3;
    }
    return -1;
}


int entered_commands_spc(char* string_g){
    if (!my_strcmp(string_g, "add")){
        return 0;
    } else if (!my_strcmp(string_g, "rm")) {
        return 1;
    } else if (!my_strcmp(string_g, "ls")) {
        return 2;
    } else if (!my_strcmp(string_g, "sync")) {
        return 3;
    } else if (!my_strcmp(string_g, "quit" )) {
        return 4;
    } else if(!my_strcmp(string_g, "ping")){
        return 5;
    }
    return -1;
}


void sync_fib() {
    block_list* common_blocks_fbcs = NULL;
    node_list* current_node_fncs = head;

    while (current_node_fncs != NULL) {
        block_list* currentt_blockk = current_node_fncs->block;
        while (currentt_blockk != NULL) {
            if (checking_uniq_of_blockks(common_blocks_fbcs, currentt_blockk->id)) {
                block_adding_pluss(currentt_blockk->id, &common_blocks_fbcs);
            }
            currentt_blockk = currentt_blockk->next;
        }
        current_node_fncs = current_node_fncs->next;
    }

    current_node_fncs = head;
    while (current_node_fncs != NULL) {
        block_list* currentt_blockk = current_node_fncs->block;
        while (currentt_blockk != NULL) {
            if (checking_uniq_of_blockks(common_blocks_fbcs, currentt_blockk->id)) {
                remove_blocku(currentt_blockk->id, 0);
            }
            currentt_blockk = currentt_blockk->next;
        }

        block_list* common_block_n2 = common_blocks_fbcs;
        while (common_block_n2 != NULL) {
            if (checking_uniq_of_blockks(current_node_fncs->block, common_block_n2->id)) {
                current_node_fncs->block_count++;
                block_adding_pluss(common_block_n2->id, &(current_node_fncs->block));
            }
            common_block_n2 = common_block_n2->next;
        }
        current_node_fncs = current_node_fncs->next;
    }

    block_list* current_common_blockk = common_blocks_fbcs;
    while (current_common_blockk != NULL) {
        block_list* temmpp = current_common_blockk;
        current_common_blockk = current_common_blockk->next;
        free(temmpp);
    }
    printf("OK\n");
}


void _free_comm(char**str, int countu)
{
    for(int index=0; index < countu; index++) free(str[index]);
    free(str);
}   

void Process_entered_commands(char **command, int count) {
    if (my_strcmp(command[0], "rm") == 0 && my_strcmp(command[1], "block") == 0 && count < 4) {
        write(1, "Enter node id\n", 14);
        _free_comm(command, count);
        return;
    }

    int comm_1 = entered_commands_spc(command[0]);
    int type_2s = 0;

    if(count > 1){
        type_2s = check_type_fpc(command[1]);
    }
    if (comm_1 == -1 || type_2s == -1) {
        write(1, "NOK: command not found\n", 23);
        return;
    }
    char* id_2 = NULL, *nid = NULL;
    if(count > 2){
        id_2 = command[2];
    }
    if (count > 3){
        nid = command[3];
    }

    if (comm_1 == 0 && type_2s == 0) {
        add_nodeu(id_2);
    } else if (comm_1 == 0 && type_2s == 1) {
        if (nid[0] == '*')
            add_block_secfto_all(id_2);
        else
            add_blocku(my_atoi(id_2), my_atoi(nid));
    } else if (comm_1 == 1 && type_2s == 0) {
        remove_nodeu(id_2);
    } else if (comm_1 == 1 && type_2s == 1) {
        if (nid[0] == '*'){
            node_list* current_node = head;
            while (current_node != NULL) {
                remove_blockud(my_atoi(id_2), current_node->id);
                current_node = current_node->next;
            }
            write(1, "OK\n", 3);
        } else {
            remove_blocku(my_atoi(id_2), my_atoi(nid));
        }
    } else if (comm_1 == 2 && type_2s == 0) {
        ls_typical_func(0);
    } else if (comm_1 == 2 && type_2s == 2) {
        ls_typical_func(1);
    } else if (comm_1 == 3) {
        sync_fib();
    } else if (comm_1 == 4) {
        quit_part_eoc();
        _free_comm(command, count);
        exit(0);
    } else if(comm_1 == 5){
        return;
    }
    _free_comm(command, count);
}


void backingup_pite(char* name_file) {
    int fdf = open(name_file, O_RDONLY);
    struct stat file_info;
    stat(name_file, &file_info);
    int size = file_info.st_size;
    char* usage_listtu = (char*)calloc(size + 1 , sizeof(char));
    int li_read = read(fdf, usage_listtu, size);

    if (li_read <= 0) {
    //    printf("No Backup Found: Starting New Blockchain\n");
        free(usage_listtu);
        return;
    } else
    {
        char* mnt_temp = calloc(10, sizeof(char));
        char* node_id_mnnid = calloc(10, sizeof(char));
        int j = 0;
    //    printf("Restoring From Backup\n");
        for(int i=0; usage_listtu[i]; i++)
        {
            if(usage_listtu[i] == ':')
            {
                add_node_secf(mnt_temp);
                strcpy(node_id_mnnid, mnt_temp);
                make_null_progg(mnt_temp, 10);
                j=0;
            }
            else if(usage_listtu[i] == ' ' || usage_listtu[i] == '\n')
            {
                add_block_secf(my_atoi(mnt_temp), my_atoi(node_id_mnnid));
                make_null_progg(mnt_temp, 10);
                j=0;
            }
            else{
                mnt_temp[j] = usage_listtu[i];
                j++;
            }
        }
        free(mnt_temp);
        free(node_id_mnnid);
    }
    free(usage_listtu);
    close(fdf);
}


void quit_part_eoc() {
    FILE* backup_file_qp = fopen("backup.txt", "w");
    if (backup_file_qp == NULL) {
        exit(EXIT_FAILURE);
    }

    node_list* curr_node_v = head;
    while (curr_node_v != NULL) {
        fprintf(backup_file_qp, "%d: ", curr_node_v->id);
        block_list* current_block_v = curr_node_v->block;

        while (current_block_v != NULL) {
            fprintf(backup_file_qp, "%d ", current_block_v->id);
            current_block_v = current_block_v->next;
        }

        fprintf(backup_file_qp, "\n");
        curr_node_v = curr_node_v->next;
    }

    fclose(backup_file_qp);
}


void save_to_file_elems() {
    FILE* backup_file_sff = fopen("backup.txt", "w");
    node_list* current_node_sff = head;

    while (current_node_sff != NULL) {
        fprintf(backup_file_sff, "%d: ", current_node_sff->id);
        block_list* current_block_sff = current_node_sff->block;

        while (current_block_sff != NULL) {
            fprintf(backup_file_sff, "%d ", current_block_sff->id);
            current_block_sff = current_block_sff->next;
        }

        fprintf(backup_file_sff, "\n");
        current_node_sff = current_node_sff->next;
    }

    fclose(backup_file_sff);
    //write(2, "Backing up blockchain...\n", 25);
}


char* my_read_txtf(){
    char* arr_m = (char*)calloc(256, sizeof(char));
    char co;
    for(int i=0; 1; i++){
        if(read(0, &co, 1) <= 0)
        {
            exit(EXIT_SUCCESS);
        }
        if (co == '\n'){
            arr_m[i] = '\0';
            break;
        }
        arr_m[i] = co;
    }
    return arr_m;
}

int compare_bid_f2(int bid, node_list*temp)
{
    block_list* b2_c = temp->next->block;
    while(b2_c)
    {
        if(bid == b2_c->id)
            return 0;
        b2_c = b2_c->next;
    }
    return 1;
}

int synchron_check_lp(){
    node_list* bmq_temp = head;
    if (head == NULL || bmq_temp->next == NULL) {
        return 1;
    }

    while (bmq_temp->next) {
        if (bmq_temp->block_count != bmq_temp->next->block_count) {
            return 0;
        }

        block_list* b1 = bmq_temp->block;
        while (b1) {
            int flagb = compare_bid_f2(b1->id,bmq_temp);
            if(flagb==1)
            {
                return 0; 
            }
            b1 = b1->next;
        }
        bmq_temp = bmq_temp->next;
    }
    return 1;
}


void node_sync_output_bpp(int flag)
{
    char *array_fu = (char*)calloc(7, sizeof(char));
    char c = (flag==1) ? 's' : '-';
    snprintf(array_fu, 7, "[%c%d]>", c, _node_count);
    write(1, array_fu, 5);
    free(array_fu);
}


int main() {
    backingup_pite("backup.txt");
    while (1) {
        int count_sob = 0;
        node_sync_output_bpp(synchron_check_lp());
        char*arr = my_read_txtf();
        if (strlen(arr) == 0) {
            write(1, "Enter a command\n", 16);
            continue;
        }
        char** str = my_split_fcw(arr, &count_sob);
        if (count_sob > 0 && my_strcmp(str[0], "quit") == 0){
            _free_comm(str, count_sob);
            save_to_file_elems();
            break;
        }
        Process_entered_commands(str, count_sob);
    }
    return 0;
}