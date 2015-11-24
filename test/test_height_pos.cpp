#include <stdint.h>
#include <stdio.h>

static const int64_t CENT = 1000000;

inline int64_t GetDynamicBlockHeightPoSAward(uint32_t nHeight) {
    uint32_t current_year = nHeight / ((60 * 60 * 24 * 365) / 128) + 1;

    if (current_year <= 2) {
        return 20 * CENT;
    } else if (current_year <= 4) {
        return 10 * CENT;
    } else if (current_year <= 6) {
        return 5 * CENT;
    } else if (current_year <= 8) {
        return (uint64_t)(2.5 * CENT);
    } else if (current_year <= 10) {
        return (uint64_t)(1.25 * CENT);
    } else if (current_year <= 12) {
        return (uint64_t)(0.75 * CENT);
    } else if (current_year <= 14) {
        return (uint64_t)(0.5 * CENT);
    } else if (current_year <= 15) {
        return (uint64_t)(0.25 * CENT);
    }
    return (uint64_t)(0.00001 * CENT);
}


int main() {
	int64_t old = -1;

	for (uint32_t i = 0; i < 2000000000; i++) {
		if (GetDynamicBlockHeightPoSAward(i) != old) {
			old = GetDynamicBlockHeightPoSAward(i);
			printf("height: %u, award: %ld\n", i, old);
		}
	}
}
