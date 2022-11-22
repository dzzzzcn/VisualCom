#ifndef _VSM_H
#define _VSM_H

#include <vector>
#include <list>
using namespace std;

#define FALSE   0
#define TRUE    1
#define NULL    0

#define VOID  void
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT* PFLOAT;
typedef double DOUBLE;
typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int* PUINT;

typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef long long LONGLONG;

typedef signed char         INT8, * PINT8;
typedef signed short        INT16, * PINT16;
typedef signed int          INT32, * PINT32;
typedef signed __int64      INT64, * PINT64;
typedef unsigned char       UINT8, * PUINT8;
typedef unsigned short      UINT16, * PUINT16;
typedef unsigned int        UINT32, * PUINT32;
typedef unsigned __int64    UINT64, * PUINT64;
typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character

typedef WCHAR TCHAR, * PTCHAR;
typedef WCHAR TBYTE, * PTBYTE;
typedef DWORD   COLORREF;

typedef LONG ACTIVESTATE;

// Time type definitions:
typedef DOUBLE REALTIME;
typedef LONGLONG  ABSTIME;
typedef const ABSTIME& CREFABSTIME;
typedef LONGLONG RELTIME;
typedef const RELTIME& CREFRELTIME;

// Time Conversion Macros
#define DSIMTICK    1e-12

// Maximum bits in bus:
#define MAXBUSBITS     32

// Handles for graphics and text styles
typedef VOID* HGFXSTYLE;
typedef VOID* HTEXTSTYLE;

// Pop-up window interfaces.
// Handles, types, etc. for pop-up windows:
typedef VOID IPOPUP;
typedef DWORD POPUPID;
typedef DWORD INSTANCEID;

// DSIM Type Definitions:
typedef LONG EVENTID;

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))
#define PALETTEINDEX(i)     ((COLORREF)(0x01000000 | (DWORD)(WORD)(i)))

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))

// Color Macro
#define  BLACK           RGB(0x00,0x00,0x00)
#define  BLUE            RGB(0x00,0x00,0xC0)
#define  GREEN           RGB(0x00,0xC0,0x00)
#define  CYAN            RGB(0x00,0xC0,0xC0)
#define  RED             RGB(0xC0,0x00,0x00)
#define  MAGENTA         RGB(0xC0,0x00,0xC0)
#define  YELLOW          RGB(0xC0,0xC0,0x00)
#define  WHITE           RGB(0xC0,0xC0,0xC0)
#define  GREY            RGB(0x80,0x80,0x80)
#define  DARKBLUE        RGB(0x00,0x00,0x40)
#define  DARKGREEN       RGB(0x00,0x40,0x00)
#define  DARKCYAN        RGB(0x00,0x40,0x40)
#define  DARKRED         RGB(0x40,0x00,0x00)
#define  DARKMAGENTA     RGB(0x40,0x00,0x40)
#define  DARKYELLOW      RGB(0x40,0x40,0x00)
#define  DARKGREY        RGB(0x40,0x40,0x40)
#define  MIDBLUE         RGB(0x00,0x00,0x80)
#define  MIDGREEN        RGB(0x00,0x80,0x00)
#define  MIDCYAN         RGB(0x00,0x80,0x80)
#define  MIDRED          RGB(0x80,0x00,0x00)
#define  MIDMAGENTA      RGB(0x80,0x00,0x80)
#define  MIDYELLOW       RGB(0x80,0x80,0x00)
#define  MIDGREY         RGB(0x80,0x80,0x80)
#define  LIGHTBLUE       RGB(0x00,0x00,0xC0)
#define  LIGHTGREEN      RGB(0x00,0xC0,0x00)
#define  LIGHTCYAN       RGB(0x00,0xC0,0xC0)
#define  LIGHTRED        RGB(0xC0,0x00,0x00)
#define  LIGHTMAGENTA    RGB(0xC0,0x00,0xC0)
#define  LIGHTYELLOW     RGB(0xC0,0xC0,0x00)
#define  LIGHTGREY       RGB(0xC0,0xC0,0xC0)
#define  BRIGHTBLUE      RGB(0x00,0x00,0xFF)
#define  BRIGHTGREEN     RGB(0x00,0xFF,0x00)
#define  BRIGHTCYAN      RGB(0x00,0xFF,0xFF)
#define  BRIGHTRED       RGB(0xFF,0x00,0x00)
#define  BRIGHTMAGENTA   RGB(0xFF,0x00,0xFF)
#define  BRIGHTYELLOW    RGB(0xFF,0xFF,0x00)
#define  BRIGHTWHITE     RGB(0xFF,0xFF,0xFF)

