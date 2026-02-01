package v2_core

// Decide role's project permission
type ProjectPermission struct {
	id          string // Project ID
	view_task   bool
	modify_task bool
	delete_task bool
	view_job    bool
	modify_job  bool
	delete_job  bool
}

// Decide role's database permission
type DatabasePermission struct {
	id     string // Database ID
	view   bool   // Can view the data field content
	modify bool   // Can create, modify, delete data or data property
}

// Role data structure
type Role struct {
	id        string               // Role id
	owner     string               // Who own this role, this field should be user id
	level     int32                // 0: Admin, 1: Mod, 2: User, 3: Guest
	projects  []ProjectPermission  // The project which this role can be access
	databases []DatabasePermission // The database which this role can be access
}

// Contain multiple roles
type RoleGroup struct {
	id    string   // Role group id
	roles []string // Role id array
}
