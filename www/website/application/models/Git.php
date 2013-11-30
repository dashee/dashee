<?php
/**
 * Our wiki is based online on googlecode, so we built
 * a model that goes and fetches the pages from the wiki folder
 *
 * @author Shahmir Javaid
 */

class Application_Model_Git
{
    /**
     * This is the URL of the Wiki
     */
    private $url;

    /**
     * Get values from the ZendRegistry, and populate our
     * variables. Also initilize variables
     */ 
    public function __construct()
    {
        $this->httpClient = new Zend_Http_Client();
        $adapter = new Zend_Http_Client_Adapter_Curl();
        $this->httpClient->setAdapter($adapter);
        
        $this->setUrl(Zend_Registry::get('gitsettings.apiurl'));

    }

    /**
     * Set the url
     * 
     * @param $url The url to set
     *
     * @throws Exception if url is invalid
     */ 
    public function setUrl($url)
    {
        $url = trim($url);
        if ($url == '')
            throw new Exception('URL must not be empty');
        
        $this->url = $url;
    }  

    /**
     * Return the current url
     *
     * @returns url
     */
    public function getUrl()
    {
        return $this->url;
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
    protected function fetch($url)
    {
        $this->httpClient->setUri($url);
        $this->httpClient->setHeaders("Cache-Control: max-age=0");

        $response = $this->httpClient->request('GET');
        $status = $response->getStatus();
        
        switch ($response->getStatus())
        {
            case 200:
                return $response->getBody();
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
     * Helpfull function to format the given date
     *
     * @param date The date to format
     * @param format the Format to set by default
     *
     * @returns a string of formatted date
     */
    static public function formatDate($date, $format = 'd M Y')
    {
        $convert = strtotime($date);

        if ($convert === false)
            throw new Zend_Exception(
                "Converting formatDate '$date' using strtotime failed"
            );

        return date($format, $convert);
    }
}
