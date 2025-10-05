#include "ApplicationManager.h"

int main()
{
	//Call applicationManager object
	ApplicationManager appMgr;

	//Initialise the screen
	appMgr.init();
	//Run main loop
	appMgr.update();

	return 0;
}