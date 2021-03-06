#include <stdio.h>
#include <sb_types.h>
#include <sb_A_impl.h>
#include <camkes.h>

static int8_t _value;

void test_event_data_port_emitter_component_init(const int64_t *in_arg) {
  printf("[%s] test_event_data_port_emitter_component_init called\n", get_instance_name());
  _value = INT8_MIN;
}

void test_event_data_port_emitter_time_triggered_handler(const int64_t *in_arg) {
  printf("---------------------------------------\n");
  if (sb_a_enqueue( &_value ) ) {
    printf("[%s] Sent %d\n", get_instance_name(), _value);
    _value = (_value + 1);
  } else {
    printf("[%s] Unable to send\n", get_instance_name());
  }
}
