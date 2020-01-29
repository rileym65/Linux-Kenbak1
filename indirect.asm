          org      4
start     load     a (arg1)      ; load A from indirect address
          store    a o           ; write to lamps
          halt                   ; and stop
arg1      data     arg2          ; indirect pointer

          org      $40
arg2      data     $a5

          end      start

