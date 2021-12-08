/*
 * Copyright (C) 2010 Amlogic Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#ifndef AML_SHELF_H
#define AML_SHELF_H

#define   COEFF_FRACTION_BIT    24
#define   DATA_FRACTION_BIT     10
#define   COEFF_HALF_ERROR      ((0x1) << (COEFF_FRACTION_BIT - 1))
#define   DATA_HALF_ERROR       ((0x1) << (DATA_FRACTION_BIT - 1))

/* Count if coefficients */
#define   COEFF_COUNT       3
#define   TMP_COEFF         2
/*Channel Count*/
#define   CF                2

#define   Clip(acc,min,max) ((acc) > max ? max : ((acc) < min ? min : (acc)))

struct IIR_param {
    /*B coefficient array*/
    int   b[COEFF_COUNT];
    /*A coefficient array*/
    int   a[COEFF_COUNT];
    /*Circular buffer for channel input data*/
    int   cx[CF][TMP_COEFF];
    /*Circular buffer for channel output data*/
    int   cy[CF][TMP_COEFF];
};

static int IIR_coefficients[2][COEFF_COUNT] = {
       {/*B coefficients*/
                36224809,    16150517,     1797672,
       },
       {/*A coefficients*/
                16777216,    26740673,    10655109,
       },

};

int audio_IIR_process(int input, int channel);
void audio_IIR_init(void);

#endif

