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
        $view->headMeta()->setName('viewport', 'width=device-width, initial-scale=1');
    }

    protected function _initNamespace()
    {
        $autoloader = Zend_Loader_Autoloader::getInstance();
        $autoloader->registerNamespace('Local_');
    }

    protected function _initRegistry()
    {
        Zend_Registry::set('wiki_extension', 'md');
        Zend_Registry::set('wiki_toc', 'TableOfContent');
        Zend_Registry::set('wiki_index', 'Index');
        Zend_Registry::set('wiki_parser', 'Markdown');

        $appsettings = $this->getOptions();
        if (!isset($appsettings["appsettings"]))
            die("appsettings variables not defined, see your `application.ini`.");
        $appsettings = $appsettings["appsettings"];

        if (!isset($appsettings["wiki_url"]))
            die("appsettings.wiki_url is not defined, see your `application.ini`.");

        foreach($appsettings as $key=>$value)
        {
            Zend_Registry::set($key, $value);
        }
    }
    
    protected function _initRouter()
    {
        $front = Zend_Controller_Front::getInstance();
        $front->setDefaultControllerName("default");
        $router = $front->getRouter();

        $route = array(

            /**
             * This will ensure, that any unknown controllers are sent to the default controller
             * which can deal with special requests accordingly, and reroute to the appropriate
             * action. Dont use this as a fucking router, create a route for any actions,
             * This action is responsible for throwing exceptions, and given the url it may throw 
             * different exceptions
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

            'download' => new Zend_Controller_Router_Route_Regex(
                '^(code|svn|download)$',
                array(
                    'controller' => 'index',
                    'action' => 'download'
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

