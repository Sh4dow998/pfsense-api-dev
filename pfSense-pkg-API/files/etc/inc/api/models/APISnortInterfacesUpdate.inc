<?php
require_once("api/framework/APIModel.inc");
require_once("api/framework/APIResponse.inc");

class APISnortInterfacesUpdate extends APIModel {
    public function __construct() {
        parent::__construct();
        $this->privileges = ["page-all", "page-services-snort-update"];
        $this->requires_auth = true;
        $this->packages = ["pfSense-pkg-snort"];
    }

    public function action() {
        if (!empty($this->validated_data) && isset($this->validated_data['interface'])) {
            $this->id = $this->get_next_id("installedpackages/snortglobal/rule/");
            $this->set_config("installedpackages/snortglobal/rule/{$this->id}", $this->validated_data);
            $this->write_config();
            return APIResponse\get(0, "Interface updated successfully");
        }
        return APIResponse\get(1, "No valid data provided or missing interface ID");
    }

    public function validate_payload() {

        if (!isset($this->initial_data["interface"])) {
            $this->errors[] = APIResponse\get(1, "Interface ID is required for update");
        } else {
            $this->validated_data["interface"] = $this->initial_data['interface'];
        }

        $this->__validate_interface();
        $this->__validate_descr();
        $this->__validate_enable();
        $this->__validate_snaplen();
        $this->__validate_alertsystemlog();
        $this->__validate_packetcapture();
        $this->__validate_unified2();
        $this->__validate_blockoffenders();
        $this->__validate_performancesettings();
    }

    private function __validate_interface() {
        if (isset($this->initial_data["interface"]) && is_string($this->initial_data["interface"])) {
            $this->validated_data["interface"] = $this->initial_data["interface"];
        } else {
            $this->errors[] = APIResponse\get(1, "Invalid or missing interface data");
        }
    }

    private function __validate_descr() {
        # Optionally allow client to specify a VLAN description. Default if not set.
        if (isset($this->initial_data['descr'])) {
            $this->validated_data["descr"] = $this->initial_data['descr'];
        } else {
            $this->validated_data["descr"] = "";
        }
    }

    private function __validate_enable() {
        # Optionally allow client to specify whether the interface is enabled. Default if set.
        if (!isset($this->initial_data["enable"])) {
            $this->validated_data["enable"] = "";
        }
    }

    private function __validate_snaplen() {
        # Optionally allow client to specify the snaplen. Default if not set.
        if (isset($this->initial_data["snaplen"])) {
            $this->validated_data["snaplen"] = $this->initial_data["snaplen"];
        } else {
            $this->validated_data["snaplen"] = "1518";
        }
    }

    private function __validate_alertsystemlog() {
        # Optionally allow client to specify whether alerts are sent to syslog. Default if not set.
        if (isset($this->initial_data['alertsystemlog'])) {

            $this->validated_data["alertsystemlog"] = $this->initial_data['alertsystemlog'];

            if ($this->initial_data['alertsystemlog_facility'] !== "LOG_AUTH") {
                $this->validated_data["alertsystemlog_limit"] = $this->initial_data['alertsystemlog_limit'];
            }

            if ($this->initial_data['alertsystemlog_facility'] !== "LOG_ALERT") {
                $this->validated_data["alertsystemlog_priority"] = $this->initial_data['alertsystemlog_facility'];
            }

        }

    }

    private function __validate_packetcapture() {
        # Optionally allow client to specify whether packet capture is enabled. Default if not set.
        if (isset($this->initial_data['enable_pkt_caps'])) {
            $this->validated_data["enable_pkt_caps"] = $this->initial_data['enable_pkt_caps'];
            if ($this->initial_data['tcpdump_file_size'] !== "128") {
                $this->validated_data["tcpdump_file_size"] = $this->initial_data['tcpdump_file_size'];
            }
        }
    }

    private function __validate_unified2() {
        # Optionally allow client to specify whether unified2 is enabled. Default if not set.
        if (isset($this->initial_data['unified2_logging_enable'])) {
            $this->validated_data["unified2_logging_enable"] = $this->initial_data['unified2_logging_enable'];
            $this->validated_data["unified2_log_vlan_events"] = $this->initial_data['unified2_log_vlan_events'];
            $this->validated_data["unified2_log_mpls_events"] = $this->initial_data['unified2_log_mpls_events'];
        }
    }

    private function __validate_blockoffenders() {
        # Optionally allow client to specify whether block offenders is enabled. Default if not set.
        if (isset($this->initial_data["blockoffenders7"])) {
            if ($this->initial_data["ips_mode"] !== "ips_mode_inline") {
                $this->validated_data["blockoffenderskill"] = $this->initial_data["blockoffenderskill"];
                $this->validated_data["blockoffendersip"] = $this->initial_data["blockoffendersip"];
            }
        }
    }

    private function __validate_performancesettings () {
        # Optionally allow client to specify detections settings.
        $this->validated_data["performance"] = $this->initial_data["performance"];
        $this->validated_data["fpm_split_any_any"] = $this->initial_data["fpm_split_any_any"];
        $this->validated_data["fpm_search_optimize"] = $this->initial_data["fpm_search_optimize"];
        $this->validated_data["fpm_no_stream_inserts"] = $this->initial_data["fpm_no_stream_inserts"];
        $this->validated_data["cksumcheck"] = $this->initial_data["cksumcheck"];
    }

}