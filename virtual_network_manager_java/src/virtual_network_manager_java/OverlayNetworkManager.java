package virtual_network_manager_java;

import java.util.HashMap;

public class OverlayNetworkManager {

	private HashMap<ConfigTransaction, ConfigTransaction> transactions;
	
	public OverlayNetworkManager() {
		transactions = new HashMap<ConfigTransaction, ConfigTransaction>();
		
	}
	
	/* Check for transaction in transactions with specified details 
	 * If available send the transaction else return null */ 
	public ConfigTransaction lookup_transaction(Switch switchObj, Slice slice) {
		ConfigTransaction configTransaction = null;
		return configTransaction; 
	}
	
	
}
