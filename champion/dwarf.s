	;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
	;;          File: dwarf.s             ;;
	;;        Desc: 42 Team warrior       ;;
	;;        Created: May 31, 2018       ;;
	;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
	.name "dwarf"
	.comment "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳"

_stub:  sti r1,%:b0i,%1         ; .eh_frame_hdr
        sti r11, %:l1v3, %1
        ld %0, r16
        ld %10, r8
        xor r2,r2,r2

w00t:	zjmp %:p0p              ; .init ──────┐
p0p:    zjmp %:t3k0             ; .fortress_start

t3k0:	fork %:l1v3
        fork %:t0rp
        zjmp %:b0i

t0rp:   sti r4, r5, r7
        zjmp %:t0rp

l1v3:   live %1337
        zjmp %:l1v3

b0i:    fork %:l1v3
        zjmp %:w00t             ; .init ──────╯
