/* #Defines */#define kFatalAlertID		128#define kDefaultTextCreator	'ttxt'#define kDefaultClipCreator	'drag'#define kNetscapeCreator	'MOSS'#define kTestText			"<!DOCTYPE NETSCAPE-Bookmark-file-1>"#define kStartOfURL			"<A HREF=\""#define kSleep				32767/* Globals */Boolean	gDone=FALSE;/* Prototypes */extern void main(void);extern void EventInit(void);extern void DoGestalt(void);extern pascal OSErr DoOpenApp(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon);extern pascal OSErr DoOpenDoc(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon);extern void DoTouch(FSSpec spec);extern void DoGetFolder(void);extern void DoChangeCreator(FSSpec spec);extern void DoConvertNetscape(FSSpec spec);extern pascal OSErr GetDirItems(short vRefNum, long dirID, StringPtr name, Boolean getFiles, Boolean getDirectories, FSSpecPtr items, short reqItemCount, short *actItemCount, short *itemIndex);extern pascal OSErr DirIDFromFSSpec(const FSSpec *spec, long *dirID, Boolean *isDirectory);extern pascal OSErr DoPrintDoc(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon);extern pascal OSErr DoQuitApp(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon);extern void EventLoop(void);/* #Includes */#include "Header.h"