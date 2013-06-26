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
        throw new Local_Exception_Http_NotFound('You hit the black hole');
    }
    
    public function indexAction()
    {
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

        $ModelWiki = new Application_Model_Wiki();
        $this->view->toc = $ModelWiki->getToc();
        $this->view->page = $ModelWiki->getPage($this->_getParam('page', null));
    }

    /** 
     * Page that links to our SVN repo, and our Compiled code
     */
    public function downloadAction()
    {
    	$this->view->headTitle()->append("Download");
        $this->view->headLink()->appendStylesheet("/css/download.css");
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
    public function aboutAction()
    {
    	$this->view->headTitle()->append("About");
    	$this->view->headLink()->appendStylesheet("/css/about.css");
    }
}
