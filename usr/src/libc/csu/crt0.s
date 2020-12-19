
.globl	_start, environ, _exit, __exit

_start:
	li 	a0, 1
	la 	a1, _procname
	la	a2, environ
	jal 	main

	# jal	_exit
	# jal	__exit
	ret

_procname:  
.string "procname"

.comm	environ,4
