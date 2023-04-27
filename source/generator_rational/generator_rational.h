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

#ifdef GENERATOR_RATIONAL
#define GENERATOR_RATIONAL

typedef struct
{
    int maxCrossingNumber;
    int (*storage_interface)(char *generatedData, int dataLength);
    char *sourceData;
} generator_rational_config_t;

#endif /* end GENERATOR_RATIONAL */