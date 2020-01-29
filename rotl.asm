        org     4
start   load    a c=1        ; start with rightmost lamp
loop    store   a o          ; store on lamps
        rotl    a 1          ; rotate lamps to the left
        load    b c=64       ; delay count
delay   sub     b c=1        ; subtract from delay count
        jpd     b nz,delay   ; jump if delay count is not zero
        jpd     loop         ; loop back to main loop
        end     start

