# Verteilen 2 Client Database

Here are formats of the database

```mermaid
---
title: Sqlite Database
---
erDiagram
    job ||--o| job_detail : has
    log {
        int id
        char(36) job
        text title
        text content
        timestamp created_at
    }
    job {
        int id
        char(36) job_id
        text title
        description content
        timestamp created_at
    }
    job_detail {
        int id
        char(36) job
        text title
        text content
        timestamp created_at
    }
```

### Table: log

The system or background task log.

### Table: job

Whenever the agent is executing a job or service, \
it will create a job table to record it

### Table: job_detail

The messages when running the job or service.