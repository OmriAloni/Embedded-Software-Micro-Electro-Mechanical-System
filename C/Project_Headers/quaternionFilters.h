/*
 * quaternionFilters.h
 *
 *  Created on: Jun 10, 2018
 *      Author: Daniel Burovoy
 */

#ifndef QUATERNIONFILTERS_H_
#define QUATERNIONFILTERS_H_

# include "TFC.h"

void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy,
                              float gz, float mx, float my, float mz,
                              float deltat);
void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy,
                            float gz, float mx, float my, float mz,
                            float deltat);
const float * getQ();

#endif /* QUATERNIONFILTERS_H_ */