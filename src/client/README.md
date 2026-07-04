# Verteilen 2 Client

Compute agent for the verteilen application.

## Purposes

## Database

There are three tables requires for this.

* log
* job
* job_detail

#### log

The system and background log information.

#### job

The job container.\
Every times server told client to run a job.\
It create a data in here.

#### job_detail

It has a foreign key with job uuid,\
It's a message data that under the job execution.

## Workflow

## Features

- [ ] WebUI

## API (REST-API)

### GET "/"

To the the homepage.

### GET "/[template]-[state]"

> [!NOTE]
> **template**
> The file name, it will fetch [template].html

> [!NOTE]
> **state**
> The state for the tempalte, it affect the context for the render

Fetch the template page components from static/template

### GET "/favicon.ico"

Get the website icon

### GET "/css/[filepath]"

Fetch css files

> [!NOTE]
> **filepath**
> The file name, it will fetch [filepath].css

### GET "/js/[filepath]"

Fetch javascript files

> [!NOTE]
> **filepath**
> The file name, it will fetch [filepath].js

### POST "/api/connect_ws_server"

```json
// Body
{
    "server-address": "string"
}
```

> [!NOTE]
> **server-address**
> The client will trying to connect to the input server address

Connecting to the server application.

### POST "/api/disconnect_ws_server"

Shutdown connection with server application.

## API (Websocket)

### GET "/ws"

Trying to listening the realtime event, such as log update.

#### Sender

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

#### Receiver

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

## Screenshots
