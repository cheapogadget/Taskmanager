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
#include "Task32.h"
#include "TaskManager32.h"

char emptyString[] = "Empty";
uint32_t rundown = 0;
bool TaskManager::update()
{
	//Serial.println(rundown);
	if (rundown > micros())
		return false;
	// return true if a run occurs
	bool ret=false;
	// loop variable to track inner runs
	bool ran = false;
	// nextlowest value not ran
	uint32_t	nextLowest = UINT32_MAX;
	currentTimeStamp = micros();

		for (int i = 0; i < taskCount;i++)
		{
			
		 
			// bail if encounter disabled or empyt task..they should sort to bottom.
			if (taskPtr[i]->isEnabled == false || taskPtr[i]->IsNotEmpty == false)
				break;
				if (taskPtr[i]->run())
				{ 
					ran = ret  = true;
				currentTimeStamp = micros();
				}
	
		}
	 
		 if ( (ran ))
		{ 
			sort();
			currentTimeStamp = micros();
			//nextLowest = UINT32_MAX;
			for (int i = 0; i < taskCount;i++)
				if(taskPtr[i]->isEnabled && taskPtr[i]->IsNotEmpty )
					nextLowest = nextLowest > taskPtr[i]->executeNextAt   ? taskPtr[i]->executeNextAt : nextLowest;
			rundown = nextLowest > micros() ? nextLowest - 500 : micros();

		 }

	return ret;
}
void TaskManager ::init(Task * t, int ss )
{
	taskCount = ss;
 
	int i = 0;
 
	for (i = 0; i < taskCount; i++)
	{
		taskPtr[i] = &t[i];
		taskPtr[i]->IsNotEmpty = true;
		taskPtr[i]->executeNextAt = micros() + taskPtr[i]->period;
		Serial.println(taskPtr[i]->executeNextAt);
	}
	for (i = i; i < TASKS_SIZE_EMPTY_DEFAULT; i++)
	{
		taskPtr[i] = &tasks[i - taskCount];
		taskPtr[i]->IsNotEmpty = false;
		taskPtr[i]->taskName = emptyString;
		taskPtr[i]->priority = TASK_PRIORITY_IDLE;
	}


}
// Sort task pointer by IsNotEmpty=True ^ IsEnabled =true ^ Priority ^ - period width ^
void TaskManager::sort()
{
	Task *  temp;
	int i, j, flag = 1;    // set flag to 1 to start first pass
						   // ("", nullptr, 0);             // holding variable
	int numLength = TASKS_SIZE_EMPTY_DEFAULT;

	for (i = 1; (i <= numLength) && flag; i++)
	{
		flag = 0;
		for (j = 0; j < (numLength - 1); j++)
		{
			if (sort_alg(taskPtr[j + 1], taskPtr[j]))
			{
				temp = taskPtr[j];             // swap elements
				taskPtr[j] = taskPtr[j + 1];
				taskPtr[j + 1] = (temp);
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
}
bool TaskManager::sort_alg(Task *a, Task   *b)
{
	if (a->IsNotEmpty != b->IsNotEmpty)
		return a->IsNotEmpty > b->IsNotEmpty;
	if (a->isEnabled != b->isEnabled)
		return a->isEnabled > b->isEnabled;

	 if (a->priority != b->priority)
		return a->priority > b->priority;

	return a->executeNextAt < b->executeNextAt;
}
TaskManager  taskManager;

