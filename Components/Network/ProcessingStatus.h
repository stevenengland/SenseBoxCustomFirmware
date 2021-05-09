#pragma once

typedef enum {
    UnknownException = 255,
    Success = 0,
    TechnicalError,
    FunctionalError
} ProcessingStatus;