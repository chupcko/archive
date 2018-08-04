#ifndef __PROTOTYPE__H_
#define __PROTOTYPE__H_

void child_dead(int);
void dump(int);
void job_data_clean(job_data_t*);
boolean_t job_data_init(job_data_t*, int, char*);
boolean_t read_next_command(job_data_t*, int);
boolean_t start_new_child(job_data_t*, char*[]);
void wait_all_children(job_data_t*);

#endif
