<?php
require_once("api/framework/APIModel.inc");
require_once("api/framework/APIResponse.inc");

class APIServicesCaptivePortalCreate extends APIModel {

    public function __construct() {

        parent::__construct();
        $this->privileges = ["page-all", "page-services-captiveportal-edit"];
        $this->requires_auth = true;
    }

    public function action() {

        $this->validate_payload();

        if (!empty($this->validated_data)) {
            $zoneId = $this->get_next_id("captiveportal");
            $this->set_config("captiveportal/{$zoneId}", $this->validated_data);
            $this->write_config();
            return APIResponse\get(0, "Captive Portal configuration created successfully", $this->validated_data);
        }
        return APIResponse\get(1, "No valid data provided");
    }

    public function validate_payload() {
        $this->__validate_zone();
        $this->__validate_descr();
        //$this->__validate_localauth_priv();
        $this->__validate_interface();
        //$this->__validate_maxproc();
        //$this->__validate_timeout();
        //$this->__validate_idletimeout();
        //$this->__validate_trafficquota();
        //$this->__validate_freelogins_count();
        //$this->__validate_freelogins_resettimeout();
        $this->__validate_enable();
        $this->__validate_auth_method();
        /*$this->__validate_auth_server();
        $this->__validate_auth_server2();
        $this->__validate_radacct_server();
        $this->__validate_reauthenticateacct();
        $this->__validate_httpsname();
        $this->__validate_preauthurl();
        $this->__validate_blockedmacsurl();
        $this->__validate_peruserbw();
        $this->__validate_bwdefaultdn();
        $this->__validate_bwdefaultup();
        $this->__validate_certref();
        $this->__validate_redirurl();
        $this->__validate_radmac_format();*/
    }

    private function __validate_zone() {
        if (isset($this->initial_data['zone'])) {
            $this->validated_data['zone'] = $this->initial_data['zone'];
        } else {
            $this->errors[] = APIResponse\get(1, "Zone is required");
        }
    }

    private function __validate_descr() {
        if (isset($this->initial_data['descr'])) {
            $this->validated_data["descr"] = $this->initial_data['descr'];
        } else {
            $this->validated_data["descr"] = "";
        }
    }
/*
    private function __validate_localauth_priv() {
        # Validate our optional 'localauth_priv' payload value
        if (isset($this->initial_data['localauth_priv'])) {
            $this->validated_data["localauth_priv"] = strval($this->initial_data['localauth_priv']);
        } else {
            $this->validated_data["localauth_priv"] = "";
        }
    }*/

    private function __validate_interface() {
        if (isset($this->initial_data['interface'])) {
            $this->initial_data["interface"] = APITools\get_pfsense_if_id($this->initial_data["interface"], true);
            if (is_string($this->initial_data["interface"])) {
                $this->validated_data["interface"] = $this->initial_data["interface"];
            } else {
                $this->errors[] = APIResponse\get(4024);
            }
        } else {
            $this->errors[] = APIResponse\get(4020);
        }
    }
/*
    private function __validate_maxproc() {
        if (isset($this->initial_data['maxproc'])) {
            $this->validated_data["maxproc"] = intval($this->initial_data['maxproc']);
        } else {
            $this->validated_data["maxproc"] = "";
        }
    }

    private function __validate_timeout() {
        if (isset($this->initial_data['timeout'])) {
            $this->validated_data["timeout"] = intval($this->initial_data['timeout']);
        } else {
            $this->validated_data["timeout"] = "";
        }
    }

    private function __validate_idletimeout() {
        if (isset($this->initial_data['idletimeout'])) {
            $this->validated_data["idletimeout"] = intval($this->initial_data['idletimeout']);
        } else {
            $this->validated_data["idletimeout"] = "";
        }
    }

    private function __validate_trafficquota() {
        if (isset($this->initial_data['trafficquota'])) {
            $this->validated_data["trafficquota"] = intval($this->initial_data['trafficquota']);
        } else {
            $this->validated_data["trafficquota"] = "";
        }
    }

    private function __validate_freelogins_count() {
        if (isset($this->initial_data['freelogins_count'])) {
            $this->validated_data["freelogins_count"] = intval($this->initial_data['freelogins_count']);
        } else {
            $this->validated_data["freelogins_count"] = "";
        }
    }

    private function __validate_freelogins_resettimeout() {
        if (isset($this->initial_data['freelogins_resettimeout'])) {
            $this->validated_data["freelogins_resettimeout"] = intval($this->initial_data['freelogins_resettimeout']);
        } else {
            $this->validated_data["freelogins_resettimeout"] = "";
        }
    }
*/
    private function __validate_enable() {

        if ($this->initial_data["enable"] === true) {
            $this->validated_data["enable"] = "";
        }

    }


