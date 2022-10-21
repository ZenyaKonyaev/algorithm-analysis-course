//
// Created by zenya2602 on 21.10.22.
//

#ifndef SRC_LEVINSTAIN_H
#define SRC_LEVINSTAIN_H


int dist_lev(char *str_1, char *str_2, int print_table_flag);
int dist_dameray_lev(char *str_1, char *str_2, int print_table_flag);
int dist_dameray_lev_rec(char *str_1, char *str_2, int len_1, int len_2);
int dist_dameray_lev_rec_hash(char *str_1, char *str_2);

#endif //SRC_LEVINSTAIN_H
