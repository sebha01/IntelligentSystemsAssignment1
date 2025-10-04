#pragma once

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>

enum Decision {
	WAIT,
	LEAVE
};