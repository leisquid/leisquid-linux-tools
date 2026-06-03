CC=gcc
CFLAGS=-Wall `pkg-config --cflags gtk+-3.0 polkit-gobject-1`
LDFLAGS=`pkg-config --libs gtk+-3.0 polkit-gobject-1`

all: server client

server: server.c
	$(CC) $(CFLAGS) $^ -o sample-service $(LDFLAGS)

client: client.c
	$(CC) $(CFLAGS) $^ -o sample-client $(LDFLAGS)

install:
	cp sample-service /usr/local/bin/
	cp sample-client /usr/local/bin/
	cp com.example.Sample.conf /etc/dbus-1/system.d/
	cp com.example.Sample.service /usr/share/dbus-1/system-services/
	cp com.example.Sample.policy /usr/share/polkit-1/actions/
	dbus-send --system --type=method_call --print-reply \
	  --dest=org.freedesktop.DBus / org.freedesktop.DBus.ReloadConfig

clean:
	rm -f sample-service sample-client

remove:
	rm /etc/dbus-1/system.d/com.example.Sample.conf /usr/share/dbus-1/system-services/com.example.Sample.service /usr/share/polkit-1/actions/com.example.Sample.policy /usr/local/bin/sample-*