#define  INVISIBLE       -1
#define  NOCOLOUR        -1

//Pen Styles 
#define PS_SOLID            0
#define PS_DASH             1       // -------  
#define PS_DOT              2       // .......  
#define PS_DASHDOT          3       // _._._._  
#define PS_DASHDOTDOT       4       // _.._.._  

//Hatch Styles 
#define HS_SOLID            0
#define HS_HORIZONTAL       1       // ----- 
#define HS_VERTICAL         2       // ||||| 
#define HS_FDIAGONAL        3       // \\\\\ 
#define HS_BDIAGONAL        4       // ///// 
#define HS_CROSS            5       // +++++ 
#define HS_DIAGCROSS        6       // xxxxx 

// Text Alignment
#define TXJ_LEFT   0
#define TXJ_RIGHT  1
#define TXJ_CENTRE 2
#define TXJ_BOTTOM 0
#define TXJ_TOP    4
#define TXJ_MIDDLE 8

#define PRODATA_TYPE_CMD 0
#define PRODATA_TYPE_DAT 1
#define PRODATA_TYPE_SYM 2

#define PRODATA_WRITE_TYPE 0
#define PRODATA_READ_TYPE 1


//Key State Masks for Mouse Messages

#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010

#define MK_LBDOWN           0x0100   //Left Mouse Button Pressed
#define MK_RBDOWN           0x0200   //Right Mouse Button Pressed
#define MK_LBUP             0x0400   //Left Mouse Button Unpressed
#define MK_RBUP             0x0800   //Right Mouse Button Unpressed
#define MK_KEYDOWN          0x4000   //Key Pressed
#define MK_KEYUP            0x8000   //Key UpPressed

#define VK_KEY_MASK       0xFF
#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04    
#define VK_BACK           0x08
#define VK_TAB            0x09
#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D

#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

//VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
//0x3A - 0x40 : unassigned
//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)

#define VK_LWIN           0x5B
#define VK_RWIN           0x5C
#define VK_APPS           0x5D

#define VK_SLEEP          0x5F

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87
#define VK_NUMLOCK        0x90
#define VK_SCROLL         0x91
#define VK_LSHIFT         0xA0
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4
#define VK_RMENU          0xA5

//flag values for fuSound and fdwSound arguments on [snd]PlaySound

#define SND_SYNC            0x0000   //play synchronously (default) 
#define SND_ASYNC           0x0001   //play asynchronously 
#define SND_NODEFAULT       0x0002   //silence (!default) if sound not found 
#define SND_MEMORY          0x0004   //pszSound points to a memory file 
#define SND_LOOP            0x0008   //loop the sound until next sndPlaySound 
#define SND_NOSTOP          0x0010   //don't stop any currently playing sound 
#define SND_PURGE           0x0040   //purge non-static events for task 
#define SND_APPLICATION     0x0080   //look for application specific association 

#define SND_NOWAIT      0x00002000L  // don't wait if the driver is busy 
#define SND_ALIAS       0x00010000L  // name is a registry alias 
#define SND_ALIAS_ID    0x00110000L  // alias is a predefined ID 
#define SND_FILENAME    0x00020000L  // name is file name 
#define SND_RESOURCE    0x00040004L  // name is resource name or atom 

#define SND_SENTRY      0x00080000L  // Generate a SoundSentry event with this sound 
#define SND_RING        0x00100000L  // Treat this as a "ring" from a communications app - don't duck me 
#define SND_SYSTEM      0x00200000L  // Treat this as a system sound 

// Pin drive flags
#define DPF_INPUT       0x01
#define DPF_OUTPUT      0x02
#define DPF_BIDIR       0x03

// State polarity bits:
#define SP_UNDEFINED    0x00           // The undefined state.
#define SP_LOW          0x01           // Polarity Low.
#define SP_FLOAT        0x02           // Polarity Float (i.e. half volts).
#define SP_HIGH         0x03           // Polarity High.
#define SP_MASK         0x03           // Use to mask off polarity.

// State strength bits:
#define SS_FLOAT        0x00           // Strength Float.
#define SS_DRIVEN       0x04           // Flag bit for driven state.
#define SS_WEAK         0x04           // Strength Weak.
#define SS_STRONG       0x0C           // Strength Strong.
#define SS_INJECT       0x14           // Strength for generators.
#define SS_POWER        0x1C           // Strength Power rail.
#define SS_MASK         0x1C           // Used to mask off strength.

// State flag bits:
#define SF_CONTENTION   0x20           //
#define SF_MESSAGE      0x40           // Message associated with state (?)
#define SF_MASK         0xE0           // Use to mask off flags.

