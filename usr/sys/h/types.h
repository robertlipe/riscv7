/* UNIX V7 source code: see /COPYRIGHT or www.tuhs.org for details. */
/* Changes: Copyright (c) 1999 Robert Nordier. All rights reserved. */

#pragma once

typedef	long       	daddr_t;  	/* disk address */
typedef	char *     	caddr_t;  	/* core address */
typedef	unsigned short	ino_t;     	/* i-node number */
//typedef	__time_t_ time_t;   	/* a time */
typedef unsigned long long	 time_t;    /* a time */
//typedef	long        	label_t[13]; 	/* program status */
typedef	short      	dev_t;    	/* device code */
typedef	long       	off_t;    	/* offset in file */
	/* selectors and constructor for device code */
#define	major(x)  	(int)(((unsigned)x>>8))
#define	minor(x)  	(int)(x&0377)
#define	makedev(x,y)	(dev_t)((x)<<8 | (y))

typedef __INT32_TYPE__    int32_t;
typedef __INT64_TYPE__    int64_t;
typedef __UINT32_TYPE__   uint32_t;
typedef __UINT64_TYPE__   uint64_t;

extern int panic(const char* message, ...);
#define	KASSERT(expression, ...) do { \
        if ((!(expression))) {  \
		panic(__VA_ARGS__); \
        } \
      } while (0)
