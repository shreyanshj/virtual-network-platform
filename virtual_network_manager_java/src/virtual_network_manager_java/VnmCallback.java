package virtual_network_manager_java;

/* Define callback in VNM
 * VnmCallback need to be implemented for any user define callback */
public interface VnmCallback {

	/* Body of the user defined callback which will be called 
	 * Need to be implemented by the user  
	 */
	public abstract boolean body(UserData<?> usrdata);
	
}
