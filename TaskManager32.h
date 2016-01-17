//	written by : Doug Reuter
//	TaskManager32 - Manage task functions on 32bt arduino bords such as ( due or zero)
//	may work on other arduino boards as well
//	http://cheapogadget.com   https://github.com/cheapogadget/Taskmanager32
//	Copyright (C) 2016 Doug Reuter   dougreuter@gmail.com

//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.

//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.
//	TaskManager.h
#ifndef _TASKMANAGER_h
#define _TASKMANAGER_h
	#include <Arduino.h>
	#include <Task32.h>

#define TASKS_SIZE_EMPTY_DEFAULT 10

class TaskManager 
{
 protected:
	 uint32_t currentTimeStamp;
	 bool sort_alg(Task *a, Task   *b);
	 Task   tasks[TASKS_SIZE_EMPTY_DEFAULT];
	
 public:
	void init(Task * t, int ss);
	void sort();
	bool update();
	int taskCount;
	Task * taskPtr[TASKS_SIZE_EMPTY_DEFAULT];
};

extern TaskManager taskManager;
 
#endif

