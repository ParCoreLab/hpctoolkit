#ifndef defer_cntxt_h
#define defer_cntxt_h

#include <ompt.h>

#include <hpcrun/thread_data.h>
/*
 * this interface is used for lazy callpath resolution 
*/

/* check whether the lazy resolution is needed in an unwind */
int  need_defer_cntxt();

/* resolve the contexts */
void resolve_cntxt();
void resolve_cntxt_fini(thread_data_t*);
void resolve_other_cntxt(thread_data_t *thread_data);

uint64_t is_partial_resolve(cct_node_t *prefix);

//deferred region ID assignment
void init_region_id();

// export registration interfaces for ompt
void start_team_fn(ompt_task_id_t parent_task_id, 
		   ompt_frame_t *parent_task_frame,
		   ompt_parallel_id_t id,
		   void *parallel_function);

void end_team_fn(ompt_parallel_id_t id,
                 ompt_task_id_t parent_task_id); 

cct_node_t *hpcrun_region_lookup(uint64_t id);

#endif
