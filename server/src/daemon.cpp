#include <dashee/daemon.h>

/**
 * Start this program as daemon.
 *
 * @param conf The config which is used to get the values for
 *             the state to run the daemon in
 */
pid_t dashee::startDaemon(
	Config * config, 
	const char * logFile, 
	const char * workingDir, 
	const char * pidFile
    )
{
    const char * logfile = config->get("logfile", logFile);
    const char * workingdir = config->get("workingdir", workingDir);
    const char * pidfile = config->get("pidfile", pidFile);

    if (!dashee::fexists(logfile))
        throw Exception("Cannot start, log file is invalid '" + (std::string)logfile + "' not found");

    // Change logging to go to stdout
    dashee::Log::openFile(logfile);

    pid_t pid;
    pid_t sid;

    // Fork our process
    pid = fork();

    // Fork failed
    if (pid < 0)
        throw Exception("fork() returned '" + dashee::itostr(pid) + "'");

    // Fork passed so parent should clean up and die
    if (pid > 0)
    {
        delete config;
        exit(0);
    }

    //Create a new Signature Id for our child
    sid = setsid();
    if (sid < 0)
        throw Exception("sid() returned '" + dashee::itostr(sid) + "'");

    // Change working directory
    if (chdir(workingdir) < 0)
        throw Exception("Cannot change directory '" + (std::string)workingdir + "'");

    if (!dashee::createPID(pidfile, true))
        throw Exception("PID '" + (std::string)pidfile + "' file already exists");

    // Close STDIN and STDOUT
    close(STDIN_FILENO);
    close(STDERR_FILENO);

    return pid;
}

/**
 * Create a pid file give by filepath.
 *
 * @param Create a pid file
 * @param Overwrite an existing pidfile (default to false)
 *
 * @retval false If file exists
 * @retval true if pid file was created
 */
bool dashee::createPID(const char * filepath, bool overwrite)
{
    if (fexists(filepath) && !overwrite)
        return false;

    FILE * fd = fopen(filepath, "w");
    
    if (fd == NULL)
        throw Exception("PID file '" + (std::string)filepath + "' could not opened for writing");

    // Write to file, close and return true;
    fprintf(fd, "%d\n", getpid());
    fclose(fd);
    return true;
}
