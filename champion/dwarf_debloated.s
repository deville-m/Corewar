.name "dwarf"
.comment "The quieter you become, the more you will be able to ear"

_stub:   live   %42
         ld     %480,r10
         fork   %:0x02
         fork   %:0x04

0x01:    st     r1,90
         ldi    %:l1v3,%-3,r5
         and    r16,r16,r16
         zjmp   %:l1v3

0x02:    fork   %:0x03
         ld     %4,r11
         ldi    %:l1v3,%1,r5
         and    r16,r16,r16
         zjmp   %:l1v3

0x03:    ld     %8,r11
         ldi    %:l1v3,%5,r5
         and    r16,r16,r16
         zjmp   %:l1v3

0x04:    ld     %12,r11
         ldi    %:l1v3,%9,r5
         and    r16,r16,r16
         zjmp   %:l1v3

l1v3:    live  %42
         sti   r5,r10,r11
         zjmp  %478
