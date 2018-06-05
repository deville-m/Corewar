.name "zork releaded"
.comment "I'M ALIIIIVE"

l2:		add r1, r1, r1
		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
