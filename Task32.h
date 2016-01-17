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
// Task.h

#ifndef _TASK_h
#define _TASK_h

#include "arduino.h"

#define TASK_PRIORITY_DEFAULT TASK_PRIORITY_MEDIUM
enum taskPriority
{
	TASK_PRIORITY_IDLE,
	TASK_PRIORITY_LOW,
	TASK_PRIORITY_MEDIUM,
	TASK_PRIORTY_HIGH,
	TASK_PRIORITY_CRITICAL,
	TASK_PRIORITY_COUNT
};

#define TASK_HISTORY_LENGTH   8
#define TASK_HISTORY_DIV >>3    
class Task
{
protected:
	uint32_t currentTimeStamp;

public:
	const char * taskName;		// Name of task
	void(*taskFunc)(void);		// Task function pointer
	bool isEnabled;			// IsEnabled = Run
	uint32_t period;			// Period in microseconds

								/* Scheduling */
	uint32_t executedLastAt;    // last time of invocation
	uint32_t executeNextAt;    // time of invocation event for event-driven tasks
	uint32_t executeLastPeriod;
	uint32_t executeNextAtEstimatedFinish;
	 
	taskPriority priority;   // priority

	uint16_t avgerageRuntime;
	uint16_t averageRuntimeHistory[TASK_HISTORY_LENGTH];
	uint8_t aveargeRuntimeIndex;

	bool IsNotEmpty;
	Task(const char * _taskName, void(*_taskFunc)(void), uint32_t _period, taskPriority _priority = TASK_PRIORITY_DEFAULT, bool _isEnabled = true);
	Task();
	bool run();
};



#endif

