#include "signals.h"

int volatile EXIT = 0;
int volatile RELOAD = 0;

/**
 * Handle reload behavior.
 *
 * Terminate signal was called set RELOAD to be true
 *
 * @param sig The signal number
 */
void signalReloadHandler(int sig)
{
    dashee::Threads::Scope scope(&lockRELOAD);
    
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
void signalTerminateHandler(int sig)
{
    dashee::Threads::Scope scope(&lockEXIT);

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
void initSignal()
{
    // Set our sigaction
    struct sigaction terminateAction;
    struct sigaction reloadAction;

    memset(&terminateAction, 0, sizeof(terminateAction));
    memset(&reloadAction, 0, sizeof(reloadAction));

    terminateAction.sa_handler = signalTerminateHandler;
    reloadAction.sa_handler = signalReloadHandler;

    if (sigaction(SIGINT, &terminateAction, 0))
        throw new std::runtime_error("Sigaction SIGINT failed");
    if (sigaction(SIGTERM, &terminateAction, 0))
        throw new std::runtime_error("Sigaction SIGTERM failed");
    if (sigaction(SIGHUP, &reloadAction, 0))
        throw new std::runtime_error("Sigaction SIGHUP failed");
}