#define INVALID_ID      -1
// State constants:
// Application code should deal only with these values;
// Manipulation of contention  and message flags is a kernel function.
enum STATE
{
	UNDEFINED = 0,
	TSTATE = 1,
	FSTATE = -1,
	PLO = SS_POWER + SP_LOW,
	ILO = SS_INJECT + SP_LOW,
	SLO = SS_STRONG + SP_LOW,
	WLO = SS_WEAK + SP_LOW,
	FLT = SS_FLOAT + SP_FLOAT,
	WHI = SS_WEAK + SP_HIGH,
	SHI = SS_STRONG + SP_HIGH,
	IHI = SS_INJECT + SP_HIGH,
	PHI = SS_POWER + SP_HIGH,
	WUD = SS_WEAK + SP_UNDEFINED,
	SUD = SS_STRONG + SP_UNDEFINED
};

// Functions for testing states.
inline BOOL islow(STATE s) { return (s & SP_MASK) == SP_LOW; }
inline BOOL ishigh(STATE s) { return (s & SP_MASK) == SP_HIGH; }
inline BOOL isfloating(STATE s) { return (s & SP_MASK) == SP_FLOAT; }
inline BOOL iscontention(STATE s) { return s & SF_CONTENTION; }
inline BOOL isdefined(STATE s) { return s != SP_UNDEFINED; }
inline BOOL ishighlow(STATE s) { return s & 1; }
inline INT  polarity(STATE s) { return s & SP_MASK; }
inline INT  strength(STATE s) { return s & SS_MASK; }

// Type for memory address
typedef DWORD ADDRESS;

enum POPUPTYPES
{
	PWT_USER = 0,
	PWT_DEBUG = 1,
	PWT_STATUS = 2,
	PWT_MEMORY = 3,
	PWT_WATCH = 5,
	PWT_SOURCE = 4,
	PWT_VAR = 6
};

// Flags for creating pop-up windows. The bottom 20 bits are reserved for use by VSM,
// whilst the remaining top 12 bits are available for user pop-ups.
enum POPUPFLAGS
{
	PWF_VISIBLE = 0x00000001,
	PWF_SIZEABLE = 0x00000002,
	PWF_LOCKPOSITION = 0x00000004,
	PWF_HIDEONANIMATE = 0x00000008,
	PWF_AUTOREFRESH = 0x00000010,
	PWF_WANTKEYBOARD = 0x00000020,
	PWF_ACTIVE = 0x00008000,
	PWF_INTERNAL = 0x80000000
};

enum DSIMMODES
{
	DSIMBOOT = 0x01,
	DSIMSETTLE = 0x02,
	DSIMNORMAL = 0x04,
	DSIMEND = 0x08
};

// Simulator Run Control Modes
enum RUNMODES
{
	RM_BATCH = -1,
	RM_START,
	RM_STOP,
	RM_SUSPEND,
	RM_SINGLESTEP,
	RM_SPECIFICSTEP,
	RM_ANIMATE,
	RM_STEPTIME,
	RM_STEPOVER,
	RM_STEPINTO,
	RM_STEPOUT,
	RM_STEPTO,
	RM_META,
	RM_DUMP
};

// Struct for active component animation event:
enum ACTIVEDATATYPES
{
	ADT_VOID = -1,
	ADT_REAL,
	ADT_BOOLEAN,
	ADT_INTEGER,
	ADT_STATE,
	ADT_PINVOLTAGE,
	ADT_PINSTATE,
	ADT_WIREINFO,
	ADT_SPICEDATA,
	ADT_DSIMDATA,
	ADT_USER = 100
};

enum FIELDINDEX
{
	DEVICENAME  = 0, 
	REFERENCE,
	SIMTYPE,
	SIMFILE,
	SIMEXTRA,
	DEVICEVALUE,
	OTHER
};

enum TEXTDIRECTION
{
	TXT_VERTICAL = 1,
	TXT_HORIZONTAL = 3
};
//Logic Font
#define LF_FACESIZE         32

typedef struct tagLOGFONTW
{
	LONG height;
	LONG width;
	LONG escapement;
	LONG orientation;
	LONG weight;
	BYTE italic;
	BYTE underline;
	BYTE strikeout;
	BYTE charset;
	BYTE outprecision;
	BYTE clipprecision;
	BYTE quality;
	BYTE pitchandfamily;
	WCHAR facename[LF_FACESIZE];
} LOGFONTW;


typedef LOGFONTW LOGFONT;

