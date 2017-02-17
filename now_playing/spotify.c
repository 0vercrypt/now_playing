#include "spotify.h"

int spotify (struct TrackInfo *info, struct TS3Functions ts3Functions) {
	HWND hSpotifyWindow = 0;
	wchar_t wcharWindowText[510];	
	char cWindowText[510];
	int iFound = 0, iStringLen = 0, iStrstrRet = 0;
	string strWindowTitle = "";
	size_t sizeTitleSize = 0;

	//printf("Entering spotify.c code:\n");
	//printf("\tStarting do\n");
	do {
		hSpotifyWindow = FindWindowEx (0, hSpotifyWindow, "SpotifyMainWindow", 0);
		if (hSpotifyWindow == 0) {
			break;
		}
		
		//printf("\tGetting window title info.\n");
		iStringLen = GetWindowTextW (hSpotifyWindow, wcharWindowText, 510);
		//printf("\tTitle length = %d\n", iStringLen);
		if (iStringLen <= 7) {
			continue;
		}
		//printf("\tConvert wide char to multibyte.\n");
		iStringLen = WideCharToMultiByte (CP_UTF8, 0, wcharWindowText, 
						wcslen (wcharWindowText), cWindowText, 
						510, 0, 0);
		//printf("\tcWindowText:  \"%s\"\n", cWindowText);
		strWindowTitle = cWindowText;

		/*
		sizeTitleSize = strWindowTitle.find(strFind);
		// following will need to be adjusted for Spotify
		iStringLen =  int(sizeTitleSize); 
		*/
		

		//printf("\tiStringLen = %d\n", iStringLen);
		if (iStringLen >= 1) {
			iFound = 1;

			cWindowText[iStringLen] = 0;
			strcpy_s (info->chTitle, sizeof (info->chTitle), cWindowText);
			info->chProgramm = "Spotify";

			break;
		}
		} while (hSpotifyWindow);
		
	//printf("\tExited Do.\n");
	//printf("Leaving spotify.c: iFound = %d\n", iFound);
	return iFound;
}