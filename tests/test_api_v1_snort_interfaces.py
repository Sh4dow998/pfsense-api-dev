
"""Script used to test the /api/v1/snort endpoint."""
import e2e_test_framework


class APIE2ETestSnortInterfaces(e2e_test_framework.APIE2ETest):
    """Class used to test the /api/v1/services/snort endpoint."""
    uri = "/api/v1/services/snort"

    get_privileges = ["page-all", "page-services-snort"]
    post_privileges = ["page-all", "page-services-snort"]
    put_privileges = ["page-all", "page-services-snort"]
    delete_privileges = ["page-all", "page-services-snort"]

    get_tests = [
        {"name": "Read all configured interfaces"}
    ]
    post_tests = [
        {
            "name": "Create Snort interface",
            "req_data": {
                "interface": "em0.102",
                "descr": "E2E Test",
                "enable": True,
                "snaplen": "1518"
            }
        }
    ]
    put_tests = [
        {
            "name": "Update Snort interface",
            "req_data": {
                "interface": "em0.102",
                "descr": "Updated E2E Test",
                "enable": False
            }
        }
    ]
    delete_tests = [
        {
            "name": "Delete Snort interface",
            "req_data": {
                "interface": "em0.102"
            }
        }
    ]

APIE2ETestSnortInterfaces()
