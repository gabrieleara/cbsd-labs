.PHONY: all server client clean

CLASSPATH :=/usr/share/java/xmlrpc-client.jar:/usr/share/java/xmlrpc-server.jar:/usr/share/java/xmlrpc-common.jar:/usr/share/java/commons-logging.jar:/usr/share/java/ws-commons-util.jar

CFLAGS :=-Xlint

all: RPCServer.class RPCClient.class

clean:
	rm -f *.class RPCServer RPCClient

server: RPCServer.class
	java -cp $(CLASSPATH):. RPCServer

client: RPCClient.class
	java -cp $(CLASSPATH):. RPCClient

%.class: %.java
	javac -cp $(CLASSPATH) $(JCFLAGS) $<
