Result: Line `204`
==================

    $ ./ecb-detect 8.txt > ecb-info.log
    Best found candidate for being encrypted with ECS (line 204):
    06df04188832b10afff94209d2aa1c8a123702de28234dcd3e0a7d36c1aa8449e6fa55e3e1e3d77d8424e87a45e38697755f84c49a99473797268113eb69098888947526035b246d00a630f6201ecc4075d8aa6604de73e2119e264e4c96751f2a67a2e46cf467a0df8f0520bcf4762b2715aba266d9b3f5e8fa67d12f9caac928b07ac3be99f41120655aa77f6433fc264673a92929e792187f87b5fda50cf2

Grepping through `ecb-info.log` for anything greater than zero, we find:

    line 132: count_equal == 12.
    line 133: count_equal == 12.
    line 204: count_equal == 30.

Even though `8` was used as the `BLOCK_SIZE`, instead of the standard `16`, I am
confident that line 204 of `8.txt` is the AES-ECB line, because when ran with
`16` as the `BLOCK_SIZE`, we get:

    line 132: count_equal == 6.
    line 133: count_equal == 6.

This is a tie, when we know there is only one line that was encrypted in ECB.

