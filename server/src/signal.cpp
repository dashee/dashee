#include <dashee/signal.h>

int volatile dashee::EXIT = 0;
int volatile dashee::RELOAD = 0;

/**
 * Handle reload behavior.
 *
 * Terminate signal was called set RELOAD to be true
 *
 * @param sig The signal number
 */
void dashee::handleReloadSignal(int sig)
{
    RELOAD = 1;
    dashee::Log::info(3, "Reload signal %d called.", sig);
}

/**
 * Handle terminal signal behaviour.
 *
 * Terminate type signals were called set EXIT to be true
 *
 * @param sig The signal thrown
 */
void dashee::handleTerminateSignal(int sig)
{
    EXIT = 1;
    dashee::Log::info(3, "Terminate signal %d called.", sig);
}

/**
 * Load and set our handlers which will be called
 * when the program recieves a signal from the outside
 * world
 *
 * @throws std::runtime_error when something does nto work
 */ 
void dashee::initSignalHandler()
{
    // Set our sigaction
    struct sigaction terminateAction;
    struct sigaction reloadAction;

    memset(&terminateAction, 0, sizeof(terminateAction));
    memset(&reloadAction, 0, sizeof(reloadAction));

    terminateAction.sa_handler = handleTerminateSignal;
    reloadAction.sa_handler = handleReloadSignal;

    if (sigaction(SIGINT, &terminateAction, 0))
        throw new std::runtime_error("Sigaction SIGINT failed");
    if (sigaction(SIGTERM, &terminateAction, 0))
        throw new std::runtime_error("Sigaction SIGTERM failed");
    if (sigaction(SIGHUP, &reloadAction, 0))
        throw new std::runtime_error("Sigaction SIGHUP failed");
}
