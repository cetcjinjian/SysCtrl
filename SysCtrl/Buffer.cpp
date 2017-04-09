// Buffer.cpp: implementation of the CBuffer class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Buffer.h"


CBuffer::CBuffer()
{
	m_iHead=0;
	m_iEnd=0;
	memset(m_Array,0,ARRAY_SIZE);
}

CBuffer::~CBuffer()
{

}

void CBuffer::ClearBuffer()
{
	memset(m_Array,0,ARRAY_SIZE);
	m_iHead = 0;
	m_iEnd = 0;
}
int CBuffer::GetSize(void)
{
	if (m_iHead==m_iEnd) return 0;

	if (m_iHead<m_iEnd) 
		return m_iEnd-m_iHead;
	else 
		return ARRAY_SIZE-m_iHead+m_iEnd;
}

int	CBuffer::GetRemainSize(void)
{
	return ARRAY_SIZE-GetSize();
}

int	CBuffer::GetBufferSize(void)
{
	return ARRAY_SIZE;
}

bool CBuffer::GetData( char * pBuffer,int iSize)
{
	int size;

	size=GetSize();
	if (size<iSize) return false;

	for (int i=0;i<iSize;i++)
	{
		pBuffer[i]=m_Array[m_iHead];
		m_iHead++;
		if (m_iHead==ARRAY_SIZE) 
			m_iHead=0;
	}

	return true;
}

bool CBuffer::CopyData( char * pBuffer,int iSize)
{
	int size;
	int site;

	site = m_iHead;

	size=GetSize();
	if (size<iSize) return false;

	for (int i=0;i<iSize;i++)
	{
		pBuffer[i]=m_Array[site];
		site++;
		if (site==ARRAY_SIZE) 
			site=0;
	}

	return true;
}

void CBuffer::AddHead(int iTotal)
{
	int temp;

	temp=m_iHead+iTotal;
	if (temp>=ARRAY_SIZE) temp=temp-ARRAY_SIZE;

	m_iHead=temp;
}

bool CBuffer::AddData(const  char *pBuffer,int iSize)
{
	int remain;

	remain=GetRemainSize();
	if (iSize>remain) return false;

	for (int i=0;i<iSize;i++)
	{
		m_Array[m_iEnd]=pBuffer[i];
		m_iEnd++;
		if (m_iEnd==ARRAY_SIZE) 
			m_iEnd=0;
	}

	return true;
}

char CBuffer::GetSiteData(int iSite)
{
	int head;

	head=m_iHead+iSite;
	if (head>=ARRAY_SIZE) 
		head=head-ARRAY_SIZE;
	return m_Array[head];
}

bool CBuffer::GetPackage( char *pArray,int iSize, char cStart, char cEnd)
{
	int remain;
	char ch;

	remain=GetSize();
	while (remain>=iSize)
	{
		ch=m_Array[m_iHead];
		if (ch!=cStart) 
			AddHead(1);
		else
		{
			GetData(pArray,iSize);
			return true;			
		}

		remain=GetSize();
	}

	return false;
}


