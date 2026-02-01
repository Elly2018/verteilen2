package v2_core

// Compute node structure
type Node struct {
	id    string  // Node ID
	owner *string // Owner user ID
}

// Compute proxy structure
type Proxy struct {
	id     string   // Proxy ID
	owner  *string  // Owner user ID
	direct bool     // true: Node - Server, false: Node - Proxy - Server
	node   []string // Downstream nodes IDs
}

// Compute database structure
type Database struct {
	id    string  // Project ID
	owner *string // Owner user ID
}

// Compute job structure
type Job struct {
	id       string   // Job ID
	args     []string // Arguments
	category int32    // 0: Condition, 1: Execution
	jobtype  string   // The job type
}

// Compute workflow structure
type Workflow struct {
	id     string   // Workflow ID
	script *string  // The script content
	kind   int32    // 0: Single node, 1: Multiple node, 2: Multiple node with multithread, 3: Multiple node setup, 4: Script
	job    []string // Job IDs
}

// Compute project structure
type Project struct {
	id          string   // Project ID
	owner       *string  // Owner user ID
	name        string   // Project Name
	description *string  // Project description
	mode        int32    // 0: Waterfall, 1: Script
	Workflow    []string // Workflow IDs
}

// Compute scheduler structure
type Scheduler struct {
	id    string // Scheduler ID
	owner string // Owner user ID
}
