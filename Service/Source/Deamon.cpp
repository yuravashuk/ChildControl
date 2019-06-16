
#include "../Includes/Deamon.h"

Deamon::Deamon() : 	_processId(0),
					_sessionId(0)//,
					//_filePtr(NULL)
{

}

Deamon::~Deamon()
{

}

int Deamon::Start()
{
    // Create child process
    _processId = fork();
    
    // Indication of fork() failure
    if (_processId < 0)
    {
        printf("fork failed!\n");
        // Return failure in exit status
        exit(1);
    }
    
    // PARENT PROCESS. Need to kill it.
    if (_processId > 0)
    {
        printf("process_id of child process %d \n", _processId);
        // return success in exit status
        exit(0);
    }
    
    //unmask the file mode
    umask(0);
    
    //set new session
    _sessionId = setsid();
    if(_sessionId < 0)
    {
        // Return failure
        exit(1);
    }
    
    // Change the current working directory to root.
    chdir("/");
    
    // Close stdin. stdout and stderr
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>0; x--)
    {
        close (x);
    }

	/* Open the log file */
    openlog ("service", LOG_PID, LOG_DAEMON);
	syslog (LOG_NOTICE, "service started\n");
    //printf("Started!\n");

	// Close stdin. stdout and stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
/*
	if (!InitSystem())
	{
		printf("Failed to init systems!\n");
		exit(1);
	}
*/
	InitSystem();

	return 0;
}

bool Deamon::KillProcess(const char* name) 
{
    pid_t p;
    size_t i;
    char* s = (char*)malloc(264);
    char buf[128];
    FILE* st;
    DIR* d = opendir("/proc");
    if (d == NULL) 
	{ 
		free(s); 
		return false; 
	}
    struct dirent* f;
    while ((f = readdir(d)) != NULL) 
	{
        if (f->d_name[0] == '.') continue;
        for (i = 0; isdigit(f->d_name[i]); i++);
        if (i < strlen(f->d_name)) continue;
        strcpy(s, "/proc/");
        strcat(s, f->d_name);
        strcat(s, "/status");
        st = fopen(s, "r");

        if (st == NULL) 
		{ 
			closedir(d); 
			free(s); 
			return false; 
		}

        do {
            if (fgets(buf, 128, st) == NULL) 
			{
				fclose(st); 
				closedir(d); 
				free(s); 
				return false; 
			}
        } while (strncmp(buf, "Name:", 5));
        fclose(st);

        for (i = 5; isspace(buf[i]); i++);
        *strchr(buf, '\n') = 0;

        if (!strcmp(&(buf[i]), name)) 
		{
            sscanf(&(s[6]), "%d", &p);
            kill(p, SIGKILL);
        }
    }
    closedir(d);
    free(s);
    return true;
}

bool Deamon::InitSystem()
{
	_webService = new WebService();
	if (!_webService->Initialize())
	{
		return false;
	}

	_threads[0] = std::thread(&WebService::ReceiveCommand, _webService);
	_threads[1] = std::thread(&WebService::UpdateLocalServer, _webService);
	_threads[2] = std::thread(&TimeController::Update, _timer);
	_threads[3] = std::thread(&Deamon::Run, this);

	for (size_t i = 0; i < 4; ++i)
		if (_threads[i].joinable()) _threads[i].join();
	
	return true;
}

void Deamon::Run()
{
	// Open a log file in write mode.
	// _filePtr = fopen ("Log.txt", "w+");
	while (true)
	{
		// Dont block context switches, let the process sleep for some time
		sleep(1);
		
#if PLATFORM == PLATFORM_LINUX
		system("killall 9 Telegram");
		if (KillProcess("Telegram"))
		{
			syslog (LOG_NOTICE, "Telegram killed...\n");
			//fprintf(_filePtr, "Telegram killed...\n");
			//fflush(_filePtr);
		}
#elif PLATFORM == PLATFORM_MAC
		system("killall 9 Telegram");
#endif
	}

	syslog (LOG_NOTICE, "service terminated\n");
    closelog();

	//fclose(_filePtr);
}




