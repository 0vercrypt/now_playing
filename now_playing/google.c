#include "google.h"

int google (struct TrackInfo *info, struct TS3Functions ts3Functions) {
	HWND hBrowserWindow = 0;
	//wchar_t wcharWindowText[500];	
	char cWindowText[500];
	int iFound = 0, iStringLen = 0, iStrstrRet = 0, 
		iLookingFirefox = 0, iLookingIE = 0, iLookingGChrome = 1;
	string strFind = " - Google Play Music", strWindowTitle = "";
	size_t sizeTitleSize = 0;

	//printf("Entering google.c code:\n");
	//printf("\tStarting do\n");
	do {
		if (iLookingFirefox) hBrowserWindow = FindWindowEx (0, hBrowserWindow, "MozillaWindowClass", 0);
		if (iLookingIE) hBrowserWindow = FindWindowEx (0, hBrowserWindow, "IEFrame", 0);
		if (iLookingGChrome) hBrowserWindow = FindWindowEx (0, hBrowserWindow, "Chrome_WidgetWin_1", 0);
		//printf("\thBrowserWindow = %d\n", hBrowserWindow);
		if (hBrowserWindow == 0) {
			if (iLookingFirefox) {
				//printf("\tSwitching to looking for IE windows.\n");
				iLookingFirefox = 0;
				iLookingIE = 1;
				continue;
			} else if (iLookingIE) {
				iLookingIE = 0;
				//iLookingGChrome =1;
				break;
				//continue;
			} else if (iLookingGChrome) {
				//printf("\tSwitching to looking for Firefox windows.\n");
				iLookingGChrome = 0;
				iLookingFirefox = 1;
				//break;
				continue;
			} else {
				//Should not get here
				break;
			}

		}
		//printf("\tGetting window title info.\n");
		//iStringLen = GetWindowTextW (hBrowserWindow, wcharWindowText, 500);
		// printf("\tTitle length = %d and wide contains %s\n", iStringLen, wcharWindowText);
		iStringLen = GetWindowText (hBrowserWindow, cWindowText, 500);
		//printf("\tTitle length = %d and contains %s\n", iStringLen, cWindowText);
		if (iStringLen == 0) {
			continue;
		}
		//printf("\tConvert wide char to multibyte.\n");
		//iStringLen = WideCharToMultiByte (CP_UTF8, 0, wcharWindowText, 
		//				wcslen (wcharWindowText), cWindowText, 
		//				500, 0, 0);
		strWindowTitle = cWindowText;
		sizeTitleSize = strWindowTitle.find(strFind);
		// following will need to be adjusted for Google
		iStringLen =  int(sizeTitleSize); 
		
		//printf("\tiStringLen = %d\n", iStringLen);
		if (strstr (cWindowText, " - Google Play Music") != 0 && iStringLen >= 1
				&& strstr (cWindowText, "Listen Now - Google Play Music") == 0
				&& strstr (cWindowText, "Last added - Google Play Music") == 0
				&& strstr (cWindowText, "Artists - Google Play Music") == 0
				&& strstr (cWindowText, "Albums - Google Play Music") == 0
				&& strstr (cWindowText, "Songs - Google Play Music") == 0
				&& strstr (cWindowText, "Genres - Google Play Music") == 0
				&& strstr (cWindowText, "Radio - Google Play Music") == 0
				&& strstr (cWindowText, "Recommendations - Google Play Music") == 0
				&& strstr (cWindowText, "Featured - Google Play Music") == 0
				&& strstr (cWindowText, "New Releases - Google Play Music") == 0
				&& strstr (cWindowText, "Queue - Google Play Music") == 0
				&& strstr (cWindowText, "Thumbs up - Google Play Music") == 0
				&& strstr (cWindowText, "Last added - Google Play Music") == 0
				&& strstr (cWindowText, "Free and purchased - Google Play Music") == 0) { 

			iFound = 1;

			memcpy (cWindowText, cWindowText, (iStringLen)); /* remove " - Google Play Music.." */
			cWindowText[iStringLen] = 0;
			strcpy_s (info->chTitle, sizeof (info->chTitle), cWindowText);
			info->chProgramm = "Google Play";

			break;
		}
		} while (iLookingFirefox || iLookingIE || iLookingGChrome);
		
	//printf("\tExited Do.\n");
	//printf("Leaving google.c: iFound = %d\n", iFound);
	return iFound;
}