<?php 

class Local_Exception_Http extends Local_Exception
{
    public function getStatus()
    {
        return 500;
    }

    public function getTitle()
    {
        return "Internal Server Error";
    }
}
