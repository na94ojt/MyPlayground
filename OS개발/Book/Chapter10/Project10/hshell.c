#include "hshell.h"

/*
 * DECLARE DEFINITIONS
 */
#define DEFAULT_STACK_SIZE				(64*1024) /* 64kbytes */
#define HIDEKI_SHELL_VER				"1st released. Sept 6th, 2003."
#define SHELL_PROMPT					"A:\\>"
#define SHELL_PROMPT_LENGTH				strlen(SHELL_PROMPT)

/*
 * GLOBAL FUNCTIONS
 */
BOOL HshInitializeShell(VOID);

/*
 * STRUCTURES
 */
typedef BOOL (*CMD_PROCESS_ROUTINE)(BYTE *pParameters);

typedef struct _INTERNAL_COMMAND {
	BYTE					*pt_cmd;
	CMD_PROCESS_ROUTINE		routine;
} INTERNEL_COMMAND, *PINTERNEL_COMMAND;

/*
 * INTERNEL FUNCTIONS
 */
static DWORD HshpMainThread(PVOID StartContext);
static VOID  HshpPrintPrompt(void);
static BOOL  HshpParser(void);

static BOOL  Hshp_CMD_help(BYTE *pParameters);
static BOOL  Hshp_CMD_cls(BYTE *pParameters);
static BOOL  Hshp_CMD_ver(BYTE *pParameters);

static BOOL  Hshp_CMD_toggle(BYTE *pParameters);

/*
 * GLOBAL VARIABLES
 */
static HANDLE m_ProcessHandle, m_ThreadHandle;

#define MAX_CMD_LINE_CHAR			128
static BYTE m_CmdLine[MAX_CMD_LINE_CHAR];

static INTERNEL_COMMAND m_InternalCmds[] = {
	"HELP",		Hshp_CMD_help,
	"CLS",		Hshp_CMD_cls,
	"VER",		Hshp_CMD_ver,
	"TOGGLE",	Hshp_CMD_toggle,

	NULL, NULL,
};

/**********************************************************************************************************
 *                                             GLOBAL FUNTIONS                                            *
 **********************************************************************************************************/
BOOL HshInitializeShell(VOID)
{
	memset(m_CmdLine, NULL, MAX_CMD_LINE_CHAR);

	/* create hideki-shell process */
	if(!PsCreateProcess(&m_ProcessHandle)) 
		return FALSE;

	/* create main thread */
	if(!PsCreateThread(&m_ThreadHandle, m_ProcessHandle, HshpMainThread, NULL, DEFAULT_STACK_SIZE, FALSE)) 
		return FALSE;
	PsSetThreadStatus(m_ThreadHandle, THREAD_STATUS_READY); /* i'm ready! */

	return TRUE;
}

/**********************************************************************************************************
 *                                           INTERNEL FUNTIONS                                            *
 **********************************************************************************************************/
static DWORD HshpMainThread(PVOID StartContext)
{
	KBD_KEY_DATA KeyData;
	BYTE cursor_x, cursor_y;
	static int cmd_next_pos=0;

	HshpPrintPrompt();
	while(1) {
		if(!KbdGetKey(&KeyData)) {
			HalTaskSwitch();
			continue;
		}

		if(KeyData.type != KBD_KTYPE_GENERAL) {
			continue;
		}

		if(KeyData.key == '\b') { /* backspace? */
			CrtGetCursorPos(&cursor_x, &cursor_y);
			if(cursor_x <= SHELL_PROMPT_LENGTH) 
				continue;
			m_CmdLine[--cmd_next_pos] = NULL;
		}

		CrtPrintf("%c", KeyData.key); /* echo */
		/* excute command */
		if(KeyData.key == '\r') {
			m_CmdLine[cmd_next_pos] = NULL;
			HshpParser();
			HshpPrintPrompt();
			cmd_next_pos = 0;
			m_CmdLine[0] = NULL;
		} 
		/* converts tab key to space key */
		else if(KeyData.key == '\t') {
			m_CmdLine[cmd_next_pos++] = ' ';
		}
		/* inserts a key into the internal command line array */
		else if(KeyData.key != '\b') { /* except BACKSPACE */
			m_CmdLine[cmd_next_pos++] = KeyData.key;
		}
	}

	return 0;
}

static VOID  HshpPrintPrompt(void)
{
	CrtPrintText(SHELL_PROMPT);
}

static BOOL  HshpParser(void)
{
	int i;
	CMD_PROCESS_ROUTINE	CmdProcessRoutine;
	BYTE *pt_cmd, *pt_parameters;

	/* no command ? */
	if(m_CmdLine[0] == NULL)
		return TRUE;

	for(i=0; m_CmdLine[i] == ' '; i++) ; /* find first chr */
	pt_cmd = &(m_CmdLine[i]);
	for(++i; m_CmdLine[i] != NULL && m_CmdLine[i] != ' '; i++) ; /* find last pos of command */
	if(m_CmdLine[i] == NULL) {
		pt_parameters = NULL;
		goto $find;
	}
	m_CmdLine[i] = NULL;
	for(++i; m_CmdLine[i] == ' '; i++) ; /* find second chr */
	pt_parameters = &(m_CmdLine[i]);

$find:
	pt_cmd = strupr(pt_cmd);
	for(i=0; m_InternalCmds[i].pt_cmd != NULL; i++) {
		if(strcmp(pt_cmd, m_InternalCmds[i].pt_cmd) == 0) {
			CmdProcessRoutine = m_InternalCmds[i].routine;
			CmdProcessRoutine(pt_parameters);
			return TRUE;
		}
	}

	return FALSE;
}

/**********************************************************************************************************
 *                                           OS SPECIFIC COMMANDS                                         *
 **********************************************************************************************************/
static BOOL Hshp_CMD_toggle(BYTE *pParameters)
{
	static BOOL bShow = TRUE;

	bShow = (bShow ? FALSE : TRUE);
	PsShowTSWachdogClock(bShow);

	return TRUE;
}

/**********************************************************************************************************
 *                                        MS-DOS COMPATIBLE COMMANDS                                      *
 **********************************************************************************************************/
static BOOL Hshp_CMD_cls(BYTE *pParameters)
{
	CrtClearScreen();

	return TRUE;
}

static BOOL Hshp_CMD_help(BYTE *pParameters)
{
	CrtPrintText(
		"help    : View available commands and their description. \r\n"
		"ver     : Show the version information of the OS and Hideki shell. \r\n"
		"cls     : Clear screen. \r\n"
		"dir     : Display all files in the current directory. \r\n"
		"type    : Print a text file onto the screen. \r\n"
		"\r\n"
		"toggle  : Show/hide the soft task-switching watchdog clock. \r\n"
		"view    : View a bitmap file (*.bmp). \r\n"
		"\r\n"
		"Even if you find any bugs or critical errors, DO NOT SEND & TELL ME. \r\n"
		"I have no duties to fix them. :( \r\n"
	);

	return TRUE;
}

static BOOL Hshp_CMD_ver(BYTE *pParameters)
{
	CrtPrintf(
		"OS Version    : Chobits OS   (%s) \r\n"
		"Shell Version : Hideki Shell (%s) \r\n"
		"Developer     : Yeori (Sun Kyung-Ryul) \r\n"
		"e-Mail        : alphamcu@hanmail.net \r\n"
		"Homepage      : www.zap.pe.kr \r\n"
		, CHOBITS_OS_VER, HIDEKI_SHELL_VER
	);

	return TRUE;
}
