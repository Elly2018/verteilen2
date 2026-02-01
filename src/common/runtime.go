package v2_core

type Project_Runtime struct {
	id              string  // Project Runtime ID
	bind            string  // Project ID
	state           int32   // 0: ready, 1: running, 2: finish
	Workflow        string  // Current running workflow
	Workflow_script *string // Current running workflow script
}
