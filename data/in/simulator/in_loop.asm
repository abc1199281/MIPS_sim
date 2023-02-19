    lw  $s1, $zero, 0 # cnt_diff = 1
    lw  $s2, $zero, 4 # in .hex, N = 10(dec), a(hex)
Loop:
    add  $s0, $s1, $s0  # cnt+=cnt_diff
    add  $s3, $s3, $s0  # x+=cnt;
    beq  $s0, $s2, Exit # Exit if cnt==N, else go to Loop.
    j Loop
Exit:
    sw $s3, $zero, 8 # x==37(hex), 55(dec)
