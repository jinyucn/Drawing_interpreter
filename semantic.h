#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "parse.h"
#include <windows.h>
#include <wingdi.h>

extern HDC hDC;
/*#ifdef _BC_COMPLIER
#include <graphics.h>
#include <conio.h>
#endif // _BC_COMPLIER
*/

#define red RGB(255,0,0)
#define black RGB(0,0,0)
#define green RGB(0,255,0)
#define blue RGB(0,0,255)
extern void DrawPixel(unsigned long, unsigned long);
extern double GetExpValue(ExprNode *);
extern void DrawLoop(double start, double End, double step, ExprNode *, ExprNode *);
extern void Deltree(ExprNode *);
extern double parameter, locx, locy, scax, scay, rot_angle;
extern COLORREF draw_color;
#endif // SEMANTIC_H
