package v2_core

import "time"

type Job_Log struct {
	id    string    // Job Log ID
	bind  string    // Job ID
	start time.Time // Job start datetime
	node  string    // Execute by node ID
	logs  []string  // Log data
}

type Workflow_Log struct {
	id    string    // Workflow Log ID
	bind  string    // Workflow ID
	start time.Time // Workflow start datetime
	state int32     // 0: Ready, 1: Running, 2: Failed
	job   []Job_Log // The job detail logs
}

type Project_Log struct {
	id       string         // Project Log ID
	bind     string         // Project ID
	kind     int32          // 0: Manually, 1: scheduler
	start    time.Time      // Project start datetime
	workflow []Workflow_Log // Workflow log content
}