    private function __validate_auth_method() {
        if (isset($this->initial_data['auth_method'])) {
            $this->validated_data["auth_method"] = $this->initial_data['auth_method'];
        } else {
            $this->errors[] = APIResponse\get(1, "auth_method is required");
        }
    }
/*
    private function __validate_auth_server() {
        if (isset($this->initial_data['auth_server'])) {
            $this->validated_data["auth_server"] = strval($this->initial_data['auth_server']);
        } else {
            $this->validated_data["auth_server"] = "";
        }
    }

    private function __validate_auth_server2() {
        if (isset($this->initial_data['auth_server2'])) {
            $this->validated_data["auth_server2"] = strval($this->initial_data['auth_server2']);
        } else {
            $this->validated_data["auth_server2"] = "";
        }
    }

    private function __validate_radacct_server() {
        if (isset($this->initial_data['radacct_server'])) {
            $this->validated_data["radacct_server"] = strval($this->initial_data['radacct_server']);
        } else {
            $this->validated_data["radacct_server"] = "";
        }
    }

    private function __validate_reauthenticateacct() {
        if (isset($this->initial_data['reauthenticateacct'])) {
            $this->validated_data["reauthenticateacct"] = boolval($this->initial_data['reauthenticateacct']);
        } else {
            $this->validated_data["reauthenticateacct"] = "";
        }
    }

    private function __validate_httpsname() {
        if (isset($this->initial_data['httpsname'])) {
            $this->validated_data["httpsname"] = strval($this->initial_data['httpsname']);
        } else {
            $this->validated_data["httpsname"] = "";
        }
    }

    private function __validate_preauthurl() {
        if (isset($this->initial_data['preauthurl'])) {
            # Check if the preauthurl is a valid URL
            $url = $this->initial_data['preauthurl'];

            if (filter_var($url, FILTER_VALIDATE_URL) === FALSE) {
                $this->errors[] = APIResponse\get(1, "Invalid URL");
            } else {
                $this->validated_data["preauthurl"] = strval($this->initial_data['preauthurl']);
            }
        } else {
            $this->validated_data["preauthurl"] = "";
        }
    }

    private function __validate_blockedmacsurl() {
        if (isset($this->initial_data['blockedmacsurl'])) {
            # Check if the blockedmacsurl is a valid URL
            $url = $this->initial_data['blockedmacsurl'];

            if (filter_var($url, FILTER_VALIDATE_URL) === FALSE) {
                $this->errors[] = APIResponse\get(1, "Invalid URL");
            } else {
                $this->validated_data["blockedmacsurl"] = strval($this->initial_data['blockedmacsurl']);
            }
        } else {
            $this->validated_data["blockedmacsurl"] = "";
        }
    }

    private function __validate_peruserbw() {
        if (isset($this->initial_data['peruserbw'])) {
            $this->validated_data["peruserbw"] = boolval($this->initial_data['peruserbw']);
        } else {
            $this->validated_data["peruserbw"] = "";
        }
    }

    private function __validate_bwdefaultdn() {
        # Check if bandwidth restrictions is enabled
        if (isset($this->initial_data['peruserbw']) && $this->initial_data['peruserbw'] == true) {

            $this->__validate_bwdefaultdn();

            if (isset($this->initial_data['bwdefaultdn'])) {
                # Check if the bwdefaultdn is > 0 and < bwdefaultup
                if (isset($this->initial_data['bwdefaultup'])) {
                    if ($this->initial_data['bwdefaultdn'] > 0 && $this->initial_data['bwdefaultdn'] < $this->initial_data['bwdefaultup']) {
                        $this->validated_data["bwdefaultdn"] = intval($this->initial_data['bwdefaultdn']);
                    } else {
                        $this->errors[] = APIResponse\get(1, "Invalid bwdefaultdn value");
                    }
                } else {
                    $this->errors[] = APIResponse\get(1, "bwdefaultup is required");
                }
            }
        } else {
            $this->validated_data["bwdefaultdn"] = "";
        }
    }

    private function __validate_bwdefaultup() {

        if (isset($this->initial_data['peruserbw']) && $this->initial_data['peruserbw'] == true) {

            $this->__validate_bwdefaultup();

            if (isset($this->initial_data['bwdefaultup'])) {
                # Check if the bwdefaultup is bigger than bwdfaultdn and > 0
                if (isset($this->initial_data['bwdefaultdn'])) {
                    if ($this->initial_data['bwdefaultup'] > $this->initial_data['bwdefaultdn'] && $this->initial_data['bwdefaultup'] > 0) {
                        $this->validated_data["bwdefaultup"] = intval($this->initial_data['bwdefaultup']);
                    } else {
                        $this->errors[] = APIResponse\get(1, "Invalid bwdefaultup value");
                    }
                } else {
                    $this->errors[] = APIResponse\get(1, "bwdefaultdn is required");

                }
            }
        } else {
            $this->validated_data["bwdefaultup"] = "";
        }
    }

    private function __validate_certref() {
        if (isset($this->initial_data['certref'])) {
            $this->validated_data["certref"] = strval($this->initial_data['certref']);
        } else {
            $this->validated_data["certref"] = "";
        }
    }

    private function __validate_redirurl() {
        if (isset($this->initial_data['redirurl'])) {
            # Check if the redirurl is a valid URL
            $url = $this->initial_data['redirurl'];

            if (filter_var($url, FILTER_VALIDATE_URL) === FALSE) {
                $this->errors[] = APIResponse\get(1, "Invalid URL");
            } else {
                $this->validated_data["redirurl"] = strval($this->initial_data['redirurl']);
            }

        } else {
            $this->validated_data["redirurl"] = "";
        }
    }

    private function __validate_radmac_format() {
        if (isset($this->initial_data['radmac_format']) && ($this->initial_data['auth_method'] == "radius")) {
            # Check if the radmac_format is a valid MAC address format
            $mac = $this->initial_data['radmac_format'];

            if (filter_var($mac, FILTER_VALIDATE_MAC) === FALSE) {
                $this->errors[] = APIResponse\get(1, "Invalid MAC address format");
            } else {
                $this->validated_data["radmac_format"] = strval($this->initial_data['radmac_format']);
            }
        } else {
            if ($this->initial_data['auth_method'] == "radius") {
                $this->errors[] = APIResponse\get(1, "radmac_format is required");
            } else {
                $this->validated_data["radmac_format"] = "";
            }
        }
    }

    /*
    private function __validate_radiusnasid() {
        if (isset($this->initial_data['radiusnasid'])) {
            $this->validated_data["radiusnasid"] = strval($this->initial_data['radiusnasid']);
        } else {
            $this->validated_data["radiusnasid"] = "";
        }
    }

    private function __validate_customhtml() {
        if (isset($this->initial_data['customhtml'])) {
            $this->validated_data["customhtml"] = strval($this->initial_data['customhtml']);
        } else {
            $this->validated_data["customhtml"] = "";
        }
    }

    private function __validate_termsconditions() {
        if (isset($this->initial_data['termsconditions'])) {
            $this->validated_data["termsconditions"] = strval($this->initial_data['termsconditions']);
        } else {
            $this->validated_data["termsconditions"] = "";
        }
    }
    */

}