; Simple program to demonstrate turning bits on and off
        org      4
start   set1     2,o     ; turn on lamp 2
        set1     0,o     ; turn on lamp 0
        set1     1,o     ; turn on lamp 1
        set0     1,o     ; turn off lamp 1
        halt             ; and stop
        end      start

