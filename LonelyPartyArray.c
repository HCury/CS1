
================================================================
DID YOU KNOW?
================================================================

  The grading criteria and final test cases used to grade each
  assignment always get posted in Webcourses, along with a
  report detailing test case pass rates, difficulty rating and
  hours spent distributions, and a variety of other statistics.

================================================================
curyhenrique_4159868_65061081_LonelyPartyArray.c
================================================================

  [Unit Test] grading-testcase01.c: PASS
  [Unit Test] grading-testcase02.c: PASS
  [Unit Test] grading-testcase03.c: PASS
  [Unit Test] grading-testcase04.c: PASS
  [Unit Test] grading-testcase05.c: PASS
  [Unit Test] grading-testcase06.c: PASS
  [Unit Test] grading-testcase07.c: PASS
  [Unit Test] grading-testcase08.c: PASS
  [Unit Test] grading-testcase09.c: PASS
  [Unit Test] grading-testcase10.c: PASS
  [Unit Test] grading-testcase11.c: PASS
  [Unit Test] grading-testcase12.c: PASS
  [Unit Test] grading-testcase13.c: PASS
  [Unit Test] grading-testcase14.c: PASS
  [Memleak Test] grading-testcase15-valgrind.c: PASS
  [Memleak Test] grading-testcase16-valgrind.c: PASS
  [Bonus Test] grading-testcase17-clone-bonus.c: fail ** (does not compile)
  [Memleak Test] grading-testcase18-clone-bonus-valgrind.c: fail ** (does not compile)

================================================================
Status Report (FYI): Compiles Without Warnings?
================================================================

  Success!

================================================================
Filename Check: LonelyPartyArray.c
================================================================

  Success! (5/5 pts)

================================================================
Final Report
================================================================

  Passed 16/18 test cases. (80.0/75.0 testcase pts)

  Additional points will be awarded based on the grading
  criteria posted in Webcourses, and final grades will be posted
  by the TAs within a week or so, after the they've had a chance
  to manually review everyone's code.

================================================================
Compile Error Log
================================================================
==3760== Memcheck, a memory error detector
==3760== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==3760== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==3760== Command: ./a.out
==3760== 
==3760== 
==3760== HEAP SUMMARY:
==3760==     in use at exit: 0 bytes in 0 blocks
==3760==   total heap usage: 9 allocs, 9 frees, 324,128 bytes allocated
==3760== 
==3760== All heap blocks were freed -- no leaks are possible
==3760== 
==3760== For counts of detected and suppressed errors, rerun with: -v
==3760== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
/tmp/cckZiiNB.o: In function `main':
grading-testcase17-clone-bonus.c:(.text+0x4e9): undefined reference to `cloneLonelyPartyArray'
collect2: error: ld returned 1 exit status
/tmp/ccOv5muK.o: In function `main':
grading-testcase18-clone-bonus-valgrind.c:(.text+0x4e9): undefined reference to `cloneLonelyPartyArray'
collect2: error: ld returned 1 exit status
/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o: In function `_start':
(.text+0x20): undefined reference to `main'
collect2: error: ld returned 1 exit status


