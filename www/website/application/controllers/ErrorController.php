<?php

class ErrorController extends Zend_Controller_Action
{

    public function errorAction()
    {
        // Create a variable and default them
        $errors = $this->_getParam('error_handler');
        $priority = Zend_Log::CRIT;

        // Set some defaults, like the layout and the css files
        $this->_helper->layout()->setLayout('error');
        $this->view->headLink()->appendStylesheet("/css/error.css");

        // Default the view variables
        $this->view->message = "Serious Internal Server Error!";
    
        // Make sure that the errors variable is correct, other wise fail out
        if (!$errors || !$errors instanceof ArrayObject) 
            return;
    
        // Deal with Local_Exception_Http class types in a specific way
        if ($errors->exception instanceof Local_Exception_Http)
        {
            $this->getResponse()->setHttpResponseCode($errors->exception->getStatus());
            $this->view->errorcode = $errors->exception->getStatus();
            $this->view->message = $errors->exception->getTitle();
            $priority = Zend_Log::NOTICE;
        }

        // Deal with all others in a default way
        else
        {
            switch ($errors->type) 
            {
                case Zend_Controller_Plugin_ErrorHandler::EXCEPTION_NO_ROUTE:
                case Zend_Controller_Plugin_ErrorHandler::EXCEPTION_NO_CONTROLLER:
                case Zend_Controller_Plugin_ErrorHandler::EXCEPTION_NO_ACTION:
                    $priority = Zend_Log::NOTICE;
                    $this->getResponse()->setHttpResponseCode(404);
                    $this->view->errorcode = 404;
                    $this->view->message = 'Page not found';
                    break;
                default:
                    $this->view->errorcode = 500;
                    $this->view->message = 'Application error';
                    $this->getResponse()->setHttpResponseCode(500);
                    break;
            }
        }
        
        // Log exception, if logger available
        if ($log = $this->getLog()) 
        {
            $log->log($this->view->message, $priority, $errors->exception);
            $log->log('Request Parameters', $priority, $errors->request->getParams());
        }
        
        // conditionally display exceptions
        if ($this->getInvokeArg('displayExceptions') == true)
        {
            $this->view->exception = $errors->exception;
            $this->view->exceptiontype = get_class($errors->exception);
        }
        
        $this->view->request = $errors->request;
    }

    public function getLog()
    {
        $bootstrap = $this->getInvokeArg('bootstrap');

        if (!$bootstrap->hasResource('Log'))
            return false;

        $log = $bootstrap->getResource('Log');
        return $log;
    }
}

