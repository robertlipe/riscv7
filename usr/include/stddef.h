// Placeholder
#pragma once

typedef __SIZE_TYPE__ size_t;
typedef signed int ptrdiff_t;
#define NULL ((void *)0)

#undef offsetof
#define offsetof(t,m) ((size_t)&((t *)0)->m)
