
/*********************************************************
//
//	SKNODE.H
//
//	SK-Machine
//	Kombinatorska SK masina
//
//	Node structures definitions
//
//	Copyright (c) 1995 by Sasa Malkov
//	All Rights Reserved.
//
//*********************************************************/

#ifndef __SKNODE_H
#define __SKNODE_H

struct cell_struct {
	char	lefttype;
	char	righttype;
	unsigned short refcount;
	struct cell_struct *left;
	struct cell_struct *right;
	};
typedef struct cell_struct Cell;

#define SKTYPE_EMPTY	0
#define SKTYPE_POINTER	1
#define SKTYPE_NUMBER	2
#define SKTYPE_SYSTEMOP	3
#define SKTYPE_USEROP	4
#define SKTYPE_TOTAL	5

#define get_left_ptr(c) ((Cell*)((c)->left))
#define get_right_ptr(c) ((Cell*)((c)->right))

/* #ifndef __SKNODE_H */
#endif
