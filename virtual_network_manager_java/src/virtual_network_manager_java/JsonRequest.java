package virtual_network_manager_java;

import org.json.JSONObject;
import org.apache.http.client.ResponseHandler;

public abstract class JsonRequest {

	protected JSONObject jsonObj;
	protected String jsonString;
	protected ResponseHandler<String> responseHandler;
	protected UserData<?> usrData;
	
	public JsonRequest(){
		jsonObj = new JSONObject();
		jsonString  = null;
		responseHandler = null;
		usrData = null;
	}
	
	/* set response handler which will be invoked while a HTTP response message is received */
	public void setResponseHandler(ResponseHandler<String> responseHandler){
		this.responseHandler = responseHandler;
	}
	
	/* send the JSON request in the specified agent URI */ 
	public abstract boolean send(String agentUri);
	
}
