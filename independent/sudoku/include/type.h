#ifndef __SDK__TYPE_H
#define __SDK__TYPE_H

typedef enum SDK_boolean
{
  SDK_FALSE = 0,
  SDK_TRUE = 1
} SDK_boolean;

typedef char SDK_character_set_type[SDK_CHARACTER_SET_INDEX_MAX];

typedef struct SDK_table_type
{
  int x;
  int y;
  int xy;
  int character_set_index_min;
  int character_set_index_max;
  struct cell
  {
    SDK_boolean initial;
    SDK_boolean fixed;
    int character_set_index;
    int possibility_count;
    SDK_boolean possibility[SDK_CHARACTER_SET_INDEX_MAX];
  } cell[SDK_XY_MAX][SDK_XY_MAX];
} SDK_table_type;

typedef enum SDK_shape_type
{
  SDK_SHAPE_REGION = 0,
  SDK_SHAPE_ROW = 1,
  SDK_SHAPE_COLUMN = 2
} SDK_shape_type;

#define SDK_SHAPE_MIN SDK_SHAPE_REGION
#define SDK_SHAPE_MAX SDK_SHAPE_COLUMN

#define SDK_BACKGROUND_WHITE 0
#define SDK_BACKGROUND_GRAY_1 1
#define SDK_BACKGROUND_GRAY_2 2
#define SDK_BACKGROUND_GRAY_3 3
#define SDK_BACKGROUND_GRAY_4 4
#define SDK_BACKGROUND_BLACK 5

#define SDK_FOREGROUND_WHITE 5
#define SDK_FOREGROUND_GRAY_1 4
#define SDK_FOREGROUND_GRAY_2 3
#define SDK_FOREGROUND_GRAY_3 2
#define SDK_FOREGROUND_GRAY_4 1
#define SDK_FOREGROUND_BLACK 0

#define SDK_MARKER_SQUARE 8
#define SDK_MARKER_ROUND 4
#define SDK_MARKER_BACKSLASH 2
#define SDK_MARKER_SLASH 1
#define SDK_MARKER_NONE 0

typedef struct SDK_postscript_flags_type
{
  int background;
  int foreground;
  int marker;
  int possibility_marker[SDK_CHARACTER_SET_INDEX_MAX];
} SDK_postscript_flags_type[SDK_XY_MAX][SDK_XY_MAX];

#endif
