#include "wmp.h"

int wmp (struct TrackInfo *info, struct TS3Functions ts3Functions) {
	HWND hWmpWindow = 0;
	wchar_t wcharWindowText[510];	
	char cWindowText[510];
	int iFound = 0, iStringLen = 0, iStrstrRet = 0;
	string strFind = " - Windows Media Player", strWindowTitle = "";
	size_t sizeTitleSize = 0;

	// printf("Entering wmp.c code:\n");
	// printf("\tStarting do\n");
	do {
		hWmpWindow = FindWindowEx (0, hWmpWindow, "WMPlayerApp", 0);
		if (hWmpWindow == 0) {
			break;
		}
		
		// printf("\tGetting window title info.\n");
		iStringLen = GetWindowTextW (hWmpWindow, wcharWindowText, 510);
		// printf("\tTitle length = %d\n", iStringLen);
		if (iStringLen <= 7) {
			continue;
		}
		// printf("\tConvert wide char to multibyte.\n");
		iStringLen = WideCharToMultiByte (CP_UTF8, 0, wcharWindowText, 
						wcslen (wcharWindowText), cWindowText, 
						510, 0, 0);
		// printf("\tcWindowText:  \"%s\"\n", cWindowText);
		strWindowTitle = cWindowText;

		
		sizeTitleSize = strWindowTitle.find(strFind);
		// following will need to be adjusted for Wmp
		sizeTitleSize = strWindowTitle.find(strFind);
		iStringLen =  int(sizeTitleSize); 
		
		

		// printf("\tiStringLen = %d\n", iStringLen);
		//if (strstr (cWindowText, " - ") != 0 && iStringLen >= 1) { 

		if (strstr (cWindowText, " - ") != 0 && iStringLen >= 10) { 
			int iFixOutput = 0;
			iFound = 1;

			// printf("\tcWindowText before: \"%s\"\n", cWindowText);
			memcpy (cWindowText, cWindowText, (iStringLen)); /* remove " - Windows Media Player" */
			/* for (int iFixOutput = 0; iFixOutput < iStringLen - 10; iFixOutput++) {
				cWindowText[iFixOutput] = cWindowText[iFixOutput + 10]; 
				//iFixOutput++;
			} */
			// printf("\tcWindowText after:  \"%s\"\n", cWindowText);
		
			// iStringLen -= 23; /* 23 = length of " - Windows Media Player" */
			cWindowText[iStringLen] = 0;
			strcpy_s (info->chTitle, sizeof (info->chTitle), cWindowText);
			info->chProgramm = "WMP";

			break;
		}
		} while (hWmpWindow);
		
	// printf("\tExited Do.\n");
	// printf("Leaving wmp.c: iFound = %d\n", iFound);
	return iFound;
}