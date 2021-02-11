# UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details.
# Changes: Copyright (c) 1999 Robert Nordier. All rights reserved.

# C return sequence which
# sets errno, returns -1.

.globl  errno
.comm	errno,4

.globl	cerror
cerror:
	#lw a0, -1
	#break 1234;
	ret
	# mov	eax,_errno
	# mov	$-1,eax
