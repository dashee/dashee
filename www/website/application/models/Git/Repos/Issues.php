<?php
/**
 * Model to deal with getting issues
 *
 * @author Shahmir Javaid
 */
class Application_Model_Git_Repos_Issues extends Application_Model_Git_Repos
{
    /**
     * Get values from the ZendRegistry, and populate our
     * variables. Also initilize variables
     */ 
    public function __construct()
    {
        parent::__construct();
    }   
    
    /**
     * Call the github API and return the releases
     *
     * @return Array of releases from the json returned
     */
    public function getAll()
    {
        $cache = Zend_Registry::get('cache');

        if (($data = $cache->load('issues')) === false)
        {
        
            $url = 
                $this->getUrl() . "/repos/" . $this->getOwner() . 
                "/" . $this->getRepo() . "/issues";
            $data = $this->fetch($url);
            $cache->save($data, 'issues');
        }

        return json_decode($data);
    }
}
