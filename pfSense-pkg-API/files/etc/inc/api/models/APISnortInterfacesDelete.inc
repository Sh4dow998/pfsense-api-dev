<?php
require_once("api/framework/APIModel.inc");
require_once("api/framework/APIResponse.inc");

class APISnortInterfacesDelete extends APIModel {
    public function __construct() {
        parent::__construct();
        $this->privileges = ["page-all", "page-services-snort-delete"];
        $this->requires_auth = true;
        $this->packages = ["pfSense-pkg-snort"];
    }

    public function action() {
        if (isset($this->validated_data['interface'])) {
            $this->id = $this->get_next_id("installedpackages/snortglobal/rule/");
            if ($this->del_config("installedpackages/snortglobal/rule/{$this->id}")) {
                $this->write_config();
                return APIResponse\get(0, "Interface deleted successfully");
            } else {
                return APIResponse\get(1, "Failed to delete interface");
            }
        }
        return APIResponse\get(1, "No valid interface ID provided");
    }

    public function validate_payload() {
        if (isset($this->initial_data['interface']) && is_numeric($this->initial_data['interface'])) {
            $this->validated_data['interface'] = $this->initial_data['interface'];
        } else {
            $this->errors[] = APIResponse\get(1, "Invalid or missing interface ID");
        }
    }
}
