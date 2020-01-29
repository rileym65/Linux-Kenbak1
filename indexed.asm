          org     4
start     load    x c=2     ; set index register
          load    a arg1,x  ; load using index register
          store   a o       ; write value to lamps
          halt              ; and halt
arg1      data    1
          data    2
          data    3
          data    4
          data    5
          end     start

