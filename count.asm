        org    4          ; move past registers
start   load   a c=0      ; set initial vlaue
loop    store  a o        ; write to output register
        add    a c=1      ; increment count
        jpd    loop       ; and loop back
        end    start

