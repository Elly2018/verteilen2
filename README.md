# Verteilen 2

A Real-time cluster management system.

It support hosting services and execute jobs.

The entire system have 4 applications for it.

#### [Client](./src/native/client/README.md)

Where calculation happens, the nodes.

#### [Server](./src/native/server/README.md)

Where the resources and command coming from. kinda like ansible server.

#### [Master](./src/native/master/README.md)

The multiple-server management, with roles and authentication, resource sharing, and cloud solutions.

#### [CLI](./src/native/cli/README.md)

Quick way to deploy and setup.

## Features

You could check the features details in [src/native/["Project Name"]](./src/native/README.md)

## Require Packages

Since the communication are using protobuf with websocket. we're require the protobuf compiler.

```bash
sudo apt-get update
sudo apt-get install libasio-dev
sudo apt install protobuf-compiler
sudo apt-get install protobuf-c-compiler libprotobuf-c-dev
```

## Quick Start

After you clone the project, you can use this bash script as a entry point

```bash
bash helper.sh
```