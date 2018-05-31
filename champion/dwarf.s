	;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
	;;          File: dwarf.s             ;;
	;;        Desc: 42 Team warrior       ;;
	;;        Created: May 31, 2018       ;;
	;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
	.name "dwarf"
	.comment "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳"

_stub:  sti r1,%:b0i,%1         ; .eh_frame_hdr
    	ld %0, r16
		ld %10, r8
		xor r2,r2,r2

w00t:	zjmp %:p0p              ; .init ──────┐
p0p:    zjmp %:t3k0             ; .fortress_start

t3k0:	ld 9,r4
		ld 900,r5
		sti r4,r5,%0
		sub r5,r8,r5
		ld 0,r2
		fork %:b0i
		zjmp %:t3k0

b0i:    live %1337
        zjmp %:w00t             ; .init ──────╯
