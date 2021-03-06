Results
=======

Procedure
---------

First, base64 decode the given file.

    $ base64 -d 6.txt > XOR-file

Now, find the keysize.

    $ ./keysize XOR-file
    The best found keysize was 29.

Finally, do the block transposition and solve individual single-byte XORs.

    $ ./block-transpose 29 XOR-file

    Initialized multibyte_key: '*****************************'.
    On block 0.
    New best score (2074)! (byte_key: ' ')
    New best score (2909)! (byte_key: '')
    New best score (3019)! (byte_key: 'E')
    New best score (3394)! (byte_key: 'H')
    New best score (3399)! (byte_key: 'P')
    New best score (4183)! (byte_key: 'R')
    New best score (5299)! (byte_key: 'T')
    Best score: 5299, for byte_key 'T'<0x54>.
    On block 1.
    New best score (1950)! (byte_key: ' ')
    New best score (3621)! (byte_key: ' ')
    New best score (3745)! (byte_key: 'd')
    New best score (4851)! (byte_key: 'e')
    Best score: 4851, for byte_key 'e'<0x65>.
    On block 2.
    New best score (525)! (byte_key: ' ')
    New best score (679)! (byte_key: '')
    New best score (788)! (byte_key: '')
    New best score (846)! (byte_key: '')
    New best score (1442)! (byte_key: '')
    New best score (1602)! (byte_key: '&')
    New best score (1683)! (byte_key: '3')
    New best score (2631)! (byte_key: '7')
    New best score (2887)! (byte_key: 'R')
    New best score (3808)! (byte_key: 'c')
    New best score (5406)! (byte_key: 'r')
    Best score: 5406, for byte_key 'r'<0x72>.
    On block 3.
    New best score (504)! (byte_key: ' ')
    New best score (938)! (byte_key: '')
    New best score (1663)! (byte_key: '')
    New best score (2540)! (byte_key: '')
    New best score (3135)! (byte_key: '"')
    New best score (4948)! (byte_key: '(')
    Best score: 4948, for byte_key '('<0x28>.
    On block 4.
    New best score (1031)! (byte_key: ' ')
    New best score (1562)! (byte_key: '')
    New best score (1884)! (byte_key: '')
    New best score (1916)! (byte_key: ' ')
    New best score (2244)! (byte_key: '&')
    New best score (3242)! (byte_key: ',')
    New best score (3272)! (byte_key: '`')
    New best score (3383)! (byte_key: 'c')
    New best score (3437)! (byte_key: 'd')
    New best score (5009)! (byte_key: 'i')
    Best score: 5009, for byte_key 'i'<0x69>.
    On block 5.
    New best score (830)! (byte_key: ' ')
    New best score (1318)! (byte_key: '')
    New best score (1571)! (byte_key: '')
    New best score (1758)! (byte_key: '!')
    New best score (2603)! (byte_key: '+')
    New best score (3318)! (byte_key: 'N')
    New best score (3517)! (byte_key: 'b')
    New best score (3582)! (byte_key: 'c')
    New best score (4059)! (byte_key: 'd')
    New best score (6253)! (byte_key: 'n')
    Best score: 6253, for byte_key 'n'<0x6e>.
    On block 6.
    New best score (1338)! (byte_key: ' ')
    New best score (2389)! (byte_key: '')
    New best score (2642)! (byte_key: ' ')
    New best score (4241)! (byte_key: '$')
    New best score (4750)! (byte_key: 'a')
    Best score: 4750, for byte_key 'a'<0x61>.
    On block 7.
    New best score (979)! (byte_key: ' ')
    New best score (1526)! (byte_key: '')
    New best score (1978)! (byte_key: ' ')
    New best score (2924)! (byte_key: '1')
    New best score (3493)! (byte_key: 'p')
    New best score (4079)! (byte_key: 'r')
    New best score (4879)! (byte_key: 't')
    Best score: 4879, for byte_key 't'<0x74>.
    On block 8.
    New best score (1582)! (byte_key: ' ')
    New best score (2101)! (byte_key: '
    ')
    New best score (2513)! (byte_key: ' ')
    New best score (2554)! (byte_key: '&')
    New best score (3810)! (byte_key: '*')
    New best score (3878)! (byte_key: 'k')
    New best score (5156)! (byte_key: 'o')
    Best score: 5156, for byte_key 'o'<0x6f>.
    On block 9.
    New best score (627)! (byte_key: ' ')
    New best score (765)! (byte_key: '')
    New best score (980)! (byte_key: '')
    New best score (1632)! (byte_key: '')
    New best score (1984)! (byte_key: '&')
    New best score (2873)! (byte_key: '7')
    New best score (3074)! (byte_key: 'R')
    New best score (3747)! (byte_key: 'c')
    New best score (3871)! (byte_key: 'n')
    New best score (5789)! (byte_key: 'r')
    Best score: 5789, for byte_key 'r'<0x72>.
    On block 10.
    New best score (2691)! (byte_key: ' ')
    New best score (4953)! (byte_key: ' ')
    Best score: 4953, for byte_key ' '<0x20>.
    On block 11.
    New best score (230)! (byte_key: ' ')
    New best score (441)! (byte_key: '')
    New best score (1114)! (byte_key: '
    ')
    New best score (1322)! (byte_key: '')
    New best score (1637)! (byte_key: '')
    New best score (1677)! (byte_key: '')
    New best score (2262)! (byte_key: '')
    New best score (3079)! (byte_key: 'B')
    New best score (3341)! (byte_key: 'C')
    New best score (3986)! (byte_key: 'D')
    New best score (4311)! (byte_key: 'R')
    New best score (5990)! (byte_key: 'X')
    Best score: 5990, for byte_key 'X'<0x58>.
    On block 12.
    New best score (1480)! (byte_key: ' ')
    New best score (1714)! (byte_key: '')
    New best score (2652)! (byte_key: '')
    New best score (2982)! (byte_key: ' ')
    New best score (3447)! (byte_key: '&')
    New best score (5261)! (byte_key: ':')
    Best score: 5261, for byte_key ':'<0x3a>.
    On block 13.
    New best score (2545)! (byte_key: ' ')
    New best score (4537)! (byte_key: ' ')
    Best score: 4537, for byte_key ' '<0x20>.
    On block 14.
    New best score (1560)! (byte_key: ' ')
    New best score (1739)! (byte_key: '')
    New best score (2670)! (byte_key: '')
    New best score (5424)! (byte_key: 'B')
    Best score: 5424, for byte_key 'B'<0x42>.
    On block 15.
    New best score (846)! (byte_key: ' ')
    New best score (968)! (byte_key: '')
    New best score (1323)! (byte_key: '')
    New best score (1836)! (byte_key: '')
    New best score (1985)! (byte_key: '!')
    New best score (2675)! (byte_key: '&')
    New best score (3673)! (byte_key: '7')
    New best score (5133)! (byte_key: 'r')
    Best score: 5133, for byte_key 'r'<0x72>.
    On block 16.
    New best score (1177)! (byte_key: ' ')
    New best score (1199)! (byte_key: '')
    New best score (1854)! (byte_key: '')
    New best score (2365)! (byte_key: ' ')
    New best score (3584)! (byte_key: ',')
    New best score (4059)! (byte_key: 'c')
    New best score (5323)! (byte_key: 'i')
    Best score: 5323, for byte_key 'i'<0x69>.
    On block 17.
    New best score (1084)! (byte_key: ' ')
    New best score (1568)! (byte_key: '')
    New best score (1807)! (byte_key: '')
    New best score (1899)! (byte_key: ' ')
    New best score (2265)! (byte_key: '!')
    New best score (3079)! (byte_key: '+')
    New best score (3362)! (byte_key: 'c')
    New best score (4125)! (byte_key: 'h')
    New best score (4150)! (byte_key: 'i')
    New best score (5033)! (byte_key: 'n')
    Best score: 5033, for byte_key 'n'<0x6e>.
    On block 18.
    New best score (415)! (byte_key: ' ')
    New best score (608)! (byte_key: '')
    New best score (2310)! (byte_key: '')
    New best score (4080)! (byte_key: '"')
    New best score (5115)! (byte_key: 'g')
    Best score: 5115, for byte_key 'g'<0x67>.
    On block 19.
    New best score (2587)! (byte_key: ' ')
    New best score (4956)! (byte_key: ' ')
    Best score: 4956, for byte_key ' '<0x20>.
    On block 20.
    New best score (1027)! (byte_key: ' ')
    New best score (1528)! (byte_key: '')
    New best score (2087)! (byte_key: ' ')
    New best score (2922)! (byte_key: '1')
    New best score (3243)! (byte_key: 'T')
    New best score (3898)! (byte_key: 'h')
    New best score (4304)! (byte_key: 'r')
    New best score (5885)! (byte_key: 't')
    Best score: 5885, for byte_key 't'<0x74>.
    On block 21.
    New best score (850)! (byte_key: ' ')
    New best score (1014)! (byte_key: '')
    New best score (1261)! (byte_key: '')
    New best score (1709)! (byte_key: '')
    New best score (1987)! (byte_key: '!')
    New best score (2108)! (byte_key: ''')
    New best score (3144)! (byte_key: '-')
    New best score (3354)! (byte_key: 'b')
    New best score (5333)! (byte_key: 'h')
    Best score: 5333, for byte_key 'h'<0x68>.
    On block 22.
    New best score (1860)! (byte_key: ' ')
    New best score (3727)! (byte_key: ' ')
    New best score (3825)! (byte_key: 'a')
    New best score (4642)! (byte_key: 'e')
    Best score: 4642, for byte_key 'e'<0x65>.
    On block 23.
    New best score (2614)! (byte_key: ' ')
    New best score (5239)! (byte_key: ' ')
    Best score: 5239, for byte_key ' '<0x20>.
    On block 24.
    New best score (965)! (byte_key: ' ')
    New best score (1543)! (byte_key: '')
    New best score (1672)! (byte_key: '')
    New best score (1971)! (byte_key: '!')
    New best score (2672)! (byte_key: '+')
    New best score (2861)! (byte_key: 'N')
    New best score (2892)! (byte_key: 'b')
    New best score (3547)! (byte_key: 'c')
    New best score (3837)! (byte_key: 'h')
    New best score (3839)! (byte_key: 'i')
    New best score (5123)! (byte_key: 'n')
    Best score: 5123, for byte_key 'n'<0x6e>.
    On block 25.
    New best score (1522)! (byte_key: ' ')
    New best score (1857)! (byte_key: '
    ')
    New best score (2398)! (byte_key: ' ')
    New best score (3318)! (byte_key: '*')
    New best score (3779)! (byte_key: 'c')
    New best score (5395)! (byte_key: 'o')
    Best score: 5395, for byte_key 'o'<0x6f>.
    On block 26.
    New best score (950)! (byte_key: ' ')
    New best score (956)! (byte_key: '')
    New best score (1209)! (byte_key: '')
    New best score (1591)! (byte_key: '')
    New best score (1849)! (byte_key: ' ')
    New best score (1895)! (byte_key: '!')
    New best score (2000)! (byte_key: '&')
    New best score (2925)! (byte_key: ',')
    New best score (2969)! (byte_key: 'c')
    New best score (3634)! (byte_key: 'd')
    New best score (3785)! (byte_key: 'h')
    New best score (4566)! (byte_key: 'i')
    Best score: 4566, for byte_key 'i'<0x69>.
    On block 27.
    New best score (1263)! (byte_key: ' ')
    New best score (1602)! (byte_key: '')
    New best score (2458)! (byte_key: '')
    New best score (3230)! (byte_key: ''')
    New best score (4378)! (byte_key: '6')
    New best score (4810)! (byte_key: 's')
    Best score: 4810, for byte_key 's'<0x73>.
    On block 28.
    New best score (1527)! (byte_key: ' ')
    New best score (2791)! (byte_key: ' ')
    New best score (3232)! (byte_key: 'a')
    New best score (3620)! (byte_key: 'b')
    New best score (4113)! (byte_key: 'c')
    New best score (4914)! (byte_key: 'e')
    Best score: 4914, for byte_key 'e'<0x65>.
    File: 'XOR-file'.
    Keysize: 29.
        Found multibyte key: 'Ter(inator X: Bring the noise'.
    Ter(inator X: Bring the noise

The XOR scoring isn't perfect, (`'(' => 'm'`), but it's pretty good.

The key is `Terminator X: Bring the noise`.

Decryption!
-----------

    $ ../5/repeat-xor "Terminator X: Bring the noise" < XOR-file

    I'm back and I'm ringin' the bell 
    A rockin' on the mike while the fly girls yell 
    In ecstasy in the back of me 
    Well that's my DJ Deshay cuttin' all them Z's 
    Hittin' hard and the girlies goin' crazy 
    Vanilla's on the mike, man I'm not lazy. 

    I'm lettin' my drug kick in 
    It controls my mouth and I begin 
    To just let it flow, let my concepts go 
    My posse's to the side yellin', Go Vanilla Go! 

    Smooth 'cause that's the way I will be 
    And if you don't give a damn, then 
    Why you starin' at me 
    So get off 'cause I control the stage 
    There's no dissin' allowed 
    I'm in my own phase 
    The girlies sa y they love me and that is ok 
    And I can dance better than any kid n' play 

    Stage 2 -- Yea the one ya' wanna listen to 
    It's off my head so let the beat play through 
    So I can funk it up and make it sound good 
    1-2-3 Yo -- Knock on some wood 
    For good luck, I like my rhymes atrocious 
    Supercalafragilisticexpialidocious 
    I'm an effect and that you can bet 
    I can take a fly girl and make her wet. 

    I'm like Samson -- Samson to Delilah 
    There's no denyin', You can try to hang 
    But you'll keep tryin' to get my style 
    Over and over, practice makes perfect 
    But not if you're a loafer. 

    You'll get nowhere, no place, no time, no girls 
    Soon -- Oh my God, homebody, you probably eat 
    Spaghetti with a spoon! Come on and say it! 

    VIP. Vanilla Ice yep, yep, I'm comin' hard like a rhino 
    Intoxicating so you stagger like a wino 
    So punks stop trying and girl stop cryin' 
    Vanilla Ice is sellin' and you people are buyin' 
    'Cause why the freaks are jockin' like Crazy Glue 
    Movin' and groovin' trying to sing along 
    All through the ghetto groovin' this here song 
    Now you're amazed by the VIP posse. 

    Steppin' so hard like a German Nazi 
    Startled by the bases hittin' ground 
    There's no trippin' on mine, I'm just gettin' down 
    Sparkamatic, I'm hangin' tight like a fanatic 
    You trapped me once and I thought that 
    You might have it 
    So step down and lend me your ear 
    '89 in my time! You, '90 is my year. 

    You're weakenin' fast, YO! and I can tell it 
    Your body's gettin' hot, so, so I can smell it 
    So don't be mad and don't be sad 
    'Cause the lyrics belong to ICE, You can call me Dad 
    You're pitchin' a fit, so step back and endure 
    Let the witch doctor, Ice, do the dance to cure 
    So come up close and don't be square 
    You wanna battle me -- Anytime, anywhere 

    You thought that I was weak, Boy, you're dead wrong 
    So come on, everybody and sing this song 

    Say -- Play that funky music Say, go white boy, go white boy go 
    play that funky music Go white boy, go white boy, go 
    Lay down and boogie and play that funky music till you die. 

    Play that funky music Come on, Come on, let me hear 
    Play that funky music white boy you say it, say it 
    Play that funky music A little louder now 
    Play that funky music, white boy Come on, Come on, Come on 
    Play that funky music 

