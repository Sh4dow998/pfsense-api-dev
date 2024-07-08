<?php

require_once("api/framework/APIModel.inc");
require_once("api/framework/APIResponse.inc");

class APIServicesCaptivePortalRead extends APIModel {

    public function __construct() {
        parent::__construct();
        $this->privileges = ["page-all", "page-services-captiveportal-read"];
        $this->requires_auth = true;
    }

    public function action() {

        $config = $this->get_config("captiveportal");
        if ($config) {
            $portalData = [];
            foreach ($config as $zoneKey => $zoneData) {
                $portalData[$zoneKey] = [
                    'zone' => $zoneData['zone'],
                    'descr' => $zoneData['descr'],
                    'localauth_priv' => $zoneData['localauth_priv'],
                    'zoneid' => $zoneData['zoneid'],
                    'interface' => $zoneData['interface'],
                    'maxproc' => $zoneData['maxproc'],
                    'timeout' => $zoneData['timeout'],
                    'idletimeout' => $zoneData['idletimeout'],
                    'trafficquota' => $zoneData['trafficquota'],
                    'freelogins_count' => $zoneData['freelogins_count'],
                    'freelogins_resettimeout' => $zoneData['freelogins_resettimeout'],
                    'enable' => $zoneData['enable'],
                    'auth_method' => $zoneData['auth_method'],
                    'auth_server' => $zoneData['auth_server'],
                    'auth_server2' => $zoneData['auth_server2'],
                    'radacct_server' => $zoneData['radacct_server'],
                    'reauthenticateacct' => $zoneData['reauthenticateacct'],
                    'httpsname' => $zoneData['httpsname'],
                    'preauthurl' => $zoneData['preauthurl'],
                    'blockedmacsurl' => $zoneData['blockedmacsurl'],
                    'peruserbw' => $zoneData['peruserbw'],
                    'bwdefaultdn' => $zoneData['bwdefaultdn'],
                    'bwdefaultup' => $zoneData['bwdefaultup'],
                    'certref' => $zoneData['certref'],
                    'redirurl' => $zoneData['redirurl'],
                    'radmac_format' => $zoneData['radmac_format'],
                    'radiusnasid' => $zoneData['radiusnasid'],
                    'customhtml' => $zoneData['customhtml'],
                    'termsconditions' => $zoneData['termsconditions'],
                    'page' => $zoneData['page']
                ];
            }
            return APIResponse\get(0, $portalData);
        }
        return APIResponse\get(1, "Failed to retrieve captive portal configuration");
    }
}