#ifndef SB_C_IMPL_H
#define SB_C_IMPL_H

#include <sb_types.h>

bool sb_c_dequeue(int8_t *);

void test_event_data_port_consumer_time_triggered_handler(const int64_t * in_arg);

void test_event_data_port_consumer_component_init(const int64_t *arg);

#endif // SB_C_IMPL_H
