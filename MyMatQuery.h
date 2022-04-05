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
// �Ķ�����ѭ�������У�����ͷ���front��β���rear
//***********************************************************************************
//***********************************************************************************
// Date: 2021-1-18
// Auther: liufeng
// ��ѭ���жӴ洢�Ķ����ΪMat����
//***********************************************************************************

//***********************************************************************************
// Date: 2022-2-15
// Auther: liufeng
// ���ڴ�������new() ��Ϊmalloc����Ϊnew �����
//***********************************************************************************

#define ERROR 0
#define OK 1

typedef struct _ImageData
{
	// ͼ�������ڴ�����
	//ֱ��ʹ�����ݺû���ʹ��ָ��ȽϺã�
	//����ʹ�����ݣ�����ռ���ڴ�ϴ�
	cv::Mat pData;
	//ͼ���ͨ����
	_ImageData* next;
}ImageData;

class CMyQueue   
{
public:
	CMyQueue();
	// �������,�������г��ȣ�����������
	CMyQueue(int iLength,int rows,int cols);
	virtual ~CMyQueue();
	//������
	bool InQueue(cv::Mat pData);
	//������
	cv::Mat OutQueue();
	//ȡͷָ��ָ��Ľڵ�
	ImageData* GetFront();
	//��ն���
	void ClearQueue();
	//����һ���ڵ㣬�����β
	void AddImageDataNode();
public:
	// ����ͷָ��
	ImageData *front;
	// ����βָ��
	ImageData *rear;		
	// ���еĳ���
	int m_QueryLength;
	// �����б���ڵ�ĸ���
	int m_nDataSum;		
	//����ͼ������飬mat���������
	int m_DataRows;
	//����ͼ���������mat���������
	int m_DataCols;
};

#endif // !defined(AFX_MYQUERY_H__AAAA56D7_72A2_4EC5_B768_6BF865B9F91D__INCLUDED_)
