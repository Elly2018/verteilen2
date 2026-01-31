package main

import (
	"fmt"
	"log"
	"time"

	socketio_client "github.com/zhouhui8915/go-socket.io-client"
)

func main() {
	var uri string
	var client *socketio_client.Client

	opts := &socketio_client.Options{
		Transport: "websocket",
		Query:     make(map[string]string),
	}

	fmt.Print("Welcome be verilen2 node.\n")

	for {
		fmt.Print("Please enter your server address: ")
		fmt.Scanln(&uri)
		fmt.Printf("Trying to connect to server: %s\n", uri)

		buffer, err := socketio_client.NewClient(uri, opts)
		if err != nil {
			log.Printf("Failed to create client: %v\n", err)
			continue
		}
		client = buffer
		break
	}
	setupHandlers(client, uri, opts)
	select {}
}

func reconnect(uri string, opts *socketio_client.Options, oldClient *socketio_client.Client) {
	maxRetries := 5
	retryDelay := 2 * time.Second

	for attempt := 1; attempt <= maxRetries; attempt++ {
		log.Printf("Reconnection attempt %d/%d...", attempt, maxRetries)

		time.Sleep(retryDelay)

		newClient, err := socketio_client.NewClient(uri, opts)
		if err != nil {
			log.Printf("Reconnection failed: %v", err)
			retryDelay *= 2 // Exponential backoff
			continue
		}

		log.Println("✓ Reconnected successfully!")

		// Re-setup handlers on new client
		setupHandlers(newClient, uri, opts)
		return
	}

	log.Println("✗ Max reconnection attempts reached. Giving up.")
}

func setupHandlers(client *socketio_client.Client, uri string, opts *socketio_client.Options) {
	client.On("connection", func() {
		log.Println("✓ Connected to server")
	})

	client.On("message", func(msg string) {
		log.Printf("Received message: %s", msg)
	})

	client.On("notification", func(data map[string]interface{}) {
		log.Printf("Received notification: %v", data)
	})

	client.On("disconnection", func() {
		log.Println("✗ Disconnected from server")
		go reconnect(uri, opts, client)
	})

	client.On("error", func(err error) {
		log.Printf("Error: %v", err)
	})
}
