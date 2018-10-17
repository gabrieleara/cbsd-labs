import org.apache.xmlrpc.client.*;
import java.util.*;
import java.net.URL;

public class RPCClient {
    public static void main(String[] args) {
        try {
            // Simple implementation of a XML-RPC client configuration
            XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();

            // The server runs on localhost using 8080 port
            config.setServerURL(new URL("http://localhost:8080/RPC2"));

            // We instantiate the new client and set its configuration
            XmlRpcClient client = new XmlRpcClient();
            client.setConfig(config);

            // The parameters are stored in a vector
            Vector<Object> params = new Vector<>();

            // We add parameters to the vector
            params.addElement(new Integer(17));
            params.addElement(new Integer(13));

            // Which object and which method to execute, padding a vector of
            // params
            Object result = client.execute("sample.sum", params);

            // After obtaining the result as object we upcast it to an integer
            int sum = ((Integer) result).intValue();

            System.out.println("The sum is: " + sum);
        } catch (Exception exception) {
            System.err.println("JavaClient: " + exception);
        }
    }
}
