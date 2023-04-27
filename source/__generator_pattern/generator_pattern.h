/*!
 *  @file generator_pattern.h
 *
 *  @brief  A pattern for generator modules
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifdef GENERATOR_PATTERN
#define GENERATOR_PATTERN

typedef struct
{
    int maxCrossingNumber;
    int (*storage_interface)(char *generatedData, int dataLength);
    char *sourceData;
} generator_pattern_config_t;

#endif /* end GENERATOR_PATTERN */