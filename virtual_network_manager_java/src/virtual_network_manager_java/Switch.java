package virtual_network_manager_java;

/*import java.util.HashMap;*/

public class Switch {
	/* Unique Data-path Id for all switch */ 
	private int dataPathId;
	
	private Controller controller;
	
	/* Ports attached/configured in the Switch 
	 * Map of ports by Port Name as Key and Port Object 
	 * 
	 * <Tentative> as db will be storing the data 
	 * private HashMap<String, Port> ports; */
	
	public Switch(int dataPathId){
		this.setDataPathId(dataPathId);
	}

	public int getDataPathId() {
		return dataPathId;
	}

	public void setDataPathId(int dataPathId) {
		this.dataPathId = dataPathId;
	}

	public Controller getController() {
		return controller;
	}

	public void setController(Controller controller) {
		this.controller = controller;
	}

	/* <tentative> 
	public Port getPorts(String portName) {
		Port portObj = null;
		return portObj;
	}

	public void setPorts(Port portObj) {
		
	}
	*/
	
}
