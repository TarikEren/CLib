/**
 * @file    String.h
 * @author  Tarık Eren Tosun
 * @date    9 Apr 2025
 * @brief   Header for arena allocated strings
 * @todo:   Implement StringTokenize
 */

#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include "../arena/Arena.h"

/**
 * @brief                   Copies memory from `source` to `destination`. Essentially a re-implementation of "memcpy".
 * @param destination       The target location
 * @param source            The source location which contains the data
 * @param size              The size of the data to be copied
 * @return
 */
void *MemoryCopy(void *destination, const void *source, size_t size);

/**
 * @brief                   Sets a memory block's values to the given integer value.
 * @param destination       The target block's address
 * @param value             The value to set the blocks to
 * @param size              The count of the address to perform the operation on
 * @return
 */
void *MemorySet(void *destination, int value, size_t size);

/**
 * @brief                   Copies n bytes from the source address to the destination address.
 *                          Safer alternative compared to CopyMemory as it considers memory overwrites as well.
 * @param destination       The target address
 * @param source            The source address
 * @param n                 The amount of bytes to copy
 * @return                  The target address
 */

void *MemoryMove(void *destination, const void *source, size_t n);

/**
 *
 * @brief                   String struct for using more modern strings.
 */
typedef struct String {
    char* c_str;
    size_t length;
}String;

/**
 * @brief                   Creates a string object using the provided data.
 * @param arena             The arena which will contain the string. NULL if normal heap allocation is requested
 * @param data              The c type string which holds the character data
 * @return                  String object
 */
String *StringCreate(Arena *arena, const char *data);

/**
 * @brief                   Deletes the provided string object, only used with heap allocated strings
 * @param string            String to be deleted
 */
void StringDelete(String *string);

/**
 * @brief                   Tokenises a given string and returns an array of the created tokens
 *                          with a NULL token at the end.
 * @param arena             The arena to be used for potential allocations
 * @param str               The string object to be tokenised
 * @param delimiter         The delimiter to look out for
 * @return                  Array of string objects which contains the tokens
 */
String **StringTokenize(Arena *arena, String* str, char delimiter);

/**
 * @brief                   Gets the substring of a String object.
 * @param arena             The arena to allocate the substring to
 * @param source            The string to get the substring of
 * @param start             The start index of the substring
 * @param len               The length of the sub string
 * @return                  String object created using the substring
 */
String *StringGetSubstring(Arena* arena, const String *source, size_t start, size_t len);

/**
 * @brief                   Appending a string object's data to another.
 * @param arena             The arena to allocate the new string to
 * @param str1              Main string to append to
 * @param str2              New string to append to the main string
 */
void AppendString(Arena *arena, String *str1, const String *str2);

/**
 * @brief                   Compares two given strings.
 * @param str1              First string to compare
 * @param str2              Second string to compare
 * @return                  0 if the strings are the same, 1 if not
 */
int StringCompare(const String *str1, const String *str2);

/**
 * @brief                   Copies the given string and allocates it to the given arena.
 * @param arena             The arena to allocate the string copy to
 * @param str               The string to copy from
 * @return                  The new string's address
 */
String *StringCopy(Arena* arena, const String *str);

/**
 * @brief                   Changes the characters of a given string to uppercase characters.
 * @param str               String to modify
 */
void StringToUpper(String *str);

/**
 * @brief                   Changes the characters of a given string to lowercase characters.
 * @param str               String to modify
 */
void StringToLower(String *str);
#endif
