#ifndef CGCORE_COUNTER_H
#define CGCORE_COUNTER_H

uint64_t cg_current_counter(void);

uint64_t cg_counter2ns(uint64_t counter);

#define cg_ns2s(ns) ((double)((ns) / 1000000000.0))

#define cg_ns2ms(ns) ((ns) / 1000000)

#define cg_s2ns(sec) ((uint64_t)((sec) * 1000000000))

#define cg_s2ms(sec) ((uint64_t)((sec) * 1000))

#endif /* CGCORE_COUNTER_H */
