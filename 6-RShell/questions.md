1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The remote client determines when a command's output is fully received through a null terminator in the EOF, the
techniques used to handle partial reads is through recv calls.

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

A networked shell protcol can definte and detect the beginning and end of a command sent over a TCP connection by
handling null terminators and EOF. Some challenges are infinite runtimes or commands aren't properly received.

3. Describe the general differences between stateful and stateless protocols.

The general differences are that stateful remember the state of the protocols while stateless does not store the state
of the protocol and is faster.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

It is used due to the applications for efficiency in speed in comparison to TCP.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The operating system provides sockets as an interface to enable applications to use network communications.
