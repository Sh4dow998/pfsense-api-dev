<?php
require_once("api/framework/APIEndpoint.inc");

class APIServicesSnortInterfaces extends APIEndpoint {
    public function __construct() {
        parent::__construct();
        $this->url = "/api/v1/services/snort";
    }

    protected function get() {
        return (new APISnortInterfacesRead())->call();
    }

    protected function post() {
        return (new APISnortInterfacesCreate())->call();
    }

    protected function put() {
        return (new APISnortInterfacesUpdate())->call();
    }

    protected function delete() {
        return (new APISnortInterfacesDelete())->call();
    }
}
