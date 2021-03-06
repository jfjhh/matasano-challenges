Test Results
============

Using the created program, I can do this:

	for i in {0..255}; do
		./byte-xor 2> /dev/null;
		echo;
	done | sort | uniq -c | sort -nr

…and obtain this list of possible plaintext messages:

     63 cOOKING mcS LIKE A POUND OF BACON
     43 w[[_]ZSywGX]_QUD[AZP[RVUW[Z
     40 gKKOMJCigWHMOAETKQJ@KBFEGKJ
     28 Cooking MC's like a pound of bacon
     25 uYY]_XQ{uEZ_]SWFYCXRYPTWUYX
     12 eIIMOHAkeUJOMCGVISHBI@DGEIH
      7 r^^ZX_V|rB]XZTPA^D_U^WSPR^_
      7 p\\XZ]T~p@_ZXVRC\F]W\UQRP\]
      7 Ieeacdm*GI-y*fcao*k*zedn*el*hkied
      7 dHHLNI@jd TKNLBFWHRICHAEFDHI
      5 vZZ^\[RxvFY\^PTEZ@[QZSWTVZ[
      3 fJJNLKBhfVILN@DUJPKAJCGDFJK
      3 Ammikle"OA%q"nkig"c"rmwlf"md"`caml
      2 kGGCAFOek[DACMIXG]FLGNJIKGF
      1 tXX\^YPztD[^\RVGXBYSXQUVTXY
      1 Txx|~yp7ZT0d7{~|r7v7gxbys7xq7uvtxy
      1 Occgebk,AO+,`egi,m,|cybh,cj,nmocb
      1 Jffb`gn)DJ.z)e`bl)h)yf|gm)fo)khjfg

It is clear that the message is `Cooking MC's like a pound of bacon`.

**Done.**

