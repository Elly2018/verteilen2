# Verteilen 2 Client Rest-API

## GET "/"

To the the homepage.

## GET "/[template]-[state]"

> [!NOTE]
> **template**
> The file name, it will fetch [template].html

> [!NOTE]
> **state**
> The state for the tempalte, it affect the context for the render

Fetch the template page components from static/template

## GET "/favicon.ico"

Get the website icon

## GET "/css/[filepath]"

Fetch css files

> [!NOTE]
> **filepath**
> The file name, it will fetch [filepath].css

## GET "/js/[filepath]"

Fetch javascript files

> [!NOTE]
> **filepath**
> The file name, it will fetch [filepath].js

## POST "/api/connect_ws_server"

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

## POST "/api/disconnect_ws_server"

Shutdown connection with server application.