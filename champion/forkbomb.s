.name ".name .name .name ....."
.comment "fork you"

st r1, 14
and r2, %0, r2
ret: live %1
fork %:ret
zjmp %:ret
