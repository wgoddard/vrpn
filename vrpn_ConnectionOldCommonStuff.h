////////////////////////////////////////////////////////
//
// first, a bunch of stuff that needs to be defined here
// if nested classes worked right on pixelflow aCC, then
// this could probably be cleaned up some
//

#ifndef VRPN_CONNECTIONOLDCOMMONSTUFF_H
#define VRPN_CONNECTIONOLDCOMMONSTUFF_H


class vrpn_File_Connection;  // for get_File_Connection()

// NOTE: most users will want to use the vrpn_Synchronized_Connection
// class rather than the default connection class (either will work,
// a regular connection just has 0 as the client-server time offset)

struct vrpn_HANDLERPARAM {
	vrpn_int32	type;
	vrpn_int32	sender;
	struct timeval	msg_time;
	vrpn_int32	payload_len;
	const char	*buffer;
};
typedef	int  (*vrpn_MESSAGEHANDLER)(void *userdata, vrpn_HANDLERPARAM p);

typedef int (* vrpn_LOGFILTER) (void * userdata, vrpn_HANDLERPARAM p);

// bufs are aligned on 8 byte boundaries
#define vrpn_ALIGN                       (8)

// Types now have their storage dynamically allocated, so we can afford
// to have large tables.  We need at least 150-200 for the microscope
// project as of Jan 98, and will eventually need two to three times that
// number.
#define	vrpn_CONNECTION_MAX_SENDERS	(2000)
#define	vrpn_CONNECTION_MAX_TYPES	(2000)

// vrpn_ANY_SENDER can be used to register callbacks on a given message
// type from any sender.

#define	vrpn_ANY_SENDER	(-1)

// vrpn_ANY_TYPE can be used to register callbacks for any USER type of
// message from a given sender.  System messages are handled separately.

#define vrpn_ANY_TYPE (-1)

// Buffer lengths for TCP and UDP.
// TCP is an arbitrary number that can be changed by the user
// using vrpn_Connection::set_tcp_outbuf_size().
// UDP is set based on Ethernet maximum transmission size;  trying
// to send a message via UDP which is longer than the MTU of any
// intervening physical network may cause untraceable failures,
// so for now we do not expose any way to change the UDP output
// buffer size.  (MTU = 1500 bytes, - 28 bytes of IP+UDP header)

#define	vrpn_CONNECTION_TCP_BUFLEN	(64000)
#define	vrpn_CONNECTION_UDP_BUFLEN	(1472)

// System message types

#define	vrpn_CONNECTION_SENDER_DESCRIPTION	(-1)
#define	vrpn_CONNECTION_TYPE_DESCRIPTION	(-2)
#define	vrpn_CONNECTION_UDP_DESCRIPTION		(-3)
#define	vrpn_CONNECTION_LOG_DESCRIPTION		(-4)

// Classes of service for messages, specify multiple by ORing them together
// Priority of satisfying these should go from the top down (RELIABLE will
// override all others).
// Most of these flags may be ignored, but RELIABLE is guaranteed
// to be available.

#define	vrpn_CONNECTION_RELIABLE		(1<<0)
#define	vrpn_CONNECTION_FIXED_LATENCY		(1<<1)
#define	vrpn_CONNECTION_LOW_LATENCY		(1<<2)
#define	vrpn_CONNECTION_FIXED_THROUGHPUT	(1<<3)
#define	vrpn_CONNECTION_HIGH_THROUGHPUT		(1<<4)

// What to log
#define vrpn_LOG_NONE				(0)
#define vrpn_LOG_INCOMING			(1<<0)
#define vrpn_LOG_OUTGOING			(1<<1)


#if !defined(_WIN32) || defined (__CYGWIN__)
#define SOCKET int
#endif


// Default port to listen on for a server
#define vrpn_DEFAULT_LISTEN_PORT_NO             (4500)

// If defined, will filter out messages:  if the remote side hasn't
// registered a type, messages of that type won't be sent over the
// link.
//#define vrpn_FILTER_MESSAGES

#define vrpn_got_first_connection "VRPN Connection Got First Connection"
#define vrpn_got_connection "VRPN Connection Got Connection"
#define vrpn_dropped_connection "VRPN Connection Dropped Connection"
#define vrpn_dropped_last_connection "VRPN Connection Dropped Last Connection"

// vrpn_CONTROL is used for notification messages sent to the user
// from the local VRPN implementation (got_first_connection, etc.)
// and for control messages sent by auxiliary services.  (Such as
// class vrpn_Controller, which will be introduced in a future revision.)

#define vrpn_CONTROL "VRPN Control"

typedef char cName [100];

// Placed here so vrpn_FileConnection can use it too.
struct vrpn_LOGLIST {
  vrpn_HANDLERPARAM data;
  vrpn_LOGLIST * next;
  vrpn_LOGLIST * prev;
};

// HACK
// These structs must be declared outside of vrpn_Connection
// (although we'd like to make them protected/private members)
// because aCC on PixelFlow doesn't handle nested classes correctly.

// Description of a callback entry for a user type.
struct vrpnMsgCallbackEntry {
  vrpn_MESSAGEHANDLER	handler;	// Routine to call
  void			* userdata;	// Passed along
  vrpn_int32		sender;		// Only if from sender
  vrpnMsgCallbackEntry	* next;		// Next handler
};

struct vrpnLogFilterEntry {
  vrpn_LOGFILTER filter;   // routine to call
  void * userdata;         // passed along
  vrpnLogFilterEntry * next;
};


#endif