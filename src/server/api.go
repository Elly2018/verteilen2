package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func register_api(router *gin.Engine) {
	api := router.Group("/api")
	api.GET("isinit", func(c *gin.Context) {
		c.String(http.StatusOK, "YES")
	})
}
