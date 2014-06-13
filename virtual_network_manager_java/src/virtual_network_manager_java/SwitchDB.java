package virtual_network_manager_java;

public class SwitchDB{

	/* DB to be used for storeing info */
	/* Mysql db*/
	
	
	/* Constructor of the Switch Class */
	public SwitchDB( /*Mysql db*/){
		
	}
	
	/* Add switch in DB */
	public void addSwitch(Switch switchObj) {
		
		
	}
	
	/* Delete switch from DB by switch*/
	public void deleteSwitch(Switch switchObj) {
		
		
	}
	
	/* Delete all switch from DB of a specific controller */
	public int deleteSwitchByController(Controller controller) {
		int no = 0;
		
		return no;
	}
	
	/* Check on-duty switch by checking switch entry in DB */
	public boolean switchOnDuty(Switch switchObj) {
		
		return true;
	}
	
	/* Add port to switch in DB <name is within the port> */
	public void addPort(Switch switchObj, Port portObj) {
		
		
	}
	
	/* Delete port from switch in DB <name is within the port> */
	public void deletePort(Switch switchObj, Port portObj) {
		
		
	}
	
	/* Get a port object by port name from DB */
	public Port getPortByName(Switch switchObj, String portName) {
		Port port = null;
		
		return port;
	}
		
}
