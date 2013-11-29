<?php

class Bootstrap extends Zend_Application_Bootstrap_Bootstrap
{
    protected function _initHtml()
    {
        $this->bootstrap('view');
        $view = $this->getResource('view');

        $view->headTitle("Dashee");
        $view->headTitle()->setSeparator(' - ');

        $view->headMeta()->setName('DESCRIPTION', 'A RC control architecture.');
        $view->headMeta()->setName('KEYWORDS', 'Robots RC Linux Architecture');
        $view->headMeta()->setName('AUTHOR', 'Shahmir Javaid, David Buttar');
        $view->headMeta()->setName('RATING', 'General');      
        $view->headMeta()->setName(
            'viewport', 
            'width=device-width, initial-scale=1'
        );
    }

    protected function _initNamespace()
    {
        $autoloader = Zend_Loader_Autoloader::getInstance();
        $autoloader->registerNamespace('Local_');
    }

    protected function _initRegistry()
    {
        $gitsettings = $this->getOptions();
        if (!isset($gitsettings["gitsettings"]))
            die(
                "gitsettings variables not defined, " .
                "see your `application.ini`."
            );
        $gitsettings = $gitsettings["gitsettings"];

        if (!isset($gitsettings['owner']))
            die(
                "gitsetting.owner is not defined," . 
                " see your `application.ini`."
            );

        foreach($gitsettings as $key=>$value)
        {
            Zend_Registry::set("gitsettings.$key", $value);
        }
    }

    /**
     * Set the Zend_Cache
     */ 
    protected function _initCaching()
    {
        $frontend= array(
            'lifetime' => 240,
            'automatic_seralization' => true
        );

        $backend= array(
            'cache_dir' => '/tmp/',
        );

        $cache = Zend_Cache::factory(
            'core',
            'File',
            $frontend,
            $backend
        );

        Zend_Registry::set('cache',$cache);
    }
    
    protected function _initRouter()
    {
        $front = Zend_Controller_Front::getInstance();
        $front->setDefaultControllerName("default");
        $router = $front->getRouter();

        $route = array(

            /**
             * This will ensure, that any unknown controllers are sent to the 
             * default controller which can deal with special requests 
             * accordingly, and reroute to the appropriate action. Dont use this
             * as a fucking router, create a route for any actions, This action 
             * is responsible for throwing exceptions, and given the url it may 
             * throw different exceptions
             */
            'noroute' => new Zend_Controller_Router_Route(
                '*',
                array(
                    'controller' => 'index',
                    'action' => 'noroute'
                )
            ),

            /**
             * Hit our index page
             */
            'index' => new Zend_Controller_Router_Route(
                '/',
                array(
                    'controller' => 'index',
                    'action' => 'index'
                )
            ),

            'wiki' => new Zend_Controller_Router_Route_Regex(
                '^wiki/?$',
                array(
                    'controller' => 'index',
                    'action' => 'wiki'
                )
            ),

            'wiki-page' => new Zend_Controller_Router_Route_Regex(
                '^wiki/(.*)$',
                array(
                    'controller' => 'index',
                    'action' => 'wiki'
                ),
                array(
                    1 => 'page'
                )
            ),

            'downloads' => new Zend_Controller_Router_Route_Regex(
                '^(code|svn|download|downloads)$',
                array(
                    'controller' => 'index',
                    'action' => 'downloads'
                )
            ),

            'issues' => new Zend_Controller_Router_Route_Regex(
                '^(issues|issue|bugs|broken|help)$',
                array(
                    'controller' => 'index',
                    'action' => 'issues'
                )
            ),

            'videos' => new Zend_Controller_Router_Route_Regex(
                '^(videos|media)$',
                array(
                    'controller' => 'index',
                    'action' => 'videos'
                )
            ),
            
            'license' => new Zend_Controller_Router_Route_Regex(
                '^(licen[sc]e|legal)$',
                array(
                    'controller' => 'index',
                    'action' => 'licence'
                )
            ),

            'about' => new Zend_Controller_Router_Route_Regex(
                '^(about)$',
                array(
                    'controller' => 'index',
                    'action' => 'about'
                )
            ),
        );

        $router->addRoutes($route);
    }

}

