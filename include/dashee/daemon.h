/**
 * @file include/dashee/daemon.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license.  
 */

#ifndef DASHEE_DAEMON_H_
#define DASHEE_DAEMON_H_

#include <dashee/Exception.h>
#include <dashee/Config.h>
#include <dashee/common.h>

namespace dashee
{
    // Start the program as daemon
    pid_t startDaemon(
	    Config * config, 
	    const char * logFile, 
	    const char * workingDir, 
	    const char * pidFile
	);

    // createPID file given as a filepath
    bool createPID(const char * filepath, bool overwrite = false);
}

#endif
