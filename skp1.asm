; Simple example demonstrating skip on 1 instruction

          org      4
start     skp1     1,arg1
          jpd      no
          load     a c=$ff
          store    a o
          halt
no        load     a c=$81
          store    a o
          halt
arg1      data     $ff
          end      start

