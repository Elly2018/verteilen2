# Verteilen 2 Client Websocket

## GET "/ws"

This is the communication between client agent and web UI.

### Sender

```json
{
    "key": "session_key",
    "data": {
        // data goes here
    }
}
```

> [!IMPORTANT]
> This is a standard format for sender.
> If the message does not follow this, the server won't response.
> The key is for the session storage.

### Receiver

```json
{
    "type": "new_log"
}
```

> [!NOTE]
> This means there are new logs happens.
> The browser will call the htmx get when received this

```json
{
    "type": "new_detail"
}
```

> [!NOTE]
> This means there are new job details happens.
> The browser will call the htmx get when received this


## GET "/ws/server"

This is the communication between client agent and server.