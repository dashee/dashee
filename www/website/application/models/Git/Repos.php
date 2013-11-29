<?php
/**
 * Model that replicates the Repo structure
 *
 * @author Shahmir Javaid
 */

class Application_Model_Git_Repos extends Application_Model_Git
{
    /**
     * Owner and repo variables
     */
    private $owner;
    private $repo;

    /**
     * Get values from the ZendRegistry, and populate our
     * variables. Also initilize variables
     */ 
    public function __construct()
    {
        parent::__construct();
        $this->setOwner(Zend_Registry::get('gitsettings.owner'));
        $this->setRepo(Zend_Registry::get('gitsettings.repo'));
    }

    /**
     * Set the owner
     * 
     * @param $owner The owner to set
     *
     * @throws Exception if owner is invalid
     */ 
    public function setOwner($owner)
    {
        $owner = trim($owner);
        if ($owner == '')
            throw new Exception('Owner must not be empty');
        
        $this->owner = $owner;
    }  

    /**
     * Return the current owner
     *
     * @returns owner
     */
    public function getOwner()
    {
        return $this->owner;
    } 

    /**
     * Set the repo
     * 
     * @param $repo The repo to set
     *
     * @throws Exception if repo is invalid
     */ 
    public function setRepo($repo)
    {
        $repo = trim($repo);
        if ($repo == '')
            throw new Exception('Repo must not be empty');
        
        $this->repo = $repo;
    }  

    /**
     * Return the current repo
     *
     * @returns repo
     */
    public function getRepo()
    {
        return $this->repo;
    } 
}
