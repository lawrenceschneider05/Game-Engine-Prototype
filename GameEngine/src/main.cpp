#include "core/application.h"
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free

#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using namespace GameEngine;

int main() {
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot

	Application app{};
	app.init();
	app.run();
	

	glfwTerminate();
	//int* a = new int(sizeof(int) * 10);
	_CrtMemCheckpoint(&sNew); //take a snapshot 

	
	if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
	{
		/*OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
		_CrtMemDumpStatistics(&sDiff);
		OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
		_CrtMemDumpAllObjectsSince(&sOld);*/
		OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
		_CrtDumpMemoryLeaks();
	}
	
	return 1;
}