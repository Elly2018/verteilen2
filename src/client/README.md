# Verteilen 2 Client

Compute agent for the verteilen application

## Tech Stacks

* Htmx
* Sqlite3
* Crow
* Boost::asio
* Boost::beast
* protobuf
* DaisyUI
* spdlog

## Features

- [ ] WebUI

## API

#### GET "/"

To the the homepage !!

#### GET "/<template>"

Fetch the template page components from static/template

#### POST "/api/connect_ws_server"

```json
// Body
{
    "body": {
        "server-address": "string"
    }
}
```

Trying to connect to the server application.

## Websocket

#### GET "/ws" Entry

Trying to listening the realtime event, such as log update.

## Screenshots
