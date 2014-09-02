#include "chobits.h"
#include "sys_desc.h"

/*
 * GLOBAL FUNCTIONS
 */
BOOL HalInitializeHal(VOID);

/*
 * DECLARES INTERNEL FUNCTION's PROTOTYPE
 */
static BOOL HalpEnableA20(void);
static BOOL HalpInitPIC(void);
static BOOL HalpInitSysTimer(BYTE timeoutPerSecond);
static BOOL HalpInitializeProcessor(void);

/**********************************************************************************************************
 *                                            GLOBAL FUNTIONS                                             *
 **********************************************************************************************************/
BOOL HalInitializeHal(VOID)
{
	if(!HalpInitializeProcessor()) {
		DbgPrint("HalpInitializeProcessor() returned an error.\r\n");
		return FALSE;
	}

	return TRUE;
}

/**********************************************************************************************************
 *                                           INTERNAL FUNTIONS                                            *
 **********************************************************************************************************/
static BOOL HalpInitializeProcessor(void)
{
	if(!HalpEnableA20()) {
		DbgPrint("HalpEnableA20() returned an error.\r\n");
		return FALSE;
	}

	DbgPrint("A20 line is configured successfully\r\n");

	if(!HalpInitPIC()) {
		DbgPrint("HalpInitPIC() returned an error.\r\n");
		return FALSE;
	}

	DbgPrint("PIC is configured successfully\r\n");

	if(!HalpInitSysTimer(TIMEOUT_PER_SECOND)) {
		DbgPrint("HalpInitSysTimer() returned an error.\r\n");
		return FALSE;
	}

	DbgPrint("System Timer is initialized successfully\r\n");

	return TRUE;
}

static BOOL HalpEnableA20(void)
{
	int *test_1 = (int *)0x00000000, test_1_buf;
	int *test_2 = (int *)0x00100000, test_2_buf;
	UCHAR status, flag;

	/* read current falg */
	do { status = READ_PORT_UCHAR((PUCHAR)0x64); } while( status & 0x02 );
	WRITE_PORT_UCHAR((PUCHAR)0x64, 0xd0);
	do { status = READ_PORT_UCHAR((PUCHAR)0x64); } while( !(status&0x01) );
	flag = READ_PORT_UCHAR((PUCHAR)0x60);
	flag |= 0x02; /* enable a20 */

	/* write modified flag */
	do { status = READ_PORT_UCHAR((PUCHAR)0x64); } while( status & 0x02 );
	WRITE_PORT_UCHAR((PUCHAR)0x64, 0xd1);
	do { status = READ_PORT_UCHAR((PUCHAR)0x64); } while( status & 0x02 );
	WRITE_PORT_UCHAR((PUCHAR)0x60, flag); /* write new flag */

	/* wait until the new flag has adapted */
	do { status = READ_PORT_UCHAR((PUCHAR)0x64); } while( status & 0x02 );

	/* test a20 line */
	test_1_buf = *test_1;
	test_2_buf = *test_2;
	*test_1 = 0xff00ccaa;
	*test_2 = 0x22cc11dd;
	if(*test_1 == *test_2) {
		*test_1 = test_1_buf;
		return FALSE;
	}
	*test_1 = test_1_buf;
	*test_2 = test_2_buf;

	return TRUE;
}

/*
 * INTERRUPT TABLE MAP
 *
 * 0x00 ~ 0x1f : Intel Reserved
 * 0x20 ~ 0x2f : IRQ relocated
 * 0x30 ~ 0x3f : For Chobits OS
 * 0x40 ~ 0xff : Reserved, we dont use.
 */
static BOOL HalpInitPIC(void)
{
	/* master 8259 */
	WRITE_PORT_UCHAR((PUCHAR)0x20, 0x11); /* edge trig, cascade mode, ICW4 */
	WRITE_PORT_UCHAR((PUCHAR)0x21, 0x20); /* start at INT vector 20h */
	WRITE_PORT_UCHAR((PUCHAR)0x21, 0x04); /* #IR2 pin has a slave */
	WRITE_PORT_UCHAR((PUCHAR)0x21, 0x01); /* not sp, nonbuffered mode, normal EOI, for x86 */
	WRITE_PORT_UCHAR((PUCHAR)0x21, 0x00);

	/* slave 8259 */
	WRITE_PORT_UCHAR((PUCHAR)0xa0, 0x11); /* edge trig, cascade mode, ICW4 */
	WRITE_PORT_UCHAR((PUCHAR)0xa1, 0x28); /* start at INT vector 28h */
	WRITE_PORT_UCHAR((PUCHAR)0xa1, 0x02); /* slave 8259 has been linked to master's #IR2 pin */
	WRITE_PORT_UCHAR((PUCHAR)0xa1, 0x01); /* not sp, nonbuffered mode, normal EOI, for x86 */
	WRITE_PORT_UCHAR((PUCHAR)0xa1, 0x00);

	return TRUE;
}

static BOOL HalpInitSysTimer(BYTE timeoutPerSecond)
{
	WORD timeout = (WORD)(1193180/timeoutPerSecond);

	WRITE_PORT_UCHAR((PUCHAR)0x43, 0x34);
	WRITE_PORT_UCHAR((PUCHAR)0x40, (UCHAR)(timeout & 0xff));
	WRITE_PORT_UCHAR((PUCHAR)0x40, (UCHAR)(timeout >> 8));

	return TRUE;
}
