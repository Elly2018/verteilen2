# Verteilen 2 Applications

If you go one more level deeper, you will get development details.\
Anyway, here are summaries for applications here.

## Common

A library which share with other applications. It has some often use functions and data structure.\
The proto-buf definition is in here as well.

## CLI

The entry point for user.\
User could just install this, and use command to automatically downlaod other application and deploy them.

## Client

The calculation agent. It provide web ui as well.\
And it has its own SQLite database in the home/.verteilen2/client.\
Mainly storage some logs and job execute detail informations.

This agent can perform execute scripts, copy files, or detect files exist, etc...\
And return the job perform result to the server application to collect the results.

It can hosting long running services and perform server request cronjobs as well.\
The setting you are enable to changes here is the worker limits and web ui port.\
Which you can change it by command arguments

## Server

The brain of the cluster. It manages the state of it's calculation agent. \
And stores project, tasks, jobs definitions in here.\
It has SQLite database as well, and it's even bigger.\
The storage even contains files. for user-define script, of course.

You could just use server application and client application. \
It's prefectly fine if you're just doing the local stuff.

## Master

The upper management for multiple server.\
It provides authentication or roles management.

And backup, share resources, advance computing, services deployment solution.
