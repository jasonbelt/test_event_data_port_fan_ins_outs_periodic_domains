#include <sb_D_impl.h>
#include <sb_queue_int8_t_2.h>
#include <string.h>
#include <camkes.h>

void sb_entrypoint_period_D_impl(int64_t *in_arg) {
  test_event_data_port_emitter_time_triggered_handler((int64_t *) in_arg);
}

bool sb_d_enqueue(const int8_t *data) {
  sb_queue_int8_t_2_enqueue(sb_d_queue_2, (int8_t*) data);
  sb_d_2_notification_emit();

  return true;
}

/************************************************************************
 *  sb_entrypoint_D_impl_initializer:
 *
 * This is the function invoked by an active thread dispatcher to
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 *
 ************************************************************************/
void sb_entrypoint_D_impl_initializer(const int64_t * in_arg) {
  test_event_data_port_emitter_component_init((int64_t *) in_arg);
}

void pre_init(void) {
  // initialise data structure for outgoing event data port d
  sb_queue_int8_t_2_init(sb_d_queue_2);
}

/************************************************************************
 * int run(void)
 * Main active thread function.
 ************************************************************************/
int run(void) {
  {
    int64_t sb_dummy;
    sb_entrypoint_D_impl_initializer(&sb_dummy);
  }
  sb_self_pacer_tick_emit();
  for(;;) {
    sb_self_pacer_tock_wait();
    {
      int64_t sb_dummy = 0;
      sb_entrypoint_period_D_impl(&sb_dummy);
    }
    sb_self_pacer_tick_emit();
  }
  return 0;
}
