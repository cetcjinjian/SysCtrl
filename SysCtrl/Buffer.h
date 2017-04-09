
/*---------------------------------------------------
文件名: Buffer.h
用  途: 用于存放串口读入数据的队列，并且把数据拼接成完整的数据包
日  期: 2005.01.05
版  本: 1.0
编  制: 严 华
---------------------------------------------------*/

#if !defined(BUFFER_H)
#define BUFFER_H



#define ARRAY_SIZE		 2000	//2008.07.04括号一定要打上

class CBuffer  
{
public:
	CBuffer();  
	virtual ~CBuffer();

	int		GetSize(void);
	bool	AddData(const  char *pBuffer,int iSize);
	bool	GetPackage(char *pArray,int iSize, char cStart, char cEnd);	
	void    ClearBuffer();
	bool	GetData( char *pBuffer,int iSize);

private:

	int		GetRemainSize(void);

	bool	CopyData( char *pBuffer,int iSize);
	void	AddHead(int iTotal);
	char	GetSiteData(int iSite);	
	int		GetBufferSize(void);
	char	m_Array[ARRAY_SIZE];
	int		m_iHead;
	int		m_iEnd;
};

#endif 
