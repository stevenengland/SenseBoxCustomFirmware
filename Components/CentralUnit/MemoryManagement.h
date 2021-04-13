#pragma once

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char* __brkval;  // NOLINT(bugprone-reserved-identifier)
#endif  // __arm__