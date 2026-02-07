package admin

import (
	"context"
	"errors"
	"log"
	"net/http"
	"os"

	firebase "firebase.google.com/go"
	"firebase.google.com/go/auth"
	"github.com/gin-gonic/gin"
	"google.golang.org/api/option"
)

type VADMIN struct {
	app *firebase.App
}

func (v VADMIN) IsAuthFileExist() bool {
	_, err := os.Stat("auth.json")
	if errors.Is(err, os.ErrNotExist) {
		return false
	}
	return err == nil
}

func (v VADMIN) IsAppRegistered() bool {
	return v.app != nil
}

func (v VADMIN) Register_api_admin(router *gin.RouterGroup) {
	admin := router.Group("/admin")

	admin.POST("/setup_firebase", func(ctx *gin.Context) {
		file, err := ctx.FormFile("file")
		if err != nil {
			ctx.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}
		if err := ctx.SaveUploadedFile(file, "auth.json"); err != nil {
			ctx.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}
		v.app = initFirebase()
		var code int32
		if v.app == nil {
			code = 0
		} else {
			code = 1
		}
		ctx.JSON(http.StatusOK, gin.H{"status": code})
	})

	admin.POST("/setup_root", func(ctx *gin.Context) {
		bg := context.Background()
		if !v.IsAppRegistered() {
			ctx.JSON(http.StatusBadRequest, gin.H{"error": "App not registered yet"})
			return
		}
		email, err := ctx.GetPostForm("email")
		if err {
			ctx.JSON(http.StatusBadRequest, gin.H{"error": "Require email"})
			return
		}
		password, err := ctx.GetPostForm("password")
		if err {
			ctx.JSON(http.StatusBadRequest, gin.H{"error": "Require password"})
			return
		}
		authc, errr := v.app.Auth(bg)
		if errr != nil {
			ctx.JSON(http.StatusInternalServerError, gin.H{"error": errr.Error()})
			return
		}
		user := (&auth.UserToCreate{}).
			Email(email).
			Password(password)

		u, errr := authc.CreateUser(bg, user)
		if errr != nil {
			ctx.JSON(http.StatusInternalServerError, gin.H{"error": errr.Error()})
			return
		}

		log.Printf("Create root user: %s\n", u.UID)
		ctx.JSON(http.StatusOK, gin.H{"status": 0})
	})
}

func initFirebase() *firebase.App {
	opt := option.WithCredentialsFile("auth.json")
	app, err := firebase.NewApp(context.Background(), nil, opt)
	if err != nil {
		log.Printf("error initializing app: %v\n", err)
	}
	return app
}
