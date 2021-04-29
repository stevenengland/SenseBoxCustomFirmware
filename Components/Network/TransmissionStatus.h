#pragma once

typedef enum {
    Timeout = 255,
    NotStarted = 0,
    InProgress,
    Completed,
    Aborted,
    TransmissionError,
    ConnectionError
} TransmissionStatus;