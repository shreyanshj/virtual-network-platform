package virtual_network_manager_java;

import java.io.IOException;

import org.json.JSONException;
import org.json.JSONObject;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClientBuilder;

public class JsonRequest {

	private JSONObject jsonObj;
	private String jsonString;
	private ResponseHandler<String> responseHandler;
	
	private JsonRequest(){
		jsonObj = new JSONObject();
		jsonString  = null;
		responseHandler = null;
	}
	
	public static JsonRequest getTepAddRequest(String address, Port port){
		JsonRequest request = new JsonRequest();
		try {
			/* Add IP address */
			request.jsonObj.accumulate("ip", address);
			request.jsonObj.accumulate("port", port.getName());
			request.jsonString = request.jsonObj.toString();
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return request;
	}
	
	public static JsonRequest getTunnelAddRequest(int vnetId, String address){
		JsonRequest request = new JsonRequest();
		try {
			/* Add IP address */
			request.jsonObj.accumulate("vni", vnetId);
			request.jsonObj.accumulate("broadcast", address);
			request.jsonString = request.jsonObj.toString();
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return request;
	}
	
	/* set response handler which will be invoked while a HTTP response message is received */
	public void setResponseHandler(ResponseHandler<String> responseHandler){
		this.responseHandler = responseHandler;
	}
	
	/* send the JSON request in the specified agent URI */ 
	public boolean send(String agentUri){
		CloseableHttpClient httpClient = HttpClientBuilder.create().build();
		try {
		    HttpPost request = new HttpPost(agentUri);
		    StringEntity params = new StringEntity(jsonString);
		    request.addHeader("content-type", "application/x-www-form-urlencoded");
		    request.setEntity(params);
		    if(responseHandler != null) {
		    	httpClient.execute(request, responseHandler);
		    }
		    else {
		    	httpClient.execute(request);
		    	throw new Exception("Response handler is not set for HTTP request");
		    }
		} catch (Exception ex) {
		    // handle exception here
			return false;
		} finally {
		    try {
				httpClient.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return true;
	}
}
