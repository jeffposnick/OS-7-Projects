/* Prototypes */extern void main(void);extern void DoGestalt(void);extern void EventInit(void);extern void EventLoop(void);extern pascal OSErr DoOpenApp(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon);extern pascal OSErr DoOpenDoc(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon);extern pascal OSErr DoPrintDoc(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon);extern pascal OSErr DoQuitApp(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon);extern OSErr GotRequiredParams(AppleEvent *appleEventPtr);/* #Defines */#define kSleep	32767#define kFatalAlertID	128/* Globals */Boolean	gDone=FALSE;/* #Includes */#include "Header.h"