#include "MyMatQuery.h"
#include <opencv2/core/cuda.inl.hpp>

//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
//#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMyQueue::CMyQueue()
{

}

CMyQueue::~CMyQueue()
{
	// ��ն���
	ClearQueue();
	if (front != NULL) {
		delete front;
		front = NULL;
	}
	if (rear != NULL) {
		delete rear;
		rear = NULL;
	}
}
/*************************************************************
// �������
// iLength�����еĳ���
// DataSize�������ڴ�����Ĵ�С
// nBitCount����ɫ��λ��
*************************************************************/
CMyQueue::CMyQueue(int iLength, int rows, int cols)  //50,640x480,8
{
	if (iLength <= 0) {
		m_QueryLength = 0;
		m_nDataSum = 0;
		rear = front = NULL;
		return;
	}
	m_QueryLength = iLength;
	m_nDataSum = 0;
	m_DataCols = cols;
	m_DataRows = rows;
	//front = (ImageData*)malloc(sizeof(ImageData));
	//rear = (ImageData*)malloc(sizeof(ImageData));
	front = new(ImageData);
	rear = new(ImageData);

	ImageData* s;
	ImageData* r = front;


	for (int i = 0; i < iLength; i++)
	{
		s = new(ImageData);
		//s = (ImageData*)malloc(sizeof(ImageData));
		r->next = s;
		r = s;
		//��ĩβ�ڵ��NEXTָ��ָ��ͷָ��ָ��Ľڵ�
		r->next = front->next;
		//��ʼ״̬βָ���ͷָ��ָ��ͬһ���ڵ�
		rear->next = front->next;
	}
}
//��ն�������
void CMyQueue::ClearQueue()
{
	ImageData* p = NULL;
	p = front->next;
	for (int i = 0; i < m_QueryLength; i++)
	{
		p->pData.release();
		p = p->next;
	}
}

//ȡͷָ��ָ��Ľڵ�
ImageData* CMyQueue::GetFront()
{
	// ���ͼ�����ݽڵ�Ϊ0
	if (m_nDataSum == 0)
	{
		return NULL;
	}
	else
	{
		return front->next;
	}
}

//����һ���ڵ㣬�����β�����е��ܳ���+1
void CMyQueue::AddImageDataNode()
{
	m_QueryLength++;
	ImageData* s = new (ImageData);
	//ImageData* s = (ImageData*)malloc(sizeof(ImageData));
	s->next = rear->next->next;
	rear->next->next = s;
	rear->next = s;
}

//������
bool CMyQueue::InQueue(cv::Mat pData)
{
	// ���βָ��ָ��Ľڵ���ͷָ��ָ��Ľڵ���ͬ��˵��ѭ������������
	// ��ʱ��������ӽڵ�
	if (rear->next == front->next && m_nDataSum > 0) {
		//����++m_nDataSum >= m_QueryLength
		//if(++m_nDataSum >= m_QueryLength){
		return ERROR;
	}
	//����Mat����
	pData.copyTo(rear->next->pData);
	rear->next = rear->next->next;
	m_nDataSum++;
	return OK;
}

//�����У�����ͼ��������ڴ�
//ʹ��ʱ������Mat a; p->OutQueue().copyTo(a);
cv::Mat CMyQueue::OutQueue()
{
	//��ʾ�������޴洢���� ���� һ�� 0 
	cv::Mat FalseReturn0 = cv::Mat::zeros(1,1,CV_8UC1);
	if (m_nDataSum == 0)
	{
		return FalseReturn0;
	}

	m_nDataSum--;

	ImageData* s = front->next;
	front->next = s->next;
	return s->pData;
}


