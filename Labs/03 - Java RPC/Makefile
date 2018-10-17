.PHONY: all server client clean

CLASSPATH :=/usr/share/java/xmlrpc-client.jar:/usr/share/java/xmlrpc-server.jar:/usr/share/java/xmlrpc-common.jar:/usr/share/java/commons-logging.jar:/usr/share/java/ws-commons-util.jar

CFLAGS :=-Xlint

all: RPCServer RPCClient

clean:
	rm *.class RPCServer RPCClient

server: RPCServer
	java -cp $(CLASSPATH):. RPCServer

client: RPCClient
	java -cp $(CLASSPATH):. RPCClient

%:	%.java
	javac -cp $(CLASSPATH) $(JCFLAGS) $<
