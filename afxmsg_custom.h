//
// Created by maximus on 4/10/2024.
//

#include "afxmsg_.h"

#define ON_WM_MOUSEHOVER() \
	{ WM_MOUSEHOVER, 0, 0, 0, AfxSig_lwl, \
		(AFX_PMSG)(AFX_PMSGW) \
		(static_cast< int (AFX_MSG_CALL CWnd::*)(int, int) > ( &ThisClass :: OnMouseHover)) },

#define ON_WM_MOUSELEAVE() \
	{ WM_MOUSELEAVE, 0, 0, 0, AfxSig_lwl, \
		(AFX_PMSG)(AFX_PMSGW) \
		(static_cast< int (AFX_MSG_CALL CWnd::*)(int, int) > ( &ThisClass :: OnMouseLeave)) },

