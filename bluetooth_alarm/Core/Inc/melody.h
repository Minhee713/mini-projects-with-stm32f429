/*
 * melody.h
 *
 *  Created on: Nov 17, 2023
 *      Author: 권민희
 */

#ifndef INC_MELODY_H_
#define INC_MELODY_H_

#define REST 0
#define C4 3822
#define D4 3405
#define E4 3033
#define F4 2863
#define G4 2551
#define A4 2272
#define B4 2024
#define C5 1911
#define D5 1702
#define E5 1516
#define F5 1431
#define G5 1275
#define A5 1136
#define B5 1012
#define C6 955
#define D6 851
#define E6 758
#define F6 715
#define G6 637
#define A6 568
#define B6 506
#define C7 477




#define C	262  	// do
#define D	294		// re
#define E	330		// mi
#define F	349		// pa
#define G	392		// sol
#define A	440		// la
#define B	494		// si
#define C1	523		// do
#define D1	587		// re
#define E1	659		// mi
#define F1  698		// pa
#define G1  783		// sol
#define A1  880		// la
#define B1  987		// si


typedef struct {
	uint16_t freq;
	uint16_t delay;
} _BUZZER;

uint8_t start = 0;
uint8_t seq = 0;
uint8_t stop = 0;

_BUZZER schoolBell[] = {
    {G, 1}, {E, 1}, {A, 1}, {A, 1},				//4
    {G, 1}, {G, 1}, {E, 2},						//3
    {G, 1}, {G, 1}, {E, 1}, {E, 1}, {D, 3},	//5
    {G, 1}, {G, 1}, {A, 1}, {A, 1},				//4
    {G, 1}, {G, 1}, {E, 2},						//3
    {G, 1}, {E, 1}, {D, 1}, {E, 1}, {C, 3}		//5
};

_BUZZER jingleBell[] = {
		 {C, 1}, {A, 2}, {G, 1}, {F, 1}, {C, 4},
		 {C, 1}, {A, 2}, {G, 1}, {F, 1}, {D, 4},
		 {D, 1}, {B, 2}, {A, 1}, {G, 1}, {E, 4},
		 {C1, 1}, {C1, 1}, {B, 1}, {G, 1}, {A, 4}, {F, 3},
		 {C, 1}, {A, 2}, {G, 1}, {F, 1}, {C, 4},
		 {C, 1}, {A, 2}, {G, 1}, {F, 1}, {D, 4},
		 {D, 1}, {B, 2}, {A, 1}, {G, 1},
		 {C1, 1}, {C1, 1}, {C1, 1}, {C1, 1},
		 {D1, 2}, {C1, 1}, {B, 1}, {G, 1}, {F, 4},
		 {A, 2}, {A, 2}, {A, 4},
		 {A, 2}, {A, 2}, {A, 4},
		 {A, 1}, {C1, 1}, {F, 3}, {G, 1}, {A, 2},
		 {B, 1}, {B, 1}, {B, 1}, {B, 1},
		 {B, 1}, {A, 1}, {A, 1}, {A, 2},
		 {A, 1}, {G, 1}, {G, 2},
		 {F, 1}, {G, 2}, {C1, 3},
		 {A, 2}, {A, 2}, {A, 4},
		 {A, 2}, {A, 2}, {A, 4},
		 {A, 1}, {C1, 1}, {F, 3}, {G, 1}, {A, 2},
		 {B, 1}, {B, 1}, {B, 1}, {B, 1},
		 {B, 1}, {A, 1}, {A, 1}, {A, 2},
		 {C1, 1}, {C1, 1}, {B, 2}, {G, 1}, {F, 4}
};


_BUZZER silentNight[] = {

		{G, 8}, {A, 2}, {G, 2}, {E, 3},
		{G, 8}, {A, 2}, {G, 2}, {E, 3},
		{D1, 8}, {D1, 8}, {B, 4},
		{C1, 8}, {C1, 8}, {G, 4},
		{A, 4}, {A, 4}, {C1, 2}, {B, 1}, {A, 1},
		{G, 1}, {A, 2}, {G, 1}, {E, 4},
		{A, 4}, {A, 4}, {C1, 2}, {B, 1}, {A, 1},
		{G, 1}, {A, 2}, {G, 1}, {E, 4},
		{D1, 8}, {D1, 8}, {F1, 8}, {D1, 3}, {B, 1}, {C1, 3}, {E1, 8},
		{C1, 4}, {G, 4}, {E, 4}, {G, 1}, {F, 2}, {D, 2}, {C, 8}

};









#endif /* INC_MELODY_H_ */
