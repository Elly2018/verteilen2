package v2_core

type Project_Runtime struct {
	id              string  // Project Runtime ID
	bind            string  // Project ID
	state           int32   // 0: ready, 1: running, 2: finish
	workflow        string  // Current running workflow
	workflow_script *string // Current running workflow script
	step            int32   // Current workflow step
}

type Project_Runtime_Group struct {
	id       string   // Project Runtime Group ID
	projects []string // Project runtime IDs
}
