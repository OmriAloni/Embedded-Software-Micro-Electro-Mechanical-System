
#ifndef PIT_H_
#define PIT_H_

#include "derivative.h"
#include "TFC.h"



void PIT_IRQHandler(void);
void enable_irq (int irq);
void pit0_init();
void delayFunc(int numberOf1msec);
void delayForUpdatetime();

#define delay200us 99999


#endif /* PIT_H_ */
