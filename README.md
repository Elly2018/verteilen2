# Verteilen 2

A cluster management system

The entire system have 4 applications for it.

#### Client

Where calculation happens, the nodes.

#### Server

Where the resources and command coming from. kinda like ansible server.

#### Master

The multiple-server management, with roles and authentication, resource sharing, and cloud solutions.

#### CLI

Quick way to deploy and setup.

## Features

You could check the features detail in src/["Project Name"]

## Require Packages

Since the communication are using protobuf with websocket. we're require the protobuf compiler.

```bash
sudo apt-get update
sudo apt-get install libasio-dev
sudo apt install protobuf-compiler
```
