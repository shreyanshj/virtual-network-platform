package virtual_network_manager_java;

public class ConfigTransaction {
	
	private Switch switchObj; 
	private int vni;
	private int operation;
	private int port_wait_count;
	private int n_ongoing_http_requests;
	private int n_failed_http_requests;
	private VnmCallback callback; 
	private UserData<?> user_data;

	
	public Switch getSwitchObj() {
		return switchObj;
	}
	public void setSwitchObj(Switch switchObj) {
		this.switchObj = switchObj;
	}
	public int getVni() {
		return vni;
	}
	public void setVni(int vni) {
		this.vni = vni;
	}
	public int getOperation() {
		return operation;
	}
	public void setOperation(int operation) {
		this.operation = operation;
	}
	public int getPort_wait_count() {
		return port_wait_count;
	}
	public void setPort_wait_count(int port_wait_count) {
		this.port_wait_count = port_wait_count;
	}
	public int getN_ongoing_http_requests() {
		return n_ongoing_http_requests;
	}
	public void setN_ongoing_http_requests(int n_ongoing_http_requests) {
		this.n_ongoing_http_requests = n_ongoing_http_requests;
	}
	public int getN_failed_http_requests() {
		return n_failed_http_requests;
	}
	public void setN_failed_http_requests(int n_failed_http_requests) {
		this.n_failed_http_requests = n_failed_http_requests;
	}
	public VnmCallback getCallback() {
		return callback;
	}
	public void setCallback(VnmCallback callback) {
		this.callback = callback;
	}
	public UserData<?> getUser_data() {
		return user_data;
	}
	public void setUser_data(UserData<?> user_data) {
		this.user_data = user_data;
	}
}
