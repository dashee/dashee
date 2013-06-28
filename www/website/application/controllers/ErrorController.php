<?php

class ErrorController extends Zend_Controller_Action
{

    public function errorAction()
    {
        $this->view->headLink()->appendStylesheet("/css/error.css");
        $this->view->errorcode = 500;
        $this->view->message = "Internal Server Error";
        
        $errors = $this->_getParam('error_handler');

        if (!$errors || !$errors instanceof ArrayObject) 
            return;

        $this->getResponse()->setHttpResponseCode(500);
        $priority = Zend_Log::CRIT;
    
        if ($errors->exception instanceof Local_Exception_Http)
        {
            $this->getResponse()->setHttpResponseCode($errors->exception->getStatus());
            $this->view->errorcode = $errors->exception->getStatus();
            $this->view->message = $errors->exception->getTitle();
            $priority = Zend_Log::NOTICE;
        }
        else
        {
            switch ($errors->type) 
            {
                case Zend_Controller_Plugin_ErrorHandler::EXCEPTION_NO_ROUTE:
                case Zend_Controller_Plugin_ErrorHandler::EXCEPTION_NO_CONTROLLER:
                case Zend_Controller_Plugin_ErrorHandler::EXCEPTION_NO_ACTION:
                    // application error
                    $priority = Zend_Log::NOTICE;
                    $this->getResponse()->setHttpResponseCode(404);
                    $this->view->errorcode = 404;
                    $this->view->message = 'Page not found';
                    break;
                default:
                    // application error
                    $this->view->message = 'Application error';
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

