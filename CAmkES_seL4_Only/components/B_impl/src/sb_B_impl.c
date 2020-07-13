#include <sb_B_impl.h>
#include <sb_queue_int8_t_2.h>
#include <sb_event_counter.h>
#include <string.h>
#include <camkes.h>

void sb_entrypoint_period_B_impl(int64_t *in_arg) {
  test_event_data_port_consumer_time_triggered_handler((int64_t *) in_arg);
}

sb_queue_int8_t_2_Recv_t sb_b_recv_queue;

/************************************************************************
 * sb_b_dequeue_poll:
 ************************************************************************/
bool sb_b_dequeue_poll(sb_event_counter_t *numDropped, int8_t *data) {
  return sb_queue_int8_t_2_dequeue(&sb_b_recv_queue, numDropped, data);
}

/************************************************************************
 * sb_b_dequeue:
 ************************************************************************/
bool sb_b_dequeue(int8_t *data) {
  sb_event_counter_t numDropped;
  return sb_b_dequeue_poll(&numDropped, data);
}

/************************************************************************
 * sb_b_is_empty:
 *
 * Helper method to determine if infrastructure port has received new
 * events
 ************************************************************************/
bool sb_b_is_empty(){
  return sb_queue_int8_t_2_is_empty(&sb_b_recv_queue);
}

/************************************************************************
 *  sb_entrypoint_B_impl_initializer:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void sb_entrypoint_B_impl_initializer(const int64_t * in_arg) {
  test_event_data_port_consumer_component_init((int64_t *) in_arg);
}

void pre_init(void) {
  // initialise data structure for incoming event data port b
  sb_queue_int8_t_2_Recv_init(&sb_b_recv_queue, sb_b_queue);
}

/************************************************************************
 * int run(void)
 * Main active thread function.
 ************************************************************************/
int run(void) {
  {
    int64_t sb_dummy;
    sb_entrypoint_B_impl_initializer(&sb_dummy);
  }
  sb_self_pacer_tick_emit();
  for(;;) {
    sb_self_pacer_tock_wait();
    {
      int64_t sb_dummy = 0;
      sb_entrypoint_period_B_impl(&sb_dummy);
    }
    sb_self_pacer_tick_emit();
  }
  return 0;
}
