package api

import (
	"net/http"
	"verteilen2_server/api/admin"

	"github.com/gin-gonic/gin"
)

func Register_api(router *gin.Engine) {
	api := router.Group("/api")

	admin.Rregister_api_admin(api)

	api.GET("isinit", func(c *gin.Context) {
		c.String(http.StatusOK, "YES")
	})

	api.POST("init", func(c *gin.Context) {
		c.String(http.StatusOK, "YES")
	})

	api.POST("login", func(c *gin.Context) {
		c.String(http.StatusOK, "YES")
	})
}