// Structure used to pass createpopup information:
struct CREATEPOPUPSTRUCT
{
	POPUPID id;
	POPUPTYPES type;
	CHAR* caption;
	INT   width, height;
	DWORD flags;
};

struct SIMDATA
{
	LONGLONG d;
	TCHAR* s;
	DOUBLE b;
	DOUBLE c;
	BOOL flag;
};

struct SPICEDATA
{
	DWORD numtimepoints;
	DWORD numpins;
	REALTIME* timepoints;
	DOUBLE* nodedata;
};

struct DSIMDATA
{
	DWORD numtimepoints;
	DWORD numpins;
	ABSTIME* timepoints;
	STATE* nodedata;
};

struct ACTIVEDATA
{
	ACTIVEDATATYPES type;
	union
	{
		INT intval;
		DOUBLE realval;
		STATE stateval;
		DOUBLE wireinfo[2];     // Voltage and current
		SPICEDATA spicedata;
		DSIMDATA dsimdata;
		VOID* userinfo;         // Pointer to user data
	};
};

struct ACTIVEEVENT
{
	DWORD instance;            // Design Global Instance value for target indicator
	DWORD callback;            // Callback Pointer to the active component object
	DWORD element;             // Sub-element within parent.
	ACTIVEDATA data;           // Data structure passed to models:
};

struct LINESTYLE
{
	INT32 style;
	INT32 width;
	COLORREF color;
	
};
struct FILLSTYLE
{
	INT32 style; 
	COLORREF color;
};

struct FONTSTYLE
{
	TCHAR* str; 
	COLORREF color;
};
struct POINT {
	LONG x;
	LONG y;
};
struct DPOINT
{
	DOUBLE x;
	DOUBLE y;
};

struct DSIZE
{
	DOUBLE cx;
	DOUBLE cy;
};

struct RECT
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
};

struct DRECT
{
	DOUBLE left;
	DOUBLE top;
	DOUBLE right;
	DOUBLE bottom;
};

struct PRODATA
{
	INT number;
	INT type;
	INT extra;
	LONGLONG data;
	TCHAR* info;
};

struct PROPCELL
{
	LONG id;
	TCHAR* name;
	TCHAR* value;
	TCHAR* description;
};
typedef std::vector<DPOINT> DPOINTS;
typedef std::list<PROPCELL> PROPCELLS;

struct ICOMPONENT
{
	virtual TCHAR* GetFieldByName(TCHAR* name) = 0;
	virtual TCHAR* GetFieldById(INT id) = 0;
	virtual BOOL GetLongFieldByName(TCHAR* name, LONG& dat) = 0;
	virtual BOOL GetLongFieldById(INT id, LONG& dat) = 0;
	virtual BOOL GetBoolFieldByName(TCHAR* name, BOOL& dat) = 0;
	virtual BOOL GetBoolFieldById(INT id, BOOL& dat) = 0;
	virtual BOOL GetColorFieldByName(TCHAR* name, COLORREF& color) = 0;
	virtual BOOL GetColorFiledById(INT id, COLORREF& color) = 0;
	virtual TCHAR* GetComponentReference() = 0;
	virtual TCHAR* GetComponentName() = 0;
	virtual INT GetFieldIndexByName(TCHAR* name) = 0;
	virtual INT GetFieldIndexById(INT id) = 0;
	virtual INT GetFieldCount() = 0;

	virtual BOOL PlaySoundByName(TCHAR* name, DWORD flag) = 0;
	virtual BOOL PlaySoundById(INT id, DWORD flag) = 0;
	virtual BOOL CyclePlaySoundByName(TCHAR* name) = 0;
	virtual BOOL CyclePlaySoundById(INT id) = 0;
	virtual BOOL StopPlayAllSound(DWORD flag) = 0;
	virtual BOOL StopPlayAllSound() = 0;

	virtual BOOL SetBitmapByName(TCHAR* name) = 0;
	virtual BOOL SetBitmapById(INT id) = 0;
	virtual COLORREF GetBitmapPixel(INT x, INT y) = 0;

	virtual VOID BeginCache() = 0;
	virtual VOID BeginCache(DRECT rect) = 0;
	virtual VOID EndCache() = 0;

	virtual VOID DrawSymbol(INT index, DOUBLE dx = 0, DOUBLE dy = 0) = 0;
	virtual VOID DrawSymbol(INT index, LINESTYLE* ls, DOUBLE dx = 0, DOUBLE dy = 0) = 0;
	virtual VOID DrawSymbol(INT index, FILLSTYLE* fs, DOUBLE dx = 0, DOUBLE dy = 0) = 0;
	virtual VOID DrawSymbol(INT index, FONTSTYLE* ts, DOUBLE dx = 0, DOUBLE dy = 0) = 0;
	virtual VOID DrawSymbol(INT index, LINESTYLE* ls, FILLSTYLE* fs, FONTSTYLE* ts, DOUBLE dx = 0, DOUBLE dy = 0) = 0;


