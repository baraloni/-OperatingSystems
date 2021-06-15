#include "VirtualMemory.h"
#include "PhysicalMemory.h"

//----------------------------Private Function

uint64_t translate(uint64_t toTrans){
    uint64_t doNotEvict[TABLES_DEPTH];  //TODO: Verify that this is the right array length
    uint64_t phisicalAddr;
    // TODO: Do.
    return phisicalAddr;
}

uint64_t findFrame(const uint64_t& doNotDelete){ // Gets an array of frames it shouldn't evict.
    uint64_t phisicalAddr;
    // Max cyclic score
    // Max frame with max cyclic score
    // Max frame index
    // TODO: Do.
    return phisicalAddr;
}

//----------------------------- Public Functions
void clearTable(uint64_t frameIndex) {
    for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
        PMwrite(frameIndex * PAGE_SIZE + i, 0);
    }
}

void VMinitialize() {
    clearTable(0);
}

int VMread(uint64_t virtualAddress, word_t* value) {
    return 1;
}


int VMwrite(uint64_t virtualAddress, word_t value) {
    return 1;
}