package v2_core

import "time"

// User data structure
type User struct {
	uid       string      // Authentication UID
	id        string      // Local database ID
	username  string      // Username
	password  string      // Hash result password
	phone     *string     // Phone number
	email     *string     // User email, For password reset or notification
	gender    *string     // Private info
	birthday  *time.Time  // Private info
	roleGroup []RoleGroup // Permission group array
}
