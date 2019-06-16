
#include "../Includes/Common.hpp"

#if PLATFORM == PLATFORM_LINUX || PLATFORM == PLATFORM_MAC
	#include "../Includes/Deamon.h"
	typedef Deamon Service;
#else
	#include "../Includes/WinService.hpp"
	typedef WinService Service;
#endif

// Service instance
Service* kService;

#if PLATFORM == PLATFORM_LINUX || PLATFORM == PLATFORM_MAC
	int main(int argc, char** argv)
#else
	int _tmain(int argc, TCHAR *argv[])
#endif
{
	kService = new Service;
	kService->Start();

	return 0;
}
