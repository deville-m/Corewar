	;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
	;;          File: dwarf.s             ;;
	;;        Desc: 42 Team warrior       ;;
	;;        Created: May 31, 2018       ;;
	;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
	.name "dwarf"
	.comment "╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳╳"

_stub:  sti r1,%:b0i,%1         ; .eh_frame_hdr
        ld %0, r16

w00t:	zjmp %:p0p              ; .init ──────┐
p0p:    zjmp %:b0i

b0i:    live %1337              ;
        zjmp %:w00t             ; .init ──────╯
