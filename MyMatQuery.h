#include <opencv2/core/mat.hpp>

#if !defined(AFX_MYQUERY_H__AAAA56D7_72A2_4EC5_B768_6BF865B9F91D__INCLUDED_)
#define AFX_MYQUERY_H__AAAA56D7_72A2_4EC5_B768_6BF865B9F91D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "StdAfx.h"

//***********************************************************************************
// Date: 2004-5-25
// Auther: csy
// 改队列是循环链队列，包含头结点front和尾结点rear
//***********************************************************************************
//***********************************************************************************
// Date: 2021-1-18
// Auther: liufeng
// 将循环列队存储的对象改为Mat类型
//***********************************************************************************

//***********************************************************************************
// Date: 2022-2-15
// Auther: liufeng
// 将内存申请由new() 变为malloc，因为new 会出错
//***********************************************************************************

#define ERROR 0
#define OK 1

typedef struct _ImageData
{
	// 图像数据内存区域
	//直接使用数据好还是使用指针比较好？
	//现在使用数据，程序占用内存较大
	cv::Mat pData;
	//图像的通道数
	_ImageData* next;
}ImageData;

class CMyQueue   
{
public:
	CMyQueue();
	// 构造队列,包含队列长度，行数，列数
	CMyQueue(int iLength,int rows,int cols);
	virtual ~CMyQueue();
	//进队列
	bool InQueue(cv::Mat pData);
	//出队列
	cv::Mat OutQueue();
	//取头指针指向的节点
	ImageData* GetFront();
	//清空队列
	void ClearQueue();
	//新增一个节点，插入队尾
	void AddImageDataNode();
public:
	// 队列头指针
	ImageData *front;
	// 队列尾指针
	ImageData *rear;		
	// 队列的长度
	int m_QueryLength;
	// 队列中保存节点的个数
	int m_nDataSum;		
	//保存图像的行书，mat矩阵的行数
	int m_DataRows;
	//保存图像的列数，mat矩阵的列数
	int m_DataCols;
};

#endif // !defined(AFX_MYQUERY_H__AAAA56D7_72A2_4EC5_B768_6BF865B9F91D__INCLUDED_)
