<?php 

class Local_Exception_Http_Forbidden extends Local_Exception_Http
{
    public function getStatus()
    {
        return 403;
    }
    
    public function getTitle()
    {
        return "Forbidden";
    }
}

