package main

import (
	"github.com/gin-gonic/gin"
)

func main() {
	r := gin.Default()

	// Get console menu
	r.Static("/", "static")

	r.Run(":8080")
}
