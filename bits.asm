          org    4
start     load   a c=0        ; clear bit position
loop1     load   b c=$42      ; need SET1 command
          add    b a          ; add in bit position
          store  b setlp      ; write modified command
setlp     set1   0,o          ; turn on a light
          jmd    delay        ; call delay subroutine
          add    a c=8        ; increment bit position
          and    c=$38        ; mask out non-bit position bits
          jpd    a nz,loop1   ; loop back if more to set
loop2     load   b c=$02      ; need SET0 command
          add    b a          ; add in bit position
          store  b reslp      ; write modified command
reslp     set0   0,o          ; turn off a light
          jmd    delay        ; call delay subroutine
          add    a c=8        ; increment bit position
          and    c=$38        ; mask out non-bit position bits
          jpd    a nz,loop2   ; loop back if more to reset
          jpd    loop1        ; jump back to set loop
          halt
delay     data   0            ; Space for return address
          load   b c=32       ; delay constant
delaylp   sub    b c=1        ; subtract 1
          jpd    b nz,delaylp ; loop until delay count is zero
          jpi    (delay)      ; then return to caller
          end    start

