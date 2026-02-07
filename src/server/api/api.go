package api

import (
	"net/http"
	"verteilen2_server/api/admin"

	"github.com/gin-gonic/gin"
)

type VAPI struct {
}

func (v VAPI) Register_api(router *gin.Engine) {
	api := router.Group("/api")
	var vadmin admin.VADMIN
	vadmin.Register_api_admin(api)

	api.GET("isinit", func(ctx *gin.Context) {
		ctx.JSON(http.StatusOK, gin.H{
			"status": vadmin.IsAppRegistered(),
		})
	})

	api.POST("login", func(ctx *gin.Context) {
		ctx.String(http.StatusOK, "YES")
	})
}
