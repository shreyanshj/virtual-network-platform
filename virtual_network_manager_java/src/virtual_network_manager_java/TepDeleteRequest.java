package virtual_network_manager_java;

import org.apache.http.client.methods.*;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClientBuilder;

public class TepDeleteRequest extends JsonRequest{

	@Override
	public boolean send(String agentUri) {
		// TODO Auto-generated method stub
		CloseableHttpClient httpClient = HttpClientBuilder.create().build();
		HttpTransactionComplete responseHandler = new HttpTransactionComplete();
		responseHandler.setUsrData(usrData);
		this.responseHandler = responseHandler;
		try {
			HttpDelete request = new HttpDelete(agentUri);
			if(this.responseHandler != null) {
		    	httpClient.execute(request, this.responseHandler);
		    }
		    else {
		    	httpClient.execute(request);
		    	throw new Exception("Response handler is not set for HTTP request");
		    }
		}
		catch(Exception ex) {
		
			return false;
		}
		return true;
	}

}
