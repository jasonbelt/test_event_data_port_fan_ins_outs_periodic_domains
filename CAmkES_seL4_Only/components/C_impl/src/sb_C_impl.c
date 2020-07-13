#include <sb_C_impl.h>
#include <sb_queue_int8_t_2.h>
#include <sb_event_counter.h>
#include <string.h>
#include <camkes.h>

void sb_entrypoint_period_C_impl(int64_t *in_arg) {
  test_event_data_port_consumer_time_triggered_handler((int64_t *) in_arg);
}

sb_queue_int8_t_2_Recv_t sb_c_recv_queue;

/************************************************************************
 * sb_c_dequeue_poll:
 ************************************************************************/
bool sb_c_dequeue_poll(sb_event_counter_t *numDropped, int8_t *data) {
  return sb_queue_int8_t_2_dequeue(&sb_c_recv_queue, numDropped, data);
}

/************************************************************************
 * sb_c_dequeue:
 ************************************************************************/
bool sb_c_dequeue(int8_t *data) {
  sb_event_counter_t numDropped;
  return sb_c_dequeue_poll(&numDropped, data);
}

/************************************************************************
 * sb_c_is_empty:
 *
 * Helper method to determine if infrastructure port has received new
 * events
 ************************************************************************/
bool sb_c_is_empty(){
  return sb_queue_int8_t_2_is_empty(&sb_c_recv_queue);
}

/************************************************************************
 *  sb_entrypoint_C_impl_initializer:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void sb_entrypoint_C_impl_initializer(const int64_t * in_arg) {
  test_event_data_port_consumer_component_init((int64_t *) in_arg);
}

void pre_init(void) {
  // initialise data structure for incoming event data port c
  sb_queue_int8_t_2_Recv_init(&sb_c_recv_queue, sb_c_queue);
}

/************************************************************************
 * int run(void)
 * Main active thread function.
 ************************************************************************/
int run(void) {
  {
    int64_t sb_dummy;
    sb_entrypoint_C_impl_initializer(&sb_dummy);
  }
  sb_self_pacer_tick_emit();
  for(;;) {
    sb_self_pacer_tock_wait();
    {
      int64_t sb_dummy = 0;
      sb_entrypoint_period_C_impl(&sb_dummy);
    }
    sb_self_pacer_tick_emit();
  }
  return 0;
}
