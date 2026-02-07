package main

import (
	"log"
	"verteilen2_server/api"

	"github.com/gin-gonic/gin"

	socketio "github.com/googollee/go-socket.io"
)

func main() {
	router := gin.New()

	socket_server := get_server()
	socket_proxy := get_proxy()
	socket_node := get_node()

	go func() {
		if err := socket_server.Serve(); err != nil {
			log.Fatalf("socketio listen error server: %s\n", err)
		}
	}()
	go func() {
		if err := socket_proxy.Serve(); err != nil {
			log.Fatalf("socketio listen error proxy: %s\n", err)
		}
	}()
	go func() {
		if err := socket_node.Serve(); err != nil {
			log.Fatalf("socketio listen error node: %s\n", err)
		}
	}()
	defer socket_server.Close()
	defer socket_proxy.Close()
	defer socket_node.Close()

	router.GET("/socket/server", gin.WrapH(socket_server))
	router.POST("/socket/server", gin.WrapH(socket_server))
	router.GET("/socket/proxy", gin.WrapH(socket_proxy))
	router.POST("/socket/proxy", gin.WrapH(socket_proxy))
	router.GET("/socket/node", gin.WrapH(socket_node))
	router.POST("/socket/node", gin.WrapH(socket_node))
	router.Static("/view", "static")

	api.Register_api(router)

	if err := router.Run(":8000"); err != nil {
		log.Fatal("failed run app: ", err)
	}
}

func get_server() *socketio.Server {
	server := socketio.NewServer(nil)

	server.OnConnect("/", func(s socketio.Conn) error {
		s.SetContext("")
		log.Println("connected:", s.ID())
		return nil
	})

	server.OnEvent("/", "notice", func(s socketio.Conn, msg string) {
		log.Println("notice:", msg)
		s.Emit("reply", "have "+msg)
	})

	server.OnError("/", func(s socketio.Conn, e error) {
		log.Println("meet error:", e)
	})

	server.OnDisconnect("/", func(s socketio.Conn, reason string) {
		log.Println("closed", reason)
	})
	return server
}

func get_proxy() *socketio.Server {
	server := socketio.NewServer(nil)

	server.OnConnect("/", func(s socketio.Conn) error {
		s.SetContext("")
		log.Println("connected:", s.ID())
		return nil
	})

	server.OnEvent("/", "notice", func(s socketio.Conn, msg string) {
		log.Println("notice:", msg)
		s.Emit("reply", "have "+msg)
	})

	server.OnEvent("/chat", "msg", func(s socketio.Conn, msg string) string {
		s.SetContext(msg)
		return "recv " + msg
	})

	server.OnEvent("/", "bye", func(s socketio.Conn) string {
		last := s.Context().(string)
		s.Emit("bye", last)
		s.Close()
		return last
	})

	server.OnError("/", func(s socketio.Conn, e error) {
		log.Println("meet error:", e)
	})

	server.OnDisconnect("/", func(s socketio.Conn, reason string) {
		log.Println("closed", reason)
	})
	return server
}

func get_node() *socketio.Server {
	server := socketio.NewServer(nil)

	server.OnConnect("/", func(s socketio.Conn) error {
		s.SetContext("")
		log.Println("connected:", s.ID())
		return nil
	})

	server.OnEvent("/", "notice", func(s socketio.Conn, msg string) {
		log.Println("notice:", msg)
		s.Emit("reply", "have "+msg)
	})

	server.OnEvent("/chat", "msg", func(s socketio.Conn, msg string) string {
		s.SetContext(msg)
		return "recv " + msg
	})

	server.OnEvent("/", "bye", func(s socketio.Conn) string {
		last := s.Context().(string)
		s.Emit("bye", last)
		s.Close()
		return last
	})

	server.OnError("/", func(s socketio.Conn, e error) {
		log.Println("meet error:", e)
	})

	server.OnDisconnect("/", func(s socketio.Conn, reason string) {
		log.Println("closed", reason)
	})
	return server
}
