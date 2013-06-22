/**
 * A static class which provides Common functions which 
 * can be used throughout the program
 *
 * @author Shahmir Javaid
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include "Exception/InvalidNumber.h"

class Common
{

private:
protected:
public:
    
    static long int strtol(const char *, int = 10);
};

#endif
