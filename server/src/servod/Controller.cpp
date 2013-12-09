#include "Controller.h"

/**
 * Construct our object
 */
Controller::Controller(Container * container)
{
    this->setContainer(container);
}

/**
 * Set the pointer to the config variable
 *
 * @param config The pointer which points to the value of the config object
 */
void Controller::setContainer(Container * container)
{
    if (container == NULL)
        throw dashee::Exception("Cannot set container to NULL");

    this->container = container;
}

/**
 * Get the pointer to the config variable
 *
 * @return the pointer to the config variable
 */
Container * Controller::getContainer()
{
    return this->container;
}

/**
 * Take a step and perform some actions
 */
void Controller::step()
{
    
}

/**
 * Destroy gracefully
 */
Controller::~Controller()
{
}
