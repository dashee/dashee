<?php
/**
 * Our wiki is based online on googlecode, so we built
 * a model that goes and fetches the pages from the wiki folder
 *
 * @author Shahmir Javaid
 */

// Include markdown so it can be rendered
include_once "markdown.php";

class Application_Model_Wiki
{
    /**
     * This is the URL of the Wiki
     */
    private $url;

    /**
     * The name of the Table Of Content page
     */
    private $toc;

    /**
     * The index page if no page is requested
     */
    private $index;

    /**
     * The extension after the page name, so .md or .wiki
     */
    private $extension;
    
    /**
     * The Zend_Http_Client object
     */
    private $httpClient;

    /**
     * The parser, only supported is Markdown currently
     */
    private $parser;

    /**
     * Get values from the ZendRegistry, and populate our
     * variables. Also initilize variables
     */ 
    public function __construct()
    {
        $this->url = Zend_Registry::get('wiki_url');
        $this->toc = Zend_Registry::get('wiki_toc');
        $this->index = Zend_Registry::get('wiki_index');
        $this->extension = Zend_Registry::get('wiki_extension');
        $this->parser = Zend_Registry::get('wiki_parser');

        $this->httpClient = new Zend_Http_Client();
        $adapter = new Zend_Http_Client_Adapter_Curl();
        $this->httpClient->setAdapter($adapter);
    }   
    
    /**
     * Fetch the URL using $httpClient
     *
     * @param $url - The URL value to get
     *
     * @returns String - Content
     *
     * @throws Local_Exception_Http_NotFound
     * @throws Local_Exception_Http_Forbidden
     * @throws Zend_Exception
     */
    private function fetch($url)
    {
        $this->httpClient->setUri($url);
        $this->httpClient->setHeaders("Cache-Control: max-age=0");

        $response = $this->httpClient->request('GET');
        $status = $response->getStatus();
        
        switch ($response->getStatus())
        {
            case 200:
                return $this->parse($response->getBody());
                break;
            case 404:
                throw new Local_Exception_Http_NotFound("Page not found '$url'");
                break;
            case 403:
                throw new Local_Exception_Http_Forbidden("'$url' Forbidden!");
                break;
            default:
                throw new Zend_Exception("URL '$url' return $status");
        }
    }
    
    /**
     * This function will parse the data according to the parser set
     *
     * @param $data - The value to parse
     *
     * @returns $string - The $data parsed
     */
    private function parse($data)
    {
        switch($this->parser)
        {
            case 'Markdown':
                return Markdown($data);
                break;
            default:
                return $data;
                break;
        }
    }
    
    /**
     * Get the value of the TableOfContent from the URL
     *
     * @return String - The HTML
     */
    public function getToc()
    {
        $url = "$this->url/$this->toc.$this->extension";
        return $this->fetch($url);
    }

    /**
     * Get a page, give the $page value. If the $page value
     * is null, the $this->index is used instead
     *
     * @param $page - The page to get or null for index
     *
     * @return String - The HTML
     */
    public function getPage($page)
    {
        if ($page === null)
            $page = $this->index;

        $url = "$this->url/$page.$this->extension";
        return $this->fetch($url);
    }
}
