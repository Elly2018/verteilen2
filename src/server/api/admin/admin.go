package admin

import "github.com/gin-gonic/gin"

func Rregister_api_admin(router *gin.RouterGroup) {
	router.Group("/admin")
}
