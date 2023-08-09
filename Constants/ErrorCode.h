#pragma once

enum ErrorCode
{             
    WellCode                      = 0,
    CommandBreakCode              = -1,

    CommandReadErrorCode          = -2,
    CommandEndFileErrorCode       = -3,

    FileHeaderReadErrorCode       = -4,
    CommandWriteDataCode          = -5,
    CommandRecognizeError         = -6,

    MachineCodeOutOfBound         = -7,
    EmptyStackGetError            = -8,

    NoQuoteDBError                = -9,
    CommandDataReadError          = -10,

    NotEmptyFixUpLinkingLabelList = -11,

    DisassemblyNameError          = -12,

    RegisterNotFound              = -13,

    InteractiveCommandNotFound    = -14,
    DebugBreakCode                = -15,
    RAMOutOfBounds                = -16,
    BreakPointNotFounded          = -17,
    SystemComponentNotFounded     = -18
};