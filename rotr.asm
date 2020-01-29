        org     4
start   load    a c=1
loop    store   a o
        rotr    a 1
        load    b c=64
delay   sub     b c=1
        jpd     b nz,delay
        jpd     loop
        end     start

