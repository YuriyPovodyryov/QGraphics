//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cvideo_qt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CVideo_Qt::CVideo_Qt(uint32_t width,uint32_t height)
{
 ScreenWidth=width;
 ScreenHeight=height;
 Init();
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CVideo_Qt::~CVideo_Qt()
{
}
//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//инициализизация видеорежима
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::Init(void)
{
 qPixmap_Ptr.reset(new QPixmap(ScreenWidth,ScreenHeight));
 qPixmap_Copy_Ptr.reset(new QPixmap(ScreenWidth,ScreenHeight));
}
//----------------------------------------------------------------------------------------------------
//получить размеры экрана
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::GetScreenSize(uint32_t &width,uint32_t &height) const
{
 width=ScreenWidth;
 height=ScreenHeight;
}
//----------------------------------------------------------------------------------------------------
//задать размеры экрана
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::SetScreenSize(uint32_t width,uint32_t height)
{
 ScreenWidth=width;
 ScreenHeight=height;
 Init();
}
//----------------------------------------------------------------------------------------------------
//получить указатель на видеобуфер
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::GetVideoPointer(void* &vptr) const
{
 vptr=qPixmap_Ptr.get();
}
//----------------------------------------------------------------------------------------------------
//получить размер строки в пикселях
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::GetLineSize(uint32_t &linesize) const
{
 linesize=ScreenWidth;
}
//----------------------------------------------------------------------------------------------------
//вывод символа в позицию
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::PutSymbol(int64_t x,int64_t y,char symbol,uint32_t color)
{ 
 char str[2]={symbol,0};
 PutString(x,y,str,color);
}
//----------------------------------------------------------------------------------------------------
//вывод строчки в позицию
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::PutString(int64_t x,int64_t y,const char *string,uint32_t color)
{
 //так как у drawText задаются координаты нижнего левого угла и выравнивание, требуется задать рамку в которую будет выводиться текст
 uint32_t width;
 uint32_t height;
 GetStringImageSize(string,width,height);
 QPainter qPainter(qPixmap_Ptr.get());
 uint8_t b=(color>>0)&0xff;
 uint8_t g=(color>>8)&0xff;
 uint8_t r=(color>>16)&0xff;
 qPainter.setPen(QPen(qRgb(r,g,b)));
 qPainter.drawText(x,y,width,height,Qt::AlignHCenter,string);
}
//----------------------------------------------------------------------------------------------------
//рисование точки
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::DrawPoint(int64_t x,int64_t y,uint32_t color)
{
 QPainter qPainter(qPixmap_Ptr.get());
 uint8_t b=(color>>0)&0xff;
 uint8_t g=(color>>8)&0xff;
 uint8_t r=(color>>16)&0xff;
 qPainter.setPen(QPen(qRgb(r,g,b)));
 qPainter.drawPoint(x,y);
}
//----------------------------------------------------------------------------------------------------
//рисование линии
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::DrawLine(int64_t x1,int64_t y1,int64_t x2,int64_t y2,uint32_t color,uint32_t thickness,LINE_TYPE line_type)
{	
 QPainter qPainter(qPixmap_Ptr.get());
 uint8_t b=(color>>0)&0xff;
 uint8_t g=(color>>8)&0xff;
 uint8_t r=(color>>16)&0xff;
 QPen qPen;
 qPen.setColor(qRgb(r,g,b));
 if (line_type==LINE_TYPE_SOLID) qPen.setStyle(Qt::SolidLine);
 if (line_type==LINE_TYPE_DOT) qPen.setStyle(Qt::DashLine);
 qPen.setWidth(thickness);
 qPainter.setPen(qPen);
 qPainter.drawLine(x1,y1,x2,y2);
}
//----------------------------------------------------------------------------------------------------
//получить размер строки в пикселях
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::GetStringImageSize(const char *string,uint32_t &width,uint32_t &height)
{
 QPainter qPainter(qPixmap_Ptr.get());
 QFontMetrics qFontMetrics(qPainter.font());
 QRect qRect=qFontMetrics.boundingRect(string);
 width=qRect.width();
 height=qRect.height();
}
//----------------------------------------------------------------------------------------------------
//нарисовать закрашеный прямоугольник
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::FillRectangle(int64_t x1,int64_t y1,int64_t x2,int64_t y2,uint32_t color)
{
 QPainter qPainter(qPixmap_Ptr.get());
 uint8_t b=(color>>0)&0xff;
 uint8_t g=(color>>8)&0xff;
 uint8_t r=(color>>16)&0xff;
 qPainter.setPen(QPen(qRgb(r,g,b)));
 qPainter.setBrush(QBrush(qRgb(r,g,b),Qt::SolidPattern));
 qPainter.drawRect(x1,y1,x2-x1,y2-y1);
}
//----------------------------------------------------------------------------------------------------
//сделать курсор внутри области графика крестиком
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::SetCursorCross(void)
{
}
//----------------------------------------------------------------------------------------------------
//сделать курсор внутри области графика лупой
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::SetCursorMagnify(void)
{
}
//----------------------------------------------------------------------------------------------------
//показать курсор
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::ShowCursor(void)
{
 //setCursor(Qt::BlankCursor);
}
//----------------------------------------------------------------------------------------------------
//скрыть курсор
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::HideCursor(void)
{
 //setCursor(Qt::BlankCursor);
}
//----------------------------------------------------------------------------------------------------
//отпустить курсор
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::UnClipCursor(void)
{
}
//----------------------------------------------------------------------------------------------------
//запереть курсор в области
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::ClipCursor(const CGrRect &cGrRect)
{
}
//----------------------------------------------------------------------------------------------------
//установить координаты курсора
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::SetCursorPos(int32_t x,int32_t y)
{
}
//----------------------------------------------------------------------------------------------------
//сохранить изображение в память
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::SaveScreen(void)
{
 *qPixmap_Copy_Ptr=*qPixmap_Ptr;
}
//----------------------------------------------------------------------------------------------------
//восстановить изображение из памяти
//----------------------------------------------------------------------------------------------------
void CVideo_Qt::RestoreScreen(void)
{
 *qPixmap_Ptr=*qPixmap_Copy_Ptr;
}
