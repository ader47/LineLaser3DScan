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
	// 清空队列
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
// 构造队列
// iLength：队列的长度
// DataSize：数据内存区域的大小
// nBitCount：颜色的位数
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
		//将末尾节点的NEXT指针指向头指针指向的节点
		r->next = front->next;
		//初始状态尾指针和头指针指向同一个节点
		rear->next = front->next;
	}
}
//清空队列数据
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

//取头指针指向的节点
ImageData* CMyQueue::GetFront()
{
	// 如果图像数据节点为0
	if (m_nDataSum == 0)
	{
		return NULL;
	}
	else
	{
		return front->next;
	}
}

//新增一个节点，插入队尾，队列的总长度+1
void CMyQueue::AddImageDataNode()
{
	m_QueryLength++;
	ImageData* s = new (ImageData);
	//ImageData* s = (ImageData*)malloc(sizeof(ImageData));
	s->next = rear->next->next;
	rear->next->next = s;
	rear->next = s;
}

//进队列
bool CMyQueue::InQueue(cv::Mat pData)
{
	// 如果尾指针指向的节点与头指针指向的节点相同，说明循环链队列已满
	// 这时不用再添加节点
	if (rear->next == front->next && m_nDataSum > 0) {
		//或者++m_nDataSum >= m_QueryLength
		//if(++m_nDataSum >= m_QueryLength){
		return ERROR;
	}
	//复制Mat矩阵
	pData.copyTo(rear->next->pData);
	rear->next = rear->next->next;
	m_nDataSum++;
	return OK;
}

//出队列，返回图像的数据内存
//使用时可以用Mat a; p->OutQueue().copyTo(a);
cv::Mat CMyQueue::OutQueue()
{
	//表示队列里无存储数据 返回 一个 0 
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


