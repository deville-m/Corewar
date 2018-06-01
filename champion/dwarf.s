    ;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
    ;;          File: dwarf.s             ;;
    ;;        Desc: 42 Team warrior       ;;
    ;;        Created: May 31, 2018       ;;
    ;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
    .name "dwarf"
    .comment "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳"

_stub:   st     r1,6            ; .eh_frame_hdr
         live   %42
         ld     %480,r10		; Const offset
         ld     %478,r14
         fork   %:0x02
         fork   %:0x04

0x01:    st     r1,95           ; .init ──────┐
         ldi    %:l1v3,%-3,r5   ; .fortress_start
         and    r16,r16,r16
         zjmp   %:l1v3

0x02:    fork   %:0x03          ; mmmmmh
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
         live   %42
         zjmp   %:l1v3

l1v3:    live  %42
         sti   r5,r10,r11		; Ecriture
         zjmp  %478            ; 0x478
