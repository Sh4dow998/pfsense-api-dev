<?php

require_once("api/framework/APIModel.inc");
require_once("api/framework/APIResponse.inc");

class APISnortInterfacesRead extends APIModel {

    public function __construct() {
        parent::__construct();    // Initialise notre classe APIModel
        $this->privileges = ["page-all", "page-services-snort"];
        $this->packages = ["pfSense-pkg-snort"];
    }

    public function action() {
        return APIResponse\get(0, $this->get_config("installedpackages/snortglobal/rule", []));
    }

}