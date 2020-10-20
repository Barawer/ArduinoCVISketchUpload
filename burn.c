int Burn(char *filename,int com)
	{
		char commend[1000],folder[1000];
		int size = 0,result;
		FILE *f;
		remove("log.txt");
		GetFullPathFromProject ("arduino_ino", folder);
		DisableBreakOnLibraryErrors ();
		result = MakeDir (folder);
		if (result != -9 && result != 0)
		{
			EnableBreakOnLibraryErrors();
			return 0;
		}
		CopyFile (filename, folder);
		sprintf (commend, "cmd.exe /c arduino_debug  --port COM%d --upload %s\\%s & >log.txt call echo %%^errorlevel%%",com,folder,filename);
		system(commend);
		f = fopen ("log.txt", "r");
		fscanf (f, "%d", &result);
		fclose(f);
		if(result == 0)
		{
			result = 1;
		}
		else
		{
			result = 0;
		}
		remove("log.txt");
		sprintf(folder,"arduino_ino\\%s",filename);
		remove(folder);
		DeleteDir ("arduino_ino");
		EnableBreakOnLibraryErrors();
		return result;
	}
