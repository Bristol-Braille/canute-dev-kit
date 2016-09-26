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
static uint8_t state[N_ROWS][N_COLUMNS] = {};

void print_state() {
    for (int row = 0; row < N_ROWS; ++row) {
        for (int column = 0; column < N_COLUMNS; ++column) {
            Serial1.print(state[row][column]);
        }
        Serial1.println();
    }
    Serial1.println();
}

void set_row (const uint8_t row, const uint8_t buffer[N_COLUMNS]) {
    delay(200);
    memset(state[row], 0, N_COLUMNS);
    print_state();
    delay(800);
    memcpy(state[row], buffer, N_COLUMNS);
    print_state();
}

void set (const uint8_t buffer[]) {
    for (int row = 0; row < N_ROWS; row++) {
        set_row(row, &buffer[row * N_COLUMNS]);
    }
}

void setup() {
    Serial1.begin(115200);
}


}// namespace Display
#endif// __DISPLAY_H__
