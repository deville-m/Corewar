	;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
	;;          File: dwarf.s             ;;
	;;        Desc: 42  Team warrior      ;;
	;;        Created: May 31, 2018       ;;
	;; -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ ;;
	.name "dwarf"
	.comment " 🤔 "

	sti r1,%:b0i,%1
    ld %0,r16					; Update carry

w00t:	zjmp %:p0p				; Kernel

p0p:	zjmp %:b0i
								; Fork aref
b0i:	live %1337				; Live reference
		zjmp %:w00t				; Return main thread
