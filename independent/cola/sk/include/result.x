#ifdef RESULT

RESULT(OK,                           0, "OK")
RESULT(NO,                           1, "No")
RESULT(DONE,                         2, "Done")
RESULT(ERROR,                      -10, "Error")
RESULT(BAD_EXPRESSION,             -11, "Missing close parenthesis")
RESULT(MISSING_CLOSE_PARENTHESIS,  -12, "Missing close parenthesis")
RESULT(MISSING_EXPRESSION,         -13, "missing_expression")
RESULT(NO_SPACE_FOR_ITEM,          -14, "No space for item")
RESULT(NO_SPACE_FOR_NAME,          -15, "No space for name")
RESULT(SOMETHING_AFTER_EXPRESSION, -16, "Something after expression")
RESULT(UNKNOWN_CHARACTER,          -17, "Unknown character")

#endif
