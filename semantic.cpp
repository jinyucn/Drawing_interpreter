#include "semantic.h"
extern void DrawPixel(unsigned long, unsigned long);
extern double GetExpValue(ExprNode *);
extern void DrawLoop(double start, double End, double step, ExprNode *, ExprNode *);
extern void Deltree(ExprNode *);
void cacux_y(ExprNode *xnode, ExprNode *ynode, double &x, double &y);

void DrawPixel(unsigned long x, unsigned long y) {
	SetPixel(hDC, x, y, draw_color);
}
double GetExpValue(ExprNode *node3) {
	switch (node3->OpCode) {
	case PLUS:
		return GetExpValue(node3->Content.CaseOperator.Left) + GetExpValue(node3->Content.CaseOperator.Right);

	case MINUS:
		return GetExpValue(node3->Content.CaseOperator.Left) - GetExpValue(node3->Content.CaseOperator.Right);

	case MUL:
		return GetExpValue(node3->Content.CaseOperator.Left) * GetExpValue(node3->Content.CaseOperator.Right);

	case DIV:
		return GetExpValue(node3->Content.CaseOperator.Left) / GetExpValue(node3->Content.CaseOperator.Right);

	case POWER:
		return pow(GetExpValue(node3->Content.CaseOperator.Left), GetExpValue(node3->Content.CaseOperator.Right));
	case FUNC:
		return (*node3->Content.CaseFunc.MathFuncPtr)(GetExpValue(node3->Content.CaseFunc.Child));
	case CONST_ID:
		//   printf("value = %f",node3->content.value);
		return node3->Content.CaseConst;
	case T:
		return *(node3->Content.CaseParmPtr);
	default:
		return 0.0;
	}
}
void DrawLoop(double start, double End, double step, ExprNode *nox, ExprNode *noy) {
    cout<<start<<" "<<End<<" "<<step<<endl;
	extern double parameter;
	double px = 0;
	double py = 0;
	printf("\n enter in loop\n");
	for (parameter = start; parameter <= End; parameter = parameter + step) {
		cacux_y(nox, noy, px, py);
		//printf("px = %f,py = %f\n", px, py);
		DrawPixel((unsigned long)px, (unsigned long)py);
	}

}

void Deltree(ExprNode *node) {
	if (node == NULL) {
		return;
	}
	switch (node->OpCode) {
	case PLUS:
	case MINUS:
	case MUL:
	case DIV:
	case POWER:
		Deltree(node->Content.CaseOperator.Left);
		Deltree(node->Content.CaseOperator.Right);
		break;
	case FUNC:
		Deltree(node->Content.CaseFunc.Child);
		break;
	default:
		break;
	}
	delete(node);
}

void cacux_y(ExprNode *xnode, ExprNode *ynode, double &x, double &y) {
	double x1, y1, temx;
	//点的初始值
	x1 = GetExpValue(xnode);
	y1 = GetExpValue(ynode);
	cout<<"data:"<<x1<<" "<<y1<<endl;
	//经过比例变换
	//printf("scal: %f\n", scax);
	x1 *= scax;
	y1 *= scay;

	temx = x1*cos(rot_angle) + y1*cos(rot_angle);
	y1 = y1*cos(rot_angle) - x1 * cos(rot_angle);
	x1 = temx;
	x = x1 + locx;
	y = y1 + locy;
}
