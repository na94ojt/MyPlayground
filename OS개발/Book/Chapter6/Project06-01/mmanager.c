#include "chobits.h"

/* ---------------------
 * CHOBITS OS MEMORY MAP
 * ---------------------
 * 0x00000000 ~ 0x000fffff : first 1 mega bytes area. ONLY FOR KERNEL
 * 0x00100000 ~ 0x001effff : second 1 mega bytes area. FOR APPLICATION PROGRAM CODE&DATA (we're not support paging yet)
 * 0x001f0000 ~ 0x001fffff : 64kbytes for app's stack
 * 0x00200000 ~ 0xffffffff : memory pool
 */

/*
 * DEFINITIONS
 */
#define MEMORY_POOL_START_ADDRESS		0x00200000

#define MEM_BLK_SIZE					512			/* each block occupies 512 bytes */

#define MEM_BLK_FREE					0
#define MEM_BLK_USED					1

/*
 * STRUCTURES
 */
typedef struct _MEM_BLK_DESC {
	DWORD					status;
	DWORD					block_size;
	struct _MEM_BLK_DESC	*pNext;
} MEM_BLK_DESC, *PMEM_BLK_DESC;

typedef struct _MEM_BLK_MANAGER {
	DWORD					nBlocks;
	DWORD					nUsedBlocks;
	DWORD					nFreeBlocks;
	MEM_BLK_DESC			*pDescEntry;
	int						*pPoolEntry;
} MEM_BLK_MANAGER, *PMEM_BLK_MANAGER;

/*
 * DECLARES INTERNEL FUNCTION
 */
static BOOL MmpCheckMemorySize(void);
static BOOL MmpCreateMemPoolBlk(void);
static DWORD MmpGetRequiredBlocksFromBytes(DWORD bytes);

/*
 * GLOBAL VARIABLES
 */
static DWORD				m_MemSize;
static MEM_BLK_MANAGER		m_MemBlkManager;

/**********************************************************************************************************
 *                                            GLOBAL FUNTIONS                                             *
 **********************************************************************************************************/
BOOL MmkInitializeMemoryManager(VOID)
{
	if(!MmpCheckMemorySize()) {
		DbgPrint("MmpCheckMemorySize() returned an error.\r\n");
		return FALSE;
	}
	if(!MmpCreateMemPoolBlk()) {
		DbgPrint("MmpCreateMemPoolBlk() returned an error.\r\n");
		return FALSE;
	}

	DbgPrint("Memory Manager is initialized successfully\r\n");

	return TRUE;
}

/**********************************************************************************************************
 *                                           INTERNAL FUNTIONS                                            *
 **********************************************************************************************************/
static BOOL MmpCheckMemorySize(void)
{
	BOOL bResult;
	DWORD *pAddr = (DWORD *)0x00000000, tmp;

	while(1) {
		pAddr += (4*1024*1024); /* 4 mega bytes */
		tmp = *pAddr;
		*pAddr = 0x11223344;
		if(*pAddr != 0x11223344)
			break;
		*pAddr = tmp;
	}

ENTER_CRITICAL_SECTION();
	m_MemSize = (DWORD)pAddr;
	bResult = (m_MemSize < MEMORY_POOL_START_ADDRESS+(1*1024*1024) ? FALSE : TRUE);
EXIT_CRITICAL_SECTION();

	return bResult;
}

static BOOL MmpCreateMemPoolBlk(void)
{
	DWORD dwUsableMemSize, dwBlksOfUsableMem, dwBlksOfAllocatableMem, dwBlksOfDescs, i;
	int *pPoolEntry;
	MEM_BLK_DESC *pPrev, *pCur;

ENTER_CRITICAL_SECTION();
	dwUsableMemSize = m_MemSize - MEMORY_POOL_START_ADDRESS;
EXIT_CRITICAL_SECTION();

	dwBlksOfUsableMem		= MmpGetRequiredBlocksFromBytes(dwUsableMemSize);
	dwBlksOfDescs			= MmpGetRequiredBlocksFromBytes(dwBlksOfUsableMem*sizeof(MEM_BLK_DESC));
	dwBlksOfAllocatableMem	= dwBlksOfUsableMem-dwBlksOfDescs;
	dwBlksOfDescs			= MmpGetRequiredBlocksFromBytes(dwBlksOfAllocatableMem*sizeof(MEM_BLK_DESC));
	pPoolEntry				= (int *)(MEMORY_POOL_START_ADDRESS+dwBlksOfDescs*MEM_BLK_SIZE);

ENTER_CRITICAL_SECTION();
	m_MemBlkManager.nBlocks			= dwBlksOfAllocatableMem;
	m_MemBlkManager.nUsedBlocks		= 0;
	m_MemBlkManager.nFreeBlocks		= dwBlksOfAllocatableMem;
	m_MemBlkManager.pDescEntry		= (MEM_BLK_DESC *)MEMORY_POOL_START_ADDRESS;
	m_MemBlkManager.pPoolEntry		= pPoolEntry;

	pPrev = m_MemBlkManager.pDescEntry;
	pPrev->status = MEM_BLK_FREE;
	for(i=1; i<dwBlksOfAllocatableMem; i++) {
		pCur = (MEM_BLK_DESC *)(MEMORY_POOL_START_ADDRESS+sizeof(MEM_BLK_DESC)*i);
		pCur->status = MEM_BLK_FREE;
		pCur->block_size = 0;
		pPrev->pNext = pCur;
		pPrev = pCur;
	}
	pCur->pNext = NULL;
EXIT_CRITICAL_SECTION();

/*
	DbgPrint("MemSize:%d, entry:0x%x, Descs:%d, Alloc:%d, Size:%d \r\n",
		dwUsableMemSize, pPoolEntry, dwBlksOfDescs, dwBlksOfAllocatableMem, sizeof(MEM_BLK_DESC));
*/

	return TRUE;
}

static DWORD MmpGetRequiredBlocksFromBytes(DWORD bytes)
{
	DWORD dwBlocks = 0;

	dwBlocks = bytes/MEM_BLK_SIZE;
	if(bytes % MEM_BLK_SIZE)
		dwBlocks++;

	return dwBlocks;
}
