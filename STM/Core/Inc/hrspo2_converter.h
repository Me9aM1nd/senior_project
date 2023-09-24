/*
 * hrspo2_converter.h
 *
 *  Created on: Sep 19, 2023
 *      Author: ASUS
 */

#ifndef INC_HRSPO2_CONVERTER_H_
#define INC_HRSPO2_CONVERTER_H_

void Max30102Setup();
void Max30102Loop(float *spo2_mean, uint32_t *heart_rate_mean, uint8_t *finger_on);


#endif /* INC_HRSPO2_CONVERTER_H_ */
