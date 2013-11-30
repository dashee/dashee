<?php

include_once "markdown.php";

class IndexController extends Zend_Controller_Action
{
    /**
     * This is the default controller to no where, throw a 404
     * because files that don't exist on the server will be used as controllers
     * and we dont want that becuase no controllers throw 500 errors
     */
    public function norouteAction()
    {
        //throw new Zend_Exception('Testing a normal exception!');
        throw new Local_Exception_Http_NotFound('You hit the black hole');
    }
    
    public function indexAction()
    {
    	$this->view->headTitle()->append("Autonomous remote control system");
        $this->view->headLink()->appendStylesheet("/css/index.css");
    }

    /**
     * Load our Wiki pages from http://dashee.googlecode.com/svn/wiki
     * and display then here, no DB required :D
     */   
    public function wikiAction()
    {
    	$this->view->headTitle()->append("Wiki");
        $this->view->headLink()->appendStylesheet("/css/wiki.css");
    }

    /** 
     * Page that links to our SVN repo, and our Compiled code
     */
    public function downloadsAction()
    {
    	$this->view->headTitle()->append("Downloads");
        $this->view->headLink()->appendStylesheet("/css/downloads.css");

        $releases = new Application_Model_Git_Repos_Releases();
        $this->view->releases = $releases->getAll();
    }

    /**
     * Page which displays our licenses
     */
    public function licenceAction()
    {
    	$this->view->headTitle()->append("Licence, the common deed.");
    	$this->view->headLink()->appendStylesheet("/css/licence.css");
    }
    
    /**
     * A little bit about does not hurt
     */
    public function videosAction()
    {
    	$this->view->headTitle()->append("Videos");
    	$this->view->headLink()->appendStylesheet("/css/videos.css");
    }

    /**
     * A little bit about does not hurt
     */
    public function aboutAction()
    {
    	$this->view->headTitle()->append("About");
    	$this->view->headLink()->appendStylesheet("/css/about.css");
    }

    /**
     * List of issues
     */
    public function issuesAction()
    {
    	$this->view->headTitle()->append("Issue tracking");
    	$this->view->headLink()->appendStylesheet("/css/issues.css");
        
        $issues = new Application_Model_Git_Repos_Issues();
        $this->view->issues = $issues->getAll();
    }
}
