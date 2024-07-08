<?php

require_once("api/framework/APIEndpoint.inc");

class APIServicesCaptivePortal extends APIEndpoint {

    public function __construct() {
        parent::__construct();
        $this->url = "/api/v1/services/captiveportal";
    }

    public function get() {
        return (new APIServicesCaptivePortalRead())->call();
    }

    public function post() {
        return (new APIServicesCaptivePortalCreate())->call();
    }

}