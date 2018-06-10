//
// Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//        * Redistributions of source code must retain the above copyright
//          notice, this list of conditions and the following disclaimer.
//        * Redistributions in binary form must reproduce the above copyright
//          notice, this list of conditions and the following disclaimer in the
//          documentation and/or other materials provided with the distribution.
//        * Neither the name of The Linux Foundation nor
//          the names of its contributors may be used to endorse or promote
//          products derived from this software without specific prior written
//          permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Abstract:            none
//
// Usage:               none
//
// Version:             0.0.2

#include "common.h"
#include "fmod_errors.h"

void (*Common_Private_Error)(FMOD_RESULT, const char *, int);

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        if (Common_Private_Error)
        {
            Common_Private_Error(result, file, line);
        }
        Common_Fatal("%s(%d): FMOD error %d - %s", file, line, result, FMOD_ErrorString(result));
    }
}

void Common_Format(char *buffer, int bufferSize, const char *formatString...)
{
    va_list args;
    va_start(args, formatString);
    Common_vsnprintf(buffer, bufferSize, formatString, args);
    va_end(args);
    buffer[bufferSize-1] = '\0';
}

void Common_Fatal(const char *format, ...)
{
    char error[1024];

    va_list args;
    va_start(args, format);
    Common_vsnprintf(error, 1024, format, args);
    va_end(args);
    error[1023] = '\0';

    do
    {
        Common_Draw("A fatal error has occurred...");
        Common_Draw("");
        Common_Draw("%s", error);
        Common_Draw("");
        Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));

        Common_Update();
        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));

    Common_Exit(0);
}

void Common_Draw(const char *format, ...)
{
    char string[1024];
    char *stringPtr = string;

    va_list args;
    va_start(args, format);
    Common_vsnprintf(string, 1024, format, args);
    va_end(args);
    string[1023] = '\0';

    unsigned int length = (unsigned int)strlen(string);

    do
    {
        bool consumeNewLine = false;
        unsigned int copyLength = length;

        // Search for new line characters
        char *newLinePtr = strchr(stringPtr, '\n');
        if (newLinePtr)
        {
            consumeNewLine = true;
            copyLength = (unsigned int)(newLinePtr - stringPtr);
        }

        if (copyLength > NUM_COLUMNS)
        {
            // Hard wrap by default
            copyLength = NUM_COLUMNS;

            // Loop for a soft wrap
            for (int i = NUM_COLUMNS - 1; i >= 0; i--)
            {
                if (stringPtr[i] == ' ')
                {
                    copyLength = i + 1;
                    break;
                }
            }
        }

        // Null terminate the sub string temporarily by swapping out a char
        char tempChar = stringPtr[copyLength];
        stringPtr[copyLength] = 0;
        Common_DrawText(stringPtr);
        stringPtr[copyLength] = tempChar;

        copyLength += (consumeNewLine ? 1 : 0);
        length -= copyLength;
        stringPtr += copyLength;
    } while (length > 0);
}

