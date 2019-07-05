//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "iinterpolater.h"
#include "interpolation/ccubicspline.h"
#include "interpolation/cquadricspline.h"
#include "interpolation/clinear.h"
#include "interpolation/cquadric.h"

//****************************************************************************************************
//статические функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//создать новый класс интерполяции кубическим сплайном
//----------------------------------------------------------------------------------------------------
IInterpolater* IInterpolater::CreateNewCubicSpline(void)
{
 return(new CCubicSpline());
}
//----------------------------------------------------------------------------------------------------
//создать новый класс интерполяции квадратичным сплайном
//----------------------------------------------------------------------------------------------------
IInterpolater* IInterpolater::CreateNewQuadricSpline(void)
{
 return(new CQuadricSpline());
}
//----------------------------------------------------------------------------------------------------
//создать новый класс интерполяции кусочно-линейной функцией
//----------------------------------------------------------------------------------------------------
IInterpolater* IInterpolater::CreateNewLinear(void)
{
 return(new CLinear());
}
//----------------------------------------------------------------------------------------------------
//создать новый класс интерполяции кусочно-квадратичной функцией
//----------------------------------------------------------------------------------------------------
IInterpolater* IInterpolater::CreateNewQuadric(void)
{
 return(new CQuadric());
}
