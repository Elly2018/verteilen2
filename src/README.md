# Verteilen 2 Applications

If you go deeper more than one folder level, you will get development details.
Anyway, here is some summary for the applications here.

## Common

A library which share with every other applications. It has some often use functions and data structure.
The proto-buf definition is in here as well.

## CLI

The entry point for user, User could just install this, and use command to automatically downlaod other application and deploy.

## Client

The calculation agent. It provide web ui as well. And it has its own sqlite database in the home/.verteilen2/client,
Mainly storage some logs and job execute detail informations.

This agent can perform execute scripts, copy files, or detect files exist, etc...
And return the job perform result to the server application to collect the results.

It can hosting long running services and perform server request cronjobs as well.
The setting you are enable to changes here is the worker limits and web ui port. which you can change it by command arguments

## Server

The brain of the cluster. It manages the state of it's calculation agent. and stores project, tasks, jobs definitions in here.
It has sqlite database as well, and it's even bigger, the storage even contains files. for user-define script, of course.

You could just use server application and client application. It's prefectly fine if you're just doing the local stuff.

## Master
