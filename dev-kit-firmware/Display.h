#ifndef __DISPLAY_H__
#define __DISPLAY_H__


namespace Display {

/** Displays a page buffer (of size #N_ROWS * #N_COLUMNS) by controlling
 * the rotors and locks.

per cell:

 first rotor:
          b t
0 : 0 : 0b000
1 : 3 : 0b011
2 : 7 : 0b111
3 : 5 : 0b101
4 : 6 : 0b110
5 : 2 : 0b010
6 : 1 : 0b001
7 : 4 : 0b100

 second rotor:
          b t
0 : 0 : 0b000
1 : 6 : 0b110
2 : 7 : 0b111
3 : 5 : 0b101
4 : 3 : 0b011
5 : 2 : 0b010
6 : 4 : 0b100
7 : 1 : 0b001

*/

void set_row (const uint8_t row, const uint8_t buffer[N_COLUMNS]) {
    for (int i = 0; i < N_COLUMNS; ++i) {
        Serial1.print(buffer[i]);
    }
    Serial1.println();
}

void set (const uint8_t buffer[]) {
    for (uint8_t row = 0; row < N_ROWS; row++) {
        set_row(row, &buffer[row * N_COLUMNS]);
    }
}

void setup() {
    Serial1.begin(115200);
}


}// namespace Display
#endif// __DISPLAY_H__