	virtual VOID SetPenColor(COLORREF col) = 0;
	virtual VOID SetPenWidth(INT width) = 0;
	virtual VOID SetPenStyle(INT style) = 0;
	virtual VOID SetBrushColor(COLORREF col) = 0;
	virtual VOID SetBrushStyle(INT style) = 0;

	virtual VOID SetTextStyle(LOGFONT lf) = 0;
	virtual VOID SetTextFont(TCHAR* font) = 0;
	virtual VOID SetTextSize(INT size) = 0;
	virtual VOID SetTextBold(BOOL flag) = 0;
	virtual VOID SetTextItalic(BOOL flag) = 0;
	virtual VOID SetUnderline(BOOL flag) = 0;
	virtual VOID SetTextHeight(LONG height) = 0;
	virtual VOID SetTextWidth(LONG width) = 0;
	
	virtual VOID DrawRectangle(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2, DOUBLE dx, DOUBLE dy) = 0;
	virtual VOID DrawRectangle(DRECT rect, DPOINT offset) = 0;
	virtual VOID DrawCircle(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2, DOUBLE dx, DOUBLE dy) = 0;
	virtual VOID DrawCircle(DRECT rect, DPOINT offset) = 0;
	virtual VOID DrawLine(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2, DOUBLE dx, DOUBLE dy) = 0;
	virtual VOID DrawLine(DRECT rect, DPOINT offset) = 0;
	virtual VOID DrawPolygon(DPOINTS pc, DPOINT offset) = 0;
	virtual VOID DrawText(DOUBLE x1, DOUBLE y1, DOUBLE dx, DOUBLE dy, TCHAR* str, INT dir = 1, INT flag = 0) = 0;

	virtual DPOINT GetPosRightBottom() = 0;
	virtual DPOINT GetPosLeftTop() = 0;
	virtual DPOINT GetSize() = 0;
	virtual BOOL GetSymbolSize(INT index, DPOINT& p) = 0;
	virtual BOOL GetLastSymbolSize(DPOINT& p) = 0;
	virtual DPOINT GetSymbolOffset(INT index) = 0;
	virtual DPOINT GetLastSymbolOffset() = 0;
	virtual VOID GetComponentPos(DPOINT& a, DPOINT& b) = 0;
	virtual BOOL GetLastSymbolArea(DPOINT& a, DPOINT& b, BOOL flag) = 0;
	virtual BOOL InsideComponent(DPOINT p) = 0;

	virtual TCHAR* GetAppDirectory(TCHAR* subfolder, BOOL reverse_flag) = 0;
	virtual LONG GetThreadTimeInterval() = 0;
	virtual BOOL GetProData(PRODATA& pro_data, BOOL backup = TRUE) = 0;
	virtual BOOL GetUserStatus(PROPCELL& status, INT mode) = 0;
	virtual VOID SetRegMemStatus(PROPCELLS* reg, PROPCELLS* mem, PROPCELLS* cmd) = 0;
	virtual VOID SetOutputInfo(TCHAR* str) = 0;

	virtual TCHAR* GetTCHARFromChar(CHAR* str) = 0;
	virtual CHAR* GetCharFromTCHAR(TCHAR* str) = 0;
	virtual BOOL TCHARCompare(TCHAR* str1, TCHAR* str2) = 0;
	
};

struct CDSIMMODEL
{
	virtual CDSIMMODEL* GetSimModel(TCHAR* device) = 0;
	virtual ICOMPONENT* GetComponentPtr() = 0;
	virtual LONG GetTimeInterval(INT dat) = 0;
	virtual BOOL IntervalProcess(RUNMODES mode) = 0;
	virtual VOID Initialize(ICOMPONENT* cpt, DSIMMODES smode) = 0;
	virtual VOID Setup(SIMDATA* sdat) = 0;
	virtual BOOL Simulate(ABSTIME time, RUNMODES mode) = 0;
	virtual VOID CallBack(ABSTIME time, EVENTID eventid) = 0;
	virtual BOOL Indicate(REALTIME time, ACTIVEDATA* data) = 0;
	virtual VOID Animate(INT element, ACTIVEDATA* data) = 0;
	virtual BOOL Plot(ACTIVESTATE state) = 0;
	virtual BOOL Actuate(WORD key, DPOINT p, UINT flags) = 0;
};

#endif _VSM_H