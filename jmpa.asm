; this program demonstrates jumping to an address in the A
; register.  Writing A into P will cause a jump to the address in 
; A plus 2.
          org      4
start     load     a c=$10         ; Destination address-2
          store    a p             ; Store into program counter
          halt                     ; should not hit this

          org      $10
          jpd      no              ; Should not hit this
          load     a c=$ff         ; Want to turn on all lights
          store    a o             ; write to lamps
          halt                     ; and stop
no        load     a c=$81         ; show error code
          store    a o             ; write to lamps
          halt                     ; and stop
          end      start

