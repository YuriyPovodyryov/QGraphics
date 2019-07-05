#ifndef C_STEP_H
#define C_STEP_H

//****************************************************************************************************
//класс управления точками, в которых нужно произвести интерполяцию
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************

#include <vector>
#include "./cgraphics/cgrpoint.h"

//****************************************************************************************************
//класс управления точками, в которых нужно произвести интерполяцию
//****************************************************************************************************

class CStep
{
 public:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
  //-константы------------------------------------------------------------------------------------------
 private:
  //-переменные-----------------------------------------------------------------------------------------
  const std::vector<CGrPoint> &Input;//входные точки
  long double Step;//шаг
  long double X;//текущее значение x
  size_t Size;//количество входных точек
  long double BeginX;//начальная точка
  long double EndX;//конечная точка
  size_t Point;//текущая точка входных данных, находящаяся перед позицией x
  size_t EndPoint;//конечная максимально возможная точка входных данных
  size_t StepIndex;//индекс шага интерполяции
  bool Done;//завершен ли путь
 public:
  //-конструктор----------------------------------------------------------------------------------------
  CStep(size_t end_point,long double step,const std::vector<CGrPoint> &input);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CStep();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  void Init(void);//выполнить инициализацию и перейти к первой точке
  bool NextStep(void);//перейти к следующему шагу
  bool UpdatePoint(void);//обновить точку
  void GetPos(long double &x,size_t &point);//получить текущую позицию
 private:
  //-закрытые функции-----------------------------------------------------------------------------------
};
#endif
