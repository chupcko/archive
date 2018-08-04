#ifndef __SDK__CONFIGURATION_H
#define __SDK__CONFIGURATION_H

#define SDK_X_MIN 2
#define SDK_X_MAX 6
#define SDK_X_DEFAULT 3
#define SDK_Y_MIN 2
#define SDK_Y_MAX 6
#define SDK_Y_DEFAULT 3

#define SDK_XY_MAX (SDK_X_MAX*SDK_Y_MAX)

#define SDK_CHARACTER_SET_NO_INDEX (-1)
#define SDK_CHARACTER_SET_INDEX_MAX (SDK_X_MAX*SDK_Y_MAX)

#define SDK_CHARACTER_NO_FIXED ' '

#define SDK_READ_BUFFER_SIZE 128

#define SDK_READ_CHARACTER_NO_FIXED SDK_CHARACTER_NO_FIXED
#define SDK_READ_CHARACTER_NO_FIXED_ALTERNATIVE '.'
#define SDK_READ_CHARACTER_COMMAND '='
#define SDK_READ_CHARACTER_X 'X'
#define SDK_READ_CHARACTER_Y 'Y'

#define SDK_PRINT_CHARACTER_NO_FIXED SDK_CHARACTER_NO_FIXED
#define SDK_PRINT_CHARACTER_HORIZONTAL_SEPARATOR '-'
#define SDK_PRINT_CHARACTER_JOIN_SEPARATOR '+'
#define SDK_PRINT_CHARACTER_VERTICAL_SEPARATOR '|'

#define SDK_DEBUG_CHARACTER_NO_FIXED SDK_PRINT_CHARACTER_NO_FIXED
#define SDK_DEBUG_CHARACTER_HORIZONTAL_SEPARATOR SDK_PRINT_CHARACTER_HORIZONTAL_SEPARATOR
#define SDK_DEBUG_CHARACTER_JOIN_SEPARATOR SDK_PRINT_CHARACTER_JOIN_SEPARATOR
#define SDK_DEBUG_CHARACTER_VERTICAL_SEPARATOR SDK_PRINT_CHARACTER_VERTICAL_SEPARATOR
#define SDK_DEBUG_CHARACTER_POSSIBILITY_BEGIN '['
#define SDK_DEBUG_CHARACTER_POSSIBILITY_END ']'

#endif
