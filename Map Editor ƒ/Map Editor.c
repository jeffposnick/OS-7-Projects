/* Includes */#include "Map Editor.h"void main(void){	ToolboxInit();		MakeMenus();		LoadIcons();		EventInit();		EventLoop();}void MakeMenus(void){	short		i, numIcons;	Handle 		menuBar;	MenuHandle 	menuHandle;		menuBar=GetNewMBar(kMenuBarID);	SetMenuBar(menuBar);	DisposeHandle(menuBar);		menuHandle=GetMHandle(mApple);	AppendResMenu(menuHandle, kAppleMenuItems);		menuHandle=GetMHandle(mIcons);	AppendResMenu(menuHandle, kIconType);		numIcons=Count1Resources(kIconType);		for(i=1; i<=numIcons; i++)		SetItemIcon(menuHandle, i, i);		DrawMenuBar();}void LoadIcons(void){	short	i, numIcons;		numIcons=Count1Resources(kIconType);	icons=(CIconHandle *)NewPtrClear(numIcons*sizeof(CIconHandle));		for(i=0; i<numIcons; i++)		icons[i]=GetCIcon(i);}void EventInit(void){	OSErr	err;		OAPPHandlerUPP=NewAEEventHandlerProc(DoOpenApp);	err=AEInstallEventHandler(kCoreEventClass, kAEOpenApplication, OAPPHandlerUPP, nil, false);	if(err!=noErr)		DoError("\pProblem installing AppleEvent handler!", (long)err, 723);			ODOCHandlerUPP=NewAEEventHandlerProc(DoOpenDoc);	err=AEInstallEventHandler(kCoreEventClass, kAEOpenDocuments, ODOCHandlerUPP, nil, false);	if(err!=noErr)		DoError("\pProblem installing AppleEvent handler!", (long)err, 724);			PDOCHandlerUPP=NewAEEventHandlerProc(DoPrintDoc);	err=AEInstallEventHandler(kCoreEventClass, kAEPrintDocuments, PDOCHandlerUPP, nil, false);	if(err!=noErr)		DoError("\pProblem installing AppleEvent handler!", (long)err, 725);			QUITHandlerUPP=NewAEEventHandlerProc(DoQuitApp);	err=AEInstallEventHandler(kCoreEventClass, kAEQuitApplication, QUITHandlerUPP, nil, false);	if(err!=noErr)		DoError("\pProblem installing AppleEvent handler!", (long)err, 723);}pascal OSErr DoOpenApp(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon){	DoNewMap();		return noErr;}pascal OSErr DoOpenDoc(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon){	AEDescList	fileSpecList;	FSSpec		spec;	OSErr		err;	DescType	type;	Size		actual;	AEKeyword	keyword;	long		count, i;		err=AEGetParamDesc(theAppleEvent, keyDirectObject, typeAEList, &fileSpecList);	if(err!=noErr)		DoError("\pAppleEvent related error!", (long)err, 2);		err=GotRequiredParams(theAppleEvent);	if(err!=noErr)		DoError("\pAppleEvent related error!", (long)err, 3);			err=AECountItems(&fileSpecList, &count);	if(err!=noErr)		DoError("\pAppleEvent related error!", (long)err, 4);			if(count!=1L)		DoError("\pOnly one map can be opened at a time!", count, 5);		for(i=1; i<=count; i++)	{		err=AEGetNthPtr(&fileSpecList, i, typeFSS, &keyword, &type, (Ptr)&spec, sizeof(FSSpec), &actual);		if(err!=noErr)			DoError("\pAppleEvent related error!", (long)err, 6);			DoOpenMap(spec);	}		return noErr;}void DoOpenMap(FSSpec theSpec){}pascal OSErr DoPrintDoc(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon){	DoError("\pPrinting is not supported!", 0, 8);		return noErr;}pascal OSErr DoQuitApp(AppleEvent *theAppleEvent, AppleEvent *reply, long refCon){	DoQuit();		return noErr;}void DoNewMap(void){	DialogPtr	theDialog;	Boolean		done=false;	Handle		theItem;	Rect		theRect;	Str255		tempStr;	short		theType, itemHit;		theDialog=GetNewDialog(kDialogID, nil, kMoveToFront);		SetDialogDefaultItem(theDialog, dOK);	SetDialogTracksCursor(theDialog, true);	SelectDialogItemText(theDialog, dWidth, 0L, 32767L);		ShowWindow(theDialog);	SetPort(theDialog);		while(!done)	{		ModalDialog(nil, &itemHit);				if(itemHit==dOK)			done=true;	}		GetDialogItem(theDialog, dWidth, &theType, &theItem, &theRect);	GetDialogItemText(theItem, tempStr);	StringToNum(tempStr, &gWidth);	GetDialogItem(theDialog, dHeight, &theType, &theItem, &theRect);	GetDialogItemText(theItem, tempStr);	StringToNum(tempStr, &gHeight);		DisposeDialog(theDialog);	DoSetupWindow(gWidth, gHeight);}void DoSetupWindow(short height, short width){	//ControlHandle	scrollHandle;	//Rect			rect;	QDErr			qdErr;	Rect			theRect;		gMap=(short *)NewPtrClear(height*width*sizeof(short));		SetRect(&theRect, kLeft, kTop, (width*kIconSize)+kLeft, (height*kIconSize)+kTop);		if((gMapWindow=NewCWindow(nil, &theRect, "\pUntitled Map", false, 8, kMoveToFront, true, nil))==nil)		DoError("\pProblem creating window!", 0, 9);			qdErr=NewGWorld(&gMapWorld, 0, &theRect, nil, nil, nil);	if(qdErr!=noErr)		DoError("\pCan't create GWorld", qdErr, 43);		gOffScreenPixels=GetGWorldPixMap(gMapWorld);			ShowWindow(gMapWindow);	SetPort(gMapWindow);		SetRect(&theRect, 32, 32, 64, 64);	PrepareToDraw(gMapWorld);	PlotCIcon(&theRect, icons[1]);	FinishDraw(gMapWorld);		/*rect=tempWindow->portRect;	rect.top-=1;	rect.bottom+=1;	rect.left=(rect.right)-kScrollBarWidth+1;	rect.right+=1;		if((scrollHandle=NewControl(tempWindow, &rect, kEmptyString, kVisable, kStartValue, kMinValue, width, scrollBarProc, nil))==nil)		DoError("\pProblem creating scrollbars!", nil, 10);*/}void PrepareToDraw(GWorldPtr theWorld){	GetGWorld(&gPort, &gDevice);	SetGWorld(theWorld, nil);	if(!(LockPixels(GetGWorldPixMap(theWorld))))		DebugStr("\pGWorld was purged");}void FinishDraw(GWorldPtr theWorld){	UnlockPixels(GetGWorldPixMap(theWorld));	SetGWorld(gPort, gDevice);}void HandleDialogEvent(EventRecord *theEvent){}void EventLoop(void){	/* Local Variables */	EventRecord event;	WindowPtr	tmpWindow;	char 		theChar;	short 		thePart;		while(gDone==false)	{		WaitNextEvent(everyEvent, &event, kSleep, nil);				//if(IsDialogEvent(&event))		//	HandleDialogEvent(&event);		//else		//{			switch(event.what)			{				case keyDown:				case autoKey:					theChar=(event.message&charCodeMask);					if((event.modifiers&cmdKey)!=0)						HandleMenuChoice(MenuKey(theChar));				break;								case kHighLevelEvent:					AEProcessAppleEvent(&event);				break;								case mouseDown:					thePart=FindWindow(event.where, &tmpWindow);					switch(thePart)					{						case inMenuBar:							HandleMenuChoice(MenuSelect(event.where));						break;											case inSysWindow:							SystemClick(&event, tmpWindow);						break;											case inContent:							if(tmpWindow==FrontWindow())								DoClick(&event);							else								SelectWindow(tmpWindow);						break;					}				break;							case updateEvt:					tmpWindow=(WindowPtr)event.message;					SetPort(tmpWindow);					BeginUpdate(tmpWindow);					//DrawMap(tmpWindow);					EndUpdate(tmpWindow);				break;			}		//}	}}void DrawMap(WindowPtr tmpWindow){	CopyBits((BitMap *)(*gOffScreenPixels), (BitMap *)&(tmpWindow->portBits), &(tmpWindow->portRect), &(tmpWindow->portRect), srcCopy, nil);}void DoClick(EventRecord *theEvent){	/*short	x, y, i, j;	char	theChar;	Point	temp, p;	Rect	tempRect, theRect;		p=theEvent->where;	GlobalToLocal(&p);	x=(p.h-(p.h%kIconSize));	y=(p.v-(p.v%kIconSize));		theChar=(theEvent->message&charCodeMask);	if((theEvent->modifiers&shiftKey)!=0)	{		while(Button())		{			GetMouse(&temp);			theRect=DrawBoundingBox(p, temp);		}				theRect.top%=kIconSize;		theRect.left%=kIconSize;		theRect.right%=kIconSize;		theRect.bottom%=kIconSize;				for(i=theRect.left; i<theRect.right; i++)			for(j=theRect.top; j<theRect.bottom; j++)			{				gMap[j*gWidth+1+x]=gIconNum-1;				tempRect.left=theRect.left+kIconSize*i;				tempRect.right=tempRect.left+kIconSize;				tempRect.top=theRect.top+kIconSize*j;				tempRect.bottom=tempRect.top+kIconSize;								PrepareToDraw(gMapWorld);				PlotCIcon(&tempRect, icons[gIconNum-1]);				FinishDraw(gMapWorld);				InvalRect(&tempRect);			}	}	else	{		theRect.top=y;		theRect.bottom=y+kIconSize;		theRect.left=x;		theRect.right=x+kIconSize;			gMap[y*gWidth+1+x]=gIconNum-1;		PrepareToDraw(gMapWorld);		PlotCIcon(&theRect, icons[gIconNum-1]);		FinishDraw(gMapWorld);		InvalRect(&tempRect);	}*/}Rect DrawBoundingBox(Point p1, Point p2){	/*Rect	theRect;		if(p1.h<p2.h)	{		theRect.left=p1.h;		theRect.right=p2.h;	}	else	{		theRect.left=p2.h;		theRect.right=p1.h;	}		if(p1.v<p2.v)	{		theRect.top=p1.v;		theRect.bottom=p2.v;		}	else	{		theRect.top=p2.v;		theRect.bottom=p1.v;	}		while(theRect.bottom%kIconSize!=0)		theRect.bottom++;	while(theRect.right%kIconSize!=0)		theRect.right++;	while(theRect.left%kIconSize!=0)		theRect.left--;	while(theRect.top%kIconSize!=0)		theRect.top--;			FrameRect(&theRect);		return theRect;*/}void HandleMenuChoice(long menuChoice){	/* Local Variables */	MenuHandle 		appleMenu;	Str255 			accName;	short 			menu, menuItem;		if(menuChoice>0)	{		menu=HiWord(menuChoice);		menuItem=LoWord(menuChoice);				switch(menu)		{			case mApple:				switch(menuItem)				{					case iAbout:						Alert(kAboutBoxID, nil);					break;										default:						appleMenu=GetMHandle(mApple);						GetItem(appleMenu, menuItem, accName );						OpenDeskAcc(accName);					break;				}			break;						case mFile:				switch(menuItem)				{					case iQuit:						DoQuit();					break;				}			break;						case mEdit:						break;						case mIcons:				gIconNum=menuItem;		}				HiliteMenu(0);	}}void DoQuit(void){	ExitToShell();}