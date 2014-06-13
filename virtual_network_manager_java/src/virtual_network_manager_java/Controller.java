package virtual_network_manager_java;

public class Controller {
	/* Controller host-name */
	private String controllerHost;
	
	/* Controller pid */
	private int controllerPid;
	
	public String getControllerHost() {
		return controllerHost;
	}

	public void setControllerHost(String controllerHost) {
		this.controllerHost = controllerHost;
	}

	public int getControllerPid() {
		return controllerPid;
	}

	public void setControllerPid(int controllerPid) {
		this.controllerPid = controllerPid;
	}
}
