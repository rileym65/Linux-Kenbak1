        org      4
start   load     a c=5     ; Load A and B with values
        load     b c=6     ; for subroutine to work on
        jmd      adder     ; call subroutine adder
        store    a o       ; write result to lamps
        halt               ; and stop

        org      $40
adder   data     0         ; return address is stored here
        add      a b       ; add B to A
        jpi      (adder)   ; Return to caller
        halt               ; this will not be executed
        end      start
