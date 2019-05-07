#ifndef _PMU_H_
#define _PMU_H_

bool pmu_init(int num);
int pmu_next();
int pmu_evaluate_and_clear(int pick);

#endif
