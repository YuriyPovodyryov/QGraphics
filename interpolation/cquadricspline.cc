//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cquadricspline.h"
#include "cstep.h"
#include <vector>

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CQuadricSpline::CQuadricSpline(void)
{
}

//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CQuadricSpline::~CQuadricSpline()
{
}
//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//выполнить интерполяцию
//----------------------------------------------------------------------------------------------------
bool CQuadricSpline::Execute(const std::vector<CGrPoint> &input,std::vector<CGrPoint> &output,long double step)
{
 size_t size=input.size();
 output.clear();
 std::vector<CGrPoint> empty;
 output.swap(empty);

 if (size<2) return(false);//квадратичный сплайн невозможно построить по такому числу точек
 if (step==0) return(false);//чёткий ноль использовать нельзя
 size_t min_amount=(input[size-1].X-input[0].X)/step+1;
 output.reserve(min_amount);

 std::vector<long double> R(size);
 R[0]=(input[1].Y-input[0].Y)/(input[1].X-input[0].X);//начальная производная
 for(size_t n=1;n<size;n++)
 {
  long double xm1=input[n-1].X;
  long double ym1=input[n-1].Y;

  long double x0=input[n].X;
  long double y0=input[n].Y;

  long double h=x0-xm1;
  R[n]=2.0*(y0-ym1)/h-R[n-1];
 }
 //вычисляем сплайн в заданных точках
 CStep cStep(size-2,step,input);
 long double x;
 size_t point;
 cStep.GetPos(x,point);

 bool first_step=true;
 //коэффициенты полинома
 long double a;
 long double b;
 long double c;

 while(1)
 {
  bool change_point=cStep.UpdatePoint();
  cStep.GetPos(x,point);

  long double x0=input[point].X;
  long double y0=input[point].Y;

  long double x1=input[point+1].X;
  long double y1=input[point+1].Y;

  long double dx1=x1-x;
  long double dx2=x-x0;

  if (change_point==true || first_step==true)//требуется пересчитать полином
  {
   first_step=false;

   long double h=x1-x0;
   a=-R[point]/(2.0*h);
   b=R[point+1]/(2.0*h);
   c=y1-R[point+1]*h/2.0;
  }
  long double y=a*dx1*dx1+b*dx2*dx2+c;
  output.push_back(CGrPoint(x,y));
  if (cStep.NextStep()==false) break;
 }
 return(true);
}

