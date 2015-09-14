Results
=======

XOR'd line in file: `line 170`.
XOR byte: `0x35`.
Decoded message: `Now that the party is jumping`.

* * *

Procedure
---------

Command:
```
make && valgrind ./xor-detect 4-corrected.txt
```

Output:
```
gcc --std=c99 -g -Wall -Werror -pedantic -O2 -I. -I.. -lm -o xor-detect xor-detect.c ../strtohex.c
==29964== Memcheck, a memory error detector
==29964== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==29964== Using Valgrind-3.10.0 and LibVEX; rerun with -h for copyright info
==29964== Command: ./xor-detect 4-corrected.txt
==29964== 
The XOR'd line is line 170, the byte is 0x35.
Original string: "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f".
Decoded string: "Now that the party is jumping
".
==29964== 
==29964== HEAP SUMMARY:
==29964==     in use at exit: 0 bytes in 0 blocks
==29964==   total heap usage: 657 allocs, 657 frees, 20,248 bytes allocated
==29964== 
==29964== All heap blocks were freed -- no leaks are possible
==29964== 
==29964== For counts of detected and suppressed errors, rerun with: -v
==29964== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

* * *

**Done.**

