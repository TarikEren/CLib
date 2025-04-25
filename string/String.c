/**
 * @file    String.c
 * @author  Tarık Eren Tosun
 * @date    9 Apr 2025
 * @brief   Arena allocated string implementation
 * @todo:   Implement StringTokenize
 */

#include <stdio.h>

#include "String.h"
#include "../log/Log.h"
#include "../arena/Arena.h"

//Re-implemented strlen so that I don't need to import string.h
size_t CStringGetLength(const char* str) {
    const char* s = str;
    while (*s) {
        ++s;
    }
    return s - str;
}

// ===== Memory Functions =====
void *MemoryCopy(void *destination, const void *source, const size_t size) {
    //Used unsigned char for bitwise operations
    unsigned char *dest = destination;
    const unsigned char *src = source;

    for (size_t i = 0; i < size; i++) {
        dest[i] = src[i];
    }

    return destination;
}

void *MemorySet(void *destination, const int value, const size_t size) {
    unsigned char *dest = destination;
    for (size_t i = 0; i < size; i++) {
        dest[i] = value;
    }
    return dest;
}

void *MemoryMove(void *destination, const void *source, const size_t n) {
    //Get the destination and source addresses as char pointers for bitwise operations
    unsigned char *dest = destination;
    const unsigned char *src = source;

    //If the destination address is lesser than the source address (i.e. comes before it)
    if (dest < src) {
        //Forward-copy
        for (size_t i = 0; i < n; i++) {
            dest[i] = src[i];
        }
    }
    //Else
    else {
        //Perform a backwards copy so we don't overwrite the source memory
        for (size_t i = n; i > 0; i--) {
            dest[i-1] = src[i-1];
        }
    }

    return dest;
}

// ===== Memory Functions =====

// ===== Base String Functions =====

// === String Creation & Deletion ===
String *StringCreate(Arena* arena, const char *data) {
    // Allocate memory for the String struct
    String *str_obj = ArenaAllocate(arena, sizeof(String));

    // Calculate the length of the input string
    size_t length = CStringGetLength(data);
    str_obj->length = length;

    // Allocate space for the string + null terminator in the arena
    str_obj->c_str = ArenaAllocate(arena, length + 1); // +1 for '\0'

    // Copy the input string into the writable arena memory
    MemoryCopy(str_obj->c_str, data, length);  // Use `memcpy` or `strncpy` if preferred
    str_obj->c_str[length] = '\0';

    return str_obj;
}

void StringDelete(String *string) {
    string->c_str = "";
    string->length = 0;
    free(string);
}

// === String Creation & Deletion ===

// === String Operations ===
String *StringGetSubstring(Arena *arena, const String *source, const size_t start, size_t len) {
    //If the start is greater than or equal to the string length, return null as it's clearly a user error
    const size_t string_length = source->length;
    if (start >= string_length) {
        return NULL;
    }

    //Clamping the n value so that the function doesn't read nonsense
    if (start + len >= string_length) {
        len = string_length - start;
    }

    //Heap allocate the new string
    char *sub_str = ArenaAllocate(arena, len + 1);
    for (size_t i = 0; i < len; i++) {
        sub_str[i] = source->c_str[i];
    }
    sub_str[len] = '\0';

    // Allocate to arena
    String *result = ArenaAllocate(arena, sizeof(*result));
    result->c_str = sub_str;
    result->length = len;

    return result;
}

String **StringTokenize(Arena *arena, String* str, char delimiter) {
    //The resulting tokens array will have a NULL token
    size_t token_count = 1;
    //For each character in the source string
    for (size_t i = 0; i < str->length; i++) {
        //If the current character is a delimiter
        if (str->c_str[i] == delimiter) {
            //Increment the token count
            token_count++;
        }
    }

    //Allocate the result array in the given arena
    String **result = ArenaAllocate(arena, (token_count + 1) * sizeof(*result));

    //Values for the index of the last token and the start of the new token
    size_t token_index = 0, start = 0;

    //For each character in the string
    for (size_t i = 0; i <= str->length; i++) {
        //If the current index is the string's length (i.e. if we reached the end)
        //or a delimiter was encountered
        if (i == str->length || str->c_str[i] == delimiter) {
            //Set the length of the token as the current index minus the start index
            const size_t len = i - start;
            //The result array's latest token should be the substring with the corresponding start and len values.
            result[token_index++] = StringGetSubstring(arena, str, start, len);
            //Set the start value of the next token as i+1
            start = i + 1;
        }
    }
    //The last token should be a NULL token to denote the end of the result array.
    //It makes looping through the array much easier as you don't need to use an index value.
    //You can just do "for (String **tok = result; *tok != NULL; ++tok)" to loop through the array.
    result[token_index] = NULL;
    return result;
}

void AppendString(Arena *arena, String *str1, const String *str2) {
    // Compute the new string‐length (excluding the null terminator)
    const size_t old_len = str1->length;
    const size_t src_len = str2->length;
    const size_t new_len = old_len + src_len;

    //Allocate space for [ old + src + '\0' ]
    char *buf = ArenaAllocate(arena, new_len + 1);

    //Copy the old contents
    MemoryCopy(buf, str1->c_str, old_len);

    //Copy the new contents (but only the chars, not the '\0')
    MemoryCopy(buf + old_len, str2->c_str, src_len);

    //Add null‑terminator
    buf[new_len] = '\0';

    //Re‑point and update length
    str1->c_str  = buf;
    str1->length = new_len;
}

int StringCompare(const String *str1, const String *str2) {
    if (str1->length != str2->length) {
        return 1;
    }

    for (size_t i = 0; i < str1->length; i++) {
        if (str1->c_str[i] != str2->c_str[i]) {
            return 1;
        }
    }

    return 0;
}

String *StringCopy(Arena* arena, const String *str) {
    String *new_str = StringCreate(arena, str->c_str);
    return new_str;
}

void StringToUpper(String *str) {
    const char offset = 'a' - 'A';
    for (size_t i = 0; i < str->length; i++) {
        if (str->c_str[i] >= 'a' && str->c_str[i] <= 'z') {
            str->c_str[i] -= offset;
        }
    }
}

void StringToLower(String *str) {
    const char offset = 'a' - 'A';
    for (size_t i = 0; i < str->length; i++) {
        if (str->c_str[i] >= 'A' && str->c_str[i] <= 'Z') {
            str->c_str[i] += offset;
        }
    }
}

// === String Operations ===

// ===== Base String Functions =====

