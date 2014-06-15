package virtual_network_manager_java;

public class Transaction {
	Switch switchObj;
	int vni;
	int operation;
	int port_wait_count;
	int n_ongoing_http_requests;
	int n_failed_http_requests;
	  /* overlay_operation_completed_handler callback; */
	UserData user_data;
}
