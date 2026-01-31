package main

import (
	"fmt"
	"log"

	socketio_client "github.com/zhouhui8915/go-socket.io-client"
)

func main() {
	var uri string
	var pass bool = false
	var client *socketio_client.Client

	opts := &socketio_client.Options{
		Transport: "websocket",
		Query:     make(map[string]string),
	}

	fmt.Print("Welcome be verilen2 node.\n")

	for !pass {
		fmt.Print("Please enter your server address: ")
		fmt.Scanln(&uri)
		fmt.Printf("Trying to connect to server: %s\n", uri)

		buffer, err := socketio_client.NewClient(uri, opts)
		if err != nil {
			log.Printf("Failed to create client: %v\n", err)
			continue
		}
		client = buffer
		pass = true
	}

	// Handle connection event
	client.On("connection", func() {
		log.Println("Connected to server")
	})

	// Handle custom events from server
	client.On("message", func(msg string) {
		log.Printf("Received message: %s", msg)
	})

	client.On("notification", func(data map[string]interface{}) {
		log.Printf("Received notification: %v", data)
	})

	// Handle disconnection
	client.On("disconnection", func() {
		log.Println("Disconnected from server")
	})

	// Handle errors
	client.On("error", func(err error) {
		log.Printf("Error: %v", err)
	})
}
