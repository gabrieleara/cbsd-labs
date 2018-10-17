import org.apache.xmlrpc.webserver.*;
import org.apache.xmlrpc.server.*;

public class RPCServer {
    public Integer sum(int x, int y) {
        return new Integer(x + y);
    }

    public static void main(String[] args) {

        try {
            System.out.println("Attempting to start XML-RPC Server...");

            // The webserver runs on 8080 port
            WebServer server = new WebServer(8080);

            // We define a new XML-RPC server
            XmlRpcServer xmlRpcServer = server.getXmlRpcServer();

            // The property handler mapping object is responsible to instantiate
            // objects for the classes that will expose RPC methods
            PropertyHandlerMapping phm = new PropertyHandlerMapping();
            phm.addHandler("sample", RPCServer.class);

            // We now set the handler on the server
            xmlRpcServer.setHandlerMapping(phm);

            // Start
            server.start();

            System.out.println("Started successfully.");

            // The program will continue running until forced termination
            System.out.println("Accepting requests. (Halt program to stop.)");

        } catch (Exception exception) {
            System.err.println("JavaServer: " + exception);
        }
    }
}
