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
 
#include <Task32.h>

Task::Task(const char * _taskName, void(*_taskFunc)(void), uint32_t _period, taskPriority _priority, bool _isEnabled)
{
	taskName = _taskName;
	taskFunc = _taskFunc;
	period = _period;
	priority = _priority;
	isEnabled = _isEnabled;
}
Task::Task() {}
bool Task::run()
{
	currentTimeStamp = micros();
	if (executeNextAt >currentTimeStamp)
		return false;
	
		 avgerageRuntime -=  averageRuntimeHistory[ aveargeRuntimeIndex];
		 executeLastPeriod = currentTimeStamp -  executedLastAt;
		 executedLastAt = currentTimeStamp;
		 
	  taskFunc();
		 averageRuntimeHistory[ aveargeRuntimeIndex] = (micros() - (currentTimeStamp TASK_HISTORY_DIV));
		 avgerageRuntime +=  averageRuntimeHistory[aveargeRuntimeIndex];
		executeNextAt = currentTimeStamp +  period;
		aveargeRuntimeIndex = (aveargeRuntimeIndex == TASK_HISTORY_LENGTH - 1) ? 0 : +1;
		executeNextAt = currentTimeStamp + period;
		executeNextAtEstimatedFinish += aveargeRuntimeIndex;
		return true;
}
